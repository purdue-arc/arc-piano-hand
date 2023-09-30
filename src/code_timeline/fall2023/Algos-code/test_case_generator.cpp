//
// Created by TPNml on 9/30/2023.
//

#include <random>
#include <vector>
#include <phSpace.h>

using namespace phSpace;

int main() {
    int x[30] = { 0 };
    for (int & i : x) {
        i = std::rand() % 36 + 48;
    }
    std::vector<int> v(x, x + sizeof x / sizeof x[0]);
    try {
        std::vector<int> output = initial_idea::minMvmtsForNotes(v);
    } catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}