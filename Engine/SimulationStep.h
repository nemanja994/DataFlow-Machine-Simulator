// Abstract simulation step class
#pragma once
#ifndef _SIMULATIONSTEP_H
#define _SIMULATIONSTEP_H

//#include "DataTypes.h"

typedef unsigned int ID;
typedef double Time;

class SimulationStep{
	Time schedTime=0; //The time at which the Event is scheduled to occur. Relative to the previous Event 
public:
	virtual void process(ID) = 0; // the Engine call this function when the Operation is ready to be processed
	virtual Time readTimeDelay() = 0; // read the Time Delay of certain operation
	virtual ID readID() = 0;  // read the operation ID
	void setSchedTime(Time t){ // set schedTime relative to other events
		schedTime = t;
	}
	Time getSchedTime(){ // read the scheduled time
		return schedTime;
	}
};

#endif