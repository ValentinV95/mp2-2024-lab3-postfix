#include <iostream>
#include "arithmetic.h"
#include "inputException.h"
#include "Vector.h"
#include <vector>

using namespace std;

int main()
{
	cout << "rules: " << endl;
	cout << "1. The variables are named 'x' + a non-negative constant. For example, just 'x', 'x1' or 'x3244'." << endl;
	cout << "2. Several unary cons need to be framed with parentheses. For example, '-(-6)'." << endl;
	cout << "3. The calculator supports the following mathematical functions:" << endl;
	cout << "   sin(x)" << endl;
	cout << "   cos(x)" << endl;
	cout << "   sqrt(x)" << endl;
	cout << "   ln(x)" << endl;
	cout << "   log2(x)" << endl;
	cout << "4. The argument of functions is always enclosed in parentheses." << endl;
	cout << "Enter an arithmetic expression:" << endl;
	string expression;
	getline(cin, expression);
	Vector<lexem*> lx, postfixLx;
	try
	{
		lx = parsingLexem(expression);
		inputVar(lx);
		postfixLx = toPostfix(lx);
		cout << calcArithmetic(postfixLx);
	}
	catch (const inputException& ex)
	{
		cout << expression << endl;
		if (ex.getPosLexemException() != -1)
		{
			for (int i = 0; i < ex.getPosLexemException(); i++) cout << " ";
			cout << "^" << endl;
		}
		cout << ex.what() << endl;
	}
	catch (...)
	{
		cout << "incorrect input";
	}
	deleteLx(lx);
	deleteLx(postfixLx);
	return 0;
}