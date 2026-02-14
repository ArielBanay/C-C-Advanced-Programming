//B"H
#include <iostream>
#include <sstream>
#include "Deck.h"
#include "Defs.h"
#include "Dragon.h"
#include "Fighter.h"
#include "Ghost.h"
#include "Ranger.h"
#include "Sorcerer.h"
#include "Troll.h"
using namespace std;

/**
 * Initialize Deck.
 * Reads a stream of strings from the user input until "00" is encountered.
 * Parses the input string into pairs of characters to create Card objects and adds them to the deck.
 * @param d A reference to the Deck object to be initialized.
 */
void init_deck(Deck& d) {

    //get cards from user
    string str = "";
    string temp;
    cout<<"Initialize deck\n";
    cin>>temp;
    while(temp!="00") {
        str+=temp;
        cin>>temp;
    }

    //add cards to deck
    for (int i=0; i<str.length(); i=i+2) {
        d += Card(str[i],str[i+1]);
    }
}

/**
 * Initialize Player.
 * Prompts the user to select a character class (Fighter, Sorcerer, or Ranger).
 * Dynamically allocates the corresponding Player object and assigns it to the pointer.
 * @param p A reference to a Player pointer to be initialized.
 */
void init_player(Player*& p) {
    //init player
    int player_choice;
    cout<<"Choose player character:\n";
    cout<<"(1) Fighter (2) Sorcerer (3) Ranger\n";
    cin>>player_choice;
    switch(player_choice) {
    case 1:
        p = new Fighter();
        break;
    case 2:
        p = new Sorcerer();
        break;
    case 3:
        p = new Ranger();
        break;
    //not suppose happen
    default:
        break;
    }
}

/**
 * Initialize Enemy.
 * Prompts the user to select an enemy type (Troll, Ghost, or Dragon).
 * Dynamically allocates the corresponding Enemy object and assigns it to the pointer.
 * @param e A reference to an Enemy pointer to be initialized.
 */
void init_enemy(Enemy*& e) {
    //init enemy
    int enemy_choice;
    cout<<"Choose enemy character:\n";
    cout<<"(1) Troll (2) Ghost (3) Dragon\n";
    cin>>enemy_choice;
    switch (enemy_choice) {
        case 1:
            e = new Troll();
            break;
        case 2:
            e = new Ghost();
            break;
        case 3:
            e = new Dragon();
            break;
        //not suppose happen
        default:
            break;
    }

}

/**
 * Take Card (Version 1).
 * Fills the player's hand with cards from the deck until the hand reaches its maximum capacity
 * or the deck becomes empty. Used at the start of the game.
 * @param p A pointer to the player who is taking cards.
 * @param deck A reference to the deck to draw cards from.
 * @return A deck_status enum indicating if the deck is empty or not.
 */
deck_status take_card_v1(Player* p, Deck& deck) {
    //Filling the player's hand to the maximum limit or until the deck is empty
    while (deck.getSize()>0 && p->get_cur_card()<p->get_max_card()) {
        p->take_card(deck[deck.getSize()-1]);
        deck-=1;
    }
    //Checking whether the game cannot start due to a lack of cards in the deck
    if (deck.getSize()==0 && (p->get_max_card()-p->get_cur_card())>0){return deck_status::Empty;}
    return deck_status::Not_Empty;
}

/**
 * Take Card (Version 2).
 * Adds up to two cards to the player's hand from the deck, respecting the maximum hand capacity.
 * Used at the end of a turn to replenish the hand.
 * @param p A pointer to the player who is taking cards.
 * @param deck A reference to the deck to draw cards from.
 * @return A deck_status enum indicating if the deck is empty or not.
 */
deck_status take_card_v2(Player* p,Deck& deck) {
    //Attempting to draw two cards as part of the end-of-turn rules
    for (int i=0; i<2; i++) {
        if (deck.getSize()>0 && p->get_cur_card()<p->get_max_card()) {
            p->take_card(deck[deck.getSize()-1]);
            deck-=1;
        }
    }
    //Report to the system if the pack has been emptied
    if (deck.getSize()==0 && (p->get_max_card()-p->get_cur_card())>0){return deck_status::Empty;}
    return deck_status::Not_Empty;
}

/**
 * Build Set Vector.
 * Parses a space-separated string representing a set of cards.
 * Converts each substring into a Card object and stores it in the provided vector.
 * @param vec A reference to the vector where the Card objects will be stored.
 * @param string_set A string containing the textual representation of the card set.
 */
void build_set_vec(vector<Card>& vec, const string& string_set) {
    //create a string stream object in order to split it according to 'whitespace'
    stringstream player_set_stream(string_set);
    string temp;

    //get the next 'Card' in the string, create card and add it to vec.
    while (player_set_stream >> temp) {
        vec.emplace_back(temp.c_str());
    }
}

/**
 * Check Set.
 * Validates the legality of a card set played by the user according to the game rules.
 * Checks for valid combinations, sums, amounts of specific cards, and prohibited moves.
 * @param vec_set A constant reference to the vector of cards to be validated.
 * @return True if the set is a valid move, false otherwise.
 */
bool check_set(const vector<Card>& vec_set) {
    //init counters
    int c_val;
    int card_cnt=0;
    int Ace_cnt=0;
    int two_cnt=0;
    int three_cnt=0;
    int four_cnt=0;
    int five_cnt=0;
    int sixtok_cnt=0;

    // count all the cards in the set
    for (const Card& card : vec_set) {
        card_cnt++;
        c_val = card.get_value();
        switch (c_val) {
            case 1:
                Ace_cnt++;
                break;
            case 2:
                two_cnt++;
                break;
            case 3:
                three_cnt++;
                break;
            case 4:
                four_cnt++;
                break;
            case 5:
                five_cnt++;
                break;
            default:
                sixtok_cnt++;
                break;
        }
    }

    //No such available turn
    if (card_cnt<1 || 6<=card_cnt || Ace_cnt>=3 ) {return false;}

    //Each one card is valid turn
    if (card_cnt == 1) {return true;}

    //One card + Ace
    if (card_cnt==2 && Ace_cnt==1) {return true;}

    //double Ace
    if (card_cnt == 2 && Ace_cnt==2) {return true;}

    //Each of the option in the instruction file
    //to each valid set can be added one more Ace && can't contain bigger than 5
    if (Ace_cnt<=1 && sixtok_cnt==0) {
        //5 , 4 twice
        if ((five_cnt<=2 && two_cnt+three_cnt+four_cnt==0 ) || (four_cnt<=2 && two_cnt+three_cnt+five_cnt==0 ) ) {return true;}
        //2,3 triple or 2,3 twice
        if ((three_cnt<=3 && two_cnt+four_cnt+five_cnt==0) || (two_cnt<=3 && three_cnt+four_cnt+five_cnt==0)) {return true;}
        //2,2,2,2
        if (two_cnt==4 && three_cnt+four_cnt+five_cnt==0) {return true;}
    }

    //if not found any case that is valid => it invalid
    return false;
}

/**
 * Main Function.
 * The entry point of the program. Manages the game loop, initialization of game objects,
 * exception handling, user input processing, and battle resolution logic.
 * @return Execution status code (0 for success, non-zero for errors).
 */
int main()
{
    //Initializing game data
    Deck deck;
    Player* player = nullptr;
    Enemy* enemy = nullptr;


    try{ init_deck(deck); }
    //Inorder to distinguish between bad alloc and other exceptions.
    catch (const bad_alloc& e) {
        cout<<"Memory Error\n";
        return 1;
    }
    catch (...) {
        return 1;
    }

    try { init_player(player); }
    catch (const bad_alloc& e) {
        cout<<"Memory Error\n";
        return 1;
    }

    try { init_enemy(enemy); }
    catch (const bad_alloc& e) {
        // player have been created successfully so need to delete it
        delete player;
        cout<<"Memory Error\n";
        return 1;
    }

    try {
        //In order of safety use getline() func inside the main loop.
        cin.ignore();
    }
    //If there wasn't an empty line immediately after the enemy choose I want to catch the exception and do nothing.
    //The program will know to deal this case safely.
    catch (...){}


    //Exceptions might bubble up from player->takecard() method.
    //Might also propagate from deck -= operator.
    try{
        //The player take cards from deck to fill his hand
        if (take_card_v1(player,deck)==deck_status::Empty) {
            //there is no enough cards to start the game
            cout<<"Deck ran out\n";
            delete player;
            delete enemy;
            return 0;
        }
    }
    catch (const bad_alloc& e) {
        delete player;
        delete enemy;
        cout<<"Memory Error\n";
        return 1;
    }
    catch (...) {
        delete player;
        delete enemy;
        return 1;
    }

    //To get all the cards a player plays on his turn as an input.
    //contain the 'cards' the user will choose from his hand.
    //The string will be converted to elements in the current set.
    string str_set;
    vector<Card> set;

    //flags
    bool exit = false;

    while(true) {
        //prints of the current stats of the game.
        cout<<"Player health: "<<player->get_cur_life()<<"\n";
        cout<<"Enemy health: "<<enemy->get_cur_life()<<"\n";
        cout<<"Player hand"<<"\n";
        player->print_hand();

        try {
            //get input set from user
            bool valid_set = false;
            //loop till the user give a valid set
            while(!valid_set) {
                cout<<"Insert card set to play\n";
                getline(cin,str_set);
                //exit case
                if (str_set == "exit") {
                    exit = true;
                    break;
                }
                set.clear();
                build_set_vec(set,str_set);
                //check set is valid.
                valid_set = check_set(set);
                if (!valid_set) {cout<<"Card set is not valid\n";}
            }
        }
        catch (const bad_alloc& e) {
            cout<<"Memory Error\n";
            delete player;
            delete enemy;
            return 1;
        }
        catch (...) {
            delete player;
            delete enemy;
            return 1;
        }

        //the user want to finish game
        if (exit) {break;}

        //update the cards in player->hand
        player->update_hand(set);

        //calc power of set
        BattleResult battle_res = player->fight(*enemy,set);

        //damage to enemy
        cout<<"Player dealt "<<battle_res.enemy_damage<<" points of damage\n";
        enemy->update_life(-1*battle_res.enemy_damage);

        //player win
        if (enemy->get_cur_life()==0) {
            cout<<"Player won\n";
            break;
        }

        //player heal
        //The set contained Heart that not canceled and there is option to heal.
        if (battle_res.player_heal>0 && (player->get_max_life() - player->get_cur_life())>0) {
            int real_heal = min(battle_res.player_heal,player->get_max_life()-player->get_cur_life());
            cout<<"Player healed "<<real_heal<<" points of damage\n";
            player->update_life(real_heal);
        }

        //player damage
        cout<<"Player took "<<battle_res.player_damage<<" points of damage\n";
        player->update_life(-1*battle_res.player_damage);

        //enemy win
        if (player->get_cur_life()==0) {
            cout<<"Player lost\n";
            break;
        }

        try {
            //Take 2 more cards from top deck
            if (take_card_v2(player,deck)==deck_status::Empty) {
                cout<<"Deck ran out\n";
                break;
            }
        }
        catch (const bad_alloc& e) {
            delete player;
            delete enemy;
            cout<<"Memory Error\n";
            return 1;
        }
        catch (...) {
            delete player;
            delete enemy;
            return 1;
        }

    }

    delete player;
    delete enemy;
    return 0;
}
