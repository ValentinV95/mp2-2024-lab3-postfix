// реализация пользовательского приложения
#include "arithmetic.h"
#include "stack.h"

#include <string>
#include <iostream>

using namespace std;

void calc_arithmetic(const string &expr) {
	TPostfix<double> postfix;
	vector<string> lexems = arithmetic_to_lexems(expr);
	try {
		postfix.toPostfix(lexems);
	}
	catch (const exception &e) {
		cout << e.what() << endl;
	}
	postfix.askOperands(cin);
	double res;
	try {
		res = postfix.calculate();
		cout << res << endl;
	}
	catch (const exception &e) {
		cout << e.what() << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "RU");
	char buf;
	string buf_to_ignore;
	// EXP
	cout << "=======================" << endl;
	cout << "Double input test" << endl;
	string input;
	cout << "Enter number: ";
	getline(cin, input);
	double input_double = 0.0;
	input_double = exp_form_to_double(input);
	cout << "Number you have wrote: " << input_double << endl;
	cout << "=======================" << endl;
	do {
		cout << "Enter arithmetic expression: " << endl;
		getline(cin, input);
		calc_arithmetic(input);
		cout << "Continue? ";
		cin >> buf;
		cin.clear();
		getline(cin, buf_to_ignore);
	} while (buf != 'n' && buf != 'N');
	cout << "=======================" << endl;
	return 0;
}
