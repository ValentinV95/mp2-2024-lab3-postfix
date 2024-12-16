#include <iostream>
#include <string>
#include "arithmetic.h"
#include <windows.h>
using namespace std;


int main()
{
	string expression;
	setlocale(LC_ALL, "ru");
	setlocale(LC_NUMERIC, "en");
	system("title Postfix form calculator");
	bool flag = 0;
	while (!flag)
	{
		cout << "Enter expression: ";
		getline(cin, expression);
		try {
			TPostfix tmp(expression);
			flag = true;
		}
		catch (invalid_argument) {
			cout << "Wrong expression!" << endl;
			system("PAUSE");
			system("cls");
		}
	}
	TPostfix postfix(expression);
	auto m = postfix.getOperands();
	for (auto& op : m)
	{
		if (isalpha(op.first[0]))
		{
			string val;
			cout << "Enter value for " << op.first << ": ";
			cin >> val;
			op.second = stod(val);
		}
	}
	cout << "Arithmetic expression: " << postfix.getInfix() << endl;
	cout << "Postfix form: " << postfix.getPostfix() << endl;
	try {
		cout << "Calculated value: " << postfix.calculate(m) << endl;
	}
	catch (logic_error) {
		cout << "Calculate error!" << endl;
		exit(0);
	}
	return 0;
}
