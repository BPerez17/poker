#ifndef HAND_EVALUATOR_H
#define HAND_EVALUATOR_H
#include <string>
#include <vector>
#include "card.h"
using namespace std;


struct EvaluatedHand {
    string name;
    int rank;
    vector<int> tiebreakers;
};


int getCardRank(const string& value);

EvaluatedHand evaluateHandDetailed(const vector<Card>& hand);

vector<vector<Card>> getCombinations(const vector<Card>& cards);

EvaluatedHand evaluateTexasHoldEmDetailed(const vector<Card>& player, const vector<Card>& community);

int getHandRank(const string& handName);

int compareHands(const vector<Card>& p1Hand, const vector<Card>& p2Hand, const vector<Card>& community);

#endif