//
// Created by TPNml on 9/23/2023.
//

#include <malloc.h>
#include <cfloat>
#include <vector>

#include "phSpace.h"
using namespace phSpace;

std::vector<int> Viterbi::run_algo(int n_layers, int layer_size,
                                   double (*lookup)(int start_i, int start_j, int end_i, int end_j)) {
    double trellis[n_layers][layer_size];
    // Make arrays for Viterbi
    double dist[n_layers][layer_size];
    int prev[n_layers][layer_size];
    for (int i = 0; i < n_layers; i++) {
        for (int j = 0; j < layer_size; j++) {
            dist[i][j] = DBL_MAX;
            prev[i][j] = INT_MIN;
        }
    }

    // Run Viterbi
    for (int i = 0; i < n_layers; i++) {
        for (int j = 0; j < layer_size; j++) {
            double min_dist = DBL_MAX;
            int min_prev = INT_MIN;
            if (i == 0) {   // If first layer (to avoid OOB accesses)
                min_dist = trellis[i][j];
            }
            else {
                for (int k = 0; k < layer_size; k++) {
                    // Check our distance recurrence and update min distances if better option
                    double curr_dist = (*lookup)(i - 1, k, i, j) + dist[i - 1][k];
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
    auto min = DBL_MAX;
    int idx = 0;
    for (int i = 0; i < layer_size; i++) {
        if (dist[n_layers - 1][i] < min) {
            min = dist[n_layers - 1][i];
            idx = i;
        }
    }

    std::vector<int> vals;
    for (int i = n_layers - 1; i >= 0; i--) {
        vals.insert(vals.begin(), idx);
        idx = prev[i][idx];
    }

    return vals;
}

