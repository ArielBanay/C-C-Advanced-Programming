//B"H

#include "Troll.h"

Troll::Troll(int max_life, int damage) : Enemy(max_life, damage) {}

Troll::~Troll(){}

const BattleResult Troll::fightFighter(const vector<Card>& set) const {
    return fight_no_H(set,5);
}

const BattleResult Troll::fightSorcerer(const vector<Card>& set) const  {
    return fight_no_D(set, 5);
}

const BattleResult Troll::fightRanger(const vector<Card>& set) const  {
    return fight_no_CS(set, 5);
}


