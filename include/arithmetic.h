// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#include <string>
#include "myvector.h"

using namespace std;

class lexem {
private:
	string sym;
	int pos;
	lexem(string s = "", int p = -1) : sym(s), pos(p) {}
};

class operation : public lexem {
private:
	int priority;
	static myVector<string> avaliable_operations;
	static void fill_operations() {
		avaliable_operations.push_back("+");
		avaliable_operations.push_back("-");
		avaliable_operations.push_back("~");
		avaliable_operations.push_back("*");
		avaliable_operations.push_back("/");
		avaliable_operations.push_back("sin(");
		avaliable_operations.push_back("cos(");
		avaliable_operations.push_back("exp(");
		avaliable_operations.push_back("pow(");
		avaliable_operations.push_back("log(");
		avaliable_operations.push_back("");
		avaliable_operations.push_back("(");
		avaliable_operations.push_back(")");
	}
};

class operand : public lexem {

};

class constant : public operand {

};

class variable : public operand {

};

class RPN {

};