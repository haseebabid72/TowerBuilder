#include "tower.h"
#include <vector>

Tower::Tower() : height(0) {}

// STACK OPERATION: Push - O(1)
// Adds a new block to the top of the tower
void Tower::Push(const Block& block) {
    towerStack.push(block);  // LIFO: Last block in is on top
    height++;
}

// STACK OPERATION: Pop - O(1)
// Removes the top block (useful for undo feature)
void Tower::Pop() {
    if (!towerStack.empty()) {
        towerStack.pop();  // Remove from top
        height--;
    }
}

// STACK OPERATION: Top - O(1)
// Returns reference to the top block without removing it
Block& Tower::Top() {
    return towerStack.top();  // Access top element
}

const Block& Tower::Top() const {
    return towerStack.top();
}

// STACK OPERATION: IsEmpty - O(1)
// Checks if the tower has any blocks
bool Tower::IsEmpty() const {
    return towerStack.empty();
}

// Get the height (number of blocks) in the tower
int Tower::GetHeight() const {
    return height;
}

// Draw all blocks in the tower
// Note: We need to copy the stack to iterate through it
void Tower::Draw() const {
    if (towerStack.empty()) return;

    // Copy stack to vector for drawing (stacks don't support iteration)
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

// Clear all blocks from the tower
void Tower::Clear() {
    while (!towerStack.empty()) {
        towerStack.pop();
    }
    height = 0;
}

// Helper method to get a copy of the stack
std::stack<Block> Tower::GetStackCopy() const {
    return towerStack;
}
