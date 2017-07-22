#include <iostream>
#include <string>

#include "Driver.h"
#include "Logger.h"

using namespace std;

int main(int argc, char* argv[])
{

	Logger logger;
	
	logger.openLog();
	
	Driver driver;

	driver.fileDir_ = argv[1];

	driver.readInputFiles();

	driver.calcInvariants();
	
	driver.calcEquations();
	
	driver.solveSimultaneousEquations();
	
	driver.outputResult();

	logger.closeLog();
	
	return 0;
}
