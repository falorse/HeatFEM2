// ˅
#include "Driver.h"
#include "Node.h"
// ˄

void Driver::calcInvariants()
{
	// ˅
	for(int i=0;i<elems_size_;i++)
	{
		elems_.at(i)->calcInvariant();
	}
	// ˄
}

void Driver::calcEquations()
{
	// ˅
	
	// ˄
}

void Driver::solveSimultaneousEquations()
{
	// ˅

	// ˄
}

void Driver::outputResult()
{
	// ˅

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
				nodes_.at(node_index - 1)->base_condition_=condition_value;
			} else if (condition == "natural") {
				nodes_.at(node_index - 1)->natural_condition_=condition_value;
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
// ˄
