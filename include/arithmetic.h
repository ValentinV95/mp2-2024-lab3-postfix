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

	void setTPostfix(string _infix); //задать строку

	void toLexem(); //перевод выражения в массив лексем

	void value_of_variable(); //присвоить значение

	size_t getPriority(string operation); //обозначить приоритет операции

	void toPostfix(); //преобразование инфикс в постфикс

	double toСonverter(string number); //конвертор из строки в дабл

	void toCalculate(); //счёт

	string getPostfix(); //получить постфикс в виде строки

	string getInfix(); //получить инфикс в виде строки

	double getResult(); //получить результат в даблах

	~TPostfix();
};