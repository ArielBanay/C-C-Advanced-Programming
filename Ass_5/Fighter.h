
#ifndef ASS_5_FIGHTER_H
#define ASS_5_FIGHTER_H
#include "Player.h"

/**
 * @class Fighter
 * Represents a specific player character class (Fighter) inheriting from Player.
 * The Fighter has specific initial stats and interacts with enemies using the fightFighter dispatch method.
 */
class Fighter : public Player{
    public:

    /**
     * Constructor.
     * Initializes a new Fighter instance with defined maximum life and card capacity.
     * @param max_life The maximum health points of the fighter (default is 60).
     * @param max_card The maximum number of cards the fighter can hold (default is 6).
     * @return A new instance of a Fighter object.
     */
    Fighter(int max_life=60,int max_card=6);

    /**
     * Copy Constructor.
     * Creates a new Fighter by copying the state of another Fighter instance.
     * @param other A reference to the source Fighter to be copied.
     * @return A new instance of a Fighter object.
     */
    Fighter(const Fighter& other);

    /**
     * Destructor.
     * Cleans up the Fighter object upon destruction.
     */
    virtual ~Fighter();

    /**
     * Fight method.
     * Calls the enemy's fightFighter method to calculate the battle result.
     * @param enemy A reference to the opponent enemy.
     * @param set The vector of cards played by the Fighter for this turn.
     * @return A BattleResult structure containing the damage dealt/taken and healing.
     */
    const BattleResult fight(const Enemy& enemy,const vector<Card>& set) const;
};


#endif //ASS_5_FIGHTER_H