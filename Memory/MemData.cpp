// MemData implementation
#include "MemData.h"

MemData::MemData(char name, double value){
	varName = name;
	varValue = value;
}

char MemData::getVarName(){
	return varName;
}

double MemData::getVarValue(){
	return varValue;
}

ofstream& operator<<(ofstream& out, MemData* data){
	out << data->varName << "=" << data->varValue<<"\n";
	return out;
}