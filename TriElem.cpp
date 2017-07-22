// ˅
#include "TriElem.h"
#include "Node.h"

// ˄

void TriElem::calcInvariant()
{
	// ˅
	// dn_dx,dn_dy,int_nq_by_lambda_,area_を計算してセット
	int i,j;
	
	// 各ノードの座標
	double x[3] = {nodes_[0]->x_, nodes_[1]->x_, nodes_[2]->x_};
	double y[3] = {nodes_[0]->y_, nodes_[1]->y_, nodes_[2]->y_};

	// 各中間定数
	double a[3] = {y[1] - y[2], y[2] - y[0], y[0] - y[1]};
	double b[3] = {x[2] - x[1], x[0] - x[2], x[1] - x[0]};
	double c[3] = {x[1] * y[2] - x[2] * y[1], x[2] * y[0] - x[0] * y[2], x[0] * y[1] - x[1] * y[0]};

	// 面積
	area_=0.5*(c[0]+c[1]+c[2]);

	// 形状関数のx,y微分, N*q/lambdaの領域積分
	for(int i=0;i<3;i++)
	{
		dn_dx_[i]=0.5*a[i]/area_;
		dn_dy_[i]=0.5*b[i]/area_;
		//TODO 形状関数積分は面積＊三分の１で近似 q_by_lambdaも多分入力値
		q_by_lambda_=1;
		int_nq_by_lambda_[i]=0.33*area_*q_by_lambda_;
	}
	
	// ˄
}

void TriElem::setNodes(Node* a, Node* b, Node* c)
{
	// ˅
	nodes_[0] = a;
	nodes_[1] = b;
	nodes_[2] = c;
	node_indexes_[0] = a->index_;
	node_indexes_[1] = b->index_;
	node_indexes_[2] = c->index_;
	// ˄
}

// ˅

TriElem::TriElem(int index)
{
	index_ = index;
}
// ˄
