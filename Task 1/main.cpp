#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>

struct TurnInput {
    int value;
};

class IInputGenerator {
public:
    virtual ~IInputGenerator() = default;
    virtual TurnInput generateInput(int round) = 0;
};

class IScoringRule {
public:
    virtual ~IScoringRule() = default;
    virtual int computeScore(const TurnInput& input) = 0;
};

class IRewardRule {
public:
    virtual ~IRewardRule() = default;
    virtual int computeReward(int baseScore, int round) = 0;
};

class SimpleInputGenerator : public IInputGenerator {
public:
    TurnInput generateInput(int round) override {
        return { round + 2 };
    }
};

class RandomInputGenerator : public IInputGenerator {
public:
    TurnInput generateInput(int round) override {
        int randVal = (std::rand() % 10) + 1;
        return { randVal };
    }
};

class StandardScoringRule : public IScoringRule {
public:
    int computeScore(const TurnInput& input) override {
        return input.value;
    }
};

class ModifiedRewardRule : public IRewardRule {
public:
    int computeReward(int baseScore, int round) override {
        if (round % 2 == 0) {
            return baseScore * 2;
        }
        return baseScore + 2;
    }
};

class ShopSystem {
public:
    void processShop() {
        std::cout << "[SHOP] offered: Bonus (+2) cost 2\n";
        std::cout << "[SHOP] skipped.\n";
    }
};

class RunSession {
private:
    std::shared_ptr<IInputGenerator> inputGenerator;
    std::shared_ptr<IScoringRule> scoringRule;
    std::shared_ptr<IRewardRule> rewardRule;
    ShopSystem shopSystem;
    int money;

public:
    RunSession(std::shared_ptr<IInputGenerator> inputGen,
               std::shared_ptr<IScoringRule> scoring,
               std::shared_ptr<IRewardRule> reward)
        : inputGenerator(inputGen), scoringRule(scoring), rewardRule(reward), money(0) {}

    void startRun() {
        std::cout << "=== RUN START ===\n";
        
        for (int round = 1; round <= 3; ++round) {
            std::cout << "Round " << round << "\n";

            TurnInput input = inputGenerator->generateInput(round);
            std::cout << "[PLAY] input generated: " << input.value << "\n";

            int baseScore = scoringRule->computeScore(input);
            std::cout << "[SCORE] base score: " << baseScore << "\n";

            int rewardGain = rewardRule->computeReward(baseScore, round);

            money += rewardGain;
            std::cout << "[REWARD] gain: " << rewardGain << " money: " << money << "\n";

            shopSystem.processShop();

            std::cout << "\n";
        }

        std::cout << "=== RUN END ===\n";
        std::cout << "Final money: " << money << "\n";
    }
};
// udah nut cek
int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    auto inputGen = std::make_shared<RandomInputGenerator>();
    auto scoringRule = std::make_shared<StandardScoringRule>();
    auto rewardRule = std::make_shared<ModifiedRewardRule>();

    RunSession session(inputGen, scoringRule, rewardRule);
    session.startRun();

    return 0;
}