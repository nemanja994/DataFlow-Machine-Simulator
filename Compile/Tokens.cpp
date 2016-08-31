// Token Class implementation
#include "Tokens.h"

ofstream& operator<<(ofstream& out, Token* operand){
	operand->printOperand(out);
	return out;
}

VariableToken::VariableToken(char name){
	this->name = name;
}

void VariableToken::printOperand(ofstream& out){
	out << name;
}

NumberToken::NumberToken(double value){
	this->value = value;
}

void NumberToken::printOperand(ofstream& out){
	out << value;
}

ResultToken::ResultToken(int id){
	this->id = id;
}

void ResultToken::printOperand(ofstream& out){
	out << "(" << id << ")";
}