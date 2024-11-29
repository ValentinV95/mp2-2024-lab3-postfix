// реализация функций и классов для вычисления арифметических выражений
#include "arithmetic.h"
#include "RPN.h"
#include <iostream>
#include "myvector.h"
#include "parser.h"

calculator::calculator(std::string str) {
	operation::fillOperations();

	for (auto it = str.begin(); it != str.end(); ++it) if (*it == ' ') str.erase(it--); // deleting spaces
	int counter = 0;
	std::string tmpstring;
	size_t j;
	bool operatorFound = true;

	for (size_t i = 0; i < str.length(); ++i) { // parsing
		if (str[i] == ',') { // !!!
			operatorFound = true;
			continue;
		}
		tmpstring = "";
		// if previous was an operator (but not the ')'): check for unary minus
		if (operatorFound && str[i] == '-') { // unary minus part
			if ((i > 0 && str[i - 1] != ')') || i == 0) { // if there is not ')' before of it is the begining of the string
				notActuallyData.push_back(new operation{ "~", static_cast<int>(i) });
				continue;
			}
		}
		operatorFound = false; // if Operator found
		// checking if it is number
		// idea is to count e (E), than check on +, -. 
		if (('0' <= str[i] && str[i] <= '9') || str[i] == '.') { // if digit
			bool eAppeared = false;
			bool dotAppeared = false;
			tmpstring = "";
			for (j = i; j < str.length(); ++j) {
				if (eAppeared == false && (str[j] == 'e' || str[j] == 'E')) { // if e
					eAppeared = true;
					tmpstring += str[j];
					if (j + 1 < str.length() && (str[j + 1] == '+' || str[j + 1] == '-')) { // if there is a + or - after e
						tmpstring += str[++j]; // add it to number
					}
					continue;
				}
				if (dotAppeared == false && str[j] == '.') { // if there is a dot
					dotAppeared = true;
					tmpstring += str[j]; // add it to number
					continue;
				}
				if (str[j] > '9' || str[j] < '0')
					break;
				tmpstring += str[j];
			}
			notActuallyData.push_back(new constant{ tmpstring, static_cast<int>(i) });
			i = j - 1;
			continue;
		}

		tmpstring = "";
		for (j = i; j < str.length(); ++j) { // checking 1 symbol, 1+2 symbol, 1+2+3 symbol etc...
			tmpstring += str[j];
			if (operation::isOperation(tmpstring)) { // if it is operation
				notActuallyData.push_back(new operation{ tmpstring, static_cast<int>(i) }); // add to lexems
				operatorFound = true;
				i = j;
				break;
			}
		}
		if (operatorFound) continue;
		tmpstring = "";
		for (j = i + 1; j < str.length(); ++j) { // adding as variable;
			tmpstring += str[j - 1]; // !!! a comma
			if (operation::canBeAfterOperand({ str[j] }) || str[j] == ',') { // if there is an operator than handle an operand after it
				variable::vectorOfVariablesNames.push_back(tmpstring); // add to variables
				notActuallyData.push_back(new variable{ tmpstring, static_cast<int>(i) }); // add to lexems
				notActuallyData.push_back(new operation{ { str[j] }, static_cast<int>(j) }); // and next operation too
				i = j;
				break;
			}
		}
		if (j == str.length()) {
			tmpstring += str[j - 1]; // if it is the end of string
			variable::vectorOfVariablesNames.push_back(tmpstring); // add to variables
			notActuallyData.push_back(new variable{ tmpstring, static_cast<int>(i) }); // and to lexems
			i = j - 1;
		}
	}
	// delete doubles on vectorOfVariablesNames
	myVector<std::string> tmpvec;
	for (size_t i = 0; i < variable::vectorOfVariablesNames.size(); ++i) {
		bool foundTheSameName = false;
		for (size_t j = 0; j < tmpvec.size(); ++j) { // add to tmp if there is no variable with this name
			if (tmpvec[j] == variable::vectorOfVariablesNames[i]) {
				foundTheSameName = true;
				break;
			}
		}
		if (!foundTheSameName) tmpvec.push_back(variable::vectorOfVariablesNames[i]);
	}
	variable::vectorOfVariablesNames = tmpvec;
	variable::VectorOfVariablesValues.resize(tmpvec.size());
	isVariablesExist = variable::vectorOfVariablesNames.size() > 0;
}
bool calculator::araThereAnyVariables() noexcept {
	return isVariablesExist;
}
void calculator::askForVariablesValues() {
	std::string str;
	for (size_t i = 0; i < variable::vectorOfVariablesNames.size(); ++i) {
		std::cout << "Enter the " << variable::vectorOfVariablesNames[i] << " variable\n";
		std::getline(std::cin, str);
		try {
			variable::VectorOfVariablesValues[i] = parser(str);
		}
		catch (std::exception& e) { // parser exception
			std::cout << "Bad number input\n";
			int it = std::stoi(e.what());
			std::cout << str.substr(0, it) << " ";
			std::cout << "\033[31m" << str[it] << "\033[0m";
			if (it + 1 < str.length()) std::cout << " " << str.substr(it + 1, str.length()) << std::endl;
			--i;
		}
	}
	for (size_t i = 0; i < notActuallyData.size(); ++i) {
		if (notActuallyData[i]->isOperation()) continue;
		try {
			dynamic_cast<operand*>(notActuallyData[i])->fillValue();
		}
		catch (std::exception& e) { // parser exception
			std::string errstr = e.what();
			std::string numstr = "";
			size_t j;
			for (j = 0; j < errstr.size(); ++j) {
				numstr += errstr[j];
				if (errstr[j] == 'E') break;
			}
			int it = std::stoi(numstr);
			errstr = std::to_string(it + notActuallyData[i]->getPos()) + errstr.substr(j, errstr.length());
			throw std::invalid_argument(errstr);
		}
	}
}
double calculator::calculate() {
	RPN rpn(notActuallyData);
	return rpn.calculate();
}
calculator::~calculator() {
	for (size_t i = 0; i < notActuallyData.size(); ++i) {
		delete[] notActuallyData[i];
	}
}