// Memory storage Singleton class
#pragma once
#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "MemData.h"
#include "MemExceptions.h"
#include <vector>
#include <string>
#include <fstream>
using std::ofstream;
using std::vector;
using std::string;

class Memory{
private:
	static Memory* memInstance;
	vector<MemData*> storage;
	ofstream MemFile;
public:
	static Memory* instance();
	void set(string, double); // Adds a new variable to storage by creating a new MemData object
	double get(string); // Find the variable with matching name in the storage and return its value if found
	static void printMemory();
	~Memory();
protected:
	Memory();
};

#endif