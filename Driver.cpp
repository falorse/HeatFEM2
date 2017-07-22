// ˅
#include "Driver.h"
#include "Node.h"

typedef Eigen::SparseMatrix<double> SpMat;
// ˄

void Driver::calcInvariants()
{
	// ˅
#pragma omp parallel for
	for (int i = 0; i < elems_size_; i++) {
		elems_.at(i)->calcInvariant();
	}
	// ˄
}

void Driver::calcEquations()
{
	// ˅
	// 各ノードの方程式を取得して、全体の連立方程式の左の行列と右のベクトルを構成する
	int i, j;

	left_mat_ = new double[nodes_size_ * nodes_size_];
	right_vector_ = new double[nodes_size_];

	//#pragma omp parallel for private(j)
	for (i = 0; i < nodes_size_; i++) {
		double* equ = nodes_[i]->calcEquation();
		for (j = 0; j < nodes_size_; j++) {
			left_mat_[i * nodes_size_ + j] = equ[j];
		}
		right_vector_[i] = equ[nodes_size_];
	}

	// ˄
}

void Driver::solveSimultaneousEquations()
{
	// ˅
	//行列とベクトルをEigen形式に変換
	outputEquationslog();


	SpMat left_mat(nodes_size_, nodes_size_);
	Eigen::VectorXd right_vec(nodes_size_);

	for (int i = 0; i < nodes_size_; i++) {
		for (int j = 0; j < nodes_size_; j++) {
			left_mat.insert(i, j) = left_mat_[i * nodes_size_ + j];
		}
	}

	delete[] left_mat_;

	for (int i = 0; i < nodes_size_; i++) {
		right_vec(i) = right_vector_[i];
	}

	delete[] right_vector_;

	Logger::out << "Matrix :\n" << left_mat << std::endl << "vec :\n" << right_vec << std::endl;

	// 計算 コレスキー分解
//		Eigen::SimplicialCholesky<SpMat> chol(left_mat);
//		Eigen::VectorXd tempretureVec = chol.solve(right_vec);

	// 計算　LU分解
	Eigen::SparseLU<SpMat > lu;
	lu.compute(left_mat);
	Eigen::VectorXd tempretureVec = lu.solve(right_vec);

	for (int i = 0; i < nodes_size_; i++) {
		nodes_[i]->t_ = tempretureVec[i];
	}

	Logger::out << "tempreture Vec" << std::endl;
	for (int i = 0; i < nodes_size_; i++) {
		Logger::out << tempretureVec[i] << " ";
	}
	Logger::out << std::endl;
	// ˄
}

void Driver::outputResult()
{
	// ˅
	// paraviewで読めるファイルを出力する
	size_t i, j;

	std::string filename = "./result.vtk";

	std::cout << "writeField " << filename << std::endl;

	std::ofstream wf;

	wf.open(filename.c_str(), std::ios_base::out);

	wf << "# vtk DataFile Version 2.0" << std::endl;
	wf << filename << std::endl;
	wf << "ASCII" << std::endl;
	wf << "DATASET UNSTRUCTURED_GRID" << std::endl;

	wf << "POINTS " << nodes_size_ << " float" << std::endl;
	for (i = 0; i < nodes_size_; i++) {
		wf << nodes_[i]->x_ << " " << nodes_[i]->y_ << " " << 0 << std::endl;
	}

	wf << "CELLS " << elems_size_ << " " << elems_size_ * (3 + 1) << std::endl;
	for (i = 0; i < elems_size_; i++) {
		wf << 3 << " ";
		for (j = 0; j < 3; j++) {
			wf << elems_[i]->nodes_[j]->index_-1;
			if (j != 2) {
				wf << " ";
			}
		}
		wf << std::endl;
	}

	wf << "CELL_TYPES " << elems_size_ << std::endl;
	for (i = 0; i < elems_.size(); i++) {
		wf << 5 << std::endl;
	}


	wf << "POINT_DATA " << nodes_size_ << std::endl;
	wf << "SCALARS t double 1" << std::endl;
	wf << "LOOKUP_TABLE default" << std::endl;
	for (i = 0; i < nodes_size_; i++) {
		wf << nodes_[i]->t_ << std::endl;
	}

	std::cout << "write file end" << std::endl;
	wf.close();
	// ˄
}

void Driver::readInputFiles()
{
	// ˅
	readMeshFile();

	readBoundaryFile();
	// ˄
}

void Driver::readMeshFile()
{
	// ˅
	string meshFile = fileDir_ + "/mesh.dat";

	ifstream in(meshFile.c_str());
	string str;

	size_t i, j;

	if (in.fail()) {
		//TODO例外を追加
	}

	//nodeの情報を登録
	getline(in, str);

	nodes_size_ = atoi(str.c_str());

	nodes_.clear();

	for (i = 0; i < nodes_size_; i++) {
		getline(in, str);
		vector<string> line = split(str, ' ');
		double x = atof(line.at(0).c_str());
		double y = atof(line.at(1).c_str());

		Node* node = new Node(x, y, i + 1, nodes_size_);

		nodes_.push_back(node);
	}

	//要素の情報を取得
	getline(in, str);

	elems_size_ = atoi(str.c_str());
	elems_.clear();

	for (i = 0; i < elems_size_; i++) {

		getline(in, str);
		vector<string> nodes_indexes = split(str, ' ');

		TriElem* elem = new TriElem(i);

		int index[3];
		for (j = 0; j < 3; j++) {
			index[j] = atoi(nodes_indexes.at(j).c_str());
			nodes_.at(index[j] - 1)->elems_.push_back(elem);
		}

		elem->q_by_lambda_ = atof(nodes_indexes.at(3).c_str());

		elem->setNodes(nodes_.at(index[0] - 1), nodes_.at(index[1] - 1), nodes_.at(index[2] - 1));

		elems_.push_back(elem);
	}

	in.close();
	// ˄
}

void Driver::readBoundaryFile()
{
	// ˅
	string meshFile = fileDir_ + "/boundary.dat";

	ifstream in(meshFile.c_str());
	string str;

	size_t i, j;

	if (in.fail()) {
		//TODO例外を追加
	}

	//nodeの情報を登録
	getline(in, str);

	int boundaries_size = atoi(str.c_str());

	for (i = 0; i < boundaries_size; i++) {

		//base or natural で変数がわかれる
		getline(in, str);
		string condition = str;

		//ノードの数
		getline(in, str);
		int nodes_size = atoi(str.c_str());

		for (j = 0; j < nodes_size; j++) {
			//ノード番号 値で格納されている
			getline(in, str);
			vector<string> value = split(str, ' ');

			int node_index = atoi(value[0].c_str());
			double condition_value = atof(value[1].c_str());

			if (condition == "base") {
				nodes_.at(node_index - 1)->base_condition_ = condition_value;
			} else if (condition == "natural") {
				nodes_.at(node_index - 1)->natural_condition_ = condition_value;
			}
		}
	}

	in.close();
	// ˄
}

// ˅

std::vector<string> Driver::split(string str, char sep)
{
	vector<string> v;
	stringstream ss(str);
	string buffer;
	while (getline(ss, buffer, sep)) {
		v.push_back(buffer);
	}
	return v;
}

void Driver::outputEquationslog()
{
	Logger::out << "outputEquationsLog" << std::endl;
	for (int i = 0; i < nodes_size_; i++) {
		for (int j = 0; j < nodes_size_; j++) {
			Logger::out << left_mat_[i * nodes_size_ + j] << " ";
		}
		Logger::out << "| t_" << i << " = " << right_vector_[i];
		Logger::out << std::endl;
	}

}
// ˄
