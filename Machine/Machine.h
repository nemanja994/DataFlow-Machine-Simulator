// Class representing the Machine which process the operations
// Singleton Class
#pragma once
#ifndef _MACHINE_H
#define _MACHINE_H

#include "Operations.h" 
#include "..\Engine\SimEngine.h"
#include <fstream>
#include <string>
#include <vector>
using std::ofstream;
using std::vector;
using std::string;

class Machine{
private:
	static Machine* machineInstance;
	ofstream logFile;
	vector<Operation*> operationList;
	void exec(string);
public:
	static Machine* instance();
	ofstream* getLogFile();
	vector<Operation*>* getOpList();
	static void executeProgram(string);
	~Machine();
protected:
	Machine();
};

#endif