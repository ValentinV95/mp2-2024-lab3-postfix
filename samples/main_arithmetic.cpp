// реализация пользовательского приложения
#include "stack.h"
#include "parser.h"
#include "myvector.h"
#include "arithmetic.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	cout << "MAIN RULES: all names of varibles which are not operators or numners are allowed.\n";
	cout << "--var not allowed! Instead, write -(-1)\n";
	cout << "You can write sinx, but not like sin expression. Write sin(expression) instead\n" << endl;
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
//		cout << e.what() << endl;
		string errstr = e.what();
		string numstr = "";
		size_t i;
		int len = 1;
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
			cout << "\033[31m" << str.substr(it, len) << "\033[0m";
			if (it + len < str.length()) cout << " " << str.substr(it + len, str.length()) << endl;
		}
		cout << endl << errstr.substr(i + 1);
	}

    return 0;
}
