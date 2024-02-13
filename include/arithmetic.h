#include <iostream>
#include <string.h>
#include <math.h>
#include "stack.h"
#include <stdlib.h>
#include <string>
using namespace std;

using namespace std;
class TCalc
{
	string infix, postfix;
	string operands;
	string* stroka;
	size_t ln;
	TStack<double> numbers;
	double result;
public:
	TCalc(string str);
	~TCalc();
	int priority(string operation);
	bool Operand(const char& symbol);
	void Lexems();
	void Postfix();
	void valueofvar();
	double Double(string number);
	string getInfix() const;
	string getPostfix() const;
	double getResult() const;
	void Calc();
};
