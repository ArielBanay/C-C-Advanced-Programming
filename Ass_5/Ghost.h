//B"H
#ifndef ASS_5_GHOST_H
#define ASS_5_GHOST_H
#include "Enemy.h"

/**
 * @class Ghost
 * Represents a specific enemy type in the game, inheriting from the Enemy class.
 * The Ghost is characterized by specific health and damage values, and has unique interaction rules with different player types.
 */
class Ghost : public Enemy{
public:
    /**
     * Constructor.
     * Initializes a new Ghost instance with specified life and damage values.
     * Passes these values to the base Enemy constructor.
     * @param max_life The maximum health points of the ghost (default is 50).
     * @param damage The damage value the ghost deals (default is 15).
     * @return A new instance of a Ghost object.
     */
    Ghost(int max_life=50,int damage=15);

    /**
     * Destructor.
     * Cleans up the Ghost object upon destruction.
     */
    ~Ghost();

    /**
     * Fight Fighter method.
     * Implementation of the specific battle logic when the Ghost fights a Fighter.
     * @param set A vector of cards played by the player.
     * @return A BattleResult structure containing the outcome of the turn.
     */
    const BattleResult fightFighter(const vector<Card>& set) const override;

    /**
     * Fight Sorcerer method.
     * Implementation of the specific battle logic when the Ghost fights a Sorcerer.
     * @param set A vector of cards played by the player.
     * @return A BattleResult structure containing the outcome of the turn.
     */
    const BattleResult fightSorcerer(const vector<Card>& set) const override;

    /**
     * Fight Ranger method.
     * Implementation of the specific battle logic when the Ghost fights a Ranger.
     * @param set A vector of cards played by the player.
     * @return A BattleResult structure containing the outcome of the turn.
     */
    const BattleResult fightRanger(const vector<Card>& set) const override;
};

#endif //ASS_5_GHOST_H