// ˅

// ˄

#ifndef NODE_H_
#define NODE_H_

// ˅
#include "vector"

class TriElem;
// ˄

class Node
{
	// ˅

	// ˄

public:

	// Nodeの位置
	double x_;

	double y_;

private:

	double t_;

	int all_nodes_size_;

public:

	int index_;

	std::vector<TriElem*> elems_;

	double base_condition_;

	double natural_condition_;

	// ノードごとの方程式の、各係数を計算してdriverに返す
	// n+1個のdoubleの配列になる
	double* calcEquation();

	void setT(double t);

	// elems_を追加する
	void addElemRef(TriElem* elem);

	// ˅
public:

	Node();

	~Node(){};
	
	Node(double x, double y, int index, int all_nodes_size);

	Node(const Node &o)
	{
		x_ = o.x_;
		y_ = o.y_;
		index_ = o.index_;
		all_nodes_size_ = o.all_nodes_size_;
	}
protected:

private:

	// ˄
};

// ˅

// ˄

#endif	// NODE_H_

// ˅

// ˄
