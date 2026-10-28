#include <iostream>
#include <vector>
#include <random>
#include <ctime>

struct Card {
    int rank;
    char suit;
};

struct Hand {
    std::vector<Card> cards;
};

enum class HandRank {
    HIGH_CARD,
    PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE
};

class ChosenHand {
private:
    std::vector<Card> selectedCards;
public:
    void selectCards(const Hand& mainHand, const std::vector<int>& indices) {
        selectedCards.clear();
        for (int index : indices) {
            if (index >= 0 && index < mainHand.cards.size()) {
                selectedCards.push_back(mainHand.cards[index]);
            }
        }
    }
    std::vector<Card> getSelectedCards() const {
        return selectedCards;
    }
};

class PokerHandChecker {
protected:
    PokerHandChecker* nextChecker = nullptr;
public:
    virtual ~PokerHandChecker() = default;
    virtual HandRank check(const std::vector<Card>& cards) = 0;
    
    void setNext(PokerHandChecker* next) {
        nextChecker = next;
    }
    
    HandRank checkNext(const std::vector<Card>& cards) {
        if (nextChecker) return nextChecker->check(cards);
        return HandRank::HIGH_CARD;
    }
};

class FlushChecker : public PokerHandChecker {
public:
    HandRank check(const std::vector<Card>& cards) override {
        if (cards.size() >= 5) {
            char firstSuit = cards[0].suit;
            bool isFlush = true;
            for (const auto& card : cards) {
                if (card.suit != firstSuit) {
                    isFlush = false;
                    break;
                }
            }
            if (isFlush) {
                std::cout << "Detected FLUSH\n";
                return HandRank::FLUSH;
            }
        }
        return checkNext(cards);
    }
};

