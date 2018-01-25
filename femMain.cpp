#include <iostream>
#include <string>

#include "Driver.h"
#include "Logger.h"
#include "time.h"
#include "omp.h"

using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 2){
        cout << "invalid input" << endl;
        cout << "usage: ./femMain input_file_directory" << endl <<
            "input_file_firectory must have mash.dat and boundary.dat" << cout;
        exit(1);
    }
    
	Logger logger;
	logger.openLog();
	
	Driver driver;

	driver.fileDir_ = argv[1];
	
	driver.readInputFiles();
	
	driver.calcElemsInvariants();
	
	driver.makeSimultaneousEquations();

	driver.solveSimultaneousEquations();
	
	driver.outputNodeTemperatures();

	logger.closeLog();

	return 0;
}
