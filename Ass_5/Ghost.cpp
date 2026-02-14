//B"H
#include "Ghost.h"

Ghost::Ghost(int max_life, int damage) : Enemy(max_life, damage) {}

Ghost::~Ghost() {}

const BattleResult Ghost::fightFighter(const vector<Card>& set) const {
    return fight_no_CS(set,15);
}

const BattleResult Ghost::fightSorcerer(const vector<Card>& set) const {
    return fight_no_H(set,15);
}

const BattleResult Ghost::fightRanger(const vector<Card>& set) const {
    return fight_no_D(set,15);
}