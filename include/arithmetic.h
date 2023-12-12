// объ€вление функций и классов дл€ вычислени€ арифметических выражений

#ifndef _ARIFMETIC_H_
#define _ARIFMETIC_H_

#include <iostream>
#include <stdexcept>
#include "string"
#include "stack.h"
#include "map"

class Postfix
{
protected:
	int operationPriority(char);
	void checkBrackets(const std::string&)const;
	bool isDigit(const char&);
	void checkingLine(std::string&);
	void throw_err(size_t i);
public:
	std::string ToPostfix(std::string);
	double calculate(const std::string&, std::map<char, double>&);
};
class invalid_argument: public std::exception {
private:
	std::string error;
public:
	invalid_argument(std::string s)
	{
		error = s;
	}
	const char* what() const noexcept
	{
		return error.c_str();
	}
};

#endif