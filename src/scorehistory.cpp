#include "scorehistory.h"
#include <sstream>
#include <vector>
#include <algorithm>

ScoreHistory::ScoreHistory() : head(nullptr), count(0) {}

ScoreHistory::~ScoreHistory() {
    DeleteList();
}

// LINKED LIST OPERATION: Insert at Head - O(1)
// Adds a new score to the beginning of the list
void ScoreHistory::AddScore(int score, int height) {
    ScoreNode* newNode = new ScoreNode(score, height);
    newNode->next = head;  // New node points to old head
    head = newNode;        // Head now points to new node
    count++;
}

// Find the best score by traversing the list - O(n)
int ScoreHistory::GetBestScore() const {
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
int ScoreHistory::GetBestHeight() const {
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

int ScoreHistory::GetCount() const {
    return count;
}

// Clear all nodes from the list - O(n)
void ScoreHistory::Clear() {
    DeleteList();
    head = nullptr;
    count = 0;
}

// Get top N scores as formatted string
std::string ScoreHistory::GetTopScores(int n) const {
    if (head == nullptr) {
        return "No games played yet!";
    }

    // Collect all scores into a vector for sorting
    std::vector<std::pair<int, int>> scores;  // (score, height)
    ScoreNode* current = head;

    while (current != nullptr) {
        scores.push_back({current->score, current->height});
        current = current->next;
    }

    // Sort by score (descending)
    std::sort(scores.begin(), scores.end(),
              [](const auto& a, const auto& b) { return a.first > b.first; });

    // Build formatted string
    std::stringstream ss;
    ss << "Top " << std::min(n, (int)scores.size()) << " Scores:\n";

    for (int i = 0; i < std::min(n, (int)scores.size()); i++) {
        ss << (i + 1) << ". Score: " << scores[i].first
           << " (Height: " << scores[i].second << ")\n";
    }

    return ss.str();
}

// LINKED LIST: Free all allocated memory - O(n)
void ScoreHistory::DeleteList() {
    ScoreNode* current = head;

    while (current != nullptr) {
        ScoreNode* next = current->next;
        delete current;           // Free current node
        current = next;           // Move to next node
    }
}
