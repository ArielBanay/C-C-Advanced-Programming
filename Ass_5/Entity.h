//B"H

#ifndef ASS_5_ENTITY_H
#define ASS_5_ENTITY_H

/**
 * @class Entity
 * Base class representing a generic game entity.
 * Provides shared foundational attributes and behaviors, such as health management,
 * for all participants in the game including players and enemies.
 * @member (const int) max_life - The maximum health points the entity can have.
 * @member (int) cur_life - The current health points of the entity.
 */
class Entity {

    protected:
    //Entity members
    const int max_life;
    int cur_life;

    /**
     * Constructor.
     * Initializes a new Entity with a defined maximum life value.
     * Sets both the current life and maximum life to the specified amount.
     * @param max_life The maximum health points for the entity (default is 0).
     * @return A new instance of an Entity object.
     */
    Entity(int max_life=0);

    /**
     * Copy Constructor.
     * Creates a new Entity by copying the health statistics from an existing Entity instance.
     * @param entity A reference to the source Entity to be copied.
     * @return A new instance of an Entity object.
     */
    Entity(const Entity& entity);

    /**
     * Virtual Destructor.
     * Ensures proper and safe cleanup of resources for derived classes within the inheritance hierarchy.
     */
    virtual ~Entity();

public:
    /**
     * Current Life Getter.
     * @return The integer value of cur_life.
     */
    int get_cur_life() const {return cur_life;}

    /**
     * Max Life Getter.
     * @return The integer value of max_life.
     */
    int get_max_life() const {return max_life;}

    /**
     * Update Life.
     * Modifies the entity's current life by a specified amount 'x'.
     * Handles both healing (positive x) and damage (negative x), keeping the value within bounds [0, max_life].
     * @param x The amount to add to the current life (negative to subtract).
     */
    virtual void update_life(int x);
};


#endif //ASS_5_ENTITY_H