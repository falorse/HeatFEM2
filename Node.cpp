
#include <vector>
#include "TriElem.h"
#include "Node.h"
#include "Logger.h"
#include "assert.h"

Node::Node(double x, double y, int index, int all_nodes_size) {
    x_ = x;
    y_ = y;
    index_ = index;
    all_nodes_size_ = all_nodes_size;
    base_condition_ = 0;
    natural_condition_ = 0;
    elems_.clear();
}

bool Node::hasBaseCondition(){
    return base_condition_ != NULL;
}


double* Node::calcCoefficients() {
    
    // ノードの方程式を構成する係数を計算
    // a_0*t_0+a_1*t_1+...=b という方程式のa_0,a_1....,bをcoefficientsに保存

    double* coefficients = new double[all_nodes_size_ + 1];

    for (int i = 0; i < all_nodes_size_ + 1; i++) {
        coefficients[i] = 0;
    }

    if (hasBaseCondition()) {
        coefficients[index_ - 1] = 1;
        coefficients[all_nodes_size_] = base_condition_;
        return coefficients;
    }

    for (int i = 0; i < elems_.size(); i++) {
        TriElem* elem = elems_.at(i);
        elem->addContribution(index_, coefficients, all_nodes_size_);
    }

    return coefficients;
}




