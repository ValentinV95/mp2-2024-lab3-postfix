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
	TStack<double> numbers;
	double result;
	string error;

public:

	TPostfix(string _infix);

	void toLexem();

	void value_of_variable();

	size_t getPriority(string operation) const;

	void toPostfix();

	double string_in_double(string number);

	void toCalculate();

	string getPostfix() const;

	string getInfix() const;

	double getResult() const;

	bool isDigit(const char& elem);

	~TPostfix();
};
