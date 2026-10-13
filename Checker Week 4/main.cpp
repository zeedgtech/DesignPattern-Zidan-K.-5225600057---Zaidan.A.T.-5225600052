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