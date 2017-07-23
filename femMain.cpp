#include <iostream>
#include <string>

#include "Driver.h"
#include "Logger.h"
#include "time.h"

using namespace std;


int main(int argc, char* argv[])
{
	clock_t st, en;
	st = clock();

	assert(argc == 2);

	Logger logger;

	logger.openLog();

	Driver driver;

	driver.fileDir_ = argv[1];

	driver.readInputFiles();
	en = clock();Logger::out<<"readInput:"<<(double)(en - st) / CLOCKS_PER_SEC<<std::endl;st=clock();
	
	driver.calcInvariants();
	en = clock();Logger::out<<"calcInvariant:"<<(double)(en - st) / CLOCKS_PER_SEC<<std::endl;st=clock();

	driver.calcEquations();
	en = clock();Logger::out<<"calcEqu:"<<(double)(en - st) / CLOCKS_PER_SEC<<std::endl;st=clock();

	driver.solveSimultaneousEquations();
	en = clock();Logger::out<<"solveSimEqu:"<<(double)(en - st) / CLOCKS_PER_SEC<<std::endl;st=clock();

	driver.outputResult();

	logger.closeLog();

	return 0;
}
