// объявление функций и классов для вычисления арифметических выражений

#pragma once

#include <iostream>
#include <iomanip>
#include "stack.h"
#include <string>

using namespace std;

class TPostfix
{
private:
	size_t size;
	string infix, postfix;
	string* data;
	TStack<string> operations;
	TStack<double> numbers;
	double result;

public:

	TPostfix();

	TPostfix(string _infix);

	void setTPostfix(string _infix);

	void toLexem();

	void value_of_variable();

	size_t getPriority(string operation);

	void toPostfix();

	double string_in_double(string number);

	void toCalculate();

	string getPostfix();

	string getInfix();

	double getResult();

	~TPostfix();
};
