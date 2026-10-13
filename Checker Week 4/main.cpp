#include <iostream>

enum class HandRank {
    HIGH_CARD,
    PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE
};

struct Hand {
    int value = 0;
};

class PokerHandChecker {
public:
    virtual HandRank check(const Hand& hand) = 0;
    void setNext(PokerHandChecker* next) {
        nextChecker = next;
    }
protected:
    PokerHandChecker* nextChecker = nullptr;
};

class FullHouseChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (hand.value == 7) {
            std::cout << "Detected FULL HOUSE\n";
            return HandRank::FULL_HOUSE;
        }
        if (nextChecker) return nextChecker->check(hand);
        return HandRank::HIGH_CARD;
    }
};

class FlushChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (hand.value == 6) {
            std::cout << "Detected FLUSH\n";
            return HandRank::FLUSH;
        }
        if (nextChecker) return nextChecker->check(hand);
        return HandRank::HIGH_CARD;
    }
};


class StraightChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (hand.value == 5) {
            std::cout << "Detected STRAIGHT\n";
            return HandRank::STRAIGHT;
        }
        if (nextChecker) return nextChecker->check(hand);
        return HandRank::HIGH_CARD;
    }
};

class PairChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (hand.value == 2) {
            std::cout << "Detected PAIR\n";
            return HandRank::PAIR;
        }
        if (nextChecker) return nextChecker->check(hand);
        return HandRank::HIGH_CARD;
    }
};

class HandGenerator {
public:
    Hand generateHand() {
        std::cout << "Generating cards for player...\n";
        Hand hand;
        hand.value = 5;
        return hand;
    }
};

class HandPlayer {
public:
    void playHand() {
        std::cout << "Player selects cards to play...\n";
    }
};

class ScoringRule {
private:
    FullHouseChecker fullHouseChecker;
    FlushChecker flushChecker;
    StraightChecker straightChecker;
    PairChecker pairChecker;

    int convertRankToScore(HandRank rank) {
        switch (rank) {
            case HandRank::FULL_HOUSE: return 25;
            case HandRank::FLUSH: return 20;
            case HandRank::STRAIGHT: return 15;
            case HandRank::PAIR: return 10;
            case HandRank::HIGH_CARD:
            default: return 5;
        }
    }

public:
    ScoringRule() {
        fullHouseChecker.setNext(&flushChecker);
        flushChecker.setNext(&straightChecker);
        straightChecker.setNext(&pairChecker);
    }

    int scoreHand(const Hand& hand) {
        std::cout << "Calculating hand score...\n";
        HandRank rank = fullHouseChecker.check(hand);
        int score = convertRankToScore(rank);
        std::cout << "Final score = " << score << "\n";
        return score;
    }
};

class BlindRule {
public:
    bool checkBlind(int score) {
        std::cout << "Checking blind requirement...\n";
        if (score >= 5) {
            std::cout << "Result: WIN\n";
            return true;
        }
        std::cout << "Result: LOSE\n";
        return false;
    }
};

