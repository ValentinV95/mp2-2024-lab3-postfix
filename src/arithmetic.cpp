// реализация функций и классов для вычисления арифметических выражений
#include "arithmetic.h"

TPostfix::std::string Error_string(std::string& s, int i) {
	std::string tmp = "Error: ";
	for (int j = 0; j < i; j++) tmp += s[j];
	tmp = tmp + '\"' + s[i] + '\"';
	for (int j = i + 1; j < s.size(); j++) tmp += s[j];
	tmp += '\n';
	return tmp;
}
TPostfix::bool is_op_or_func(std::string s) {
	for (int i = 0; i < 11; i++) if (s == pr[i]) return true;
	return false;
}
TPostfix::bool is_op_or_func(char c) {
	std::string s;
	s = c;
	for (int i = 0; i < 5; i++) if (s == pr[i]) return true;
	return false;
}
TPostfix::int get_prior(std::string& s) {
	for (int i = 0; i < 11; i++) if (s == pr[i]) return i;
	return -1;
}
TPostfix::double valid(std::string& s) {
	double res = 0;
	int i = 0, mod = 0, pw = 0;
	while ((s[i] != '.') && (s[i] != 'e') && (i != s.size())) {
		res *= 10;
		res += (int)s[i] - 48;
		i++;
	}
	int m = i;
	if (s[i] == '.') i++;
	while ((s[i] != 'e') && (i != s.size())) {
		res += ((int)s[i] - 48) * pow(10, m - i);
		i++;
	}
	if (s[i] == 'e') {
		i++;
		if (s[i] == '-') mod = -1;
		else mod = 1;
		i++;
	};
	while (i != s.size()) {
		pw *= 10;
		pw += (int)s[i] - 48;
		i++;
	}
	res *= pow(10, mod * pw);
	return res;
}
TPostfix::std::string number_check(std::string& s, int& i) {
	std::string tmp;
	tmp = s[i];
	i++;
	while (i != s.size() && s[i] != '.' && s[i] != 'e' && s[i] != ')' && !is_op_or_func(s[i])) {
		tmp += s[i];
		i++;
	}
	if (s[i] == '.') tmp += s[i++];
	while ((i != s.size()) && (s[i] != 'e') && !is_op_or_func(s[i]) && (s[i] != ')')) {
		if (s[i] == '.') throw std::invalid_argument(Error_string(s, i) + "There cannot be more than one \'.\' in a number");
		tmp += s[i];
		i++;
	}
	if (tmp == ".") throw std::invalid_argument(Error_string(s, i - 1) + "Writing a number in the form of \".\" is not possible");
	if (i != s.size() && s[i] == 'e') {
		tmp += s[i];
		i++;
		if ((i < s.size() - 1) && ((s[i] == '+') || (s[i] == '-'))) {
			tmp += s[i];
			i++;
			if ((int)s[i] < 49 || (int)s[i]>57)
				throw std::invalid_argument(Error_string(s, i) + "When specifying a number with \'e\', there must be a natural number after the \'+\' or \'-\' sign");
			tmp += s[i];
			i++;
		}
		else throw std::invalid_argument(Error_string(s, i) + "After \'e\' there should be a + or sign -");
	};
	while (i != s.size() && ((int)s[i] >= 48 && (int)s[i] <= 57)) {
		tmp += s[i];
		i++;
	}
	if (i != s.size() && !is_op_or_func(s[i]) && s[i] != ')') throw std::invalid_argument(Error_string(s, i) + "The operand must be followed by an operator or a closing parenthesis");
	i--;
	return tmp;
}
TPostfix::TPostfix(std::string& s) {
	int i = 0;
	std::string tmp;
	TStack<std::string> St;
	TStack<int> bracket; //данный стек нужен, чтобы указвать на ошибки в расстановке скобок
	while (i < s.size()) {
		tmp = s[i];
		if (is_op_or_func(s[i])) { //обработка операций
			if ((i == 0) || (s[i - 1] == '(')) {
				if (tmp == "-") tmp = "~";
				else throw std::invalid_argument(Error_string(s, i) + "Binary operators cannot be preceded by an opening parenthesis");
			}
			else if (is_op_or_func(s[i - 1])) throw std::invalid_argument(Error_string(s, i) + "Two operators cannot stand in a row");
			if (i == s.size() - 1 || s[i + 1] == ')') throw std::invalid_argument(Error_string(s, i) + "The operator must be followed by an operand");
			while (!St.isEmpty() && St.show_back() != "(" && get_prior(St.show_back()) >= get_prior(tmp)) RPN.push_back(St.pop_back());
			St.push_back(tmp);
		}
		else if ((s[i] == '(') && (i < s.size() - 1) && (s[i + 1] != ')')) { //обработка открывающей скобки
			bracket.push_back(i);
			St.push_back(tmp);
		}
		else if (s[i] == ')') { //обработка закрывающей скобки
			if (bracket.GetCount() == 0) throw std::invalid_argument(Error_string(s, i) + "The brackets are placed incorrectly");
			bracket.pop_back();
			if (i != s.size() - 1 && !is_op_or_func(s[i + 1]) && s[i + 1] != ')') throw std::invalid_argument(Error_string(s, i + 1) + "The operand must be followed by an operator or a closing parenthesis");
			while (St.show_back() != "(") RPN.push_back(St.pop_back());
			St.pop_back();
		}
		else if ((i < s.size() - 2) && (is_op_or_func(tmp + s[i + 1] + s[i + 2]))) { // обработка функций
			if ((i > s.size() - 6) || s[i + 3] != '(') throw std::invalid_argument(Error_string(s, i + 3) + "After a function must be a \'(\'");
			tmp = tmp + s[i + 1] + s[i + 2];
			i += 2;
			St.push_back(tmp);
		}
		else if (((int)s[i] >= 48 && (int)s[i] <= 57) || (s[i] == '.')) {// обработка чисел
			RPN.push_back(number_check(s, i));
		}
		else if (s[i] == 'x') { //обработка переменных
			i++;
			while ((i != s.size()) && ((int)s[i] >= 48 && (int)s[i] <= 57)) {
				tmp += s[i];
				i++;
			}
			if (i != s.size() && !is_op_or_func(s[i]) && s[i] != ')') throw std::invalid_argument(Error_string(s, i) + "You can't name variables this way");
			i--;
			RPN.push_back(tmp);
		}
		else throw std::invalid_argument(Error_string(s, i) + "This writing is not correct");
		i++;
	}
	if (bracket.GetCount() > 1) {
		while (bracket.GetCount() != 1) bracket.pop_back();
		throw std::invalid_argument(Error_string(s, bracket.pop_back()) + "The brackets are placed incorrectly");
	}
	while (!St.isEmpty()) RPN.push_back(St.pop_back());
}
TPostfix::double count() {
	TStack<double> St;
	std::map <std::string, double> variables;
	for (int i = 0; i < RPN.size(); i++) {
		if (is_op_or_func(RPN[i])) {
			if (RPN[i] == "+") St.push_back(St.pop_back() + St.pop_back());
			else if (RPN[i] == "-") St.push_back(-St.pop_back() + St.pop_back());
			else if (RPN[i] == "*") St.push_back(St.pop_back() * St.pop_back());
			else if (RPN[i] == "/") St.push_back(1 / St.pop_back() * St.pop_back());
			else if (RPN[i] == "~") St.push_back(-St.pop_back());
			else if (RPN[i] == "sin") St.push_back(sin(St.pop_back()));
			else if (RPN[i] == "cos") St.push_back(cos(St.pop_back()));
			else if (RPN[i] == "tan") St.push_back(tan(St.pop_back()));
			else if (RPN[i] == "cot") St.push_back(1 / tan(St.pop_back()));
			else if (RPN[i] == "exp") St.push_back(exp(St.pop_back()));
			else St.push_back(log(St.pop_back()));
		}
		else {
			if (RPN[i][0] == 'x') {
				if (variables.count(RPN[i]))
					St.push_back(variables.find(RPN[i])->second);
				else {
					double tmp;
					std::cout << "Enter a value for " << RPN[i] << ": ";
					std::cin >> tmp;
					variables.insert(std::pair<std::string, double> {RPN[i], tmp});
					St.push_back(tmp);
				}
			}
			else St.push_back(valid(RPN[i]));
		}
	}
	return St.pop_back();
}