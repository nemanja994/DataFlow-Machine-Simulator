// Dividation class implementation
#include "Operations.h"

Dividation::Dividation(ID opID, Operand* opA, Operand* opB) :
ArithmeticOperation(opID, opA, opB, Dividation_Delay){}

bool Dividation::isReady(){
	if (a && b && a->isAvailable() && b->isAvailable()) return true;
	else return false;
}

void Dividation::execute(){
	if (output) output->setOutputValue(a->getOperandValue() / b->getOperandValue());
	delete a;
	delete b;
	a = nullptr;
	b = nullptr;
}