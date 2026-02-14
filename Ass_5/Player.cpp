//B"H

#include "Player.h"
#include <algorithm>

Player::Player(int max_life, int max_card) : Entity(max_life),max_card(max_card){
    Hand = vector<Card>(0);
}

Player::Player(const Player& other) : Entity(other), max_card(other.max_card){
    Hand = other.Hand;
}

Player::~Player() {}

void Player::take_card(const Card& c) {
    //who sent C need to free it
    Hand.push_back(c);
}

void Player::update_hand(const vector<Card>& set) {
    vector<Card>::iterator iter;
    //Iteratively go over all cards in a 'hand'
    for (const Card& card : set){

        //find the card in Hand
        iter = std::find(Hand.begin(),Hand.end(),card);

        //if the card in Hand erase it from Hand, suppose to be always true.
        if (iter != Hand.end()){
            Hand.erase(iter);
        }
    }
}

void Player::print_hand() const {
    for (int i=Hand.size()-1; i>=0; i--){
        cout << Hand[i] << " ";
    }
    cout << endl;
}


