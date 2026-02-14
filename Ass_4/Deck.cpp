//b"h

#include "Deck.h"


//private's:
int Deck::cnt_deck=0;

//public's
Deck::Deck() :size(0), array(nullptr) {
    cnt_deck++;
}

Deck::Deck(const Deck &other): array(nullptr) {
    //allocate memory for new with same size.
    array = new Card*[other.size];

    // deep copy of each card from other
    for (int i=0; i<other.size; i++) {
        array[i]=new Card(*other.array[i]);
    }

    //updates
    this->size=other.size;
    cnt_deck++;
}

Deck::~Deck() {
    for (int i=0; i<this->size; i++) {
        delete array[i];
    }
    delete[] array;
    cnt_deck--;
}

Deck& Deck::operator=(const Deck &other) {
    //same instance of Deck, nothing to do.
    if (this==&other){return *this;}

    //deep copy of each card from other to temp array
    Card** temp=new Card*[other.size];
    for (int i=0; i<other.size; i++) {
        temp[i]=new Card(*other.array[i]);
    }

    //free all old data
    for (int i=0; i<size; i++) {
        delete array[i];
    }
    delete[] array;

    //update new data
    this->array=temp;
    this->size=other.size;

    return *this;
}

Deck& Deck::operator+=(const Card &other) {
    //creating new array with the appropriate size
    Card** temp_array = new Card*[size+1];

    //deep copy of other & add it to idx 0
    temp_array[0] = new Card(other);

    //copy all the Cards from the original deck to the new one
    for (int i=0;i<this->size;i++) {
        temp_array[i+1]=this->array[i];
    }
    //deallocate memory for the original Card pointers array
    delete [] this->array;
    this->array=temp_array;
    this->size++;
    return *this;
}

Deck& Deck::operator-=(int n){
    //illegal input, the deck doesn't change
    if (n<0) {
        cout<<"Invalid number\n";
        return *this;
    }

    if (n==0){return *this;}

    if (n<size) {
        //Initialize a new array of the appropriate size
        Card** temp = new Card*[size-n];
        for (int i=0; i<size-n; i++) {
            temp[i]=array[i];
        }
        //free all the cards from top deck & old array
        for (int i=size-n; i<size; i++) {
            delete array[i];
        }
        delete[] array;

        //Member data update
        array=temp;
        size=size-n;
        return *this;
    }

    //n>=size
    for (int i=0; i<size; i++) {
        delete array[i];
    }
    delete[] array;
    this->array=nullptr;
    this->size=0;
    return *this;
}

void Deck::peek(int n) const {
    if (n<0) {
        cout<<"Invalid number\n";
        return;
    }
    //Support the option where the user wants to see more cards than are in the deck.
    if (n>size) {n=size;}
    //Iteratively traverses the elements from the end of the array and prints them.
    for (int i=size-1; i>size-n-1; i--) {
        cout<<*array[i]<<"\n";
    }
}

Card& Deck::operator[](int idx) {
    //assume 0<=idx<=size-1 according to the ass instruction
    return *array[idx];
}

const Card& Deck::operator[](int idx) const {
    //assume 0<=idx<=size-1 according to the ass instruction
    return *array[idx];
}

ostream& operator<<(ostream &os, const Deck &deck) {
    //empty deck
    if (deck.size==0) {cout<<"[]\n";return os;}

    cout<<"[";
    for (int i=0; i<deck.size; i++) {
        cout<<*deck.array[i];
        if (i<deck.size-1) {cout<<",";}
    }
    cout<<"]\n";
    return os;
}
