/**
 * Tower Builder - C++ Game with Data Structures
 *
 * This game demonstrates three fundamental data structures:
 *
 * 1. STACK (tower.h/cpp)
 *    - Used for the tower of blocks
 *    - LIFO (Last In, First Out) structure
 *    - Perfect for stacking blocks on top of each other
 *
 * 2. QUEUE (game.cpp)
 *    - Used for upcoming block preview
 *    - FIFO (First In, First Out) structure
 *    - Shows players what blocks are coming next
 *
 * 3. LINKED LIST (scorehistory.h/cpp)
 *    - Used for game score history
 *    - Dynamic size, O(1) insertion at head
 *    - Tracks all games played with scores and heights
 *
 * How to Play:
 * - Blocks move horizontally across the screen
 * - Press SPACE to drop the block
 * - Stack blocks on top of each other
 * - Overhanging parts get trimmed off
 * - Game ends when you miss completely
 *
 * Controls:
 * - SPACE: Drop block
 * - P: Pause/Unpause
 * - R: Restart (when game over)
 *
 * Educational Purpose:
 * This game is designed to help students understand:
 * - When to use different data structures
 * - Time complexity of operations
 * - Real-world applications of CS concepts
 */

#include "raylib.h"
#include "game.h"

int main() {
    // Window configuration
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Tower Builder - Data Structures Demo");
    SetTargetFPS(60);

    // Create game instance
    Game game;

    // Main game loop
    while (!WindowShouldClose()) {
        // Update game state
        game.Update();

        // Render
        BeginDrawing();
        game.Draw();
        EndDrawing();
    }

    // Cleanup
    CloseWindow();

    return 0;
}
