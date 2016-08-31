// Subtraction Class implementation
#include "Operations.h"

Subtraction::Subtraction(ID opID, Operand* opA, Operand* opB) :
ArithmeticOperation(opID, opA, opB, Subtraction_Delay){}

bool Subtraction::isReady(){
	// if both Operand are initialised and available return true
	if (a && b && a->isAvailable() && b->isAvailable()) return true;
	else return false;
}

void Subtraction::execute(){
	if (output) output->setOutputValue(a->getOperandValue() - b->getOperandValue());
	delete a;
	delete b;
	a = nullptr;
	b = nullptr;
}