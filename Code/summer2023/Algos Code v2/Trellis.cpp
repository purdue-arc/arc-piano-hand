#include "pianoHandNamespace.h"
using namespace pianoHandNamespace;

Trellis::Trellis(int n_layers) {
    this->n_layers = n_layers;
    this->layers = (Layer **) malloc(n_layers * sizeof(Layer *));
}

void Trellis::free() {
    std::free(this->layers);
}

int Trellis::get_n_layers() {
    return this->n_layers;
}

Layer *Trellis::get_layer(int n) {
    if (n >= this->n_layers) {
        return nullptr;
    }
    return layers[n];
}