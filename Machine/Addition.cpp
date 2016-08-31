// Addition Class implementation
#include "Operations.h"

Addition::Addition(ID opID, Operand* opA, Operand* opB):
	ArithmeticOperation(opID, opA, opB, Addition_Delay){}

bool Addition::isReady(){
	// if both Operand are initialised and available return true
	if (a && b && a->isAvailable() && b->isAvailable()) return true;
	else return false;
}

void Addition::execute(){
	if (output) output->setOutputValue(a->getOperandValue()+b->getOperandValue());
	delete a;
	delete b;
	a = nullptr;
	b = nullptr;
}