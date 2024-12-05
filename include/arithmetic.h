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
	const myVector<lexem*>& getData() const noexcept;
	bool araThereAnyVariables() noexcept;
	void askForVariablesValues(std::istream& in, std::ostream& out);
	double calculate();
	~calculator();
};