#include "pianoHandNamespace.h"
using namespace pianoHandNamespace;

Node::Node() 
{
	this->Node::Node(0, FingerState::FingerState());
}

Node::Node(FingerState fs)
{
	this->Node::Node(0, fs);
}

Node::Node(double weight, FingerState fs) 
{
	this->weight = weight;
	this->fs = fs;
}

double Node::getWeight()
{
	return weight;
}

void Node::setWeight(double weight)
{
	this->weight = weight;
}

FingerState Node::getFingerState()
{
	return fs;
}