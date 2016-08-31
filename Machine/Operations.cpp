// Operation class implementation
#include "Operations.h"
#include "Machine.h"
#include <sstream>
#include <iomanip>
using std::stringstream;
#define logFile *(Machine::instance()->getLogFile())
#define SKIP input.ignore(256, ' '); 
// ignore(skip) all characters until nlank space is found, including the blank space

Operation::Operation(ID opID, Time t){
	id = opID;
	time = (Time)t;
}

void Operation::logOperation(ID opID, Time currentTime){
	string printID="";
	printID = printID + "(" + std::to_string(opID) + ")";
	logFile << std::setw(10)<<std::left << printID;
	logFile << (currentTime - time) << "ns/" << currentTime << "ns\n";
}

void Operation::putToSchedList(int& added){
	if (isReady()) {
		SimEngine::addOperation(this);
		added += 1; 
		// Added tracks how many operations are ready and added to scheduler
	}
}

Operation* Operation::makeOperation(string line){
	stringstream input(line);
	input.get(); // read first character from the line
	ID id;  input >> id; // read Operation ID
	SKIP;
	char sign = input.get(); // read the sign character from the input
	SKIP;
	Operand* a = Operand::makeOperand(input); // read the Operand from the input string
	SKIP;
	Operand* b = Operand::makeOperand(input); // read the Operand from the input string
	switch (sign){ // create new Operation
	case '=':
		return new Assignement(id, a, b);
		break;
	case '+':
		return new Addition(id, a, b);
		break;
	case '-':
		return new Subtraction(id, a, b);
		break;
	case '*':
		return new Multiplication(id, a, b);
		break;
	case '/':
		return new Dividation(id, a, b);
		break;
	case '^':
		return new Exponentation(id, a, b);
		break;
	default:
		return nullptr;
		break;
	}
}

bool Operation::checkID(int id){
	return this->id == id ? true : false;
}

void Operation::setOutput(Output* out){
	output = out;
}

void Operation::process(ID opID){
	Time currentTime = SimEngine::instance()->getCurrentTime();
	logOperation(opID, currentTime);
	this->execute(); // Call execute method which is unique to each operation
}

ArithmeticOperation::ArithmeticOperation(ID opID, Operand* opA, Operand* opB, Time t) :
Operation(opID, t){
	a = opA;
	b = opB;
}