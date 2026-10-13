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

