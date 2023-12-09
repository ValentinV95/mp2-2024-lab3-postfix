// объ€вление функций и классов дл€ вычислени€ арифметических выражений

#pragma once
#include "stack.h"
#include <cmath>
#include <string>
#include <map>
#include <vector>

using namespace std;

double string_to_decimal(const string &expr);

int string_to_integer(const string &expr);

double exp_form_to_double(const string &expr);

size_t operator_priority(const string &expr) {
	if (expr == "+") { return 1; }
	else if (expr == "-") { return 1; }
	else if (expr == "*") { return 2; }
	else if (expr == "/") { return 2; }
	else if (expr == "sin") { return 3; }
	else if (expr == "cos") { return 3; }
	else if (expr == "tan") { return 3; }
	else if (expr == "~") { return 2; }
	else if (expr == "exp") { return 3; }
	else if (expr == "lg") { return 3; }
	else { return 0; }
}

template<typename T>
class TPostfix {
public:
	TPostfix(): operands(), postfix_lexems() { }
	void toPostfix(const vector<string> &expr);
private:
	map<string, T> operands;
	vector<string> postfix_lexems;
};

template<typename T>
void TPostfix<T>::toPostfix(const vector<string> &expr) {
	TStack<string> stack;
	string stackItem;
	for (size_t i = 0; i < expr.size(); i++) {
		if (expr[i] == "(") { stack.push(expr[i]); }
		else if (expr[i] == ")") {
			stackItem = stack.pop();
			while (stackItem != "(") {
				postfix_lexems.push_back(stackItem);
				stackItem = stack.pop();
			}
		}
		else if (operator_priority(expr[i]) > 0) {
			while (!stack.isEmpty()) {
				stackItem = stack.pop();
				if (operator_priority(expr[i]) <= operator_priority(stackItem)) {
					postfix_lexems.push_back(stackItem);
				}
				else {
					stack.push(stackItem);
					break;
				}
			}
			stack.push(stackItem);
		}
		else {
			operands[expr[i]] = T(0);
			postfix_lexems.push_back(expr[i]);
		}
	}
	while (!stack.isEmpty()) {
		stackItem = stack.pop();
		postfix_lexems.push_back(stackItem);
	}
}