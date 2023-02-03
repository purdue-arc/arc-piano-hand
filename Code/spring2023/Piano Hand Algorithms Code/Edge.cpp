#include "pianoHandNamespace.h"
using namespace pianoHandNamespace;
#include <string>

Edge::Edge(Node startNode, Node endNode)
{
	this->startNode = startNode;
	this->endNode = endNode;
}

Edge::Edge(double weight, Node startNode, Node endNode, int startLayerIndex, int endLayerIndex) 
{
	this->edgeWeight = weight;
	this->startNode = startNode;
	this->endNode = endNode;
	this->startLayerIndex = startLayerIndex;
	this->endLayerIndex = endLayerIndex;
}

Edge Edge::minWeight(vector<Edge> te) {
    Edge minEdge = Edge(0, 0, Node(), Node(), DBL_MAX);
        for (Edge t : te) {
            if (t.getWeight() < minEdge.getWeight()) {
                minEdge = t;
            }
		}
    return minEdge;
}

double Edge::getWeight()
{
	return edgeWeight;
}

void Edge::setWeight(double weight)
{
	edgeWeight = weight;
}

int Edge::getStartLayerIndex()
{
	return startLayerIndex;
}

int Edge::getEndLayerIndex()
{
	return endLayerIndex;
}

Node Edge::getStartNode()
{
	return startNode;
}

Node Edge::getEndNode()
{
	return endNode;
}

char[] toString() {
    return String.format("Edge<(%d,%s)->(%d,%s), weight=%f>",
    startLayerIndex, startNode, endLayerIndex, endNode, weight);
}

