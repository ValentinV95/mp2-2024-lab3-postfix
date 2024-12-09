// реализация функций и классов для вычисления арифметических выражений
#include "arithmetic.h"
#include "RPN.h"
#include <iostream>
#include "myvector.h"
#include "parser.h"

calculator::calculator(std::string str) {
	operation::fillOperations();
	variable::vectorOfVariablesNames.resize(0);
	variable::VectorOfVariablesValues.resize(0);
	
	int counter = 0;
	std::string tmpstring;
	size_t j;
	bool operatorFound = true;

	for (size_t i = 0; i < str.length(); ++i) { // parsing
		if (str[i] == ' ') continue;
		tmpstring = "";
		// if previous was an operator (but not the ')'): check for unary minus
		if (operatorFound && str[i] == '-') { // unary minus part
			if ((notActuallyData.size() > 0 && notActuallyData[notActuallyData.size() - 1]->getSym() != ")") || notActuallyData.size() == 0) { // if there is not ')' before of it is the begining of the string
				notActuallyData.push_back(new operation{ "~", static_cast<int>(i) });
				continue;
			}
		}
		operatorFound = false; // if Operator found
		// checking if it is number
		// idea is to count e (E), than check on +, -. 
		// NUMBER PARSING
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

		// OPERATOR PARSING
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

		// VARIABLE PARSING
		tmpstring = "";
		for (j = i + 1; j < str.length(); ++j) { // adding as variable;
			tmpstring += str[j - 1]; // !!! a comma
			if (str[j] == ' ') {
				variable::vectorOfVariablesNames.push_back(tmpstring); // add to variables
				notActuallyData.push_back(new variable{ tmpstring, static_cast<int>(i) }); // add to lexems
				i = j;
				break;
			}
			else if (operation::canBeAfterOperand({ str[j] })) { // if there is an operator than handle an operand after it
				variable::vectorOfVariablesNames.push_back(tmpstring); // add to variables
				notActuallyData.push_back(new variable{ tmpstring, static_cast<int>(i) }); // add to lexems
				notActuallyData.push_back(new operation{ { str[j] }, static_cast<int>(j) }); // and next operation too
				operatorFound = true;
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

//	for (size_t i = 0; i < notActuallyData.size(); ++i) std::cout << notActuallyData[i]->getSym() << " ";
//	std::cout << std::endl;
	check();
}
const myVector<lexem*>& calculator::getData() const noexcept { return notActuallyData; }
void calculator::check() {
	for (size_t i = 0; i < notActuallyData.size(); ++i) {
		if (notActuallyData[i]->isOperation()) { // operator branch
			if (notActuallyData[i]->getSym() == ")") { // ) operator branch
				if (i == 0) // ) as first symbol
					throw std::invalid_argument(std::to_string(notActuallyData[i]->getSym().length()) + "L" + std::to_string(notActuallyData[i]->getPos()) + "ENo closing bracket for this bracket, code: 0");
				if (notActuallyData[i - 1]->getSym() == "(") // () case
					throw std::invalid_argument(std::to_string(notActuallyData[i]->getSym().length()) + "L" + std::to_string(notActuallyData[i]->getPos()) + "EMissing operand, code: 1");
				if (notActuallyData[i - 1]->isOperation() && notActuallyData[i - 1]->getSym() != ")") // op)... instead of op var)...
					throw std::invalid_argument(std::to_string(notActuallyData[i - 1]->getSym().length()) + "L" + std::to_string(notActuallyData[i - 1]->getPos()) + "EMissing operand, code: 2");
			}
			else if (notActuallyData[i]->getSym() == "(" && i > 0) { // ( operator branch
				if (notActuallyData[i - 1]->getSym() == ")") // )( case
					throw std::invalid_argument(std::to_string(notActuallyData[i]->getSym().length()) + "L" + std::to_string(notActuallyData[i]->getPos()) + "EMissing operator, code: 3");
				if (!notActuallyData[i - 1]->isOperation()) // var(... instead of var+(...
					throw std::invalid_argument(std::to_string(notActuallyData[i - 1]->getSym().length()) + "L" + std::to_string(notActuallyData[i - 1]->getPos()) + "EMissing operator, code: 4");
			}
			else if (dynamic_cast<operation*>(notActuallyData[i])->getOperandsCount() == 1 && i > 0) { // 1 operand branch
				if (!notActuallyData[i - 1]->isOperation() || notActuallyData[i - 1]->getSym() == ")") // extra operand on the left side
					throw std::invalid_argument(std::to_string(notActuallyData[i]->getSym().length()) + "L" + std::to_string(notActuallyData[i]->getPos()) + "EInvalid unary operator syntax, code: 5");
				if (i + 1 >= notActuallyData.size()) // no operator on the right side
					throw std::invalid_argument(std::to_string(notActuallyData[i]->getSym().length()) + "L" + std::to_string(notActuallyData[i]->getPos()) + "ENo operands for this operator, code: 6");
			}
			else if (dynamic_cast<operation*>(notActuallyData[i])->getOperandsCount() >= 2) { // 2 and more operands branch
				if (i == 0) // no operand on the left side
					throw std::invalid_argument(std::to_string(notActuallyData[i]->getSym().length()) + "L" + std::to_string(notActuallyData[i]->getPos()) + "ENo operands for this operator, code: 7");
				if (notActuallyData[i - 1]->isOperation() && notActuallyData[i - 1]->getSym() != ")" && notActuallyData[i - 1]->getSym() != "(") // same 
					throw std::invalid_argument(std::to_string(notActuallyData[i]->getSym().length()) + "L" + std::to_string(notActuallyData[i]->getPos()) + "ETwo or more operators in a row, code: 8");
				if (notActuallyData[i - 1]->getSym() == "(") // same
					throw std::invalid_argument(std::to_string(notActuallyData[i]->getSym().length()) + "L" + std::to_string(notActuallyData[i]->getPos()) + "ENo operands for this operator, code: 9");
			}
		}
		else if (i > 0) { // operand branch
			if (notActuallyData[i - 1]->getSym() == ")") // ) symbol
				throw std::invalid_argument(std::to_string(notActuallyData[i]->getSym().length()) + "L" + std::to_string(notActuallyData[i]->getPos()) + "EMissing operator, code: 10");
			if (!notActuallyData[i - 1]->isOperation()) // another operand
				throw std::invalid_argument(std::to_string(notActuallyData[i]->getSym().length()) + "L" + std::to_string(notActuallyData[i]->getPos()) + "EMissing operator, code: 11");
		}
	}
}
bool calculator::araThereAnyVariables() noexcept {
	return isVariablesExist;
}
void calculator::askForVariablesValues(std::istream& in, std::ostream& out) {
	std::string str;
	for (size_t i = 0; i < variable::vectorOfVariablesNames.size(); ++i) {
		out << "Enter the " << variable::vectorOfVariablesNames[i] << " variable\n";
		std::getline(in, str);
		try {
			variable::VectorOfVariablesValues[i] = parser(str);
		}
		catch (std::exception& e) { // parser exception
			out << "Bad number input\n";
			int it = std::stoi(e.what());
			out << str.substr(0, it) << " ";
			out << "\033[31m" << str[it] << "\033[0m";
			if (it + 1 < str.length()) out << " " << str.substr(it + 1, str.length()) << std::endl;
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