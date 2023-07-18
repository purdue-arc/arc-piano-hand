#include "pianoHandNamespace.h"
using namespace pianoHandNamespace;     

Node ** Viterbi(Trellis *T) {
    int capacity = T->get_n_layers();
    if (capacity < 1) return nullptr;

    std::unordered_map<Node *, double> dist = {};
    std::unordered_map<Node *, Node *> prev = {};

    // Initialize dist and prev arrays
    for (Node *n : T->get_layer(0)->getNodes()) {
        dist.insert({n, 0.0});
        prev.insert({n, nullptr});
    }
    for (int i = 1; i < capacity; i++) {
        for (Node *n : T->get_layer(i)->getNodes()) {
            dist.insert({n, DBL_MAX});
            prev.insert({n, nullptr});
        }
    }
    
    // Run Viterbi
    for (int i = 0; i < capacity - 1; i++) {
        for (Node *curr_node : T->get_layer(i)->getNodes()) {
            for (Node *next_node : T->get_layer(i + 1)->getNodes()) {
                double d = dist[curr_node] + costFunctions::aggregate_cost(curr_node->getFingerState(), next_node->getFingerState());
                if (d < dist.at(next_node)) {
                    dist[next_node] = d;
                }
            }
        }
    }

    // Check the node in the last layer with the shortest distance
    Node *min_node = nullptr;
    double min_dist = DBL_MAX;
    for (Node *node : T->get_layer(capacity - 1)->getNodes()) {
        if (dist[node] < min_dist) {
            min_dist = dist[node];
            min_node = node;
        }
    }

    // Back prop to get a path
    Node **node_stack = (Node **) malloc(capacity * sizeof(Node *));
    Node *current_ptr = min_node;
    for (int i = 0; i < capacity; i++) {
        if (current_ptr == nullptr) {
            throw std::exception("Stack reached nullptr in prev dict before reaching first layer");
            return nullptr;
        }
        node_stack[capacity - i - 1] = current_ptr;
        current_ptr = prev[current_ptr];
    }

    return node_stack;
}