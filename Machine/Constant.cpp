// Constant class implementation
#include "Operands.h"

Constant::Constant(double val){
	value = val;
}

double Constant::getOperandValue(){
	return value;
}

bool Constant::isAvailable(){ // Constant is always available
	return true;
}