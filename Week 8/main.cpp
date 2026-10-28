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

class PairChecker : public PokerHandChecker {
public:
    HandRank check(const std::vector<Card>& cards) override {
        for (size_t i = 0; i < cards.size(); ++i) {
            for (size_t j = i + 1; j < cards.size(); ++j) {
                if (cards[i].rank == cards[j].rank) {
                    std::cout << "Detected PAIR\n";
                    return HandRank::PAIR;
                }
            }
        }
        return checkNext(cards);
    }
};

class HandGenerator {
public:
    Hand generateHand() {
        std::cout << "Generating random cards for player...\n";
        Hand hand;
        
        std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
        std::uniform_int_distribution<int> rankDist(2, 14);
        const char suits[] = {'H', 'D', 'C', 'S'};
        std::uniform_int_distribution<int> suitDist(0, 3);

        for (int i = 0; i < 5; ++i) {
            hand.cards.push_back({rankDist(rng), suits[suitDist(rng)]});
            std::cout << "Card [" << i << "]: Rank " << hand.cards.back().rank 
                      << ", Suit " << hand.cards.back().suit << "\n";
        }
        return hand;
    }
};

class HandPlayer {
private:
    ChosenHand chosenHand;
public:
    std::vector<Card> playHand(const Hand& mainHand) {
        std::cout << "Player selects cards to play...\n";
        std::vector<int> selectedIndices = {0, 1, 2, 3, 4}; 
        chosenHand.selectCards(mainHand, selectedIndices);
        return chosenHand.getSelectedCards();
    }
};

class ScoringRule {
private:
    FlushChecker flushChecker;
    PairChecker pairChecker;

    int convertRankToScore(HandRank rank) {
        switch (rank) {
            case HandRank::FLUSH: return 20;
            case HandRank::PAIR: return 10;
            case HandRank::HIGH_CARD:
            default: return 5;
        }
    }

public:
    ScoringRule() {
        flushChecker.setNext(&pairChecker);
    }

    int scoreHand(const std::vector<Card>& playedCards) {
        std::cout << "Calculating hand score...\n";
        HandRank rank = flushChecker.check(playedCards);
        int score = convertRankToScore(rank);
        std::cout << "Final score = " << score << "\n";
        return score;
    }
};

class BlindRule {
public:
    bool checkBlind(int score) {
        std::cout << "Checking blind requirement (Min 10)...\n";
        if (score >= 10) {
            std::cout << "Result: WIN\n";
            return true;
        }
        std::cout << "Result: LOSE\n";
        return false;
    }
};

class RewardRule {
public:
    int earnMoney(bool win, int score) {
        std::cout << "Calculating reward...\n";
        if (win) return score;
        return 0;
    }
};