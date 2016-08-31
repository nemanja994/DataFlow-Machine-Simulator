// Various tokens recognized by the compiler
#pragma once
#ifndef _TOKEN_H
#define _TOKEN_H

#include <fstream>
using std::ofstream;

class Token{ // Abstract Token type
public:
	virtual void printOperand(ofstream&) = 0;
	friend ofstream& operator << (ofstream&, Token*);
};

class VariableToken:public Token{ // Variable
private:
	char name;
public:
	VariableToken(char);
	void printOperand(ofstream&);
};

class NumberToken:public Token{ // Number(Constant)
private:
	double value;
public:
	NumberToken(double);
	void printOperand(ofstream&);
};

class ResultToken :public Token{ // Result of the previous step(s)
private:
	int id; // processID
public:
	ResultToken(int);
	void printOperand(ofstream&);
};

#endif