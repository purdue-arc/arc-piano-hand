#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> minMovementsAndCostToSatisfyNotes(vector<int>& notes) {
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

    vector<int> result = {cost, movements};
    return result;
}

int main() {
    vector<int> notes = {1, 3, 2, -5, -4, 3, 7, 6};
    vector<int> result = minMovementsAndCostToSatisfyNotes(notes);

    int totalCost = result[0];
    int totalMovements = result[1];

    cout << "Total Cost: " << totalCost << endl;      // Output: 13
    cout << "Total Movements: " << totalMovements << endl;  // Output: 3

    return 0;
}
