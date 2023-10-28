//
// Created by TPNml on 9/23/2023.
//

#include <malloc.h>
#include <iostream>
#include <vector>

#include "phSpace.h"
using namespace phSpace;

Viterbi::Viterbi(int trellis_length) {
    this->trellis_length = trellis_length;
}

int Viterbi::hand_cost(int start_i, int start_j, int end_i, int end_j) {
    Hand *h1 = this->possible_fingerings[start_i][start_j];
    Hand *h2 = this->possible_fingerings[end_i][end_j];
    int cost = 0;
    for (Finger *f1 : h1->fingers) {
        for (Finger *f2 : h2->fingers) {
            if (f1->getID() == f2->getID()) {
                if (f1->isPlaying() && f2->isPlaying() && f1->getNote()->midiNumber != f2->getNote()->midiNumber) {
                    cost += (f2->getNote()->midiNumber - f1->getNote()->midiNumber) * (f2->getNote()->midiNumber - f1->getNote()->midiNumber);
                }
                if (f1->getID() == f2->getID()) {
                    if (f2->isPlaying()) {
                        if (f1->isPlaying()) {
                            if (f1->getNote()->midiNumber == f2->getNote()->midiNumber) {
                                cost += 50 * 50;
                            } else {
                                cost += (f2->getNote()->midiNumber - f1->getNote()->midiNumber) * (f2->getNote()->midiNumber - f1->getNote()->midiNumber);
                            }
                        }
                        /*
                        else {
                            cost += (f2->getNote()->midiNumber - f2->getPositionOnHand()) * (f2->getNote()->midiNumber - f2->getPositionOnHand());
                        }
                         */
                    }
                }
            }
        }
    }
    return cost;
}

int Viterbi::layerSize(int end_i) {
    return this->possible_fingerings[end_i].size();
}

void Viterbi::update_fingerings(std::vector<Hand *> new_fingerings) {
    if (this->possible_fingerings.size() == this->trellis_length) {
        this->possible_fingerings.erase(this->possible_fingerings.begin());
        // Update weights
    }
    this->possible_fingerings.push_back(new_fingerings);
}

std::vector<Hand *> Viterbi::run_algo(bool silent) {
    int n_layers = this->possible_fingerings.size();
    // Make arrays for Viterbi
    int *dist[n_layers];
    int *prev[n_layers];
    for (int i = 0; i < n_layers; i++) {
        int layer_size = this->layerSize(i);
        dist[i] = new int[layer_size];
        prev[i] = new int[layer_size];
        for (int j = 0; j < layer_size; j++) {
            dist[i][j] = INT_MAX;
            prev[i][j] = INT_MIN;
        }
    }

    // Run Viterbi
    for (int i = 0; i < n_layers; i++) {
        int layer_size = this->layerSize(i);
        for (int j = 0; j < layer_size; j++) {
            int min_dist = INT_MAX;
            int min_prev = INT_MIN;
            if (i == 0) {   // If first layer (to avoid OOB accesses)
                min_dist = 0;
            }
            else {
                for (int k = 0; k < layer_size; k++) {
                    // Check our distance recurrence and update min distances if better option
                    int curr_dist = hand_cost(i - 1, k, i, j) + dist[i - 1][k];
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
    for (int i = 0; i < layerSize(n_layers-1); i++) {
        if (dist[n_layers - 1][i] < min) {
            min = dist[n_layers - 1][i];
            idx = i;
        }
    }

    std::vector<Hand *> stack;

    for (int i = n_layers - 1; i >= 0; i--) {
        stack.push_back(possible_fingerings[i][idx]);
        idx = prev[i][idx];
    }


    std::vector<Hand *> output;
    for (int i = stack.size() - 1; i >= 0; i--) {
        output.push_back(stack[i]);
    }

    if (!silent) {
        //for (int i = 0; i < output.size(); i++) {
        //    std::cout << "(" << i << "," << output[i]->toString() << ") -> ";
        //}
        //std::cout << "end" << std::endl;

        std::cout << "Array contents:\n\n";
        std::cout << "dist:\n";
        for (int i = 0; i < n_layers; i++) {
            int layer_size = layerSize(i);
            for (int j = 0; j < layer_size; j++) {
                std::cout << dist[i][j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
        std::cout << "prev:\n";
        for (int i = 0; i < n_layers; i++) {
            int layer_size = layerSize(i);
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

    return output;
}

std::vector<Hand *> Viterbi::run_algo() {
    return Viterbi::run_algo(true);
}