// Multiplication class implementation
#include "Operations.h"

Multiplication::Multiplication(ID opID, Operand* opA, Operand* opB) :
	ArithmeticOperation(opID, opA, opB, Multiplication_Delay){}

bool Multiplication::isReady(){
	if (a && b && a->isAvailable() && b->isAvailable()) return true;
	else return false;
}

void Multiplication::execute(){
	if (output) output->setOutputValue(a->getOperandValue() * b->getOperandValue());
	delete a;
	delete b;
	a = nullptr;
	b = nullptr;
}