// реализация пользовательского приложения

#include "arithmetic.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>


int main()
{
	
		cout << "Hello! It`s your new calculator!" << endl;
		cout << "You can use operations +,-,/,*. If \"-\" is unary, use breckets for correct work." << endl;
		cout << "Names of your variables can use letters, digits and dots (not on the first position) and \"_\"." << endl;
		cout << "Double numbers should use dot instead of comma, can use form with \'e\'" << endl << endl;
		cout << setprecision(8) << fixed;

		while (true)
		{
			try
			{
				string exp;
				cout << "Give the expression without spaces: ";
				getline(cin,exp);
				string error;
				for (int i = 0; i < exp.length(); i++)
				{
					error += exp[i];
					if (exp[i] == ' ')
					{
						error += " <- You shouldn`t use spaces";
							throw invalid_argument(error.c_str());
					}
				}
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
					cin.ignore();
					continue;
			
				if (choice == 3)
					break;
			}
			catch (exception& e) {
				cout << e.what() << endl << endl;
			}
		}
		
}
