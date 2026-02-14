//B"H

#ifndef ASS_5_TROLL_H
#define ASS_5_TROLL_H
#include "Enemy.h"

/**
 * @class Troll
 * Represents a specific enemy type in the game, inheriting from the Enemy class.
 * The Troll is characterized by high durability (health) and specific combat interactions with different player classes.
 */
class Troll : public Enemy{
    public:

    /**
     * Constructor.
     * Initializes a new Troll instance with specified life and damage values.
     * Passes these values to the base Enemy constructor.
     * @param max_life The maximum health points of the troll (default is 100).
     * @param damage The damage value the troll deals (default is 5).
     * @return A new instance of a Troll object.
     */
    Troll(int max_life=100,int damage=5);

    /**
     * Destructor.
     * Cleans up the Troll object upon destruction.
     */
    ~Troll();

    /**
     * Fight Fighter method.
     * Implementation of the specific battle logic when the Troll fights a Fighter.
     * @param set A vector of cards played by the player.
     * @return A BattleResult structure containing the outcome of the turn.
     */
    const BattleResult fightFighter(const vector<Card>& set) const override;

    /**
     * Fight Sorcerer method.
     * Implementation of the specific battle logic when the Troll fights a Sorcerer.
     * @param set A vector of cards played by the player.
     * @return A BattleResult structure containing the outcome of the turn.
     */
    const BattleResult fightSorcerer(const vector<Card>& set) const override;

    /**
     * Fight Ranger method.
     * Implementation of the specific battle logic when the Troll fights a Ranger.
     * @param set A vector of cards played by the player.
     * @return A BattleResult structure containing the outcome of the turn.
     */
    const BattleResult fightRanger(const vector<Card>& set) const override;
};


#endif //ASS_5_TROLL_H