// Memory Exceptions
#pragma once
#ifndef _MEMEXCEPT_H
#define _MEMEXCEPT_H

#include <exception>
using std::exception;

class MemExceptions :public exception{
protected:
	const char* errormsg;
public:
	MemExceptions(const char* msg="Error") :exception(msg){};
	const char* what() const throw() { return errormsg; }
};

class VariableNotFoundException :public MemExceptions{
public:
	VariableNotFoundException(const char* msg = "Variable not found in memory"){
		errormsg = msg;
	}
};

#endif