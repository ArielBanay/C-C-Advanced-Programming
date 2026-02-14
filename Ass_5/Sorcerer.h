//B"H

#ifndef ASS_5_SORCERER_H
#define ASS_5_SORCERER_H
#include "Player.h"

/**
 * @class Sorcerer
 * Represents a specific player character class (Sorcerer) inheriting from Player.
 * The Sorcerer has unique initial stats (typically lower health and higher card capacity) and interacts with enemies using specific combat logic.
 */
class Sorcerer : public Player {
    public:

    /**
     * Constructor.
     * Initializes a new Sorcerer instance with defined maximum life and card capacity.
     * @param max_life The maximum health points of the sorcerer (default is 40).
     * @param max_card The maximum number of cards the sorcerer can hold (default is 8).
     * @return A new instance of a Sorcerer object.
     */
    Sorcerer(int max_life=40,int max_card=8);

    /**
     * Copy Constructor.
     * Creates a new Sorcerer by copying the state of another Sorcerer instance.
     * @param other A reference to the source Sorcerer to be copied.
     * @return A new instance of a Sorcerer object.
     */
    Sorcerer(const Sorcerer& other);

    /**
     * Destructor.
     * Cleans up the Sorcerer object upon destruction.
     */
    virtual ~Sorcerer();

    /**
     * Fight method.
     * Triggers the enemy's logic for fighting a Sorcerer to determine the battle outcome.
     * @param enemy A reference to the opponent enemy.
     * @param set The vector of cards played by the Sorcerer for this turn.
     * @return A BattleResult structure containing the damage dealt/taken and healing.
     */
    const BattleResult fight(const Enemy& enemy, const vector<Card>& set) const;
};


#endif //ASS_5_SORCERER_H