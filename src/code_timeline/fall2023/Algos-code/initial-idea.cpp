#include <iostream>
#include <vector>
#include <cmath>

#include "phSpace.h"
using namespace phSpace;

std::vector<int> initial_idea::minMvmtsForNotes(const std::vector<int>& notes) {
    // This is a greedy algo - is there a way we could improve on this in the case where making
    // one large movement is better than making 2 smaller ones?

    int start = 0; // Piano Hand Start index
    int movements = 0; // Times hand is moved
    int cost = 0; // Number of notes moved (want to minimize)

    for (int note : notes) {
        if (note < start) {
            cost += abs(start - note);
            movements++;
            start = note;
        } else if (note > start + 4) {
            cost += abs(note - (start + 4));
            movements++;
            start = note - 4;
        }
    }

    std::vector<int> result = {cost, movements};
    return result;
}

int run() {
    std::vector<int> notes = {1, 3, 2, -5, -4, 3, 7, 6};
    std::vector<int> result = initial_idea::minMvmtsForNotes(notes);

    int totalCost = result[0];
    int totalMovements = result[1];

    std::cout << "Total Cost: " << totalCost << "\n";      // Output: 13
    std::cout << "Total Movements: " << totalMovements << "\n";  // Output: 3

    return 0;
}
