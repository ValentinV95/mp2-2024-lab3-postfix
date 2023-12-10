// реализация пользовательского приложения
#include "arithmetic.h"
#include "stack.h"

#include <string>
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "RU");
	// EXP
	cout << "=======================" << endl;
	cout << "Double input test" << endl;
	string input;
	cout << "Enter number: ";
	cin >> input;
	double input_double = 0.0;
	input_double = exp_form_to_double(input);
	cout << "Number you have wrote: " << input_double << endl;
	cout << "=======================" << endl;
	//
	string text = "~15   +a b  -sin(a n,*(~sa 1))/ joker=*(b)*x1";
	vector<string> tmp = arithmetic_to_lexems(text);
	string text2 = "15 * 25 - sin(95) / 2";
	vector<string> tmp2 = arithmetic_to_lexems(text2);
	//for (size_t i = 0; i < tmp.size(); i++) {
	//	cout << tmp[i] << endl;
	//}
	TPostfix<double> a;
	try {
		a.toPostfix(tmp);
	}
	catch (const exception &e) {
		cout << e.what() << endl;
	}
	a.askOperands(cin);
	try {
		cout << a.calculate() << endl;
	}
	catch (const exception &e) {
		cout << e.what() << endl;
	}
	try {
		a.toPostfix(tmp2);
	}
	catch (const exception &e) {
		cout << e.what() << endl;
	}
	a.askOperands(cin);
	try {
		cout << a.calculate() << endl;
	}
	catch (const exception &e) {
		cout << e.what() << endl;
	}
	return 0;
}
