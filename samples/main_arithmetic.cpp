// реализация пользовательского приложения

#include "arithmetic.h"
#include <iostream>
#include <vector>
#include <string>


int main()
{
	
		cout << "Hello! It`s your new calculator!" << endl;
		cout << "You can use operations +,-,/,*. If \"-\" is unary, use breckets for correct work." << endl;
		cout << "Names of your variables can use letters, digits and dots (not on the first position) and \"_\"." << endl;
		cout << "Double numbers should use dot instead of comma, can use form with \'e\'" << endl << endl;
		
		string exp;
		while (true)
		{
			try
			{
				cout << "Give the expression without spaces: ";
				cin >> exp;
				Arithmetic expression(exp);

				int choice;
				cout << "Do you want to calculate? \n1. Yes 2. New expression 3. Exit " << endl;
				cin >> choice;
				while (choice==1)
				{
					double res;
					res = expression.calculate();
					cout << "The result  is: " << res << endl << endl;
					cout << "Do you want to calculate? \n1. Yes 2. New expression 3. Exit " << endl;
					cin >> choice;
				}

				if (choice == 2)
					continue;
			
				if (choice == 3)
					break;
			}
			catch (exception& e) {
				cout << e.what() << endl << endl;
			}
		}

}
