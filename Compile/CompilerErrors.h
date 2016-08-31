// Compiler Exceptions
#pragma once
#ifndef _COMPILERERROR_H
#define _COMPILERERROR_H

#include <exception>
using std::exception;

class CompilerExceptions :public exception{
protected:
	const char* errormsg;
public:
	CompilerExceptions(const char* msg = "Error") :exception(msg){};
	const char* what() const throw() { return errormsg; }
};

class ProgramError :public CompilerExceptions{
public:
	ProgramError(const char* msg = "The program is badly written"){
		errormsg = msg;
	}
};

class VariableError :public CompilerExceptions{
public:
	VariableError(const char* msg = "Variable name can only be one character long"){
		errormsg = msg;
	}
};

class MismatchedParantheses :public CompilerExceptions{
public:
	MismatchedParantheses(const char* msg = "There are mismatched parentheses"){
		errormsg = msg;
	}
};

#endif