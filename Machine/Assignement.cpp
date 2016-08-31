// Assignement class implementation
#include "Operations.h"

Assignement::Assignement(ID opID, Operand* opA, Operand* opB) :
	ArithmeticOperation(opID, opA, opB, Assignement_Delay){}

bool Assignement::isReady(){
	if (a && b && b->isAvailable()) return true;
	else return false;
}

void Assignement::execute(){
	((Variable *)a)->setVarValue(b->getOperandValue());
	if (output==nullptr) output->setOutputValue(b->getOperandValue());
	delete a;
	a = nullptr;
	delete b;
	b = nullptr;
}