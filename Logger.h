



#ifndef LOGGER_H_
#define LOGGER_H_


#include "iostream"
#include "fstream"


class Logger
{
	
	
	

public:

	void openLog();

	void closeLog();

	
public:
	static std::fstream out;
	
	~Logger(){};
	
	Logger(){};
	
protected:
	
private:
	
	
};





#endif	// LOGGER_H_




