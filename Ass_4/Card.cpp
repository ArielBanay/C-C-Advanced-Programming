//b"h

#include "Card.h"
//private's:

/**
 * Card value calculation.
 * Assigns a numerical value to the card based on its rank:
 * K: 20, Q: 15, J/T: 10, A: 1, and '2'-'9': their face value.
 * @return The integer value of the card.
 */
int Card:: calc_val() const {
    if (rank=='K') {return 20;}
    if (rank=='Q') {return 15;}
    if (rank=='J' || rank=='T') {return 10;}
    if (rank>='2' && rank<='9'){return rank-'0';}
    if (rank=='A') {return 1;}
    return 0;
}

//public's
Card::Card():rank('Z'),sign('Z'),value(0){}

Card::Card(char rank, char sign): rank(rank) , sign(sign) {
    //helper method to calculate card value
    this->value=calc_val();
}

Card::Card(const char* RS ): Card(RS[0],RS[1])  {}

Card::Card(const Card &card):rank(card.rank),sign(card.sign),value(card.value){}

Card::~Card() {}

Card& Card::operator=(const Card &other) {
    //data members are primitive, therefore there is no need to deepcopy and checking about self assignment.
    this->rank=other.rank;
    this->sign=other.sign;
    this->value=other.value;
    return *this;
}

//6 comparison signs
bool Card::operator==(const Card &other) const {
    //equal
    if (this->rank==other.rank && this->sign==other.sign) {return true;}
    return false;
}

bool Card::operator!=(const Card &other) const {
    return !(*this==other);
}

bool Card::operator>(const Card &other) const {
    //equals
    if (*this==other){return false;}

    //equal ranks, different sign
    if (this->rank == other.rank) {
        if (this->sign=='C' && other.sign!='C') {
            return true;
        }
        if (this->sign=='S' && (other.sign=='H' || other.sign=='D')) {
            return true;
        }
        if (this->sign=='H' && other.sign=='D') {
            return true;
        }
        //equal ranks and no positive decision was reached using the signs.
        return false;
    }

    //different ranks, use the value to determine
    if (this->value > other.value) { return true; }

    //special case
    //this== 'J' | 'T' , other == 'J' | 'T'
    if (this->value == 10 && other.value == 10 ) {
        // J is bigger than T
        if (this->rank=='J' && other.rank=='T') { return true;}

        // all other possible option is false (equal or this < other)
        return false;
    }
    //In none of the cases has it been proven that this>other
    return false;
}

bool Card::operator>=(const Card &other) const {
    return *this==other || *this>other;
}

bool Card::operator<(const Card &other) const{
    return other > *this;
}

bool Card::operator<=(const Card &other) const {
    return other >= *this;
}

ostream& operator<<(ostream &os, const Card &card) {
    cout<<card.rank<<card.sign;
    return os;
}





