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