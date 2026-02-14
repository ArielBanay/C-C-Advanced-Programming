//B"H

#ifndef ASS_5_RANGER_H
#define ASS_5_RANGER_H
#include "Player.h"

/**
 * @class Ranger
 * Represents a specific player character class (Ranger) inheriting from Player.
 * The Ranger starts with distinct health and card capacity values and has a unique combat interaction with enemies.
 */
class Ranger : public Player {

    public:

    /**
     * Constructor.
     * Initializes a new Ranger instance with defined maximum life and card capacity.
     * @param max_life The maximum health points of the ranger (default is 50).
     * @param max_card The maximum number of cards the ranger can hold (default is 7).
     * @return A new instance of a Ranger object.
     */
    Ranger(int max_life=50,int max_card=7);

    /**
     * Copy Constructor.
     * Creates a new Ranger by copying the state of another Ranger instance.
     * @param other A reference to the source Ranger to be copied.
     * @return A new instance of a Ranger object.
     */
    Ranger(const Ranger& other);

    /**
     * Destructor.
     * Cleans up the Ranger object upon destruction.
     */
    virtual ~Ranger();

    /**
     * Fight method.
     * Triggers the enemy's logic for fighting a Ranger to determine the battle outcome.
     * @param enemy A reference to the opponent enemy.
     * @param set The vector of cards played by the Ranger for this turn.
     * @return A BattleResult structure containing the damage dealt/taken and healing.
     */
    const BattleResult fight(const Enemy& enemy, const vector<Card>& set) const;
};


#endif //ASS_5_RANGER_H