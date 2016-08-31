// Exponentation class implementation
#include "Operations.h"
#include <cmath>

Exponentation::Exponentation(ID opID, Operand* opA, Operand* opB) :
	ArithmeticOperation(opID, opA, opB, Exponentation_Delay){}

bool Exponentation::isReady(){
	if (a && b && a->isAvailable() && b->isAvailable()) return true;
	else return false;
}

void Exponentation::execute(){
	if (output) output->setOutputValue(pow(a->getOperandValue(),b->getOperandValue()));
	delete a;
	delete b;
	a = nullptr;
	b = nullptr;
}