// ˅

// ˄

#ifndef DRIVER_H_
#define DRIVER_H_

// ˅
#include "vector"
#include "Node.h"
#include "TriElem.h"
#include "string"
#include "iostream"
#include "fstream"
#include "cstdlib"
#include "sstream"
using namespace std;
// ˄

class Driver
{
	// ˅
	
	// ˄

private:

	// 全要素
	std::vector<TriElem*> elems_;

	// 全ノード
	std::vector<Node*> nodes_;

	// 連立方程式の左辺のn*n行列(nはノードの数)
	// キャッシュミスしないように一次元配列で表現
	double* left_mat_;

	// 連立方程式の右辺のn列ベクトル
	double* right_vector;

	int elems_size_;

	int nodes_size_;

public:

	string fileDir_;

	// 各要素で、後にノードが方程式の計算で使う値を計算して保存する
	void calcInvariants();

	// ノードごとの方程式を計算してleft_mat_とright_vectorに入れる
	void calcEquations();

	// 連立方程式を解いて、各ノードに温度をセットする
	void solveSimultaneousEquations();

	// paraviewで見れる形でアウトプット
	void outputResult();

	void readInputFiles();

	// inputFiles/args[0]/からmesh.datを読んでノードと要素を登録する
	// メッシュファイルの形式は、
	// （ノード数）、（x,y座標）＊ノード数、（要素数）、（要素を構成するノード番号＊３）＊要素数
	void readMeshFile();

	// inputFiles/args[0]/からboundary.datを読んで境界条件を各ノードに登録する
	// ファイルの形式は、
	// （境界条件数）、（base or natural,境界上ノード数）、（ノード番号、境界条件の値）＊境界上ノード数
	void readBoundaryFile();

	// ˅
public:
	std::vector<string> split(const string str, char sep);
	
	~Driver(){};
protected:
	
private:
	
	// ˄
};

// ˅

// ˄

#endif	// DRIVER_H_

// ˅

// ˄
