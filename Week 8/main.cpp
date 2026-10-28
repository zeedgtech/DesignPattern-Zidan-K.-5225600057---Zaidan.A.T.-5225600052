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