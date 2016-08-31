// Implementation of utility functions for string processing
#include "Compiler.h"

bool Compiler::isNumber(char input){
	if (isdigit(input)) return true;
	else return false;
}

bool Compiler::isVariable(char input){
	if (isalpha(input)) return true;
	else return false;
}

bool Compiler::isOperator(char input){
	switch (input){
	case '=':
		return true;
		break;
	case '+':
		return true;
		break;
	case  '-':
		return true;
		break;
	case '*':
		return true;
		break;
	case '/':
		return true;
		break;
	case '^':
		return true;
		break;
	default:
		return false;
		break;
	}
}

int Compiler::getOperatorWeight(char op){
	switch (op){
	case '+':
		return 2;
		break;
	case  '-':
		return 2;
		break;
	case '*':
		return 3;
		break;
	case '/':
		return 3;
		break;
	case '^':
		return 4;
		break;
	}
}

bool Compiler::isRightAssociative(char op){
	return op == '^';
}

bool Compiler::hasHigherPrecedence(char op1, char op2){
	// second operation is the operation from the top of the stack!!!
	int operator1 = getOperatorWeight(op1);
	int operator2 = getOperatorWeight(op2);
	if (!isRightAssociative(op1) && operator1 <= operator2) return true;
	if (isRightAssociative(op1) && operator1 < operator2) return true;
	return false;
}