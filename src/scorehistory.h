#ifndef SCOREHISTORY_H
#define SCOREHISTORY_H

#include <string>

/**
 * Score Node - Building block of Linked List
 *
 * WHY LINKED LIST?
 * - Dynamic size - don't need to pre-allocate array
 * - Easy insertion at head - O(1)
 * - Memory efficient for keeping game history
 * - Natural for maintaining ordered list of scores
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

public:
    ScoreHistory();
    ~ScoreHistory();

    // LINKED LIST Operations
    void AddScore(int score, int height);  // O(1) - Insert at head
    int GetBestScore() const;              // O(n) - Find maximum score
    int GetBestHeight() const;             // O(n) - Find maximum height
    int GetCount() const;                  // O(1) - Get number of games
    void Clear();                          // O(n) - Delete all nodes

    // Display top N scores
    std::string GetTopScores(int n = 5) const;  // O(n) - Get formatted string of top scores

private:
    void DeleteList();  // Helper to free memory
};

#endif // SCOREHISTORY_H
