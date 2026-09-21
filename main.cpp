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