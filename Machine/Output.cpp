// Output class implementation
#include "Operands.h"
#include "Machine.h"
#include <algorithm>
using std::iterator;
using std::vector;
#define OpList (Machine::instance()->getOpList())

Output::Output(int id){
	operationID = id;
	available = false;
	// find the Operation with the same ID, and set it's output as this output
	vector<Operation*>::iterator it = std::find_if(OpList->begin(), OpList->end(), [&](Operation* op)->bool{
		if (op->checkID(id)) return true;
		else return false;
	});
	(*it)->setOutput(this);
}

double Output::getOperandValue(){
	return value;
}

void Output::setOutputValue(double val){
	available = true;
	value = val;
}

bool Output::isAvailable(){
	return available;
}