#include <iostream>
#include <string>

#include "Driver.h"
#include "Logger.h"
#include "time.h"
#include "omp.h"

using namespace std;

int main(int argc, char* argv[])
{
	clock_t st, en;
	st = clock();

	assert(argc == 2);

	Eigen::initParallel();

	Logger logger;

	logger.openLog();
//omp_set_num_threads(1);
//#pragma omp parallel for
//for(int i=0;i<8;i++)
//{
//	printf("%d: %d\n", omp_get_thread_num(), i);
//}
//	omp_set_num_threads(4);
//#pragma omp parallel for
//for(int i=0;i<8;i++)
//{
//	printf("%d: %d\n", omp_get_thread_num(), i);
//}
//	int n = 4000;
//	Eigen::MatrixXd A = Eigen::MatrixXd::Ones(n, n);
//	Eigen::MatrixXd B = Eigen::MatrixXd::Ones(n, n);
//	Eigen::MatrixXd C = A*B;
//	std::cout << C.sum() << "\n";
//	en = clock();
//	Logger::out << "Eigen omp threads num: " << Eigen::nbThreads() << " of all " << omp_get_max_threads() << " threads" << std::endl;
//	Logger::out << "calc test:" << (double) (en - st) / CLOCKS_PER_SEC << std::endl;
//	st = clock();
//
//	Eigen::setNbThreads(4);
//	Eigen::MatrixXd D = Eigen::MatrixXd::Ones(n, n);
//	Eigen::MatrixXd E = Eigen::MatrixXd::Ones(n, n);
//	Eigen::MatrixXd F = D*E;
//	std::cout << F.sum() << "\n";
//	
//	en = clock();
//	Logger::out << "Eigen omp threads num: " << Eigen::nbThreads() << " of all " << omp_get_max_threads() << " threads" << std::endl;
//	Logger::out << "calc test:" << (double) (en - st) / CLOCKS_PER_SEC << std::endl;
//	st = clock();

	Driver driver;

	driver.fileDir_ = argv[1];
	
	driver.readInputFiles();
	
	omp_set_num_threads(omp_get_max_threads());
	Logger::out << "OMP_NUM_THREADS=" << omp_get_max_threads() << std::endl;
	
	en = clock();
	Logger::out << "readInput:" << (double) (en - st) / CLOCKS_PER_SEC << std::endl;
	st = clock();

	driver.calcInvariants();
	en = clock();
	Logger::out << "calcInvariant:" << (double) (en - st) / CLOCKS_PER_SEC << std::endl;
	st = clock();

	driver.calcEquations();
	en = clock();
	Logger::out << "calcEqu:" << (double) (en - st) / CLOCKS_PER_SEC << std::endl;
	st = clock();

	driver.solveSimultaneousEquations();
	en = clock();
	Logger::out << "solveSimEqu:" << (double) (en - st) / CLOCKS_PER_SEC << std::endl;
	st = clock();

	driver.outputResult();

	logger.closeLog();

	return 0;
}
