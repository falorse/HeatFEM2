// ˅
#include "Logger.h"
#include "sstream"

std::fstream Logger::out;
// ˄

void Logger::openLog()
{
	// ˅
	std::string filename="./log.txt";
	
	// ログファイルを開く。outは、クラススタティック変数。
	out.open(filename.c_str(), std::ios::out);

	if (!out.is_open()) {
		std::cout << "file open error " << std::endl;
	}
	// ˄
}

void Logger::closeLog()
{
	// ˅
	out.close();
	// ˄
}

// ˅

// ˄
