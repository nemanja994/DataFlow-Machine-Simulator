#pragma once
#ifndef _OPERATIONS_H
#define _OPERATIONS_H

#include "..\Engine\SimEngine.h"
#include "..\Engine\SimulationStep.h"
#include "Operands.h"
#include <string>
using std::string;

/*     Operation Delay Information        */
#define Assignement_Delay 3
#define Addition_Delay 5
#define Subtraction_Delay 5
#define Multiplication_Delay 8
#define Dividation_Delay 8
#define Exponentation_Delay 10
/*-----------------------------------------*/

class Operation:public SimulationStep{ // Abstract Operation Class
protected:
	Time time;
	ID id;
	Output* output; // if this operation result is the input of the other operation
	Operation(ID,Time);
	void logOperation(ID, Time); // log the Operation ID and the Time needed for the simulation step to Output File
public:
	void process(ID); // The Scheduler calls this function when it process the event
	virtual void execute()=0; // Each operation has different execute method
	virtual bool isReady() = 0;
	Time readTimeDelay(){ return time;}
	ID readID(){ return id; };
	bool checkID(int id); // check whether this operation ID is the same as the id passed to the method
	void setOutput(Output*); 
	void putToSchedList(int&); // put to simulation engine and count how many operations have been put to scheduled list of operations
	static Operation* makeOperation(string); // create an Operation from the input string
};

class ArithmeticOperation :public Operation{ // Abstract Arithmetic Operation
protected:
	Operand* a;
	Operand* b;
	ArithmeticOperation(ID,Operand*, Operand*,Time);
public:
	virtual bool isReady() = 0;
};

class Assignement :public ArithmeticOperation{
public:
	void execute();
	bool isReady();
	Assignement(ID, Operand*, Operand*);
	~Assignement(){
		delete a; a = nullptr;
		delete b; b = nullptr;
	}
};

class Addition :public ArithmeticOperation{
public:
	void execute();
	bool isReady();
	Addition(ID, Operand*, Operand*);
	~Addition(){
		delete a; a = nullptr;
		delete b; b = nullptr;
	}
};

class Subtraction :public ArithmeticOperation{
public:
	void execute();
	bool isReady();
	Subtraction(ID, Operand*, Operand*);
	~Subtraction(){
		delete a; a = nullptr;
		delete b; b = nullptr;
	}
};

class Multiplication : public ArithmeticOperation{
public:
	void execute();
	bool isReady();
	Multiplication(ID, Operand*, Operand*);
	~Multiplication(){
		delete a; a = nullptr;
		delete b; b = nullptr;
	}
};

class Dividation : public ArithmeticOperation{
public:
	void execute();
	bool isReady();
	Dividation(ID, Operand*, Operand*);
	~Dividation(){
		delete a; a = nullptr;
		delete b; b = nullptr;
	}
};

class Exponentation : public ArithmeticOperation{
public:
	void execute();
	bool isReady();
	Exponentation(ID, Operand*, Operand*);
	~Exponentation(){
		delete a; a = nullptr;
		delete b; b = nullptr;
	}
};

#endif