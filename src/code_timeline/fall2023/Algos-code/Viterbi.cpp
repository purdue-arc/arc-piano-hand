//
// Created by TPNml on 9/23/2023.
//

#include "Viterbi.h"
#include <malloc.h>
#include <iostream>
#include <vector>

// Sample trivial cost function (cost is the value of the end node)
int cost(std::vector<std::vector<int>> trellis, int start_i, int start_j, int end_i, int end_j) {
    return trellis[end_i][end_j];
}

int main() {
    // Data initialization
    std::vector<std::vector<int>> trellis =
    {
        {1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 1},
        {1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 1}
    };
    int n_layers = 11;
    int layer_size = 8;

    // Make arrays for Viterbi
    int dist[n_layers][layer_size];
    int prev[n_layers][layer_size];
    for (int i = 0; i < n_layers; i++) {
        for (int j = 0; j < layer_size; j++) {
            dist[i][j] = INT_MAX;
            prev[i][j] = INT_MIN;
        }
    }

    // Run Viterbi
    for (int i = 0; i < n_layers; i++) {
        for (int j = 0; j < layer_size; j++) {
            int min_dist = INT_MAX;
            int min_prev = INT_MIN;
            if (i == 0) {   // If first layer (to avoid OOB accesses)
                min_dist = trellis[i][j];
            }
            else {
                for (int k = 0; k < layer_size; k++) {
                    // Check our distance recurrence and update min distances if better option
                    int curr_dist = cost(trellis, i - 1, k, i, j) + dist[i - 1][k];
                    if (curr_dist < min_dist) {
                        min_dist = curr_dist;
                        min_prev = k;
                    }
                }
            }
            // Add values to array
            dist[i][j] = min_dist;
            prev[i][j] = min_prev;
        }
    }
    // Find the minimum-distance item in the final layer
    int min = INT_MAX;
    int idx = 0;
    for (int i = 0; i < layer_size; i++) {
        if (dist[n_layers - 1][i] < min) {
            min = dist[n_layers - 1][i];
            idx = i;
        }
    }

    // Print results
    std::cout << "Final distance: " << dist[n_layers - 1][idx] << "\n"; 
    for (int i = n_layers - 1; i >= 0; i--) {
        // Use cout as a pseudo-stack
        std::cout << "(" << i << "," << idx << ") -> ";
        idx = prev[i][idx];
    }
    std::cout << "end\n\n";
    std::cout << "Array contents:\n\n";
    std::cout << "dist:\n";
    for (int i = 0; i < n_layers; i++) {
        for (int j = 0; j < layer_size; j++) {
            std::cout << dist[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    std::cout << "prev:\n";
    for (int i = 0; i < n_layers; i++) {
        for (int j = 0; j < layer_size; j++) {
            if (prev[i][j] == INT_MIN) {
                std::cout << "n" << " ";
            }
            else {
                std::cout << prev[i][j] << " ";
            }
        }
        std::cout << "\n";
    }
}
