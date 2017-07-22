#include <iostream>
#include <string>

#include "Driver.h"

using namespace std;

int main(int argc, char* argv[])
{

	Driver driver;

	driver.fileDir_ = argv[1];

	driver.readInputFiles();

	driver.calcInvariants();
	
	driver.calcEquations();
	
	driver.solveSimultaneousEquations();
	
	driver.outputResult();

	return 0;
}
