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
	virtual int getPriority() { return -1; };
	virtual double getValue() { return NAN; };
	virtual void fillValue() {}
	virtual double execute(const myVector<double>& operands) { return NAN; }
	virtual int getOperandsCount() { return 0; }
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
		if (priority == -1) throw invalid_argument(to_string(lex.getPos()));
	}
	bool static isOperation(const lexem& lex) {
		for (size_t i = 0; i < availableOperations.size(); ++i)
			if (lex.getSym() == availableOperations[i])
				return true;
		return false;
	}
	int getPriority() override {
		return priority;
	}
	int getOperandsCount() override {
		return operandsCount;
	}
	double execute(const myVector<double>& operands) override { // operands = { a, b }. operation = +. return a + b (v[0] + v[1]). operation = ~. return ~a (-v[0])
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
	double getValue() override final {
		return value;
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
	void fillValue() override {
		for (size_t i = 0; i < vectorOfVariablesNames.size(); ++i) {
			if (getSym() == vectorOfVariablesNames[i]) {
				value = VectorOfVariablesValues[i];
				return;
			}
		}
	}
	virtual ~variable() {}
};

class calculator {
private:
	myVector<lexem*> notActuallyData; // new delete construction
public:
	calculator(const string& str) {
		// parse to vector of lexems
		// remember than it should be unique names of variables
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
			notActuallyData[i]->fillValue();
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

class RPN { // reverse polish notation
private:
	myVector<lexem*> infix;
	myVector<lexem*> postfix;
	void toRpn() {
		myStack<lexem*> st;
		for (size_t i = 0; i < infix.size(); ++i) {
			if (infix[i]->getSym() == "(") {
				st.push(infix[i]);
			}
			if (infix[i]->getSym() == ")") {
				st.pop();
				if (st.isEmpty()) throw invalid_argument(to_string(infix[i]->getPos())); // redundant check
				while (st.top()->getSym() != "(") {
					if (st.isEmpty()) throw invalid_argument(to_string(infix[i]->getPos())); // redundant check
					postfix.push_back(st.pop());
				}
				st.pop();
			}
			else if (infix[i]->getPriority() != -1) {
				while (!st.isEmpty() && (st.top()->getPriority() >= infix[i]->getPriority())) {
					postfix.push_back(st.pop());
				}
				st.push(infix[i]);
			}
			else {
				postfix.push_back(infix[i]);
			}
		}
		while (!st.isEmpty()) {
			if (st.top()->getSym() == "(") throw invalid_argument(to_string(st.top()->getPos())); // redundant check
			postfix.push_back(st.pop());
		}
	}
public:
	RPN(const myVector<lexem*>& s) : infix(s), postfix() { toRpn(); }
	double calculate() {
		myVector<double> operands;
		myStack<double> st;
		for (size_t i = 0; i < postfix.size(); ++i) {
			if (postfix[i]->getPriority() == -1)
				st.push(postfix[i]->getValue());
			else {
				for (int i = 0; i <= postfix[i]->getOperandsCount(); ++i) {
					if (st.isEmpty()) throw invalid_argument(to_string(postfix[i]->getPos())); // redundant check
					operands.push_back(st.pop());
				}
				st.push(postfix[i]->execute(operands));
			}
		}
		if (st.isEmpty()) throw invalid_argument("0"); // redundant check. How is it possible?
		return st.pop(); // if there is more than one - check
	}
};