//B"H

#include "Enemy.h"
using namespace std;


Enemy::Enemy(int max_life, int damage) : Entity(max_life), damage(damage) {}

Enemy::Enemy(const Enemy& other) : Entity(other), damage(other.damage) {}

Enemy::~Enemy(){}

BattleResult Enemy::fight_no_H(const vector<Card>& set, int i) const {
    BattleResult result{0,0,i};

    int total_val=0;

    //flags indicate does set contain this sign
    bool D = false;
    bool C = false;
    bool S = false;

    //iterate through the vector & sum total val
    for (const Card& card : set) {
        total_val += card.get_value();
        if (card.get_sign()=='C') {
            C = true;
        }
        else if (card.get_sign()=='D') {
            D = true;
        }
        else if (card.get_sign()=='S') {
            S = true;
        }
    }
    //Activating special forces if available
    if (C && S) {total_val = 2*total_val;}
    if (D) { result.player_damage = max(0,result.player_damage-total_val);}
    result.enemy_damage = total_val;
    return result;
}

BattleResult Enemy::fight_no_D(const vector<Card>& set, int i) const {
    BattleResult result{0,0,i};

    int total_val=0;

    //flags indicate does set contain this sign
    bool C = false;
    bool S = false;
    bool H = false;

    //iterate through the vector & sum total val
    for (const Card& card : set) {
        total_val += card.get_value();
        if (card.get_sign()=='H') {
            H = true;
        }
        else if (card.get_sign()=='S') {
            S = true;
        }
        else if (card.get_sign()=='C') {
            C = true;
        }
    }
    //Activating special forces if available
    if ( C && S ){ total_val = 2*total_val;}
    if (H) { result.player_heal = total_val;}
    result.enemy_damage = total_val;
    return result;
}

BattleResult Enemy::fight_no_CS(const vector<Card>& set, int i) const {
    BattleResult result{0,0,i};

    int total_val=0;

    //flags indicate does set contain this sign
    bool D = false;
    bool H = false;

    //iterate through the vector & sum total val
    for (const Card& card : set) {
        total_val += card.get_value();
        if (card.get_sign()=='H') {
            H = true;
        }
        else if (card.get_sign()=='D') {
            D = true;
        }
    }
    //Activating special forces if available
    if (D) { result.player_damage = max(0,result.player_damage-total_val);}
    if (H) { result.player_heal = total_val;}
    result.enemy_damage = total_val;
    return result;
}


