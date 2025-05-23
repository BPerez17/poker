#include "hand_evaluator.h"
#include <algorithm>
#include <map>
#include <set>
#include <cmath>


int getCardRank(const string& value) {
    if (value == "2") return 2;
    if (value == "3") return 3;
    if (value == "4") return 4;
    if (value == "5") return 5;
    if (value == "6") return 6;
    if (value == "7") return 7;
    if (value == "8") return 8;
    if (value == "9") return 9;
    if (value == "10") return 10;
    if (value == "J") return 11;
    if (value == "Q") return 12;
    if (value == "K") return 13;
    if (value == "A") return 14;
    return -1; // Invalid
}

string evaluateHand(const vector<Card>& hand) {
    if (hand.size() != 5) return "Invalid hand";

    map<int, int> rankCount;
    map<string, int> suitCount;
    vector<int> ranks;

    for (const auto& card : hand) {
        int rank = getCardRank(card.getValue());
        ranks.push_back(rank);
        rankCount[rank]++;
        suitCount[card.getSuit()]++;
    }

    sort(ranks.begin(), ranks.end());

    // Check for flush
    bool isFlush = false;
    for (const auto& s : suitCount) {
        if (s.second == 5) {
            isFlush = true;
            break;
        }
    }

    // Check for straight
    bool isStraight = true;
    for (int i = 0; i < 4; ++i) {
        if (ranks[i+1] != ranks[i] + 1) {
            isStraight = false;
            break;
        }
    }

    // Special case: A-2-3-4-5
    if (!isStraight && ranks == vector<int>{2, 3, 4, 5, 14}) {
        isStraight = true;
    }

    if (isStraight && isFlush) return "Straight Flush";

    // Count occurrences
    set<int> counts;
    for (const auto& pair : rankCount) {
        counts.insert(pair.second);
    }

    if (counts.count(4)) return "Four of a Kind";
    if (counts.count(3) && counts.count(2)) return "Full House";
    if (isFlush) return "Flush";
    if (isStraight) return "Straight";
    if (counts.count(3)) return "Three of a Kind";
    
    int pairCount = 0;
    for (const auto& pair : rankCount) {
        if (pair.second == 2) pairCount++;
    }

    if (pairCount == 2) return "Two Pair";
    if (pairCount == 1) return "One Pair";

    return "High Card";
}

vector<vector<Card>> getCombinations(const vector<Card>& cards) {
    vector<vector<Card>> combinations;
    vector<bool> select(cards.size(), false);
    fill(select.begin(), select.begin() + 5, true); // pick 5 of 7

    do {
        vector<Card> combo;
        for (size_t i = 0; i < cards.size(); ++i) {
            if (select[i]) combo.push_back(cards[i]);
        }
        combinations.push_back(combo);
    } while (prev_permutation(select.begin(), select.end()));

    return combinations;
}

string evaluateTexasHoldEm(const vector<Card>& playerCards, const vector<Card>& communityCards) {
    if (playerCards.size() != 2 || communityCards.size() != 5) {
        return "Invalid input: must provide 2 hole cards and 5 community cards";
    }

    vector<Card> allCards = playerCards;
    allCards.insert(allCards.end(), communityCards.begin(), communityCards.end());

    vector<vector<Card>> combos = getCombinations(allCards);

    string bestHand = "High Card";
    vector<string> handRanking = {
        "High Card", "One Pair", "Two Pair", "Three of a Kind", "Straight",
        "Flush", "Full House", "Four of a Kind", "Straight Flush"
    };

    map<string, int> handRankIndex;
    for (size_t i = 0; i < handRanking.size(); ++i) {
        handRankIndex[handRanking[i]] = i;
    }

    for (const auto& combo : combos) {
        string hand = evaluateHand(combo);
        if (handRankIndex[hand] > handRankIndex[bestHand]) {
            bestHand = hand;
        }
    }

    return bestHand;
}

int getHandRank(const string& handName) {
    if (handName == "High Card") return 0;
    if (handName == "One Pair") return 1;
    if (handName == "Two Pair") return 2;
    if (handName == "Three of a Kind") return 3;
    if (handName == "Straight") return 4;
    if (handName == "Flush") return 5;
    if (handName == "Full House") return 6;
    if (handName == "Four of a Kind") return 7;
    if (handName == "Straight Flush") return 8;
    return -1; // Unknown hand
}
