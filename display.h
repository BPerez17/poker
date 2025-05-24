#include <vector>
#include <string>

#ifndef DISPLAY_H
#define DISPLAY_H
#include "card.h"
#include "player.h"
using namespace std;

vector<Card> loadData(string filename);

void generateHand(vector<Card>& deck, Player& user);

//plan to add more players into display function with a vector of players

void tableDisplay(vector<Card>& deck, vector<Card>& communitycards, Player& user, Player& computer, int pot, int round);

//helper functions

void shuffle(vector<Card>& deck);

void printCredits();

#endif