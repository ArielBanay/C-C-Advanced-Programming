#!/bin/bash

parameters=($@)
len_p=${#parameters[@]} 
err="false"


if [ $len_p -le 1 ]; then
	echo "Number of parameters received : $len_p" >&2
	err="true"

elif [[ ! ${parameters[$((len_p-1))]} =~ ^[0-9]+(\.[0-9]+)?$ ]]; then
	echo "Not a valid number : ${parameters[$((len_p-1))]}" >&2
	err="true"
elif (( $(echo "${parameters[$((len_p-1))]} == 0" | bc -l) )); then
	echo "Not a valid number : ${parameters[$((len_p-1))]}" >&2
	err="true"
else
	dir_lst=("${parameters[@]:0:$((len_p-1))}")

	#check for each element if it is a legale directory.
	for elem in "${dir_lst[@]}"; do

		if [[ ! -f "$elem" ]]; then
			echo "File does not exist: $elem" >&2
			err="true"
		fi
	done
fi

if [[ $err == "true" ]]; then
	echo "Usage : calculatePayment.sh <valid_file_name> [More_Files] ... <money>"

else

total_price=0

for valid_file in "${dir_lst[@]}"; do
	while read -r price; do
		if [[ $price =~ ^\.[0-9]+$ ]]; then
			price="0$price"
		fi
		if [[ -n $price ]]; then
			total_price=$(echo "$price + $total_price" | bc -l)
		fi
	done < <(grep -oE '([0-9]*\.[0-9]+|[0-9]+)' "$valid_file")
done


total_price_rounded=$(printf "%.2f" $total_price)
echo "Total purchase price: $total_price_rounded"
customer_paid=${parameters[$((len_p-1))]}

#calc the delta between original total price Vs. amount customer paid and round it.
delta=$(echo "$customer_paid-$total_price" | bc -l)
delta_rounded=$(printf "%.2f" $delta)

if (( $(echo "$delta_rounded > 0" | bc -l) )); then
	echo "Your change is $delta_rounded shekel"
elif (( $(echo "$delta_rounded < 0" | bc -l) )); then
	more2pay=$(echo "$delta_rounded * -1" | bc -l)
	#fix the issue of the digit after decimal point that bc produced
	more2pay=$(printf "%.2f" $more2pay)
	echo "You need to add $more2pay shekel to pay the bill"

else echo "Exact payment"
fi
fi #for the outer if statement.