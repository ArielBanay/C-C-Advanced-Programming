//b"h

#include "Card.h"
#include "Deck.h"
#include <iostream>
#include <cstring>
using namespace std;

/**
 * Design Assumptions for case handlers (2-8):
 * According to the assignment requirements, functions handling deck operations (cases 2-8)
 * are only invoked if a Deck instance has been successfully initialized.
 * To ensure efficiency and avoid redundant logic, internal null-pointer checks
 * for 'deckptr' are omitted within these functions. The caller is responsible
 * for ensuring that 'deckptr' is valid and non-null before invocation.
 */


/**
 * Deck initialization handler.
 * Checks if a Deck instance already exists using the static counter.
 * If no deck exists, it allocates a new Deck; otherwise, it prevents
 * multiple instantiations and notifies the user.
 * @param deckptr A reference to a pointer that will hold the new Deck address.
 * @return None.
 */
void case1(Deck*& deckptr) {
    if (Deck::get_cnt_deck()==0) {
        deckptr = new Deck();
    }
    else {
        cout<<"Deck already exists\n";
    }
}

/**
 * Card comparison handler.
 * Reads two card representations and a comparison operator from the input.
 * Constructs temporary Card objects and performs the requested logical
 * comparison using overloaded operators, printing the boolean result.
 * @return None.
 */
void case2() {
    char first[3];
    char second[3];
    char eq[3];
    bool res=false;
    cin>>first;
    cin>>second;
    cin>>eq;
    Card f_card(first);
    Card s_card(second);
    if (strcmp(eq,"==")==0) {
        res = f_card==s_card;
    } else if (strcmp(eq,"!=")==0) {
        res = f_card!=s_card;
    } else if (strcmp(eq,">")==0) {
        res = f_card>s_card;
    } else if (strcmp(eq,"<")==0) {
        res = f_card<s_card;
    } else if (strcmp(eq,">=")==0) {
        res = f_card>=s_card;
    } else if (strcmp(eq,"<=")==0) {
        res = f_card<=s_card;
    }
    cout<<(res ? "True" : "False")<<"\n";
}

/**
 * Card insertion handler.
 * Reads a specified number of cards from input and prepends them to the deck.
 * It stores card representations in a temporary buffer and adding them to the deck using the += operator.
 * @param deckptr A reference to the pointer of the deck where cards will be added.
 * @return None.
 */
void case3(Deck*& deckptr) {
    int num;
    char c[3];
    cin>>num;
    //invalid input
    if (num<0) {
        cout<<"Invalid number\n";
        return;
    }
    char* temp = new char[2*num];
    for (int i=0; i<2*num; i=i+2) {
        cin>>c;
        temp[i]=c[0];
        temp[i+1]=c[1];
    }
    for (int j=0; j<2*num; j=j+2) {
        *deckptr += Card(temp[j],temp[j+1]);
    }

    delete[] temp;
}

/**
 * Card removal handler.
 * Reads the number of cards to be removed from the input and updates the deck
 * by calling the subtraction assignment operator. Handles negative input
 * by displaying an error message.
 * @param deckptr A reference to the pointer of the deck to be modified.
 * @return None.
 */
void case4(Deck*& deckptr) {
    int num;
    cin>>num;
    //invalid input
    if (num<0) {
        cout<<"Invalid number\n";
        return;
    }
    *deckptr-=(num);
}

/**
 * Peek.
 * Reads the number of cards to view from the input and calls the deck's
 * peek method to display them from the top-down. Includes validation
 * for negative input values.
 * @param deckptr A pointer to the constant deck to be inspected.
 * @return None.
 */
void case5(const Deck* deckptr) {
    int num;
    cin>>num;
    if (num<0) {
        cout<<"Invalid number\n";
        return;
    }
    deckptr->peek(num);
}

/**
 * Individual card access handler.
 * Reads an index from the input and displays the card at that specific
 * position in the deck. Includes boundary checking to ensure the index
 * is within the valid range of the current deck size.
 * @param deckptr A pointer to the constant deck to be accessed.
 * @return None.
 */
void case6(const Deck* deckptr) {
    int idx;
    cin>>idx;
    if (idx<0 || idx>=deckptr->getSize()) {
        cout<<"Invalid index\n";
        return;
    }
    cout<<(*deckptr)[idx]<<"\n";
}

/**
 * Card replacement handler.
 * Reads an index and a new card representation from the input.
 * If the index is valid, it replaces the card at the specified position
 * using the assignment operator of the Card class.
 * @param deckptr A reference to the pointer of the deck to be modified.
 * @return None.
 */
void case7( Deck*& deckptr) {
    int idx;
    char c[3];
    //get the idx and the card to replace.
    cin>>idx;
    cin>>c;
    if (idx<0 || idx>=deckptr->getSize()) {
        cout<<"Invalid index\n";
        return;
    }
    //"Replacing" the old card with a new one by changing the values of the card
    //according to the values of the new card.
    (*deckptr)[idx] = Card(c);
}

/**
 * Deck reset handler.
 * Deallocates the current Deck instance if it exists, using the static
 * counter to verify presence. Resets the pointer to nullptr to prevent
 * dangling references and allow for a clean state.
 * @param deckptr A reference to the deck pointer to be deleted and nulled.
 * @return None.
 */
void reset_deck(Deck*& deckptr) {
    if (Deck::get_cnt_deck()!=0) {
        delete deckptr;
        deckptr = nullptr;
    }
}

/**
 * Main execution func.
 * Manages the system by displaying a menu and routing
 * user input to the appropriate case handlers. Manages the program's lifecycle,
 * including deck persistence and final memory cleanup before exit.
 * @return Returns 0 upon successful termination.
 */
int main() {

    Deck* deckptr = nullptr;

    //initialize auxiliary variables
    bool exit_flag=false;
    int user_choice;
    const char* menu2print = "Menu:\n1. Build Empty Deck\n2. Compare Cards\n3. Add Cards\n4. Remove Cards\n5. Look at Top Cards\n6. Card at\n7. Swap Card\n8. Print Deck\n9. Delete Deck\n10. Exit\n";


    //main loop
    while (!exit_flag) {
        cout<<menu2print;

        //get input from user
        cin>>user_choice;

        //input validation
        if (user_choice<1 || user_choice>10) {
            continue;
        }
        //Case analysis and handling based on user selection
        switch (user_choice) {
        case 1:
            case1(deckptr);
            break;
        case 2:
            case2();
            break;
        case 3:
            case3(deckptr);
            break;
        case 4:
            case4(deckptr);
            break;
        case 5:
            case5(deckptr);
            break;
        case 6:
            case6(deckptr);
            break;
        case 7:
            case7(deckptr);
            break;
        case 8:
            cout<<*deckptr;
            break;
        case 9:
            reset_deck(deckptr);
            break;
        case 10:
            reset_deck(deckptr);
            exit_flag=true;
            break;
        }
    }

    //finish the program
    return 0;
}