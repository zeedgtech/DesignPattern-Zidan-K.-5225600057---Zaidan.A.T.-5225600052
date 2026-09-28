#include <iostream>

using namespace std;


class Player {
public:
    void PlayerAction() {
        cout << "1. Player inputs movement / action.\n";
    }
};


class GameSystem {
public:
    void ResolveSystem() {
        cout << "2. System evaluates collisions and actions.\n";
        cout << "3. Reward, damage, or score is calculated.\n";
    }
};


class GameState {
private:
    bool gameOver = false;
    int frameCount = 0;

public:
    bool IsGameOver() const {
        return gameOver;
    }
};

int main() {
    cout << "=== Game Session Started ===\n";
    
    cout << "=== Game Session Ended ===\n";
    return 0;
}