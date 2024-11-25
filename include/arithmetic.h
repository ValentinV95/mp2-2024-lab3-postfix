// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#include <string>
#include <iostream>
#include "myvector.h"
#include "stack.h"
#include "parser.h"
#include <cmath>
#pragma once
using namespace std;

// vector<double>
// vector<operand>

class lexem {
private:
	string sym;
	int pos;
public:
	lexem(string s = "", int p = -1) : sym(s), pos(p) {}
	const string& getSym() const noexcept { return sym; }
	const int& getPos() const noexcept { return pos; }
	virtual bool isOperation() = 0;
	virtual ~lexem() {}
};

class operation : public lexem {
private:
	int priority;
	int operandsCount;
	static myVector<string> availableOperations;
	static myVector<int> priotities;
	static myVector<int> vOperandsCount;
	static myVector<int> vCanBeAfterOperand;
	static void fillOperations() {
		availableOperations.push_back("+");
		availableOperations.push_back("-");
		availableOperations.push_back("~"); // it won't be in final RPN
		availableOperations.push_back("*");
		availableOperations.push_back("/");
		availableOperations.push_back("sin");
		availableOperations.push_back("cos");
		availableOperations.push_back("exp");
		availableOperations.push_back("pow");
		availableOperations.push_back("log");
		availableOperations.push_back("(");
		availableOperations.push_back(")");

		priotities.push_back(1);
		priotities.push_back(1);
		priotities.push_back(3);
		priotities.push_back(2);
		priotities.push_back(2);
		priotities.push_back(3);
		priotities.push_back(3);
		priotities.push_back(3);
		priotities.push_back(3);
		priotities.push_back(3);
		priotities.push_back(3);
		priotities.push_back(0);
		priotities.push_back(0);

		vOperandsCount.push_back(2);
		vOperandsCount.push_back(2);
		vOperandsCount.push_back(1);
		vOperandsCount.push_back(2);
		vOperandsCount.push_back(2);
		vOperandsCount.push_back(1);
		vOperandsCount.push_back(1);
		vOperandsCount.push_back(1);
		vOperandsCount.push_back(2);
		vOperandsCount.push_back(1);
		vOperandsCount.push_back(0);
		vOperandsCount.push_back(0);

		vCanBeAfterOperand.push_back(1);
		vCanBeAfterOperand.push_back(1);
		vCanBeAfterOperand.push_back(0);
		vCanBeAfterOperand.push_back(1);
		vCanBeAfterOperand.push_back(1);
		vCanBeAfterOperand.push_back(0);
		vCanBeAfterOperand.push_back(0);
		vCanBeAfterOperand.push_back(0);
		vCanBeAfterOperand.push_back(0);
		vCanBeAfterOperand.push_back(0);
		vCanBeAfterOperand.push_back(0);
		vCanBeAfterOperand.push_back(1);
	}
public:
	operation(const lexem& lex) : priority(-1) { 
		fillOperations(); 
		for (size_t i = 0; i < availableOperations.size(); ++i) {
			if (lex.getSym() == availableOperations[i]) {
				priority = priotities[i];
				operandsCount = vOperandsCount[i];
				break;
			}
		}
	}
	bool isOperation() override final {
		return true;
	}
	bool static isOperation(const lexem& lex) {
		for (size_t i = 0; i < availableOperations.size(); ++i)
			if (lex.getSym() == availableOperations[i])
				return true;
		return false;
	}
	int getPriority() {
		return priority;
	}
	int getOperandsCount() {
		return operandsCount;
	}
	double execute(const myVector<double>& operands) { // operands = { a, b }. operation = +. return a + b (v[0] + v[1]). operation = ~. return ~a (-v[0])
		double res;
		if (this->getSym() == "+")
			res = operands[0] + operands[1];
		else if (this->getSym() == "-")
			res = operands[0] - operands[1];
		else if (this->getSym() == "~")
			res = -operands[0];
		else if (this->getSym() == "*")
			res = operands[0] * operands[1];
		else if (this->getSym() == "/")
			res = operands[0] / operands[1];
		else if (this->getSym() == "sin")
			res = sin(operands[0]);
		else if (this->getSym() == "cos")
			res = cos(operands[0]);
		else if (this->getSym() == "exp")
			res = exp(operands[0]);
		else if (this->getSym() == "pow")
			res = pow(operands[0], operands[1]);
		else if (this->getSym() == "log")
			res = log(operands[0]);
		else // exception?
			res = 0.0;
		return res;
	}
	virtual ~operation() {}
};

class operand : public lexem { // constructor required
protected:
	double value;
	// *operand op
public:
	// operand(const lexem& lex) { op->create(lex) }
	double getValue() {
		return value;
	}
	bool isOperation() override final {
		return false;
	}
	virtual ~operand() {}
};

class constant : public operand { // constructor required
	// create(lex) { parse(lex) }
public:

	virtual ~constant() {}
};

class variable : public operand { // constructor required
public:
	static myVector<string> vectorOfVariablesNames;
	static myVector<double> VectorOfVariablesValues;
	// create(lex) { nan }
	void fillValue() {
		for (size_t i = 0; i < vectorOfVariablesNames.size(); ++i) {
			if (getSym() == vectorOfVariablesNames[i]) {
				value = VectorOfVariablesValues[i];
				return;
			}
		}
	}
	virtual ~variable() {}
};

class RPN { // reverse polish notation
private:
	myVector<lexem*> infix;
	myVector<lexem*> postfix;
	void toRpn() {
		myStack<operation*> st;
		for (size_t i = 0; i < infix.size(); ++i) {
			if (infix[i]->getSym() == "(") {
				st.push(dynamic_cast<operation*>(infix[i]));
			}
			if (infix[i]->getSym() == ")") {
				st.pop();
				if (st.isEmpty()) throw invalid_argument(to_string(infix[i]->getPos()) + "ENo opening bracket for this bracket"); // redundant check
				while (st.top()->getSym() != "(") {
					if (st.isEmpty()) throw invalid_argument(to_string(infix[i]->getPos()) + "ENo opening bracket for this bracket"); // redundant check
					postfix.push_back(st.pop());
				}
				st.pop();
			}
			else if (infix[i]->isOperation()) { // if it is an opertion
				while (!st.isEmpty() && (st.top()->getPriority() >= dynamic_cast<operation*>(infix[i])->getPriority())) {
					postfix.push_back(st.pop());
				}
				st.push(dynamic_cast<operation*>(infix[i]));
			}
			else {
				postfix.push_back(infix[i]);
			}
		}
		while (!st.isEmpty()) {
			if (st.top()->getSym() == "(") throw invalid_argument(to_string(st.top()->getPos()) + "ENo closing bracket for this bracket"); // redundant check
			postfix.push_back(st.pop());
		}
	}
public:
	RPN(const myVector<lexem*>& s) : infix(s), postfix() { toRpn(); }
	double calculate() {
		myVector<double> operands;
		myStack<double> st;
		operation* tmpOperator;
		operand* tmpOperand;
		for (size_t i = 0; i < postfix.size(); ++i) {
			if (!postfix[i]->isOperation()) // is operand
				st.push( dynamic_cast<operand*>(postfix[i])->getValue());
			else { // is operation
				tmpOperator = dynamic_cast<operation*>(postfix[i]);
				for (int _ = 0; _ <= tmpOperator->getOperandsCount(); ++_) {
					if (st.isEmpty()) throw invalid_argument(to_string(tmpOperator->getPos()) + "ENo operand for this operator"); // redundant check
					operands.push_back(st.pop());
				}
				st.push(tmpOperator->execute(operands));
			}
		}
		if (st.isEmpty()) throw invalid_argument("0EUnknown error"); // redundant check. How is it possible?
		return st.pop(); // if there is more than one - check
	}
};

class calculator {
private:
	myVector<lexem*> notActuallyData; // new delete construction
public:
	calculator(string str) {
		// parse to vector of lexems
		// remember than it should be unique names of variables
		// prohibited names: sin(, cos(, +, etc. Avaliable names: sin, cos, nis(, soc(), etc.

		for (auto it = str.begin(); it != str.end(); ++it) if (*it == ' ') str.erase(it);
		for (auto it = str.begin(); it != str.end(); ++it) {

		}

	}
	void askForVariablesValues() {
		string str;
		for (size_t i = 0; i < variable::vectorOfVariablesNames.size(); ++i) {
			cout << "Enter the " << variable::vectorOfVariablesNames[i] << " variable\n";
			getline(cin, str);
			try {
				variable::VectorOfVariablesValues.push_back(parser(str));
			}
			catch (exception& e) {
				cout << "Bad number input\n";
				int it = stoi(e.what());
				cout << str.substr(0, it) << " ";
				cout << "\033[31m" << str[it] << "\033[0m";
				if (it >= str.length()) cout << " " << str.substr(it, str.length()) << endl;
				else cout << " " << str.substr(it + 1, str.length()) << endl;
				--i;
			}
		}
		for (size_t i = 0; i < notActuallyData.size(); ++i) {
			dynamic_cast<variable*>(notActuallyData[i])->fillValue();
		}
	}
	double calculate() {
		RPN rpn(notActuallyData); // exceptions hadler
		return rpn.calculate(); // exceptions handler
	}
	~calculator() {
		for (size_t i = 0; i < notActuallyData.size(); ++i) {
			delete[] notActuallyData[i];
		}
	}
};