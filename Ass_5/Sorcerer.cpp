//B"H

#include "Sorcerer.h"


Sorcerer::Sorcerer(int max_life,int max_card): Player(max_life,max_card) {}

Sorcerer::Sorcerer(const Sorcerer& other) : Player(other) {}

Sorcerer::~Sorcerer() {}

const BattleResult Sorcerer::fight(const Enemy& enemy, const vector<Card>& set) const {
    return enemy.fightSorcerer(set);
}
