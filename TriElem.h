// ˅

// ˄

#ifndef TRIELEM_H_
#define TRIELEM_H_

// ˅
#include "Node.h"

class Node;
// ˄

class TriElem
{
	// ˅
	
	// ˄

public:

	// 三角形要素が持つノード
	Node* nodes_[3];

	// 要素が持つノードの番号
	int node_indexes_[3];

	// 形状関数
	double n_[3];

	// 形状関数のx偏微分
	double dn_dx_[3];

	// 形状関数のy偏微分
	double dn_dy_[3];

	// (形状関数*q/lambda) の要素領域積分
	double int_nq_by_lambda_[3];

	// 要素の面積
	double area_;

	int index_;

private:

	double q_by_lambda_;

public:

	// dn_dx,dn_dy,int_nq_by_lambda_,area_を計算してセット
	void calcInvariant();

	void setNodes(Node* a, Node* b, Node* c);

	// ˅
public:
	TriElem();
	
	TriElem(int index);
	
	~TriElem(){};
	
	TriElem(Node a, Node b, Node c);
	
protected:

private:

	// ˄
};

// ˅

// ˄

#endif	// TRIELEM_H_

// ˅

// ˄
