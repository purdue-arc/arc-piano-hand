#include "pianoHandNamespace.h"
using namespace pianoHandNamespace;

Trellis::Trellis() {
}

int Trellis::link_edges() {
    this->edges.clear();
    if (layers.size() <= 1) return NOT_ENOUGH_LAYERS;
    for (int i = 0; i < layers.size() - 1; i++) {
        for (Node n1 : layers[i].getNodes()) {
            for (Node n2 : layers[i+1].getNodes()) {
                edges.push_back(Edge::Edge(0, n1, n2, i, i+1));
            }
        }
    }
}

Edge Trellis::min_weight_edges(int layerIndex, Node n) {
    Edge *minEdge = &(Edge::Edge(DBL_MAX, Node::Node(), Node::Node(), -1, -1));
    for (auto e : this->edges) {
        if (&(e.getEndNode()) == &n) {
            if (e.getWeight() < minEdge->getWeight()) {
                minEdge = &e;
            }
        }
    }
    return *minEdge;
}

Edge Trellis::getEdge(int layerIndex, Node n) {
    for (auto e : this->edges) {
        if (&(e.getEndNode()) == &n) {
            return e;
        }
    }
    return Edge::Edge(0, Node::Node(), Node::Node(), -1, -1);
}