#include <vector>
#include <string>

#ifndef PLAYER_H
#define PLAYER_H
#include "card.h"
using namespace std;

class Player{
    private:
        string name = "user";
        double cash = 5000;
        vector<Card> hand;
        // int wins = 0;
    public:
        Player();
        Player(string name);
        string getName();
        double getCash();
        void addCash(double bet);
        void removeCash(double bet);
        void setHand(vector<Card>& cards);
        vector<Card>& getHand();

        // void addWin();  NOTE: not implemented
        // int getWins(); NOTE: not implemented

};



#endif