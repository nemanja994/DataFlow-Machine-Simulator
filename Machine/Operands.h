// Class which represent various type of operands
#pragma once
#ifndef _OPERANDS_H
#define _OPERANDS_H

#include <string>
#include <istream>
using std::string;
using std::istream;

class Operand{ // Abstract Operand Class
public:
	virtual double getOperandValue() = 0;
	virtual bool isAvailable() = 0;
	static Operand* makeOperand(istream&); // create Operand from the input stream
};

class Constant :public Operand{ // class representing a Constant number
private:
	double value;
public:
	Constant(double);
	double getOperandValue();
	bool isAvailable();
};

class Variable :public Operand{ // class which represents Variable
private:
	char varName;
public:
	Variable(char);
	double getOperandValue();
	void setVarValue(double);
	bool isAvailable();
};

class Output :public Operand{ 
	// class which represent an output of some operation that is used as input variable in the other operation
private:
	int operationID;
	double value;
	bool available;
public:
	Output(int);
	double getOperandValue();
	void setOutputValue(double);
	bool isAvailable();
};

#endif