// ˅
#include "TriElem.h"
#include "Node.h"

// ˄

void TriElem::calcInvariant()
{
	// ˅

	// ˄
}

void TriElem::setNodes(Node* a, Node* b, Node* c)
{
	// ˅
	nodes_[0]=a;
	nodes_[1]=b;
	nodes_[2]=c;
	node_indexes_[0]=a->index_;
	node_indexes_[1]=b->index_;
	node_indexes_[2]=c->index_;
	// ˄
}

// ˅
TriElem::TriElem(int index){
	index_=index;
}
// ˄
