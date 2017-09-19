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
	
	Driver driver;

	driver.fileDir_ = argv[1];
	
	driver.readInputFiles();
	
	omp_set_num_threads(omp_get_max_threads());

	driver.calcInvariants();
	
	driver.calcEquations();

	driver.solveSimultaneousEquations();
	
	driver.outputResult();

	logger.closeLog();

	return 0;
}
