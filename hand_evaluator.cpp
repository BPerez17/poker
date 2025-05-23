#include "hand_evaluator.h"
#include <algorithm>
#include <map>
#include <set>
#include <cmath>
using namespace std;

struct EvaluatedHand {
    std::string name;          // e.g., "One Pair"
    int rank;                  // 0 = High Card, 1 = One Pair, ..., 8 = Straight Flush
    std::vector<int> tiebreakers;  // descending ranks for tie-breaking
};

enum HandRank {
    HIGH_CARD = 0,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH
};


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


EvaluatedHand evaluateHandDetailed(const std::vector<Card>& hand) {
    std::map<int, int> rankCount;
    std::map<std::string, int> suitCount;
    std::vector<int> ranks;

    for (const auto& card : hand) {
        int rank = getCardRank(card.getValue());
        ranks.push_back(rank);
        rankCount[rank]++;
        suitCount[card.getSuit()]++;
    }

    std::sort(ranks.begin(), ranks.end(), std::greater<int>()); // high to low

    bool isFlush = false;
    for (auto& s : suitCount) {
        if (s.second == 5) {
            isFlush = true;
            break;
        }
    }

    bool isStraight = true;
    for (int i = 0; i < 4; ++i) {
        if (ranks[i] - 1 != ranks[i+1]) {
            isStraight = false;
            break;
        }
    }

    // Special case: A-2-3-4-5
    if (!isStraight && std::set<int>(ranks.begin(), ranks.end()) == std::set<int>{14, 2, 3, 4, 5}) {
        isStraight = true;
        ranks = {5, 4, 3, 2, 1};
    }

    std::vector<int> tiebreakers;

    if (isStraight && isFlush)
        return {"Straight Flush", 8, {ranks[0]}};

    // Collect groups by frequency
    std::vector<std::pair<int, int>> groups;
    for (auto& [rank, count] : rankCount)
        groups.push_back({count, rank});  // {freq, rank}

    std::sort(groups.rbegin(), groups.rend());  // highest freq first

    if (groups[0].first == 4)
        return {"Four of a Kind", 7, {groups[0].second, groups[1].second}};
    if (groups[0].first == 3 && groups[1].first == 2)
        return {"Full House", 6, {groups[0].second, groups[1].second}};
    if (isFlush)
        return {"Flush", 5, ranks};
    if (isStraight)
        return {"Straight", 4, {ranks[0]}};
    if (groups[0].first == 3)
        return {"Three of a Kind", 3, {groups[0].second, groups[1].second, groups[2].second}};
    if (groups[0].first == 2 && groups[1].first == 2)
        return {"Two Pair", 2, {std::max(groups[0].second, groups[1].second), std::min(groups[0].second, groups[1].second), groups[2].second}};
    if (groups[0].first == 2)
        return {"One Pair", 1, {groups[0].second, groups[1].second, groups[2].second, groups[3].second}};
    
    return {"High Card", 0, ranks};
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


EvaluatedHand evaluateTexasHoldEmDetailed(const std::vector<Card>& player, const std::vector<Card>& community) {
    std::vector<Card> all = player;
    all.insert(all.end(), community.begin(), community.end());

    std::vector<std::vector<Card>> combos = getCombinations(all);

    EvaluatedHand best = evaluateHandDetailed(combos[0]);

    for (const auto& combo : combos) {
        EvaluatedHand current = evaluateHandDetailed(combo);

        if (current.rank > best.rank ||
            (current.rank == best.rank && current.tiebreakers > best.tiebreakers)) {
            best = current;
        }
    }

    return best;
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

int compareHands(const std::vector<Card>& p1, const std::vector<Card>& p2, const std::vector<Card>& community) {
    EvaluatedHand h1 = evaluateTexasHoldEmDetailed(p1, community);
    EvaluatedHand h2 = evaluateTexasHoldEmDetailed(p2, community);


    if (h1.rank > h2.rank) return 1;
    if (h2.rank > h1.rank) return 2;

    // Tie-breaker
    if (h1.tiebreakers > h2.tiebreakers) return 1;
    if (h2.tiebreakers > h1.tiebreakers) return 2;

    return 0; // tie
}
