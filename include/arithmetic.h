// объ€вление функций и классов дл€ вычислени€ арифметических выражений

#pragma once
#include "stack.h"
#include <cmath>
#include <string>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

double string_to_decimal(const string &expr);
int string_to_integer(const string &expr);

double exp_form_to_double(const string &expr);

size_t operator_priority(const string &expr);

inline bool is_arithmetical(char inp) {
	return (inp == '(' || inp == ')' || inp == '*' || inp == '/' || inp == '-' || inp == '+' || inp == '~');
}
inline bool is_alphabet_or_numeric(char inp) {
	return ((inp >= 'A' && inp <= 'Z') || (inp >= 'a' && inp <= 'z') || (inp >= '0' && inp <= '9') || (inp == '.'));
}
inline bool is_alphabet_or_numeric(const string& inp) {
	for (size_t i = 0; i < inp.size(); i++) {
		if ((inp[i] < 'A' || inp[i] > 'Z') && (inp[i] < 'a' || inp[i] > 'z') && (inp[i] < '0' || inp[i] > '9') && (inp[i] != '.')) {
			return false;
		}
	}
	return true;
}

vector<string> arithmetic_to_lexems(const string &expr);

// 1 if correct
bool check_infix_correctness(const vector<string>& lexems);

template<typename T>
class TPostfix {
public:
	TPostfix(): operands(), postfix_lexems() { }
	void toPostfix(const vector<string> &expr);
	T calculate();
	void askOperands(istream& from, ostream& log = cout);
private:
	map<string, T> operands;
	vector<string> postfix_lexems;
};

template<typename T>
void TPostfix<T>::toPostfix(const vector<string> &expr) {
	operands.clear();
	postfix_lexems.clear();
	if (!check_infix_correctness(expr)) {
		throw invalid_argument("Postfix: Bad syntax");
	}
	TStack<string> stack;
	string stackItem;
	string lexem;
	for (size_t i = 0; i < expr.size(); i++) {
		lexem = expr[i];
		if (lexem == "(") { stack.push(lexem); }
		else if (lexem == ")") {
			stackItem = stack.pop();
			while (stackItem != "(") {
				postfix_lexems.push_back(stackItem);
				if (stack.isEmpty()) {
					throw invalid_argument("Postfix: Missing opening bracket");
				}
				stackItem = stack.pop();
			}
		}
		else if (operator_priority(lexem) > 0) {
			while (!stack.isEmpty()) {
				stackItem = stack.pop();
				if (operator_priority(lexem) <= operator_priority(stackItem)) {
					postfix_lexems.push_back(stackItem);
				}
				else {
					stack.push(stackItem);
					break;
				}
			}
			stack.push(lexem);
		}
		else {
			operands[lexem] = T(0);
			postfix_lexems.push_back(lexem);
		}
	}
	while (!stack.isEmpty()) {
		stackItem = stack.pop();
		if (stackItem == "(") {
			throw invalid_argument("Postfix: Missing closing bracket");
		}
		postfix_lexems.push_back(stackItem);
	}
}

template<typename T>
void TPostfix<T>::askOperands(istream& from, ostream& log) {
	bool is_numeric;
	char elem;
	// ask operands
	for (auto it = operands.begin(); it != operands.end(); it++) {
		is_numeric = true;
		for (size_t i = 0; i < it->first.size(); i++) {
			elem = it->first[i];
			if ((elem < '0' || elem > '9') && elem != '.' && elem != 'e') {
				is_numeric = false;
			}
		}
		if (is_numeric) {
			it->second = T(exp_form_to_double(it->first));
		}
		else {
			log << "\"" << it->first << "\": ";
			from >> it->second;
		}
	}
}

template<typename T>
T TPostfix<T>::calculate() {
	if (postfix_lexems.size() == 0) {
		throw exception("Postfix: No expression to solve");
	}
	TStack<T> vars;
	T arg1;
	T arg2;
	for (size_t i = 0; i < postfix_lexems.size(); i++) {
		if (postfix_lexems[i] == "+") {
			arg1 = vars.pop();
			arg2 = vars.pop();
			vars.push(arg2 + arg1);
		}
		else if (postfix_lexems[i] == "-") {
			arg1 = vars.pop();
			arg2 = vars.pop();
			vars.push(arg2 - arg1);
		}
		else if (postfix_lexems[i] == "*") {
			arg1 = vars.pop();
			arg2 = vars.pop();
			vars.push(arg2 * arg1);
		}
		else if (postfix_lexems[i] == "/") {
			arg1 = vars.pop();
			arg2 = vars.pop();
			vars.push(arg2 / arg1);
		}
		else if (postfix_lexems[i] == "~") {
			arg1 = vars.pop();
			vars.push(-arg1);
		}
		else if (postfix_lexems[i] == "sin") {
			arg1 = vars.pop();
			vars.push(sin(arg1));
		}
		else if (postfix_lexems[i] == "cos") {
			arg1 = vars.pop();
			vars.push(cos(arg1));
		}
		else if (postfix_lexems[i] == "tan") {
			arg1 = vars.pop();
			vars.push(tan(arg1));
		}
		else if (postfix_lexems[i] == "exp") {
			arg1 = vars.pop();
			vars.push(exp(arg1));
		}
		else if (postfix_lexems[i] == "lg") {
			arg1 = vars.pop();
			vars.push(log10(arg1));
		}
		else {
			vars.push(operands[postfix_lexems[i]]);
		}
	}
	return vars.pop();
}