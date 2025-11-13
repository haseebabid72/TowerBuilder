# 🏗️ Tower Builder - Data Structures Game

A fun and educational stacking game built with C++ and raylib that demonstrates fundamental data structures in action!

![Game Screenshot](https://img.shields.io/badge/Language-C%2B%2B17-blue)
![Build System](https://img.shields.io/badge/Build-CMake-green)
![Graphics](https://img.shields.io/badge/Graphics-raylib-red)

## 🎮 Game Description

Tower Builder is a simple yet addictive stacking game where blocks move horizontally across the screen. Your goal is to stop each block at the perfect moment to stack it on top of the previous one. The overhanging parts get trimmed off, making each new block narrower. The game ends when you miss completely!

**But here's the educational twist**: This game isn't just fun—it's a practical demonstration of three fundamental data structures used in computer science!

## 📚 Data Structures Implemented

### 1. **STACK** - Tower Management
**Implementation**: Lines 75-145 in `src/game.cpp`

The tower of blocks is implemented using a **Stack** data structure.

```cpp
std::stack<Block> towerStack;
```

**Why Stack?**
- Blocks stack on top of each other (LIFO - Last In, First Out)
- The most recently placed block is always at the top
- We only need to interact with the top block for comparison
- Perfect natural fit for a tower!

**Operations Used**:
- `push()` - O(1) - Add new block to top
- `top()` - O(1) - Get reference to top block
- `pop()` - O(1) - Remove top block (for undo feature)
- `empty()` - O(1) - Check if tower is empty

**Real-world Applications**:
- Function call stack in programming
- Undo/Redo functionality
- Browser history (back button)
- Expression evaluation

### 2. **QUEUE** - Upcoming Blocks Preview
**Implementation**: Lines 260-322 in `src/game.cpp`

Upcoming blocks are pre-generated and stored in a **Queue**.

```cpp
std::queue<Block> blockQueue;
```

**Why Queue?**
- Fair ordering - blocks spawn in the order they were generated (FIFO - First In, First Out)
- Players can see what's coming next
- Smooth gameplay without random surprises

**Operations Used**:
- `push()` - O(1) - Add new block to back of queue
- `front()` - O(1) - View next block without removing
- `pop()` - O(1) - Remove block from front when spawning

**Real-world Applications**:
- Print job scheduling
- Task queues in operating systems
- Breadth-First Search (BFS)
- Request handling in web servers

### 3. **LINKED LIST** - Score History
**Implementation**: Lines 150-245 in `src/game.cpp`

Game scores are tracked using a custom **Singly Linked List**.

```cpp
struct ScoreNode {
    int score;
    int height;
    ScoreNode* next;  // Pointer to next node
};
```

**Why Linked List?**
- Dynamic size - no need to pre-allocate array
- O(1) insertion at head for new scores
- Memory efficient for keeping game history
- Easy to traverse for finding best scores

**Operations Used**:
- Insert at head - O(1)
- Traverse - O(n)
- Find best score - O(n)

**Real-world Applications**:
- Music playlists
- Browser history (forward/backward navigation)
- Image viewer (previous/next)
- Undo/Redo with more complex operations

## 🎯 Gameplay Features

### Core Mechanics
- ✅ Smooth horizontal block movement
- ✅ Precise drop mechanics with SPACE key
- ✅ Automatic trimming of overhanging blocks
- ✅ Game over on complete miss
- ✅ Score tracking with combos

### Scoring System
- **+10 points** for each successful stack
- **+50 points** for perfect alignment
- **Combo bonus**: +10 extra points per consecutive perfect stack
- **Game over** when overlap is less than 10% of block width

### Visual Feedback
- 🟦 Colorful blocks with rotating color palette
- ⭐ "PERFECT x[combo]!" indicator for perfect stacks
- 📊 Real-time score and height display
- 👀 Next 3 blocks preview (Queue visualization)
- 🎮 Clean, minimalist UI

### Difficulty Progression
- Speed increases every 5 blocks
- Blocks get progressively narrower as you trim them
- Requires increasing precision as game progresses

## 🛠️ Technical Details

### Tech Stack
- **Language**: C++17
- **Graphics Library**: raylib 5.0
- **Build System**: CMake 3.11+
- **Platform**: Cross-platform (Windows, macOS, Linux)

### Project Structure
```
TowerBuilder/
├── src/
│   └── game.cpp              # Single-file implementation (all code)
│                              # Contains: Block, Tower (STACK),
│                              # ScoreHistory (LINKED LIST), Game, main()
├── assets/
│   ├── sprites/              # Block textures (optional)
│   ├── sounds/               # Sound effects (optional)
│   └── fonts/                # Custom fonts (optional)
├── CMakeLists.txt            # Build configuration
└── README.md                 # This file
```

**Single-File Design**: All code is contained in one `game.cpp` file (~570 lines) for simplicity and ease of understanding. Perfect for learning!

### Code Statistics
- **Total Lines**: ~570 lines
- **Source Files**: 1 (game.cpp)
- **Data Structures**: 3 (Stack, Queue, Linked List)
- **Classes**: 3 (Block, Tower, ScoreHistory, Game)

## 🚀 Building and Running

### Prerequisites
- CMake 3.11 or higher
- C++17 compatible compiler (GCC, Clang, MSVC)
- Git (for cloning)

### Build Instructions

#### Linux / macOS
```bash
# Clone the repository
git clone https://github.com/haseebabid72/TowerBuilder.git
cd TowerBuilder

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build
cmake --build .

# Run
./bin/TowerBuilder
```

#### Windows (Visual Studio)
```bash
# Clone the repository
git clone https://github.com/haseebabid72/TowerBuilder.git
cd TowerBuilder

# Create build directory
mkdir build
cd build

# Configure for Visual Studio
cmake ..

# Build
cmake --build . --config Release

# Run
.\bin\Release\TowerBuilder.exe
```

#### Windows (MinGW)
```bash
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
.\bin\TowerBuilder.exe
```

## 🎮 Controls

| Key | Action |
|-----|--------|
| `SPACE` | Drop the current block |
| `P` | Pause/Unpause the game |
| `R` | Restart game (when game over) |
| `ESC` | Quit game |

## 📖 Educational Value

This project is perfect for:

### 🎓 Computer Science Students
- See data structures in a real, interactive application
- Understand when to use Stack vs Queue vs Linked List
- Learn about time complexity through practical examples
- Study clean, well-commented C++ code

### 👨‍🏫 Educators
- Use as a teaching aid for data structures course
- Demonstrate abstract concepts in a visual way
- Show students that CS concepts power real applications
- Provide as a starter project for students to modify

### 💻 Beginner Programmers
- Learn C++17 features
- Understand game loop architecture
- See how to structure a medium-sized project
- Practice reading and understanding existing code

## 🔧 Extending the Game

Want to add more features? Here are some ideas:

### Easy
- [ ] Add sound effects (block drop, game over, perfect stack)
- [ ] Customize block colors
- [ ] Add background music
- [ ] Change block textures

### Medium
- [ ] Implement high score persistence (save to file)
- [ ] Add power-ups (wider blocks, slower speed)
- [ ] Create different difficulty modes
- [ ] Add particle effects for perfect stacks

### Advanced
- [ ] Implement undo feature (pop from stack)
- [ ] Add multiplayer mode
- [ ] Create level system with goals
- [ ] Integrate more data structures (hash map for achievements, BST for sorted scores)

## 📝 Code Highlights

### Stack Usage Example
```cpp
// From game.cpp - Tower class
void Tower::Push(const Block& block) {
    towerStack.push(block);  // O(1) - Add to top
    height++;
}

const Block& Tower::Top() const {
    return towerStack.top();  // O(1) - Peek at top
}
```

### Queue Usage Example
```cpp
// From game.cpp - Game class
void Game::SpawnNextBlock() {
    currentBlock = blockQueue.front();  // FIFO: Get first
    blockQueue.pop();                   // Remove from queue
    blockQueue.push(generateBlock());   // Add new to back
}
```

### Linked List Usage Example
```cpp
// From game.cpp - ScoreHistory class
void ScoreHistory::AddScore(int score, int height) {
    ScoreNode* newNode = new ScoreNode(score, height);
    newNode->next = head;  // Point to old head
    head = newNode;        // New node becomes head (O(1))
}
```

## 🙏 Credits

- **Original Inspiration**: [tower_game by iamkun](https://github.com/iamkun/tower_game)
- **Graphics Library**: [raylib by Ramon Santamaria](https://www.raylib.com/)
- **Data Structures Concept**: Educational integration by this project

## 📄 License

This project is open source and available under the MIT License.

## 🤝 Contributing

Contributions, issues, and feature requests are welcome!

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📧 Contact

For questions or suggestions, please open an issue on GitHub.

---

**Happy Stacking! 🏗️**

*Remember: In programming and in this game, a solid foundation is everything!*
