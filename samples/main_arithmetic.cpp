// реализация пользовательского приложения
#include "stack.h"
#include "parser.h"
#include "myvector.h"
#include "arithmetic.h"
#include <iostream>
#include <iomanip>

using namespace std;

// parse to vector of lexems
// remember than it should be unique names of variables
// prohibited names: sin(, cos(, +, etc. Avaliable names: si(n, nis(, soc(), etc.
// in my case, it is possible to write sin5, logx etc., It means, brackets priority brackets
// please, enter numbers 
// pow syntax is: a pow b = pow(a, b) NOOOO!!! do it better with , sym
// finally, you mush enter pow as pow(a, b)

int main()
{
	cout << "MAIN RULES: all names, including si(n, `!2 are allowed. Also, expression like +(a, b) is allowed\n";
	cout << "--var not allowed! Instead, write -(-1). Also, please, write functions like pow((expr1), (expr2))\n";
	cout << "You can write sinx, but sinexpr, instead of sin(expr) leads you to undefined behaviour\n" << endl;
	cout << "Enter the expression" << endl;
	string str;
	string tmpstr;
	getline(cin, str);
	try {
		calculator expr(str);
		if (expr.araThereAnyVariables()) {
			while (true) {
				cout << "Now enter your variables" << endl;
				expr.askForVariablesValues();
				cout << endl << "Result: " << expr.calculate() << endl;
				cout << "Do you want to enter another values of variables (y/n)?" << endl;
				getline(cin, tmpstr);
				if (tmpstr == "y") continue;
				break;
			}
		}
		else {
			expr.askForVariablesValues();
			cout << endl << "Result: " << expr.calculate() << endl;
		}
	}
	catch (exception& e) {
		string errstr = e.what();
		string numstr = "";
		size_t i;
		int len = 0;
		for (i = 0; i < errstr.size(); ++i) {
			numstr += errstr[i];
			if (errstr[i] == 'L') break;
		}
		if (i < errstr.length()) {
			len = stoi(numstr);
			++i;
		}
		else i = 0;
		numstr = "";

		for (; i < errstr.size(); ++i) {
			numstr += errstr[i];
			if (errstr[i] == 'E') break;
		}
		if (i >= errstr.length()) throw runtime_error("Bad exception");
		int it = stoi(numstr);
		if (it != -1) {
			cout << str.substr(0, it) << " ";
			if (it + len > str.length()) throw runtime_error("Bad exception");
			cout << "\033[31m" << str.substr(it, len + 1) << "\033[0m";
			if (it + len + 1 < str.length()) cout << " " << str.substr(it + len + 1, str.length()) << endl;
		}
		cout << endl << errstr.substr(i + 1);
	}

    return 0;
}
