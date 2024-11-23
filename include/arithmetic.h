// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#include <string>
#include <exception>
#include <stdexcept>
#include "myvector.h"
#include "stack.h"
#include "parser.h"

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
	virtual ~lexem() {}
};

class operation : public lexem {
private:
	int priority;
	static myVector<string> availableOperations;
	static myVector<int> priotities;
	static myVector<int> operandsCount;
	static void fillOperations() {
		availableOperations.push_back("+");
		availableOperations.push_back("-");
		availableOperations.push_back("~");
		availableOperations.push_back("*");
		availableOperations.push_back("/");
		availableOperations.push_back("sin(");
		availableOperations.push_back("cos(");
		availableOperations.push_back("exp(");
		availableOperations.push_back("pow(");
		availableOperations.push_back("log(");
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

		operandsCount.push_back(2);
		operandsCount.push_back(2);
		operandsCount.push_back(1);
		operandsCount.push_back(2);
		operandsCount.push_back(2);
		operandsCount.push_back(1);
		operandsCount.push_back(1);
		operandsCount.push_back(1);
		operandsCount.push_back(2);
		operandsCount.push_back(1);
		operandsCount.push_back(0);
		operandsCount.push_back(0);
	}
public:
	operation(const lexem& lex) : priority(-1) { 
		fillOperations(); 
		for (size_t i = 0; i < availableOperations.size(); ++i) {
			if (lex.getSym() == availableOperations[i]) {
				priority = priotities[i];
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
	virtual ~operation() {}
};

class operand : public lexem {
private:
	double value;
	// *operand op
public:
	// operand(const lexem& lex) { op->create(lex) }
	double getValue() override {
		return value;
	}
	virtual ~operand() {}
};

class constant : public operand {
	// create(lex) { parse(lex) }
};

class variable : public operand {
	// create(lex) { getFromVariablesVector(lex) }
};

class RPN { // reverse polish notation
private:
	myVector<lexem> infix;
	myVector<lexem*> postfix;
	void toRpn() {
		myStack<lexem*> st;
		for (size_t i = 0; i < infix.size(); ++i) {
			if (infix[i].getSym() == "(") {
				st.push(&infix[i]);
			}
			if (infix[i].getSym() == ")") {
				st.pop();
				if (st.isEmpty()) throw invalid_argument(to_string(infix[i].getPos())); // redundant check
				while (st.top()->getSym() != "(") {
					if (st.isEmpty()) throw invalid_argument(to_string(infix[i].getPos())); // redundant check
					postfix.push_back(st.pop());
				}
				st.pop();
			}
			else if (operation::isOperation(infix[i])) {
				while (!st.isEmpty() && (st.top()->getPriority() >= (&infix[i])->getPriority())) {
					postfix.push_back(st.pop());
				}
				st.push(&infix[i]);
			}
			else {
				postfix.push_back(&infix[i]);
			}
		}
		while (!st.isEmpty()) {
			if (st.top()->getSym() == "(") throw invalid_argument(to_string(st.top()->getPos())); // redundant check
			postfix.push_back(st.pop());
		}
	}
public:
	RPN(const myVector<lexem>& s) : infix(s), postfix() { toRpn(); }
	double calculate() {
		double res = 0.0;
		myStack<lexem*> st;
		
		return res;
	}
};