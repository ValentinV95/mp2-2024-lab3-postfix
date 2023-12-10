// реализация пользовательского приложения

#include "arithmetic.h"
#include <iostream>
#include <vector>
#include <string>


int main()
{
	try
	{
		cout << "Hello! It`s your new calculator!" << endl;
		cout << "You can use operations +,-,/,*. If \"-\" is unary, use breckets for correct work." << endl;
		cout << "Names of your variables can use letters, digits and dotes (not on the first position) and \"_\"." << endl << endl;
		cout << "Give the expression without spaces: ";
		string exp;
		cin >> exp;
		Arithmetic expression(exp);
		while (true)
		{
			int choice;
			cout << "Do you want to calculate? \n1. Yes 2. New expression 3. Exit " << endl;
			cin >> choice;
			if (choice == 1)
			{
				double res;
				res = expression.calculate();
				cout << "The result  is: " << res << endl;;
			}
			if (choice == 2)
			{
				cout << "Give the expression: ";
				cin >> exp;
				Arithmetic expression(exp);
			}
			if (choice == 3)
				break;
			
		}
	}
	catch (exception& e) {
		cout << e.what();
	}
}
