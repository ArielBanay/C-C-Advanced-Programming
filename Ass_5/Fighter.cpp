//B"H

#include "Fighter.h"
#include "Enemy.h"

Fighter::Fighter(int max_life,int max_card): Player(max_life,max_card) {}

Fighter::Fighter(const Fighter& other) : Player(other) {}

Fighter::~Fighter() {}

const BattleResult Fighter::fight(const Enemy& enemy, const vector<Card>& set) const {
    return enemy.fightFighter(set);
}

