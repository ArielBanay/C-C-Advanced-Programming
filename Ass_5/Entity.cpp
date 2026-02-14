// B"H

#include "Entity.h"
#include <algorithm>
using namespace std;

Entity::Entity(int max_life) : max_life(max_life) , cur_life(max_life) {}

Entity::Entity(const Entity& entity) : max_life(entity.max_life), cur_life(entity.cur_life) {}

Entity::~Entity() {}

void Entity::update_life(int x) {
    if (x>=0){
        cur_life = min(cur_life+x,max_life);
    }
    else {
        cur_life = max(0,cur_life+x);
    }
}
