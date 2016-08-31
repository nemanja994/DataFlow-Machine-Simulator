// Compiler class implementation
#include "Compiler.h"
#include <fstream>
#include <iostream>
using std::ifstream;
using std::ofstream;
// ignore(skip) all characters until nlank space is found, including the blank space

Compiler* Compiler::compilerInstance = nullptr;

Compiler::Compiler(){};

Compiler* Compiler::instance(){
	if (!compilerInstance) compilerInstance = new Compiler();
	return compilerInstance;
}

void Compiler::compile(string fileName){
	instance()->compilerExe(fileName);
}

void Compiler::compilerExe(string fileName){
	string txtFileName = fileName;
	string imfFileName = txtFileName;
	string postfixFileName = txtFileName;
	imfFileName.replace(imfFileName.end()-3, imfFileName.end(), "imf"); // Change the txtFileName string from file.txt to file.imf
	postfixFileName.replace(postfixFileName.end() - 3, postfixFileName.end(), "pfn");
	this->txtFile=ifstream(txtFileName);  // set txtFile
	this->imfFile=ofstream(imfFileName); // set imfFile
	this->postfixFile = ofstream(postfixFileName);
	int processID = 0;
	if (txtFile){
		string txtLine;
		while (getline(txtFile, txtLine)){
			try{
				printToImfFile(infixToPostfix(txtLine),processID);
			}
			catch (VariableError& e){
				std::cerr << e.what() << std::endl;
				std::cout << "Press any key to Exit. The Program is badly written";
				char c;
				std::cin >> c;
				exit(1);
			}
			catch (ProgramError& e){
				std::cerr << e.what() << std::endl;
				std::cout << "Press any key to Exit. The Program is badly written";
				char c;
				std::cin >> c;
				exit(1);
			}
			catch (MismatchedParantheses& e){
				std::cerr << e.what() << std::endl;
				std::cout << "Press any key to Exit. The Program is badly written";
				char c;
				std::cin >> c;
				exit(1);
			}
		}
	}
	txtFile.close();
	imfFile.close();
}