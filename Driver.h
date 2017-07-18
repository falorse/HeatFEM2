// ˅

// ˄

#ifndef DRIVER_H_
#define DRIVER_H_

// ˅

// ˄

class Driver
{
	// ˅
	
	// ˄

private:

	// 全要素
	std::vector<TriElem> elems_;

	// 全ノード
	std::vector<Node> nodes_;

	// 連立方程式の左辺のn*n行列(nはノードの数)
	double[][] left_mat_;

	// 連立方程式の右辺のn列ベクトル
	double[] right_vector;

public:

	void readInputFiles();

	// 各要素で、後にノードが方程式の計算で使う値を計算して保存する
	void calcInvariants();

	// ノードごとの方程式を計算してleft_mat_とright_vectorに入れる
	void calcEquations();

	// 連立方程式を解いて、各ノードに温度をセットする
	void solveSimultaneousEquations();

	// paraviewで見れる形でアウトプット
	void outputResult();

	// ˅
public:
	
protected:
	
private:
	
	// ˄
};

// ˅

// ˄

#endif	// DRIVER_H_

// ˅

// ˄
