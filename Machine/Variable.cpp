// Variable class implementation
#include "Operands.h"
#include "Memory.h"

Variable::Variable(char name){
	varName = name;
}

void Variable::setVarValue(double val){
	string variableName;
	variableName.push_back(varName);
	Memory::instance()->set(variableName, val);
}

double Variable:: getOperandValue(){
	string variableName;
	variableName.push_back(varName);
	return Memory::instance()->get(variableName);
}

bool Variable::isAvailable(){ 
	// Variable is only available if it's value is set and stored in the memory
	try{
		getOperandValue();
		return true;
	}
	catch(VariableNotFoundException& e){
		return false;
	}
}