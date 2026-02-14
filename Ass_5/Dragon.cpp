//B"H
#include "Dragon.h"

Dragon::Dragon(int max_life, int damage) : Enemy(max_life, damage) {}

Dragon::~Dragon() {}

const BattleResult Dragon::fightFighter(const vector<Card>& set) const {
    return fight_no_D(set,10);
}

const BattleResult Dragon::fightSorcerer(const vector<Card>& set) const {
    return fight_no_CS(set,10);
}

const BattleResult Dragon::fightRanger(const vector<Card>& set) const {
    return fight_no_H(set,10);
}

