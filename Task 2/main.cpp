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
    void UpdateState() {
        cout << "4. Game state updates (Positions, HP, Score).\n";
        frameCount++;
        
        if (frameCount >= 3) {
            gameOver = true;
            cout << "5. Win/Lose condition met. Ending session.\n";
        } else {
            cout << "5. Check win/lose condition: Continuing loop...\n";
        }
    }

    bool IsGameOver() const {
        return gameOver;
    }
};

class GameSession {
private:
    Player player;
    GameSystem system;
    GameState state;

public:
    void StartGame() {
        cout << "=== Game Session Started ===\n";
        while (!state.IsGameOver()) {
            player.PlayerAction();
            system.ResolveSystem();
            state.UpdateState();
            cout << "-----------------------------------\n";
        }
        cout << "=== Game Session Ended ===\n";
    }
};

int main() {
    cout << "=== Game Session Started ===\n";
    
    cout << "=== Game Session Ended ===\n";
    return 0;
}