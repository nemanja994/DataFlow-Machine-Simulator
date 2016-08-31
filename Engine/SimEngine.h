// Simulation Engine singleton class
#pragma once
#ifndef _SIMENGINE_H
#define _SIMENGINE_H

#include "SimulationStep.h"
#include <list>
using std::list;

class SimEngine{
private:
	Time currentTime=0; // current simulation time
	static SimEngine* engineInstance;
	list<SimulationStep*> operationList; // list of operations ready to be processed
	bool processStep(); // process one Step in simulation
public:
	static SimEngine* instance();
	static void addOperation(SimulationStep*);
	list<SimulationStep*>* getOpList(){ return &operationList; }
	Time getCurrentTime(); 
	static bool processOperations(); // process the operations in the list
protected:
	SimEngine();
};

#endif