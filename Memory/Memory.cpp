// Memory implementation
#include "Memory.h"
#include <algorithm>
using std::iterator;

Memory* Memory::memInstance = nullptr;

Memory::Memory(){};

Memory::~Memory(){
	while (!storage.empty()){
		MemData* tmp = storage.back();
		storage.pop_back();
	}
}

Memory* Memory::instance(){
	if (!memInstance) memInstance = new Memory();
	return memInstance;
}

void Memory::set(string varName, double val){
	storage.push_back(new MemData(varName[0], val));
}

double Memory::get(string varName){
	vector<MemData*>::iterator it = std::find_if(storage.begin(), storage.end(),[&](MemData* variable)->bool{
		return variable->getVarName() == varName[0] ? true : false;});
	if (it == storage.end()) throw VariableNotFoundException();
	else return (*it)->getVarValue();
}

void Memory::printMemory(){
	Memory::instance()->MemFile = ofstream("Memory.mdb");
	std::for_each(Memory::instance()->storage.begin(), Memory::instance()->storage.end(), [&](MemData* data){
		Memory::instance()->MemFile << data;
	});
}