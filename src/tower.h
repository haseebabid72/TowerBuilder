#ifndef TOWER_H
#define TOWER_H

#include <stack>
#include "block.h"

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
    Tower();

    // STACK Operations
    void Push(const Block& block);     // O(1) - Add block to top of tower
    void Pop();                        // O(1) - Remove top block (undo feature)
    Block& Top();                      // O(1) - Get reference to top block
    const Block& Top() const;          // O(1) - Get const reference to top block
    bool IsEmpty() const;              // O(1) - Check if tower is empty
    int GetHeight() const;             // O(1) - Get number of blocks

    // Game-specific methods
    void Draw() const;                 // Draw all blocks in the tower
    void Clear();                      // Remove all blocks

    // Helper to iterate through stack for drawing
    std::stack<Block> GetStackCopy() const;
};

#endif // TOWER_H
