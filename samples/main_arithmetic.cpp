// реализация пользовательского приложения
#include "stack.h"
#include "parser.h"
#include "myvector.h"
#include "arithmetic.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>

/*
		try {
		while (true) {
			getline(cin, s);
			std::ios_base::fmtflags f(cout.flags());
			num = parser(s);
			cout << num << endl;
			cout << fixed << setprecision(20) << num << endl;
			cout.flags(f);
		}
		catch (exception& e) {
		int it = stoi(e.what());
		cout << s.substr(0, it) << " ";
		cout << "\033[31m" << s[it] << "\033[0m";
		if (it >= s.length()) cout << " " << s.substr(it, s.length()) << endl;
		else cout << " " << s.substr(it + 1, s.length()) << endl;
	}
*/

using namespace std;

int main()
{
	cout << "enter the expression" << endl;
	string str;
	getline(cin, str);
	try {
		calculator expr(str);
		expr.askForVariablesValues();
		cout << expr.calculate() << endl;
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}

    return 0;
}
