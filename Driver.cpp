
#include "Driver.h"
#include "Node.h"

typedef Eigen::SparseMatrix<double> SpMat;


void Driver::calcElemsInvariants() {
    
    for (int i = 0; i < elems_size_; i++) {
        elems_.at(i)->calcInvariants();
    }

}

void Driver::setCoefficientsToMatRow(double* coefficients_of_equation,
    double* mat, int row) {

    for (int i = 0; i < nodes_size_; i++) {
        mat[row * nodes_size_ + i] = coefficients_of_equation[i];
    }
}

void Driver::makeSimultaneousEquations() {
    
    // 各ノードの方程式の係数を取得して、全体の連立方程式の左の行列と右のベクトルを構成する
    int i, j;

    left_mat_ = new double[nodes_size_ * nodes_size_];
    right_vector_ = new double[nodes_size_];

    for (i = 0; i < nodes_size_; i++) {
        double* coefficients_of_equation = nodes_[i]->calcCoefficients();

        setCoefficientsToMatRow(coefficients_of_equation, left_mat_, i);

        right_vector_[i] = coefficients_of_equation[nodes_size_];
    }

}

void Driver::solveSimultaneousEquations() {
    
    //行列とベクトルをEigen形式に変換
    int i, j;

    SpMat left_mat(nodes_size_, nodes_size_);
    //	SpMat left_mat = initEigenMatrix();

    Eigen::VectorXd right_vec(nodes_size_);


    for (i = 0; i < nodes_size_; i++) {
        for (j = 0; j < nodes_size_; j++) {
            left_mat.insert(i, j) = left_mat_[i * nodes_size_ + j];
        }
    }

    for (i = 0; i < nodes_size_; i++) {
        right_vec(i) = right_vector_[i];
    }

    delete[] left_mat_;
    delete[] right_vector_;

    // 計算 

    Eigen::VectorXd temparetureVec;
    Eigen::BiCGSTAB<SpMat> lu;
    lu.compute(left_mat);
    temparetureVec = lu.solve(right_vec);

    for (i = 0; i < nodes_size_; i++) {
        nodes_[i]->t_ = temparetureVec[i];
    }

}

void Driver::outputNodeTemperatures() {
    
    // paraviewで読めるファイルを出力する
    size_t i, j;

    std::string filename = fileDir_ + "/result.vtk";

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
            wf << elems_[i]->nodes_[j]->index_ - 1;
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

}

void Driver::readInputFiles() {
    
    readMeshFile();

    readBoundaryFile();

}

void Driver::readMeshFile() {
    
    string mesh_file_path = fileDir_ + "/mesh.dat";

    ifstream mesh_file(mesh_file_path.c_str());
    string line;

    size_t i, j;

    if (mesh_file.fail()) {
        cout << mesh_file_path << "が見つかりませんでした" << endl;
        exit(1);
    }

    //nodeの情報を登録
    getline(mesh_file, line);

    nodes_size_ = atoi(line.c_str());
    nodes_.clear();

    for (i = 0; i < nodes_size_; i++) {
        getline(mesh_file, line);
        vector<string> node_info = split(line, ' ');
        double x = atof(node_info.at(0).c_str());
        double y = atof(node_info.at(1).c_str());

        Node* node = new Node(x, y, i + 1, nodes_size_);

        nodes_.push_back(node);
    }

    //要素の情報を取得
    getline(mesh_file, line);

    elems_size_ = atoi(line.c_str());
    elems_.clear();

    for (i = 0; i < elems_size_; i++) {

        getline(mesh_file, line);
        vector<string> nodes_indexes = split(line, ' ');

        TriElem* elem = new TriElem(i);

        int index[3];
        for (j = 0; j < 3; j++) {
            index[j] = atoi(nodes_indexes.at(j).c_str());
            nodes_.at(index[j] - 1)->elems_.push_back(elem);
        }

        elem->q_by_lambda_ = 0;

        elem->setNodes(nodes_.at(index[0] - 1), nodes_.at(index[1] - 1), nodes_.at(index[2] - 1));

        elems_.push_back(elem);
    }

    mesh_file.close();

}

void Driver::readBoundaryFile() {
    
    string boundary_file_path = fileDir_ + "/boundary.dat";

    ifstream boundary_file(boundary_file_path.c_str());
    string line;

    size_t i, j;

    if (boundary_file.fail()) {
        cout << boundary_file_path << "が見つかりませんでした" << endl;
        exit(1);
    }

    //nodeの情報を登録
    getline(boundary_file, line);

    int boundaries_size = atoi(line.c_str());

    for (i = 0; i < boundaries_size; i++) {

        //base or natural で変数がわかれる
        getline(boundary_file, line);
        string condition = line;

        //ノードの数
        getline(boundary_file, line);
        int nodes_size = atoi(line.c_str());

        for (j = 0; j < nodes_size; j++) {
            //ノード番号 値で格納されている
            getline(boundary_file, line);
            vector<string> value = split(line, ' ');

            int node_index = atoi(value[0].c_str());
            double condition_value = atof(value[1].c_str());

            if (condition == "base") {
                nodes_.at(node_index - 1)->base_condition_ = condition_value;
            } else if (condition == "natural") {
                nodes_.at(node_index - 1)->natural_condition_ = condition_value;
            }
        }
    }

    boundary_file.close();

}



std::vector<string> Driver::split(string str, char sep) {
    vector<string> v;
    stringstream ss(str);
    string buffer;
    while (getline(ss, buffer, sep)) {
        v.push_back(buffer);
    }
    return v;
}

void Driver::outputEquationslog() {
    Logger::out << "outputEquationsLog" << std::endl;
    for (int i = 0; i < nodes_size_; i++) {
        for (int j = 0; j < nodes_size_; j++) {
            Logger::out << left_mat_[i * nodes_size_ + j] << " ";
        }
        Logger::out << "| t_" << i << " = " << right_vector_[i];
        Logger::out << std::endl;
    }
}

