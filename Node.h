// ˅

// ˄

#ifndef NODE_H_
#define NODE_H_

// ˅

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

	// ノードごとの方程式の、各係数を計算してdriverに返す
	// n+1個のdoubleの配列になる
	double* calcEquation();

	void setT(double t);

	// ˅
public:
	
protected:
	
private:
	
	// ˄
};

// ˅

// ˄

#endif	// NODE_H_

// ˅

// ˄
