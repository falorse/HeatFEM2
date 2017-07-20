// ˅
#include <vector>
#include "TriElem.h"

#include "Node.h"

Node::Node(double x, double y, int index, int all_nodes_size)
{
	x_ = x;
	y_ = y;
	index_ = index;
	all_nodes_size_ = all_nodes_size;
	elems_.clear();
}
// ˄

double* Node::calcEquation()
{
	// ˅
	double d[all_nodes_size_ + 1];
	return d;
	// ˄
}

void Node::setT(double t)
{
	// ˅

	// ˄
}

void Node::addElemRef(TriElem* elem)
{
	// ˅
	elems_.push_back(elem);
	// ˄
}

// ˅

// ˄
