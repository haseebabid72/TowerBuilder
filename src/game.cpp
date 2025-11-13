#include "game.h"
#include <cmath>
#include <sstream>
#include <iomanip>

Game::Game()
    : gameOver(false), isPaused(false), score(0),
      consecutivePerfects(0), blockSpeed(INITIAL_SPEED), direction(1) {
    InitializeGame();
}

Game::~Game() {}

void Game::InitializeGame() {
    tower.Clear();
    score = 0;
    consecutivePerfects = 0;
    blockSpeed = INITIAL_SPEED;
    direction = 1;
    gameOver = false;

    // Create base block (doesn't move, sits at bottom)
    Block baseBlock(
        SCREEN_WIDTH / 2 - INITIAL_BLOCK_WIDTH / 2,
        SCREEN_HEIGHT - 100,
        INITIAL_BLOCK_WIDTH,
        BLOCK_HEIGHT,
        GetBlockColor(0),
        0  // No speed for base block
    );
    baseBlock.isMoving = false;
    tower.Push(baseBlock);  // STACK: Push base block

    // QUEUE: Generate upcoming blocks for preview
    GenerateUpcomingBlocks(3);

    // Spawn first moving block
    SpawnNextBlock();
}

// QUEUE OPERATION: Enqueue - O(1)
// Pre-generate blocks and add them to the queue (FIFO)
void Game::GenerateUpcomingBlocks(int count) {
    for (int i = 0; i < count; i++) {
        float width = tower.IsEmpty() ? INITIAL_BLOCK_WIDTH : tower.Top().rect.width;

        Block newBlock(
            0,  // Start from left
            0,  // Y will be set when spawned
            width,
            BLOCK_HEIGHT,
            GetBlockColor(tower.GetHeight() + blockQueue.size()),
            blockSpeed
        );

        blockQueue.push(newBlock);  // QUEUE: Add to back of queue
    }
}

// QUEUE OPERATION: Dequeue - O(1)
// Get the next block from the queue and spawn it
void Game::SpawnNextBlock() {
    if (blockQueue.empty()) {
        GenerateUpcomingBlocks(1);
    }

    currentBlock = blockQueue.front();  // QUEUE: Get front element (FIFO)
    blockQueue.pop();                   // QUEUE: Remove from front

    // Position the block at the top
    float yPos = SCREEN_HEIGHT - 100 - (tower.GetHeight() * BLOCK_HEIGHT);
    currentBlock.SetPosition(0, yPos);
    currentBlock.isMoving = true;
    currentBlock.speed = blockSpeed;

    // Generate one more block to keep queue filled
    GenerateUpcomingBlocks(1);
}

void Game::Update() {
    if (gameOver) {
        // Press R to restart
        if (IsKeyPressed(KEY_R)) {
            Reset();
        }
        return;
    }

    if (IsKeyPressed(KEY_P)) {
        isPaused = !isPaused;
    }

    if (isPaused) return;

    float deltaTime = GetFrameTime();

    // Update current block movement
    UpdateBlockMovement(deltaTime);

    // Drop block on SPACE press
    if (IsKeyPressed(KEY_SPACE)) {
        DropBlock();
    }
}

void Game::UpdateBlockMovement(float deltaTime) {
    if (!currentBlock.isMoving) return;

    // Move block horizontally
    currentBlock.rect.x += blockSpeed * direction * deltaTime;

    // Bounce at screen edges
    if (currentBlock.GetRight() >= SCREEN_WIDTH) {
        direction = -1;
    } else if (currentBlock.GetLeft() <= 0) {
        direction = 1;
    }
}

void Game::DropBlock() {
    if (!currentBlock.isMoving) return;

    currentBlock.isMoving = false;
    TrimAndStackBlock();
}

void Game::TrimAndStackBlock() {
    if (tower.IsEmpty()) {
        // First block, just add it
        tower.Push(currentBlock);  // STACK: Push
        AddScore(10);
        SpawnNextBlock();
        return;
    }

    // STACK: Peek at top block for comparison
    const Block& topBlock = tower.Top();  // O(1) operation

    float overlapStart, overlapEnd;
    if (!CheckOverlap(currentBlock, topBlock, overlapStart, overlapEnd)) {
        // No overlap - Game Over!
        gameOver = true;
        SaveCurrentScore();  // LINKED LIST: Add to score history
        return;
    }

    // Calculate overlap
    float overlapWidth = overlapEnd - overlapStart;
    float originalWidth = currentBlock.rect.width;

    // Check if overlap is too small (less than 10%)
    if (overlapWidth < originalWidth * 0.1f) {
        gameOver = true;
        SaveCurrentScore();
        return;
    }

    // Create trimmed block
    Block trimmedBlock = currentBlock;
    trimmedBlock.rect.x = overlapStart;
    trimmedBlock.rect.width = overlapWidth;

    // STACK: Push trimmed block onto tower
    tower.Push(trimmedBlock);  // O(1) operation

    // Calculate score based on accuracy
    float accuracy = overlapWidth / originalWidth;
    bool isPerfect = std::abs(overlapWidth - originalWidth) < PERFECT_THRESHOLD;

    if (isPerfect) {
        consecutivePerfects++;
        AddScore(50 + (consecutivePerfects * 10));  // Bonus for combos
    } else {
        consecutivePerfects = 0;
        AddScore(10 + static_cast<int>(accuracy * 10));
    }

    // Increase difficulty
    if (tower.GetHeight() % 5 == 0) {
        blockSpeed += SPEED_INCREMENT;
    }

    // Spawn next block
    SpawnNextBlock();
}

bool Game::CheckOverlap(const Block& current, const Block& below,
                        float& overlapStart, float& overlapEnd) {
    float currentLeft = current.GetLeft();
    float currentRight = current.GetRight();
    float belowLeft = below.GetLeft();
    float belowRight = below.GetRight();

    // Calculate overlap region
    overlapStart = std::max(currentLeft, belowLeft);
    overlapEnd = std::min(currentRight, belowRight);

    return overlapEnd > overlapStart;  // True if there's overlap
}

void Game::Draw() {
    ClearBackground(RAYWHITE);

    // Draw tower (STACK visualization)
    tower.Draw();

    // Draw current moving block
    if (!gameOver) {
        currentBlock.Draw();
    }

    // Draw UI
    DrawUI();

    // Draw next blocks preview (QUEUE visualization)
    DrawNextBlockPreview();

    // Draw instructions
    DrawInstructions();

    if (gameOver) {
        DrawGameOverScreen();
    }

    if (isPaused) {
        DrawText("PAUSED", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 20, 40, RED);
    }
}

void Game::DrawUI() {
    // Score
    DrawText(TextFormat("Score: %d", score), 20, 20, 30, DARKBLUE);

    // Tower height
    DrawText(TextFormat("Height: %d", tower.GetHeight() - 1), 20, 60, 25, DARKGREEN);

    // Best score
    int bestScore = scoreHistory.GetBestScore();
    if (bestScore > 0) {
        DrawText(TextFormat("Best: %d", bestScore), 20, 95, 20, GRAY);
    }

    // Combo indicator
    if (consecutivePerfects > 0) {
        DrawText(TextFormat("PERFECT x%d!", consecutivePerfects),
                 SCREEN_WIDTH / 2 - 80, 100, 25, GOLD);
    }

    // Games played (LINKED LIST size)
    DrawText(TextFormat("Games: %d", scoreHistory.GetCount()),
             SCREEN_WIDTH - 150, 20, 20, GRAY);
}

void Game::DrawGameOverScreen() {
    // Semi-transparent overlay
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.7f));

    // Game Over text
    DrawText("GAME OVER!", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 100, 50, RED);

    // Final score
    DrawText(TextFormat("Final Score: %d", score),
             SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 - 30, 30, WHITE);

    DrawText(TextFormat("Tower Height: %d", tower.GetHeight() - 1),
             SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 + 10, 25, WHITE);

    // Best score
    DrawText(TextFormat("Best Score: %d", scoreHistory.GetBestScore()),
             SCREEN_WIDTH / 2 - 110, SCREEN_HEIGHT / 2 + 45, 25, GOLD);

    // Instructions
    DrawText("Press R to Restart", SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 + 100, 25, LIGHTGRAY);
}

// QUEUE: Visualize upcoming blocks
void Game::DrawNextBlockPreview() {
    DrawText("Next Blocks:", SCREEN_WIDTH - 180, 60, 20, DARKGRAY);

    // We need to peek at the queue without removing elements
    std::queue<Block> tempQueue = blockQueue;  // Copy queue
    int yOffset = 100;

    // Show next 3 blocks in queue (FIFO order)
    for (int i = 0; i < 3 && !tempQueue.empty(); i++) {
        Block previewBlock = tempQueue.front();  // QUEUE: Front element
        tempQueue.pop();                         // Remove to see next

        // Draw small preview
        Rectangle previewRect = {
            SCREEN_WIDTH - 170,
            static_cast<float>(yOffset + i * 40),
            previewBlock.rect.width * 0.4f,  // Scaled down
            BLOCK_HEIGHT * 0.6f
        };

        DrawRectangleRec(previewRect, previewBlock.color);
        DrawRectangleLinesEx(previewRect, 1.0f, BLACK);
    }
}

void Game::DrawInstructions() {
    DrawText("SPACE - Drop Block", 20, SCREEN_HEIGHT - 80, 20, DARKGRAY);
    DrawText("P - Pause", 20, SCREEN_HEIGHT - 50, 20, DARKGRAY);
    DrawText("R - Restart (when game over)", 20, SCREEN_HEIGHT - 20, 18, DARKGRAY);
}

void Game::AddScore(int points) {
    score += points;
}

// LINKED LIST: Save score to history
void Game::SaveCurrentScore() {
    scoreHistory.AddScore(score, tower.GetHeight() - 1);  // O(1) insertion at head
}

void Game::Reset() {
    InitializeGame();
}

Color Game::GetBlockColor(int index) {
    return blockColors[index % 10];
}
