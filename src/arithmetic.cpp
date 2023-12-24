// реализация функций и классов для вычисления арифметических выражений

#include "arithmetic.h"
#include <map>

int TPostfix::priority_of_operations(char op) {
	if (op == '+' || op == '-')
	{
		return 1;
	}
	if (op == '*' || op == '/')
	{
		return 2;
	}
	if (op == '~')
	{
		return 3;
	}
	return 0;
}

int TPostfix::priority_of_operations(const string& op) {
	if (op == "+" || op == "-")
	{
		return 1;
	}
	if (op == "*" || op == "/")
	{
		return 2;
	}
	if (op == "~")
	{
		return 3;
	}
	return 0;
}

void TPostfix::checking_brackets(const std::string& s) const
{
    int opening_bracket = 0, closing_bracket = 0;
    for (int i = 0; i < s.size(); i++){
        if (s[i] == '('){
			opening_bracket++;
        }
        if (s[i] == ')'){
			closing_bracket++;
        }
    }
    if (opening_bracket != closing_bracket){
        throw invalid_argument("wrong number of brackets");
    }
}

string TPostfix::check_string_is_a_number(const string& str, size_t start_number, size_t end_number) {
	string str_number;
	if (str[start_number] == '.' && start_number + 1 == end_number) {
		throw invalid_argument("A number cannot be just a point");
	}
	str_number = str[start_number++];
	while (start_number != end_number && str[start_number] != '.' && str[start_number] != 'e') {
		str_number += str[start_number++];
	}
	if (str[start_number] == '.') {
		str_number += str[start_number++];
	}
	while (start_number != end_number && str[start_number] != 'e') {
		if (str[start_number] == '.') {
			throw invalid_argument("wrong num...ber");
		}
		str_number += str[start_number++];
	}
	if (start_number != end_number && str[start_number] == 'e') {
		str_number += str[start_number++];
		if (start_number != end_number && str[start_number] == '-') {
			str_number += str[start_number++];
			if (start_number != end_number && (str[start_number] >= '0' && str[start_number] <= '9')) {
				str_number += str[start_number++];
			}
			else {
				throw invalid_argument("after 'e-' there must be a natural number");
			}
		}
		else
		{
			if (start_number != end_number && (str[start_number] >= '0' && str[start_number] <= '9')) {
				str_number += str[start_number++];
			}
			else {
				throw invalid_argument("after 'e' there must be a natural number");
			}
		}
	}
	while (start_number != end_number) {
		if (str[start_number] == '.' || str[start_number] == 'e') {
			throw invalid_argument("wrong number...");
		}
		str_number += str[start_number++];
	}
	return str_number;
}

double TPostfix::string_to_number(const string& s_str) {
	double res = 0.0;
	int i = 0, z = 1, res_pow = 0;
	while (i != s_str.size() && s_str[i] != '.' && s_str[i] != 'e') {
		res *= 10;
		res += s_str[i++] - '0';
	}
	if (s_str[i] == '.') {
		i++;
	}
	int k = i;
	while (i != s_str.size() && s_str[i] != 'e') {
		if (s_str[i] == '.') {
			throw invalid_argument("wrong num...ber");
		}
		res += (s_str[i++] - '0') * pow(10, k - i);
	}
	if (s_str[i] == 'e') {
		i++;
		if (s_str[i] == '-') {
			z = -1;
			i++;
		}
	}
	while (i != s_str.size()) {
		if (s_str[i] == '.') {
			throw invalid_argument("wrong number...");
		}
		res_pow *= 10;
		res_pow += s_str[i++] - '0';
	}
	res *= pow(10, z * res_pow);
	return res;
}

vector<string> TPostfix::to_postfix() {
	string str, elem_str;
	size_t j = 0, open_bracket = 0;
	TStack<string> stack_of_operations;
	for (size_t i = 0; i < infix.size(); i++) {
		if (infix[i] != ' ') {
			str += infix[i];
		}
	}
	if (str.size() == 0) {
		throw invalid_argument("expression must not be empty");
	}
	checking_brackets(str);
	while (j < str.size()) {
		elem_str = str[j];
		if (priority_of_operations(str[j])) {
			if (j == str.size() - 1 && str[j + 1] == ')') {
				throw invalid_argument("after the operation there must be a number or a unary minus");
			}
			if (j == 0 || str[j - 1] == '(' || priority_of_operations(str[j - 1])) {
				if (elem_str == "-") {
					elem_str = "~";
				}
				else {
					throw invalid_argument("there must be a closing bracket or number before the operation");
				}
			}
			while (!stack_of_operations.isEmpty() && stack_of_operations.top() != "(" && priority_of_operations(elem_str) != 3
				&& priority_of_operations(stack_of_operations.top()) >= priority_of_operations(elem_str)) {
				postfix.push_back(stack_of_operations.pop());
			}
			stack_of_operations.push(elem_str);
		}
		else if ((str[j] >= '0' && str[j] <= '9') || str[j] == '.') {
			if (str[j] == '0' && (str[j + 1] >= '0' && str[j + 1] <= '9')) {
				throw invalid_argument("wrong number");
			}
			size_t k = j;
			while (str[j] != ')' && (str[j] != '-' || str[j - 1] == 'e') && str[j] != '+' && str[j] != '*' && str[j] != '/' && j != str.size()) {
				j++;
			}
			postfix.push_back(check_string_is_a_number(str,k,j));
			j--;
		}
		else if (str[j] == 'x') {
			j++;
			while (j != str.size() && str[j] >= '0' && str[j] <= '9') {
				elem_str += str[j++];
			}
			if (j != str.size() && priority_of_operations(str[j]) == 0 && str[j] != ')') {
				throw invalid_argument("variable name error");
			}
			j--;
			postfix.push_back(elem_str);
		}
		else if (str[j] == '(' || str[j] == ')') {
			if (str[j] == '(') {
				if (str[j + 1] == ')' || j > str.size() - 4) {
					throw invalid_argument("opening bracket is not in place");
				}
				open_bracket++;
				stack_of_operations.push(elem_str);
			}
			else {
				if (open_bracket == 0) {
					throw invalid_argument("closing bracket is not in place");
				}
				if (priority_of_operations(str[j - 1]) > 0 ||  (j != str.size() - 1 && str[j + 1] != ')' && priority_of_operations(str[j + 1]) == 0)) {
					throw invalid_argument("the surrounding of the closing bracket is incorrect");
				}
				open_bracket--;
				while (stack_of_operations.top() != "(") {
					postfix.push_back(stack_of_operations.pop());
				}
				stack_of_operations.pop();
			}
		}
		else {
			throw invalid_argument("incorrect expression input");
		}
		j++;
	}
	while (stack_of_operations.isEmpty() == 0) {
		postfix.push_back(stack_of_operations.pop());
	}
	return postfix;
}

double TPostfix::calculate(map<string, double>& variables) {
	TStack<double> result;
	string tmp;
	double first, second;
	for (size_t i = 0; i < postfix.size(); i++) {
		tmp = postfix[i];
		if (tmp[0] == 'x') {
			double value;
			if (variables.count(tmp) == 0) {
				cout << "Enter the " << tmp << ": ";
				cin >> value;
				variables[tmp] = value;
				result.push(value);
			}
			else {
				result.push(variables[tmp]);
			}
			
		}
		else if (priority_of_operations(tmp) > 0) {
			if (tmp == "+") {
				second = result.pop();
				first = result.pop();
				result.push(first + second);
			}
			else if (tmp == "-") {
				second = result.pop();
				first = result.pop();
				result.push(first - second);
			}
			else if (tmp == "*") {
				second = result.pop();
				first = result.pop();
				result.push(first * second);
			}
			else if (tmp == "/") {
				second = result.pop();
				first = result.pop();
				result.push(first / second);
			}
			else {
				second = result.pop();
				result.push(-second);
			}
		}
		else {
			result.push(string_to_number(tmp));
		}
	}
	return result.pop();
}