// ˅
#include <vector>
#include "TriElem.h"
#include "Node.h"
#include "Logger.h"

Node::Node(double x, double y, int index, int all_nodes_size)
{
	x_ = x;
	y_ = y;
	index_ = index;
	all_nodes_size_ = all_nodes_size;
	base_condition_ = 0;
	natural_condition_ = 0;
	elems_.clear();
}
// ˄

double* Node::calcEquation()
{
	// ˅
	// ノードの方程式を構成してreturn
	// a_0*t_0+a_1+t_1+...=b という方程式になるので、a_0,a_1....,bをequに保存してreturn

	double* equ=new double[all_nodes_size_+1];
	for(int i=0;i<all_nodes_size_+1;i++)
	{
		equ[i]=0;
	}
	
	// 基本境界条件導入
	if(base_condition_!=NULL)
	{
		equ[index_-1]=1;
		equ[all_nodes_size_]=base_condition_;
		return equ;
		delete[] equ;
	}
	
	for (int i = 0; i < elems_.size(); i++) {
		TriElem* elem = elems_.at(i);

		// dn_dxなどの番号0(0,1,2)
		int index_for_elem = 3;

		for (int j = 0; j < 3; j++) {
			if (elem->node_indexes_[j] == index_) {
				index_for_elem = j;
			}
		}

		// 各要素の積分によって計算される係数を計算
		// dn_dx_[index_for_elem]*dn_dx_[0]-dn_dy_[index_for_elem]*dn_dy_[0] が 一番目のノードの温度に対する係数

		for (int j = 0; j < 3; j++) {
			// このノードを持っていない要素の場合ここで例外を出す
			equ[elem->node_indexes_[j] - 1] = (-1) * elem->dn_dx_[index_for_elem] * elem->dn_dx_[j] - elem->dn_dy_[index_for_elem] * elem->dn_dy_[j];
		}

		equ[all_nodes_size_] = elem->int_nq_by_lambda_[i];

	}

	Logger::out<<"calcEqu"<<index_<<std::endl;
	for(int i=0;i<all_nodes_size_+1;i++)
	{
		Logger::out<<equ[i]<< " ";
	}
	Logger::out<<std::endl;
	
	return equ;
	
	delete[] equ;
	// ˄
}

void Node::setT(double t)
{
	// ˅

	// ˄
}

// ˅

// ˄
