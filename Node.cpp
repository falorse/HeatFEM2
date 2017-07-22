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
	base_condition_=0;
	natural_condition_=0;
	elems_.clear();
}
// ˄

double* Node::calcEquation()
{
	// ˅
	// ノードの方程式を構成してreturn
	double d[all_nodes_size_ + 1];
	
	for(int i=0;i<all_nodes_size_+1;i++)
	{
		d[i]=1;
	}
	
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
