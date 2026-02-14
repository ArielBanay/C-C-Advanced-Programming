//B"H

#include "Ranger.h"

Ranger::Ranger(int max_life,int max_card): Player(max_life,max_card) {}

Ranger::Ranger(const Ranger& other) : Player(other) {}

Ranger::~Ranger() {}

const BattleResult Ranger::fight(const Enemy& enemy, const vector<Card>& set) const {
    return enemy.fightRanger(set);
}