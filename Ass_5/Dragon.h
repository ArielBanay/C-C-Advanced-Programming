//B"H
#ifndef ASS_5_DRAGON_H
#define ASS_5_DRAGON_H
#include "Enemy.h"

/**
 * @class Dragon
 * Represents a specific enemy type in the game, inheriting from the Enemy class.
 * The Dragon is characterized by specific health and damage values.
 */
class Dragon : public Enemy {

    public:
    /**
     * Initializes a new Dragon instance with specified life and damage values.
     * Passes these values to the base Enemy constructor.
     * @param max_life The maximum health points of the dragon (default is 75).
     * @param damage The damage value the dragon deals (default is 10).
     * @return A new instance of a Dragon object.
     */
    Dragon(int max_life=75,int damage=10);

    /**
     * Destructor.
     * Cleans up the Dragon object upon destruction.
     */
    ~Dragon();

    /**
     * Fight Fighter method.
     * Implementation of the specific battle logic when the Dragon fights a Fighter.
     * @param set A vector of cards played by the player.
     * @return A BattleResult structure containing the outcome of the turn.
     */
    const BattleResult fightFighter(const vector<Card>& set) const override;

    /**
     * Fight Sorcerer method.
     * Implementation of the specific battle logic when the Dragon fights a Sorcerer.
     * @param set A vector of cards played by the player.
     * @return A BattleResult structure containing the outcome of the turn.
     */
    const BattleResult fightSorcerer(const vector<Card>& set) const override;

    /**
     * Fight Ranger method.
     * Implementation of the specific battle logic when the Dragon fights a Sorcerer.
     * @param set A vector of cards played by the player.
     * @return A BattleResult structure containing the outcome of the turn.
     */
    const BattleResult fightRanger(const vector<Card>& set) const override;
};


#endif //ASS_5_DRAGON_H