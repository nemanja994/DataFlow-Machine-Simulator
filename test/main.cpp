#include "DataFlowSimulator.h"
#include <ctime>
#include <iostream>

int main(int argc, char *argv[]){
	int startTime = clock();
	Compiler::compile(argv[1]);
	Machine::executeProgram(argv[1]);
	std::cout << "Execution time: " << (clock() - startTime) / double(CLOCKS_PER_SEC) * 1000 << " ms" << std::endl;
	return 0;
}