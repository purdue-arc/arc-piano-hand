#include "pianoHandNamespace.h"
using namespace pianoHandNamespace;

Layer::Layer() {
	nodes = std::vector<Node>();
}

int Layer::add(Node node)
{
	nodes.push_back(node);
}

int Layer::remove(Node node)
{
	for(auto i = 0; i < sizeof(nodes); i++) {
		if (&nodes[i] == &node) {
			nodes.erase(nodes.begin()+i);
		}
	}
}
