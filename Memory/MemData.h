// Class which represents variable data stored in memory
#pragma once
#ifndef _MEMDATA_H
#define _MEMDATA_H

#include <string>
#include <fstream>
using std::ofstream;
using std::string;

class MemData{
	friend class Memory;
private:
	char varName;
	double varValue;
	MemData(char,double);
	char getVarName(); // a helper method used for returning variable name
	double getVarValue(); // a helper method used for reading the variable value from the storage
	friend ofstream& operator << (ofstream&, MemData*);
};

#endif