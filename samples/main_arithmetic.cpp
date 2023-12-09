// реализация пользовательского приложения

#include "arithmetic.h"

int main()
{
	cout << "Hello! Read the rules for entering a mathematical expression, please:" << "\n";
	cout << " - Input your expression without spaces;" << "\n";
	cout << " - You can use operations such as +, -, *, /;" << "\n";
	cout << " - In floating point numbers, put a dot instead of a comma;" << "\n";
	cout << " - Variables can be named in any English letters (necessarily lowercase!);" << "\n";
	cout << " - Don't skip the multiplication operation!" << "\n";
	cout << " - Enter only the permitted types of numbers (entry of the type 09 is not allowed)" << "\n";
	cout << " - The exponent is written using the English capital letter E (for example: 2.0E10 or 1.E-2)." << "\n" << "\n";

	string infix;
	TPostfix math_exp;

	while (1)
	{
		cout << "Enter an arithmetic expression: ";
		cin >> infix;

		try
		{
			math_exp.setTPostfix(infix);
			cout << "Infix form: " << math_exp.getInfix() << "\n";
			math_exp.toPostfix();
			cout << "Postfix form: " << math_exp.getPostfix() << "\n";
			math_exp.toCalculate();
			cout << setprecision(10) << "Result: " << math_exp.getResult() << "\n";
		}
		catch (exception& e) {
			cout << e.what() << "\n";
			break;
		}

		break;
	}

	return 0;
}