#include "arithmetic.h"
#include "expr_err.h"
#include "locale.h"
int main()
{
	ArithmeticExpression AE;
	Vec<string>* Names=&(variable::GetNameVec());
	string s;
	bool end = false, proceed = true, skip = false;
	size_t sz, i;
	double res, tmp;
	char c;
	cout << "Before you start, see the instructions in the file MANUAL.txt in the root directory\n\n\n";
	system("pause");
	while (!end)
	{
		proceed = true;
		skip = false;
		cout << "Enter expression:\n";
		getline(cin, s);
		try
		{
			AE.Rebuild(s);
		}
		catch (expression_error e)
		{
			cout << "Error\t" << e.what() << '\n' << "Press any key to continue" << '\n' << endl;
			skip = true;
		}
		if (!skip)
		{
			cout << "You entered: " << AE.GetInfix();
			cout << "\nThis expression in postfix form: " << AE.PrintPostfix();
			while (proceed)
			{
				sz = (*Names).GetSize();
				for (i = 2; i < sz; i++)
				{
					cout << "\nEnter value of " << (*Names)[i] <<" : ";
					cin >> tmp;
					variable::Init(i, tmp);
				}
				res = AE.Calculate();
				cout << "\nCalculation result: ";
				if (isinf(res))
				{
					if (res < 0.0)
						cout << "-";
					cout << "infinity";
				}
				else if (isnan(res))
					cout << "undetermined";
				else
					cout << res;
				do
				{
					cout << "\n\nWould you like to calculate the expression for other variables values? Y/N ";
					cin >> c;
				} while (c != 'Y' && c != 'y' && c != 'N' && c != 'n');
				if (c == 'n' || c == 'N')
					proceed = false;
			}
			do
			{
				cout << "\n\nWould you like to calculate another expression? Y/N ";
				cin >> c;
			} while (c != 'Y' && c != 'y' && c != 'N' && c != 'n');
			if (c == 'n' || c == 'N')
				end = true;
		}
		variable::GetValVec().clear();
		variable::GetNameVec().clear();
		cin.ignore(32767, '\n');
	}
	return 0;
}
