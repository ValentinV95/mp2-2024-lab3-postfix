// объ€вление функций и классов дл€ вычислени€ арифметических выражений

#include <iostream>
#include <string>
#include <vector>
#include "stack.h"
#include <map>

class TPostfix {

	string infix;
	vector<string> postfix;

	int priority_of_operations(char op);
	int priority_of_operations(const string& op);
	void checking_brackets(const std::string& s) const;
	string check_string_is_a_number(const string& str, size_t start_number, size_t end_number);
	double string_to_number(const string& s_str);	
public:
	TPostfix(string str_infix)
	{
		infix = str_infix;
	}
	string get_infix()
	{
		return infix;
	}
	vector<string> get_postfix()
	{
		return postfix;
	}
	vector<string> to_postfix();
	double calculate(map<string, double>& variables);
};