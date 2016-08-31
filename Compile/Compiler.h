// Compiler singleton class
#pragma once
#ifndef _COMPILER_H
#define _COMPILER_H

#include "CompilerErrors.h"
#include <string>
#include <fstream>
using std::ofstream;
using std::ifstream;
using std::string;

class Compiler{
private:
	static Compiler* compilerInstance;
	void compilerExe(string);
	string infixToPostfix(string); // convert from infix to postfix notation ( The compiler can recognize +,-,*,/,^,(,) signs)
	void printToImfFile(string,int&); // explode postfix notation to individual steps
	// utility functions for input string processing
	bool isNumber(char);
	bool isVariable(char);
	bool isOperator(char);
	bool hasHigherPrecedence(char, char); // checks which operator has higher precedence
	int getOperatorWeight(char);
	bool isRightAssociative(char);
	ifstream txtFile;
	ofstream imfFile, postfixFile;
public:
	static Compiler* instance();
	static void compile(string);
protected:
	Compiler();
};

#endif