#include "pianoHandNamespace.h"
using namespace pianoHandNamespace;
std::vector<Edge> Viterbi(Trellis t) {
    // For layer in layers
    for (auto i = 0; i < t.layers.size(); i++) {
        if (&(t.layers[i + 1]) == NULL) {
            break;
        }
        // For edges in the layer
        for (auto edge : t.edges) {
            if (edge.getEndLayerIndex() == i + 1) {
                edge.setWeight(edge.getStartNode().getWeight());
            }
        }

        // Destroy unoptimal edges
        for (auto node : t.layers[i + 1].getNodes()) {
            Edge minEdge = t.min_weight_edges(i, node);
            int i = 0;
            while (i < t.edges.size()) {
                Edge edge = t.edges[i];
                if (&(minEdge) != &edge) {
                    t.edges.erase(t.edges.begin() + i);
                }
                else {
                    i++;
                }
            }
        }

        // Update node weights
        for (auto node : t.layers[i + 1].getNodes()) {
            Edge e = t.getEdge(i + 1, node);
            node.setWeight(node.getWeight() + e.getWeight());
        }
    }
    // Check the optimal node
    Node *minNode = &(Node::Node(DBL_MAX, FingerState::FingerState()));
    for (auto node : t.layers[t.layers.size() - 1].getNodes()) {
        if (node.getWeight() < minNode->getWeight()) {
            minNode = &node;
        }
    }

    // Back prop to find the optimal path
    std::vector<Edge> optimalEdges = std::vector<Edge>();
    while (&(optimalEdges[0].getStartNode()) == NULL) {
        for (int i = 0; i < t.edges.size(); i++) {
            if (&(t.edges[i].getEndNode()) == &(optimalEdges[0].getStartNode())) {
                optimalEdges.insert(optimalEdges.begin(), t.edges[i]);
                break;
            }
        }
    }
    return optimalEdges;

}