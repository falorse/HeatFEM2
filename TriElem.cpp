
#include "TriElem.h"
#include "Node.h"
#include "assert.h"

void TriElem::calcArea() {
    // 各ノードの座標
    double xs[3] = {nodes_[0]->x_, nodes_[1]->x_, nodes_[2]->x_};
    double ys[3] = {nodes_[0]->y_, nodes_[1]->y_, nodes_[2]->y_};

    double intermediates[3] = {
        xs[1] * ys[2] - xs[2] * ys[1],
        xs[2] * ys[0] - xs[0] * ys[2],
        xs[0] * ys[1] - xs[1] * ys[0]
    };

    area_ = 0.5 * (intermediates[0] + intermediates[1] + intermediates[2]);
}

void TriElem::calcInvariants() {
    // dn_dx,dn_dy,int_nq_by_lambda_,area_を計算してセット

    double y_diffs[3] = {
        nodes_[1]->y_ - nodes_[2]->y_,
        nodes_[2]->y_ - nodes_[0]->y_,
        nodes_[0]->y_ - nodes_[1]->y_
    };

    double x_diffs[3] = {
        nodes_[2]->x_ - nodes_[1]->x_,
        nodes_[0]->x_ - nodes_[2]->x_,
        nodes_[1]->x_ - nodes_[0]->x_
    };

    calcArea();

    // 形状関数のx,y微分, N*q/lambdaの領域積分
    for (int i = 0; i < 3; i++) {
        dn_dx_[i] = 0.5 * y_diffs[i] / area_;
        dn_dy_[i] = 0.5 * x_diffs[i] / area_;
        q_by_lambda_ = 0;
        int_nq_by_lambda_[i] = q_by_lambda_;
    }

}

void TriElem::setNodes(Node* a, Node* b, Node* c) {

    nodes_[0] = a;
    nodes_[1] = b;
    nodes_[2] = c;
    node_indexes_[0] = a->index_;
    node_indexes_[1] = b->index_;
    node_indexes_[2] = c->index_;
}

TriElem::TriElem(int index) {
    index_ = index;
}

int TriElem::searchNodeNumber(int node_index) {

    int node_number = 3;

    for (int i = 0; i < 3; i++) {
        if (this->node_indexes_[i] == node_index) {
            node_number = i;
        }
    }

    assert(node_number != 3);

    return node_number;
}

void TriElem::addContribution(int node_index,
    double* coefficients, int all_nodes_size) {

    int node_number = this->searchNodeNumber(node_index);

    // 各係数への寄与を計算して足す
    for (int i = 0; i < 3; i++) {
        double value = (-1) * dn_dx_[node_number] * dn_dx_[i]
            - dn_dy_[node_number] * dn_dy_[i];

        coefficients[node_indexes_[i] - 1] += value;
    }

    coefficients[all_nodes_size] -= int_nq_by_lambda_[node_number];
}

