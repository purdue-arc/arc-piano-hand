#include "pianoHandNamespace.h"
using namespace pianoHandNamespace;

Node::Node()
{
	this->Node::Node(0, nullptr);
}

Node::Node(FingerState *fs_ptr)
{
	this->Node::Node(0, fs_ptr);
}

Node::Node(double weight, FingerState *fs_ptr)
{
	this->weight = weight;
	this->fs_ptr = fs_ptr;
}

double Node::getWeight()
{
	return weight;
}

void Node::setWeight(double weight)
{
	this->weight = weight;
}

FingerState *Node::getFingerState()
{
	return this->fs_ptr;
}