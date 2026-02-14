//B"H

#ifndef ASS_5_ENEMY_H
#define ASS_5_ENEMY_H
#include <vector>
#include "Defs.h"
#include "Card.h"
#include "Entity.h"

/**
 * @class Enemy
 * Abstract base class representing an enemy in the game, inheriting from the Entity class.
 * Manages combat logic and damage calculation against various player types
 * while utilizing shared health and state management functionality.
 * @member (const int) damage - The base damage value that the enemy deals to the player.
 */
class Enemy : public Entity {

protected:
    //enemy members
    const int damage;

    //constructors & destructors
    /**
     * Constructor.
     * Initializes a new Enemy instance with specific life and damage values.
     * Accessible only by derived classes.
     * @param max_life The maximum health of the enemy.
     * @param damage The base damage the enemy deals.
     * @return A new instance of an Enemy object.
     */
    Enemy(int max_life=0,int damage=0);

    /**
     * Copy Constructor.
     * Creates a new Enemy by copying the state of another Enemy instance.
     * Copies the life stats and the damage value.
     * @param other A reference to the source Enemy to be copied.
     * @return A new instance of an Enemy object.
     */
    Enemy(const Enemy& other);

    /**
     * Fight helper (No Hearts).
     * Calculates battle results considering Clubs, Diamonds, and Spades, but ignoring Hearts.
     * Used when the enemy mechanics prevent the player from healing.
     * @param set The vector of cards played by the user.
     * @param i The base damage to be inflicted by the enemy.
     * @return A BattleResult structure with calculated damage and zero healing.
     */
    BattleResult fight_no_H(const vector<Card>& set, int i) const;

    /**
     * Fight helper (No Diamonds).
     * Calculates battle results considering Clubs, Spades, and Hearts, but ignoring Diamonds.
     * Used when the enemy mechanics prevent the player from shielding damage.
     * @param set The vector of cards played by the user.
     * @param i The base damage to be inflicted by the enemy.
     * @return A BattleResult structure with calculated damage/healing but no damage reduction.
     */
    BattleResult fight_no_D(const vector<Card>& set, int i) const;

    /**
     * Fight helper (No Clubs/Spades).
     * Calculates battle results considering Diamonds and Hearts, but ignoring the Clubs/Spades combo.
     * Used when the enemy mechanics prevent the player from doubling their attack power.
     * @param set The vector of cards played by the user.
     * @param i The base damage to be inflicted by the enemy.
     * @return A BattleResult structure with calculated damage/healing without the double-damage bonus.
     */
    BattleResult fight_no_CS(const vector<Card>& set, int i) const;

public:
    /**
     * Virtual Destructor.
     * Ensures proper cleanup of derived class resources when deleting an Enemy pointer.
     */
    virtual ~Enemy();

    //polymorphic methods for each specific enemy
    /**
     * Fight Fighter (Pure Virtual).
     * Defines the interface for combat logic when this enemy fights a Fighter.
     * Must be implemented by derived classes.
     * @param set The vector of cards played by the Fighter.
     * @return A BattleResult structure representing the outcome.
     */
    virtual const BattleResult fightFighter(const vector<Card>& set) const =0;

    /**
     * Fight Sorcerer (Pure Virtual).
     * Defines the interface for combat logic when this enemy fights a Sorcerer.
     * Must be implemented by derived classes.
     * @param set The vector of cards played by the Sorcerer.
     * @return A BattleResult structure representing the outcome.
     */
    virtual const BattleResult fightSorcerer(const vector<Card>& set) const =0;

    /**
     * Fight Ranger (Pure Virtual).
     * Defines the interface for combat logic when this enemy fights a Ranger.
     * Must be implemented by derived classes.
     * @param set The vector of cards played by the Ranger.
     * @return A BattleResult structure representing the outcome.
     */
    virtual const BattleResult fightRanger(const vector<Card>& set) const =0;

};


#endif //ASS_5_ENEMY_H