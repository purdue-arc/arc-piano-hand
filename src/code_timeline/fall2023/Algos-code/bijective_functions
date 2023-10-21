#include <iostream>
#include <vector>

// Generates all bijective functions mapping fingers to notes and prints to console
// Works best when fingers <= notes
void bijective_functions(std::vector<int>& func, std::vector<bool>& used, const int notes, const int fingers) {
    if (func.size() == notes) {
        for (int i = 0; i < notes; i++) {
            std::cout << func[i] << " ";
        }
        std::cout << std::endl;
        return;
    }
    for (int i = 0; i < fingers; i++) {
        if (!used[i]) {
            func.push_back(i);
            used[i] = true;
            bijective_functions(func, used, notes, fingers);
            func.pop_back();
            used[i] = false;
        }
    }
}

// main function to test method
/* int main() {
    int notes, fingers;
    std::cout << "Enter the size of set notes: ";
    std::cin >> notes;
    std::cout << "Enter the size of set fingers: ";
    std::cin >> fingers;
    std::vector<int> func;
    std::vector<bool> used(notes, false);
    bijective_functions(func, used, notes, fingers);
    return 0;
} */