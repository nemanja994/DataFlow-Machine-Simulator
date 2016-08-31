// Machine implementation
#include "Machine.h"
#include "Memory.h"
#include <string>
#include <algorithm>
using std::string;
using std::ifstream;

Machine* Machine::machineInstance = nullptr;

Machine::Machine(){};

Machine::~Machine(){
	while (!operationList.empty()){
		Operation* tmp = operationList.back();
		operationList.pop_back();
		delete tmp; tmp = nullptr;
	}
}

Machine* Machine::instance(){
	if (!machineInstance) machineInstance = new Machine();
	return machineInstance;
}

ofstream* Machine::getLogFile(){
	return &logFile;
}

vector<Operation*>* Machine::getOpList(){
	return &operationList;
}

void Machine::executeProgram(string txtFileName){
	instance()->exec(txtFileName);
}

void Machine::exec(string txtFileName){
	// change the filename.txt to filename.imf and filename.log
	string imfFileName = txtFileName;
	string logFileName = txtFileName;
	imfFileName.replace(imfFileName.end()-3, imfFileName.end(), "imf"); // the last 3 char in filename were .txt
	logFileName.replace(logFileName.end()-3, logFileName.end(), "log");
	logFile=ofstream(logFileName);
	ifstream imfFile(imfFileName);
	if (imfFile){
		string txtline;
		while (getline(imfFile, txtline)){
			operationList.push_back(Operation::makeOperation(txtline));
		}
	}
	int availableOperations = 0; // count how many operations have been put to scheduler
	while (1){ // while there are available operations put them to scheduler
		std::for_each(operationList.begin(), operationList.end(), [&](Operation* op){
			op->putToSchedList(availableOperations); 
		});
		while (1) {
			if (!SimEngine::instance()->processOperations()) break;
		}
		if (operationList.size() == availableOperations) break;
	}
	Memory::printMemory();
	imfFile.close();
	logFile.close();
}