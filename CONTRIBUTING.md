# Contributing to Tower Builder

Thank you for your interest in contributing to Tower Builder! This document provides guidelines and information for contributors.

## 🎯 Project Goals

This project has two main goals:
1. **Educational**: Demonstrate data structures (Stack, Queue, Linked List) in a fun, practical way
2. **Playable**: Create an enjoyable game that people actually want to play

When contributing, please keep both goals in mind!

## 🚀 How to Contribute

### Reporting Bugs

If you find a bug, please open an issue with:
- Clear description of the problem
- Steps to reproduce
- Expected vs actual behavior
- Your operating system and compiler version
- Any relevant error messages or screenshots

### Suggesting Features

We welcome feature suggestions! Please open an issue with:
- Clear description of the feature
- Why it would be valuable (educational or gameplay-wise)
- How it might be implemented (optional)

### Code Contributions

1. **Fork the repository**
2. **Create a feature branch**
   ```bash
   git checkout -b feature/your-feature-name
   ```
3. **Make your changes**
   - Follow the coding style (see below)
   - Add comments explaining data structure usage
   - Test your changes thoroughly
4. **Commit your changes**
   ```bash
   git commit -m "Add feature: your feature description"
   ```
5. **Push to your fork**
   ```bash
   git push origin feature/your-feature-name
   ```
6. **Open a Pull Request**

## 💻 Coding Style

### General Guidelines
- Use C++17 features appropriately
- Follow clear, descriptive naming conventions
- Add comments for complex logic
- **Always comment data structure operations** (this is educational!)

### Naming Conventions
```cpp
// Classes: PascalCase
class GameController { };

// Functions: PascalCase
void UpdateGameState();

// Variables: camelCase
int currentScore;

// Constants: UPPER_SNAKE_CASE
const int MAX_BLOCKS = 100;

// Private members: camelCase with no prefix
class Example {
private:
    int memberVariable;  // Not m_memberVariable
};
```

### Comment Data Structure Operations
This is crucial for educational value!

```cpp
// GOOD: Explains the data structure concept
tower.Push(block);  // STACK: O(1) - Add block to top of tower

// BAD: Just states what the code does
tower.Push(block);  // Push block
```

### Code Formatting
- Indent with 4 spaces (no tabs)
- Opening braces on same line for functions/classes
- Clear spacing between logical sections
- Maximum line length: 100 characters

Example:
```cpp
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
```

## 🎨 Feature Ideas

### Good for Beginners
- [ ] Add sound effects
- [ ] Create custom block textures
- [ ] Add background music
- [ ] Improve color schemes
- [ ] Add visual effects (particles, animations)

### Intermediate
- [ ] Implement save/load for high scores
- [ ] Add difficulty selection (Easy/Medium/Hard)
- [ ] Create achievement system
- [ ] Add multiple block themes
- [ ] Implement tutorial mode

### Advanced
- [ ] Add multiplayer mode
- [ ] Integrate additional data structures:
  - Hash map for achievements
  - Binary search tree for sorted leaderboard
  - Priority queue for special blocks
- [ ] Create level system with goals
- [ ] Add physics-based block wobbling
- [ ] Implement replay system

## 📚 Educational Enhancements

If you're adding new data structures:
1. **Create a separate class** (like Tower, ScoreHistory)
2. **Comment extensively** - explain WHY this data structure
3. **Document time complexity** - O(1), O(n), etc.
4. **Add to README** - update the data structures section
5. **Include real-world applications** - help students understand

Example template for new data structure:
```cpp
/**
 * ClassName - Demonstrates [DATA STRUCTURE NAME]
 *
 * WHY [DATA STRUCTURE]?
 * - Reason 1
 * - Reason 2
 * - Natural fit for [use case]
 *
 * Time Complexity:
 * - Operation1: O(1) - Description
 * - Operation2: O(n) - Description
 */
class ClassName {
    // Implementation
};
```

## 🧪 Testing

Before submitting a PR:
1. **Build on your platform**
   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```
2. **Test gameplay** - play at least one full game
3. **Check for memory leaks** (if you added dynamic allocation)
4. **Verify cross-platform** (if possible)

## 📝 Documentation

If you change functionality:
- Update README.md
- Update code comments
- Add explanatory comments for complex code
- Update this CONTRIBUTING.md if needed

## ❓ Questions?

Feel free to:
- Open an issue with the "question" label
- Start a discussion in GitHub Discussions
- Comment on existing issues/PRs

## 🎓 Learning Resources

If you're new to the technologies used:

### C++
- [LearnCpp.com](https://www.learncpp.com/)
- [C++ Reference](https://en.cppreference.com/)

### Data Structures
- [VisuAlgo](https://visualgo.net/) - Visualize data structures
- [GeeksforGeeks Data Structures](https://www.geeksforgeeks.org/data-structures/)

### raylib
- [raylib Cheatsheet](https://www.raylib.com/cheatsheet/cheatsheet.html)
- [raylib Examples](https://www.raylib.com/examples.html)

### CMake
- [CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/)

## 📜 Code of Conduct

- Be respectful and constructive
- Help newcomers learn
- Focus on education and fun
- Credit others' work appropriately

## 🙏 Thank You!

Every contribution helps make this project better for learners and players alike. Whether you're fixing a typo or adding a major feature, your effort is appreciated!

Happy coding! 🏗️
