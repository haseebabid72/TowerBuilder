/**
 * Tower Builder - C++ Game with Data Structures
 * Single-file implementation
 *
 * This game demonstrates three fundamental data structures:
 *
 * 1. STACK - Used for the tower of blocks (LIFO structure)
 * 2. QUEUE - Used for upcoming block preview (FIFO structure)
 * 3. LINKED LIST - Used for game score history (dynamic size)
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
 */

#include "raylib.h"
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

// ============================================================================
// BLOCK STRUCTURE
// ============================================================================

/**
 * Block Structure
 * Represents a single building block in the tower
 * Used in STACK data structure for tower management
 */
struct Block {
    Rectangle rect;      // Position and dimensions (x, y, width, height)
    Color color;         // Block color for visual distinction
    float speed;         // Horizontal movement speed
    bool isMoving;       // Whether block is currently moving horizontally

    // Constructors
    Block() : rect{0, 0, 0, 0}, color(WHITE), speed(0), isMoving(false) {}

    Block(float x, float y, float width, float height, Color color, float speed = 200.0f)
        : rect{x, y, width, height}, color(color), speed(speed), isMoving(true) {}

    // Methods
    void Draw() const {
        DrawRectangleRec(rect, color);
        DrawRectangleLinesEx(rect, 2.0f, BLACK);
    }

    void SetPosition(float x, float y) {
        rect.x = x;
        rect.y = y;
    }

    float GetLeft() const { return rect.x; }
    float GetRight() const { return rect.x + rect.width; }
    float GetTop() const { return rect.y; }
    float GetBottom() const { return rect.y + rect.height; }
};

// ============================================================================
// TOWER CLASS - STACK DATA STRUCTURE
// ============================================================================

/**
 * Tower Class - Demonstrates STACK Data Structure
 *
 * WHY STACK?
 * - Blocks are stacked on top of each other (LIFO - Last In, First Out)
 * - The most recently placed block is at the top
 * - We only interact with the top block for comparison
 * - Natural fit for a tower building game
 *
 * Time Complexity:
 * - Push: O(1) - Add block to top
 * - Pop: O(1) - Remove block from top
 * - Peek: O(1) - View top block
 */
class Tower {
private:
    std::stack<Block> towerStack;  // STACK: Core data structure for tower
    int height;                     // Number of blocks in tower

public:
    Tower() : height(0) {}

    // STACK OPERATION: Push - O(1)
    void Push(const Block& block) {
        towerStack.push(block);  // LIFO: Last block in is on top
        height++;
    }

    // STACK OPERATION: Pop - O(1)
    void Pop() {
        if (!towerStack.empty()) {
            towerStack.pop();
            height--;
        }
    }

    // STACK OPERATION: Top - O(1)
    Block& Top() { return towerStack.top(); }
    const Block& Top() const { return towerStack.top(); }

    // STACK OPERATION: IsEmpty - O(1)
    bool IsEmpty() const { return towerStack.empty(); }

    int GetHeight() const { return height; }

    // Draw all blocks in the tower
    void Draw() const {
        if (towerStack.empty()) return;

        // Copy stack to vector for drawing
        std::vector<Block> blocks;
        std::stack<Block> tempStack = towerStack;

        while (!tempStack.empty()) {
            blocks.push_back(tempStack.top());
            tempStack.pop();
        }

        // Draw blocks from bottom to top
        for (int i = blocks.size() - 1; i >= 0; i--) {
            blocks[i].Draw();
        }
    }

    void Clear() {
        while (!towerStack.empty()) {
            towerStack.pop();
        }
        height = 0;
    }
};

// ============================================================================
// SCORE HISTORY - LINKED LIST DATA STRUCTURE
// ============================================================================

/**
 * Score Node - Building block of Linked List
 *
 * WHY LINKED LIST?
 * - Dynamic size - don't need to pre-allocate array
 * - Easy insertion at head - O(1)
 * - Memory efficient for keeping game history
 */
struct ScoreNode {
    int score;              // Points earned in this game
    int height;             // Tower height achieved
    ScoreNode* next;        // Pointer to next node (LINKED LIST concept)

    ScoreNode(int s, int h) : score(s), height(h), next(nullptr) {}
};

/**
 * ScoreHistory Class - Demonstrates LINKED LIST Data Structure
 *
 * Time Complexity:
 * - Insert at head: O(1)
 * - Get top N scores: O(n)
 * - Clear all: O(n)
 */
class ScoreHistory {
private:
    ScoreNode* head;        // LINKED LIST: Head pointer
    int count;              // Number of games played

    // LINKED LIST: Free all allocated memory - O(n)
    void DeleteList() {
        ScoreNode* current = head;
        while (current != nullptr) {
            ScoreNode* next = current->next;
            delete current;
            current = next;
        }
    }

public:
    ScoreHistory() : head(nullptr), count(0) {}

    ~ScoreHistory() { DeleteList(); }

    // LINKED LIST OPERATION: Insert at Head - O(1)
    void AddScore(int score, int height) {
        ScoreNode* newNode = new ScoreNode(score, height);
        newNode->next = head;  // New node points to old head
        head = newNode;        // Head now points to new node
        count++;
    }

    // Find the best score by traversing the list - O(n)
    int GetBestScore() const {
        if (head == nullptr) return 0;

        int best = 0;
        ScoreNode* current = head;

        // LINKED LIST TRAVERSAL: Follow next pointers
        while (current != nullptr) {
            if (current->score > best) {
                best = current->score;
            }
            current = current->next;  // Move to next node
        }

        return best;
    }

    // Find the best height by traversing the list - O(n)
    int GetBestHeight() const {
        if (head == nullptr) return 0;

        int best = 0;
        ScoreNode* current = head;

        while (current != nullptr) {
            if (current->height > best) {
                best = current->height;
            }
            current = current->next;
        }

        return best;
    }

    int GetCount() const { return count; }

    void Clear() {
        DeleteList();
        head = nullptr;
        count = 0;
    }
};

// ============================================================================
// GAME CLASS - INTEGRATES ALL DATA STRUCTURES
// ============================================================================

/**
 * Game Class - Main Game Controller
 *
 * Integrates all three data structures:
 * 1. STACK - Tower management
 * 2. QUEUE - Upcoming blocks preview
 * 3. LINKED LIST - Score history
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
    int consecutivePerfects;
    float blockSpeed;
    int direction;  // 1 = right, -1 = left

    // Game constants
    static constexpr float BLOCK_HEIGHT = 30.0f;
    static constexpr float INITIAL_BLOCK_WIDTH = 200.0f;
    static constexpr float INITIAL_SPEED = 150.0f;
    static constexpr float SPEED_INCREMENT = 15.0f;
    static constexpr float SCREEN_WIDTH = 800.0f;
    static constexpr float SCREEN_HEIGHT = 600.0f;
    static constexpr float PERFECT_THRESHOLD = 5.0f;

    Color blockColors[10] = {
        SKYBLUE, PINK, GOLD, LIME, ORANGE,
        PURPLE, BEIGE, VIOLET, MAROON, DARKBLUE
    };

    Color GetBlockColor(int index) {
        return blockColors[index % 10];
    }

    // QUEUE OPERATION: Enqueue - O(1)
    void GenerateUpcomingBlocks(int count = 3) {
        for (int i = 0; i < count; i++) {
            float width = tower.IsEmpty() ? INITIAL_BLOCK_WIDTH : tower.Top().rect.width;

            Block newBlock(
                0, 0, width, BLOCK_HEIGHT,
                GetBlockColor(tower.GetHeight() + blockQueue.size()),
                blockSpeed
            );

            blockQueue.push(newBlock);  // QUEUE: Add to back of queue
        }
    }

    // QUEUE OPERATION: Dequeue - O(1)
    void SpawnNextBlock() {
        if (blockQueue.empty()) {
            GenerateUpcomingBlocks(1);
        }

        currentBlock = blockQueue.front();  // QUEUE: Get front element (FIFO)
        blockQueue.pop();                   // QUEUE: Remove from front

        float yPos = SCREEN_HEIGHT - 100 - (tower.GetHeight() * BLOCK_HEIGHT);
        currentBlock.SetPosition(0, yPos);
        currentBlock.isMoving = true;
        currentBlock.speed = blockSpeed;

        GenerateUpcomingBlocks(1);
    }

    void UpdateBlockMovement(float deltaTime) {
        if (!currentBlock.isMoving) return;

        currentBlock.rect.x += blockSpeed * direction * deltaTime;

        if (currentBlock.GetRight() >= SCREEN_WIDTH) {
            direction = -1;
        } else if (currentBlock.GetLeft() <= 0) {
            direction = 1;
        }
    }

    bool CheckOverlap(const Block& current, const Block& below,
                      float& overlapStart, float& overlapEnd) {
        float currentLeft = current.GetLeft();
        float currentRight = current.GetRight();
        float belowLeft = below.GetLeft();
        float belowRight = below.GetRight();

        overlapStart = std::max(currentLeft, belowLeft);
        overlapEnd = std::min(currentRight, belowRight);

        return overlapEnd > overlapStart;
    }

    void TrimAndStackBlock() {
        if (tower.IsEmpty()) {
            tower.Push(currentBlock);  // STACK: Push
            score += 10;
            SpawnNextBlock();
            return;
        }

        // STACK: Peek at top block for comparison
        const Block& topBlock = tower.Top();  // O(1) operation

        float overlapStart, overlapEnd;
        if (!CheckOverlap(currentBlock, topBlock, overlapStart, overlapEnd)) {
            gameOver = true;
            scoreHistory.AddScore(score, tower.GetHeight() - 1);  // LINKED LIST: Add to history
            return;
        }

        float overlapWidth = overlapEnd - overlapStart;
        float originalWidth = currentBlock.rect.width;

        if (overlapWidth < originalWidth * 0.1f) {
            gameOver = true;
            scoreHistory.AddScore(score, tower.GetHeight() - 1);
            return;
        }

        // Create trimmed block
        Block trimmedBlock = currentBlock;
        trimmedBlock.rect.x = overlapStart;
        trimmedBlock.rect.width = overlapWidth;

        // STACK: Push trimmed block onto tower
        tower.Push(trimmedBlock);  // O(1) operation

        // Calculate score
        float accuracy = overlapWidth / originalWidth;
        bool isPerfect = std::abs(overlapWidth - originalWidth) < PERFECT_THRESHOLD;

        if (isPerfect) {
            consecutivePerfects++;
            score += 50 + (consecutivePerfects * 10);
        } else {
            consecutivePerfects = 0;
            score += 10 + static_cast<int>(accuracy * 10);
        }

        // Increase difficulty
        if (tower.GetHeight() % 5 == 0) {
            blockSpeed += SPEED_INCREMENT;
        }

        SpawnNextBlock();
    }

    void DropBlock() {
        if (!currentBlock.isMoving) return;
        currentBlock.isMoving = false;
        TrimAndStackBlock();
    }

    void DrawUI() {
        DrawText(TextFormat("Score: %d", score), 20, 20, 30, DARKBLUE);
        DrawText(TextFormat("Height: %d", tower.GetHeight() - 1), 20, 60, 25, DARKGREEN);

        int bestScore = scoreHistory.GetBestScore();
        if (bestScore > 0) {
            DrawText(TextFormat("Best: %d", bestScore), 20, 95, 20, GRAY);
        }

        if (consecutivePerfects > 0) {
            DrawText(TextFormat("PERFECT x%d!", consecutivePerfects),
                     SCREEN_WIDTH / 2 - 80, 100, 25, GOLD);
        }

        DrawText(TextFormat("Games: %d", scoreHistory.GetCount()),
                 SCREEN_WIDTH - 150, 20, 20, GRAY);
    }

    void DrawGameOverScreen() {
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.7f));
        DrawText("GAME OVER!", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 100, 50, RED);
        DrawText(TextFormat("Final Score: %d", score),
                 SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 - 30, 30, WHITE);
        DrawText(TextFormat("Tower Height: %d", tower.GetHeight() - 1),
                 SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 + 10, 25, WHITE);
        DrawText(TextFormat("Best Score: %d", scoreHistory.GetBestScore()),
                 SCREEN_WIDTH / 2 - 110, SCREEN_HEIGHT / 2 + 45, 25, GOLD);
        DrawText("Press R to Restart", SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 + 100, 25, LIGHTGRAY);
    }

    // QUEUE: Visualize upcoming blocks
    void DrawNextBlockPreview() {
        DrawText("Next Blocks:", SCREEN_WIDTH - 180, 60, 20, DARKGRAY);

        std::queue<Block> tempQueue = blockQueue;
        int yOffset = 100;

        for (int i = 0; i < 3 && !tempQueue.empty(); i++) {
            Block previewBlock = tempQueue.front();
            tempQueue.pop();

            Rectangle previewRect = {
                SCREEN_WIDTH - 170,
                static_cast<float>(yOffset + i * 40),
                previewBlock.rect.width * 0.4f,
                BLOCK_HEIGHT * 0.6f
            };

            DrawRectangleRec(previewRect, previewBlock.color);
            DrawRectangleLinesEx(previewRect, 1.0f, BLACK);
        }
    }

    void DrawInstructions() {
        DrawText("SPACE - Drop Block", 20, SCREEN_HEIGHT - 80, 20, DARKGRAY);
        DrawText("P - Pause", 20, SCREEN_HEIGHT - 50, 20, DARKGRAY);
        DrawText("R - Restart (when game over)", 20, SCREEN_HEIGHT - 20, 18, DARKGRAY);
    }

public:
    Game() : gameOver(false), isPaused(false), score(0),
             consecutivePerfects(0), blockSpeed(INITIAL_SPEED), direction(1) {
        InitializeGame();
    }

    void InitializeGame() {
        tower.Clear();
        score = 0;
        consecutivePerfects = 0;
        blockSpeed = INITIAL_SPEED;
        direction = 1;
        gameOver = false;

        // Create base block
        Block baseBlock(
            SCREEN_WIDTH / 2 - INITIAL_BLOCK_WIDTH / 2,
            SCREEN_HEIGHT - 100,
            INITIAL_BLOCK_WIDTH,
            BLOCK_HEIGHT,
            GetBlockColor(0),
            0
        );
        baseBlock.isMoving = false;
        tower.Push(baseBlock);  // STACK: Push base block

        // QUEUE: Generate upcoming blocks
        GenerateUpcomingBlocks(3);
        SpawnNextBlock();
    }

    void Update() {
        if (gameOver) {
            if (IsKeyPressed(KEY_R)) {
                InitializeGame();
            }
            return;
        }

        if (IsKeyPressed(KEY_P)) {
            isPaused = !isPaused;
        }

        if (isPaused) return;

        float deltaTime = GetFrameTime();
        UpdateBlockMovement(deltaTime);

        if (IsKeyPressed(KEY_SPACE)) {
            DropBlock();
        }
    }

    void Draw() {
        ClearBackground(RAYWHITE);

        tower.Draw();           // Draw STACK

        if (!gameOver) {
            currentBlock.Draw();
        }

        DrawUI();
        DrawNextBlockPreview();  // Draw QUEUE preview
        DrawInstructions();

        if (gameOver) {
            DrawGameOverScreen();
        }

        if (isPaused) {
            DrawText("PAUSED", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 20, 40, RED);
        }
    }
};

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Tower Builder - Data Structures Demo");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) {
        game.Update();

        BeginDrawing();
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
