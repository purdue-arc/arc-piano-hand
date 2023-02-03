#include "pianoHandNamespace.h"
using namespace pianoHandNamespace;

Layer::Layer() {
	nodes = std::vector<Node>();
}

int Layer::add(Node node)
{
	if (std::count(nodes.begin(), nodes.end(), node)) {
		throw std::invalid_argument("Node already in Layer");
	}
	nodes.push_back(node);
	return 0;
}

int Layer::remove(Node node)
{
	for(auto i = 0; i < sizeof(nodes); i++) {
		if (&nodes[i] == &node) {
			nodes.erase(nodes.begin()+i);
			return 0;
		}
	}
	throw std::invalid_argument("Node not in Layer");
}
