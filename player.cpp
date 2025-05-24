#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "player.h"
#include "card.h"
using namespace std;

Player::Player(): name("user"), cash(5000){}

Player::Player(string name): name(name), cash(5000){}

string Player::getName(){
    return this->name;
}

double Player::getCash(){
    return this->cash;
}

void Player::addCash(double bet){
    this->cash+=bet;
}
void Player::removeCash(double bet){
    if(bet > this->cash){
        cash = 0;
    }
    else{
        this->cash-=bet;
    }
}
void Player::setHand(vector<Card>& cards){
    this->hand = cards;
}

vector<Card>& Player::getHand(){
    return this->hand;
}




