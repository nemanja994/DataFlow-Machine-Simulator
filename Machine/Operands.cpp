#include "Operands.h"
#include <sstream>

Operand* Operand::makeOperand(istream& input){
	if (isdigit(input.peek())){
		// next char is digit
		double number; 
		input >> number; // read the number from the input string
		Operand*a = new Constant(number);
		return a;
	}
	if (isalpha(input.peek())){
		// next char is variable name
		char name;
		input >> name;
		Operand* a = new Variable(name);
		return a;
	}
	if (input.peek() == '('){
		// next operand is the output of the previous operation
		input.get(); //skip '(' character and read id afterwards
		int id; 
		input >> id;
		Operand* a = new Output(id);
		return a;
	}
}