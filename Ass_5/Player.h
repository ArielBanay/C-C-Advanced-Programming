//B"H

#ifndef ASS_5_PLAYER_H
#define ASS_5_PLAYER_H

#include <vector>
#include "Defs.h"
#include "Card.h"
#include "Enemy.h"
#include "Entity.h"
using namespace std;

/**
 * @class Player
 * Abstract base class representing a player in the game, inheriting from the Entity class.
 * Manages the player's health state, hand of cards, and common combat interactions
 * by leveraging shared functionality from the Entity base class.
 * @member (const int) max_card - The maximum number of cards the player can hold in their hand.
 * @member (vector<Card>) Hand - A container storing the Card objects currently held by the player.
 */
class Player : public Entity {

protected:

    //player members
    const int max_card;
    vector<Card> Hand;

    //constructors & destructors
    /**
     * Constructor.
     * Initializes a new Player instance with defined maximum life and card capacity.
     * Accessible only by derived classes.
     * @param max_life The maximum health points of the player (default is 0).
     * @param max_card The maximum number of cards the player can hold (default is 0).
     * @return A new instance of a Player object.
     */
    Player(int max_life=0, int max_card=0);

    /**
     * Copy Constructor.
     * Creates a new Player by copying the state of another Player instance.
     * Copies the life stats and the hand of cards.
     * @param other A reference to the source Player to be copied.
     * @return A new instance of a Player object.
     */
    Player(const Player& other);


public:

    /**
     * Virtual Destructor.
     * Ensures proper cleanup of derived class resources when deleting a Player pointer.
     */
    virtual ~Player();

    //polymorphic methods for each specific enemy

    /**
     * Fight method (Pure Virtual).
     * Defines the interface for combat logic against a specific enemy.
     * Must be implemented by derived classes to handle specific player-enemy interactions.
     * @param enemy A reference to the opponent enemy.
     * @param set The vector of cards played by the player.
     * @return A BattleResult structure containing the outcome of the turn.
     */
    virtual const BattleResult fight(const Enemy& enemy, const vector<Card>& set) const =0;


    //same function for all players
    /**
     * Take Card.
     * Adds a new card to the player's hand.
     * Note: The caller is responsible for freeing the memory of the card object passed as an argument.
     * @param c A reference to the card to be added.
     */
    void take_card(const Card& c);

    /**
     * Update Hand.
     * Removes a set of played cards from the player's hand.
     * Iterates through the provided set and finds the corresponding cards in the hand to erase them.
     * @param set A vector of cards that were played and need to be removed.
     */
    void update_hand(const vector<Card>& set);


    /**
     * Max Card Getter.
     * @return The integer value of max_card.
     */
    int get_max_card() const {return max_card;}

    /**
     * Current Card Count Getter.
     * @return The size of the Hand vector.
     */
    int get_cur_card() const {return Hand.size();}

    /**
     * Print Hand.
     * Prints the current cards in the player's hand to the console.
     */
    void print_hand() const;
};

#endif //ASS_5_PLAYER_H