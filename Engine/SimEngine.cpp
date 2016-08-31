#include "SimEngine.h"
#include <iterator>
#include <algorithm>
#define OpList (SimEngine::instance()->getOpList())

SimEngine* SimEngine::engineInstance = nullptr;

SimEngine* SimEngine::instance(){
	if (!engineInstance) engineInstance = new SimEngine();
	return engineInstance;
}

SimEngine::SimEngine(){}

void SimEngine::addOperation(SimulationStep* op){
	if (op == nullptr) return;
	op->setSchedTime(op->readTimeDelay());
	Time stime = op->getSchedTime();
	list<SimulationStep*>::iterator it = OpList->begin();
	while (it != OpList->end() && stime >= (*it)->getSchedTime()){
		stime -= (*it)->getSchedTime();
		++it;
	}
	if (it != OpList->end()){
		(*it)->setSchedTime((*it)->getSchedTime() - stime);
	}
	op->setSchedTime(stime);
	if (it != OpList->begin()) it;
	if (OpList->empty()) OpList->push_back(op);
	else OpList->insert(it, op);
}

Time SimEngine::getCurrentTime(){
	return currentTime;
}

bool SimEngine::processOperations(){
	while (instance()->processStep()); // while there are operations in the list
	return (!instance()->operationList.empty());;
}

bool SimEngine::processStep(){
	SimulationStep* step = operationList.front(); 
	if (step == nullptr) return false;
	this->currentTime += step->getSchedTime();
	if (step) step->process(step->readID());
	operationList.pop_front();
	return !operationList.empty();
}