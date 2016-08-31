// Methods for Infix to Postfix notation conversion
#include "Compiler.h"
#include "Tokens.h"
#include <sstream>
#include <stack>
using std::stack;
using std::stringstream;

string Compiler::infixToPostfix(string infixLine){
	// this compiler is using Shunting yard algorith for converting infix to postfix notation
	string postfixLine;
	stack<char> operatorStack;
	bool equalSign; int equalCount = 0;
	int operatorCount = 0;
	int numberCount = 0;
	for (int i = 0; i < infixLine.length(); i++){ // cycle trough infixLine
		// skip if the character is blank space
		if (infixLine[i] == ' ') continue;
		// if char is variable and next char is not a variable
		if (isVariable(infixLine[i]) && !isVariable(infixLine[i + 1])){
			postfixLine.push_back(infixLine[i]);
			postfixLine.push_back(' '); // add a space between characters
			numberCount += 1;
			continue;
		} // if variable name is two or more characters long throw an exception
		else if (isVariable(infixLine[i]) && isVariable(infixLine[i + i])){
			throw VariableError();
			break;
		}
		// if character is an operator sign, and next char is not an operator
		if (isOperator(infixLine[i]) && !isOperator(infixLine[i + 1])){
			if (infixLine[i] == '='){ // If the token is an operator '='
				equalSign = true; equalCount += 1;
				if (equalCount > 1) throw ProgramError();
				postfixLine.push_back(infixLine[i]);
				postfixLine.push_back(' ');
				continue;
			}
			/* If the token is an operator, o1, then:
			while there is an operator token o2, at the top of the operator stack and either
			o1 is left - associative and its precedence is less than or equal to that of o2, or
			o1 is right associative, and has precedence less than that of o2,
			pop o2 off the operator stack, onto the output queue;
			at the end of iteration push o1 onto the operator stack. */
			while (!operatorStack.empty() && hasHigherPrecedence(infixLine[i], operatorStack.top()) && operatorStack.top() != '('){
				postfixLine.push_back(operatorStack.top());
				operatorStack.pop();
				postfixLine.push_back(' ');
			}
			operatorStack.push(infixLine[i]);
			operatorCount += 1;
			continue;
		} // if the character is an operator and the next character is also an operator sign throw an error
		else if (isOperator(infixLine[i]) && isOperator(infixLine[i + 1])) {
			throw ProgramError();
			break;
		}
		// if char is number
		if (isNumber(infixLine[i])){
			if (isNumber(infixLine[i + 1])){ // if next char is number
				postfixLine.push_back(infixLine[i]);
				continue;
			}
			else if (infixLine[i + 1] == '.' && isNumber(infixLine[i + 2])){
				postfixLine.push_back(infixLine[i]);
				continue;
			}
			else {
				postfixLine.push_back(infixLine[i]);
				postfixLine.push_back(' '); // add a space between characters
				numberCount += 1;
				continue;
			}
		}
		if (infixLine[i] == '.' && isNumber(infixLine[i - 1]) && isNumber(infixLine[i + 1])){
			// if char is '.' and characters before and after it are numbers, put '.' to return string
			postfixLine.push_back(infixLine[i]);
			continue;
		}
		// if the character is a '('
		if (infixLine[i] == '(') {
			operatorStack.push(infixLine[i]);
			continue;
		}
		// if the character is a ')'
		if (infixLine[i] == ')') {
			while (!operatorStack.empty()){
				char operation = operatorStack.top();
				if (operation == '(') break; // left parantheses has been found
				else{
					postfixLine.push_back(operation);
					operatorStack.pop();
					postfixLine.push_back(' ');
				}
			}
			if (operatorStack.empty()) throw MismatchedParantheses();
			else {
				operatorStack.pop(); // pop the '(' sign from the stack
				continue;
			}
		}
		// if the character is not a variable, number or an operator throw an error
		throw ProgramError();
		break;
	}
	// pop the remaining operator signs from the stack
	if (!operatorStack.empty() && (operatorStack.top() == '(' || operatorStack.top() == ')')) throw MismatchedParantheses();
	while (!operatorStack.empty()){
		postfixLine.push_back(operatorStack.top());
		operatorStack.pop();
		postfixLine.push_back(' ');
	}
	// if the program is badly written throw an error
	if (equalSign){
		if (!(operatorCount + 2 == numberCount)) throw ProgramError();
	}
	else if (!(numberCount == operatorCount + 1)) throw ProgramError();
	postfixFile << postfixLine << "\n";
	return postfixLine;
}

void Compiler::printToImfFile(string postfixLine, int& processID){
	stack<Token*> operandStack;
	stringstream postfixInput(postfixLine);
	VariableToken* resultVar;
	char equalSign;
	if (isVariable(postfixLine[0]) && postfixLine[2] == '='){ // if postfixLine starts with 'var ='
		resultVar = new VariableToken(postfixInput.get());
		postfixInput.get(); // skip white space
		equalSign = postfixInput.get(); // read equal sign;
		postfixInput.get();
	}
	while (postfixInput.peek() != EOF){
		// skip blank space
		if (postfixInput.peek() == ' ') {
			postfixInput.get();
			continue;
		}
		// if the character is a Variable push it to the operandStack
		if (isVariable(postfixInput.peek())){
			operandStack.push(new VariableToken(postfixInput.get()));
			continue;
		}
		// if the character is a number push it to the operandStack
		if (isNumber(postfixInput.peek())){
			double val; postfixInput >> val; // read the double value from the input string
			operandStack.push(new NumberToken(val));
			continue;
		}
		// if the character is an operator
		if (isOperator(postfixInput.peek())){
			processID += 1;
			char sign = postfixInput.get(); // read the operator type
			imfFile << "(" << processID << ") " << sign << " ";
			Token* operand1 = operandStack.top();
			operandStack.pop();
			Token* operand2 = operandStack.top();
			operandStack.pop();
			imfFile << operand2 << " ";
			imfFile << operand1 << "\n";
			delete operand1; operand1 = nullptr;
			delete operand2; operand2 = nullptr;
			operandStack.push(new ResultToken(processID));
			continue;
		}
	}
	if (resultVar && equalSign == '='){
		processID += 1;
		imfFile << "(" << processID << ") " << equalSign << " ";
		imfFile << resultVar << " ";
		imfFile << operandStack.top() << "\n";
		operandStack.pop();
	}
}