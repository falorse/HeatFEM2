#include <iostream>
#include <string>

#include "Driver.h"

using namespace std;

int main(int argc, char* argv[]){
    cout<<argc<<endl;
    
    Driver driver;


    driver.fileDir_=argv[1];
        cout<<driver.fileDir_<<endl;
    
    driver.readInputFiles();
    
    return 0;
}
