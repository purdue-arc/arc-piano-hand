//
// Created by TPNml on 9/23/2023.
//

#include "Viterbi.h"
#include <malloc.h>
#include <iostream>

int cost(int start_i, int start_j, int end_i, int end_j) {
    int trellis[4][3] = {{2, 4, 3},
                         {3, 2, 4},
                         {5, 3, 2},
                         {2, 3, 4}};
    return trellis[end_i][end_j];
}

int main() {
    int trellis[4][3] = {{2, 4, 3},
                         {3, 2, 4},
                         {5, 3, 2},
                         {2, 3, 4}};

    int n_layers = 4;
    int layer_size = 3;

    int dist[n_layers][layer_size];
    int prev[n_layers][layer_size];
    for (int i = 0; i < n_layers; i++) {
        for (int j = 0; j < layer_size; j++) {
            dist[i][j] = INT_MAX;
            prev[i][j] = INT_MIN;
        }
    }

    for (int i = 0; i < n_layers; i++) {
        for (int j = 0; j < layer_size; j++) {
            int min_dist = INT_MAX;
            int min_prev = INT_MIN;
            if (i == 0) {
                min_dist = trellis[i][j];
            }
            else {
                for (int k = 0; k < layer_size; k++) {
                    int curr_dist = cost(i-1, k, i, j) + dist[i-1][k];
                    if (curr_dist < min_dist) {
                        min_dist = curr_dist;
                        min_prev = k;
                    }
                }
            }
            dist[i][j] = min_dist;
            prev[i][j] = min_prev;
        }
    }
    int min = INT_MAX;
    int idx = 0;
    for (int i = 0; i < layer_size; i++) {
        if (dist[n_layers - 1][i] < min) {
            min = dist[n_layers - 1][i];
            idx = i;
        }
    }
    std::cout << "Final distance: " << dist[n_layers - 1][idx] << "\n";
    for (int i = n_layers - 1; i >= 0; i--) {
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
            std::cout << prev[i][j] << " ";
        }
        std::cout << "\n";
    }
}
