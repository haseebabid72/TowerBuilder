#ifndef GAME_H
#define GAME_H

#include <queue>
#include "raylib.h"
#include "tower.h"
#include "scorehistory.h"

/**
 * Game Class - Main Game Controller
 *
 * Integrates all three data structures:
 * 1. STACK - Tower management (tower.h)
 * 2. QUEUE - Upcoming blocks preview (blockQueue)
 * 3. LINKED LIST - Score history (scoreHistory)
 */
class Game {
private:
    // Data Structures
    Tower tower;                      // STACK: Main tower
    std::queue<Block> blockQueue;     // QUEUE: Upcoming blocks (FIFO)
    ScoreHistory scoreHistory;        // LINKED LIST: Game history

    // Game state
    Block currentBlock;
    bool gameOver;
    bool isPaused;
    int score;
    int consecutivePerfects;          // Combo counter for perfect stacks
    float blockSpeed;                 // Current horizontal speed
    int direction;                    // 1 = right, -1 = left

    // Game constants
    static constexpr float BLOCK_HEIGHT = 30.0f;
    static constexpr float INITIAL_BLOCK_WIDTH = 200.0f;
    static constexpr float INITIAL_SPEED = 150.0f;
    static constexpr float SPEED_INCREMENT = 15.0f;
    static constexpr float SCREEN_WIDTH = 800.0f;
    static constexpr float SCREEN_HEIGHT = 600.0f;
    static constexpr float PERFECT_THRESHOLD = 5.0f;  // Pixels for "perfect" alignment

    // Colors for blocks
    Color blockColors[10] = {
        SKYBLUE, PINK, GOLD, LIME, ORANGE,
        PURPLE, BEIGE, VIOLET, MAROON, DARKBLUE
    };

public:
    Game();
    ~Game();

    void Update();
    void Draw();
    void Reset();

private:
    // Game logic
    void InitializeGame();
    void GenerateUpcomingBlocks(int count = 3);  // QUEUE: Pre-generate blocks
    void SpawnNextBlock();                        // QUEUE: Dequeue and spawn
    void DropBlock();                             // Drop current block onto tower
    bool CheckOverlap(const Block& current, const Block& below, float& overlapStart, float& overlapEnd);
    void TrimAndStackBlock();
    void UpdateBlockMovement(float deltaTime);
    void CheckGameOver();

    // UI helpers
    void DrawUI();
    void DrawGameOverScreen();
    void DrawNextBlockPreview();                  // Show blocks in queue
    void DrawInstructions();

    // Scoring
    void AddScore(int points);
    void SaveCurrentScore();

    // Utility
    Color GetBlockColor(int index);
};

#endif // GAME_H
