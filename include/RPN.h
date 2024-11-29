#include "lexems.h"
#pragma once

class RPN { // reverse polish noration
private:
	myVector<lexem*> infix;
	myVector<lexem*> postfix;
	void toRpn();
public:
	RPN(const myVector<lexem*>& s);
	double calculate();
};