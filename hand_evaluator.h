#ifndef HAND_EVALUATOR_H
#define HAND_EVALUATOR_H
#include <string>
#include <vector>
#include "card.h"
using namespace std;

int getCardRank(const string& value);

string evaluateHand(const vector<Card>& hand);

vector<vector<Card>> getCombinations(const vector<Card>& cards);

string evaluateTexasHoldEm(const vector<Card>& playerCards, const vector<Card>& communityCards);

int getHandRank(const string& handName);

int compareHands(const vector<Card>& p1Hand, const vector<Card>& p2Hand, const vector<Card>& community);

#endif