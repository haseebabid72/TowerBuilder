#ifndef BLOCK_H
#define BLOCK_H

#include "raylib.h"

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

    // Constructor
    Block();
    Block(float x, float y, float width, float height, Color color, float speed = 200.0f);

    // Methods
    void Update(float deltaTime);  // Update position for horizontal movement
    void Draw() const;             // Render the block
    void MoveLeft(float deltaTime);
    void MoveRight(float deltaTime);
    void SetPosition(float x, float y);

    // Utility
    float GetLeft() const;
    float GetRight() const;
    float GetTop() const;
    float GetBottom() const;
};

#endif // BLOCK_H
