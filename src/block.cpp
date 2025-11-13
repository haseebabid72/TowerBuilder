#include "block.h"

Block::Block()
    : rect{0, 0, 0, 0}, color(WHITE), speed(0), isMoving(false) {}

Block::Block(float x, float y, float width, float height, Color color, float speed)
    : rect{x, y, width, height}, color(color), speed(speed), isMoving(true) {}

void Block::Update(float deltaTime) {
    if (isMoving) {
        // Move horizontally back and forth
        rect.x += speed * deltaTime;
    }
}

void Block::Draw() const {
    // Draw the block with a slight border for better visibility
    DrawRectangleRec(rect, color);
    DrawRectangleLinesEx(rect, 2.0f, BLACK);
}

void Block::MoveLeft(float deltaTime) {
    rect.x -= speed * deltaTime;
}

void Block::MoveRight(float deltaTime) {
    rect.x += speed * deltaTime;
}

void Block::SetPosition(float x, float y) {
    rect.x = x;
    rect.y = y;
}

float Block::GetLeft() const {
    return rect.x;
}

float Block::GetRight() const {
    return rect.x + rect.width;
}

float Block::GetTop() const {
    return rect.y;
}

float Block::GetBottom() const {
    return rect.y + rect.height;
}
