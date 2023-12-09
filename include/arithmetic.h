// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "stack.h"
using namespace std;

class Arithmetic
{
	string infix;
	string postfix;
	string operands;
	string* variables;
	string* SetOfLexems;
	int lexemSize;
	int variableSize;
	
public:
	~Arithmetic();
	Arithmetic(string& str);
	string getInfix() const;
	string getPostfix() const;
	string getOperands() const;
	bool isOperation(const char& x);
	int priority(const char& operation);
	void makePostfix();
	double makeDouble(string number);
	void Parser();
	void infixCheck();
	bool isOperand(const char& first_symbol);
	bool isDigit(const char& first_symbol);
	double calculate();
};