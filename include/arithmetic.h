// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#include "lexems.h"
#pragma once

class calculator {
private:
	bool isVariablesExist;
	myVector<lexem*> notActuallyData;
	void check();
public:
	calculator(std::string str);
	bool araThereAnyVariables() noexcept;
	void askForVariablesValues();
	double calculate();
	~calculator();
};