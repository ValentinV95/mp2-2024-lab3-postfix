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
	setlocale(LC_ALL, "Russian");
	cout << "Перед началом работы просмотрите инструкцию в файле MANUAL.txt\n\n\n";
	system("pause");
	while (!end)
	{
		proceed = true;
		skip = false;
		cout << "Введите вычисляемое выражение:\n";
		getline(cin, s);
		try
		{
			AE.Rebuild(s);
		}
		catch (expression_error e)
		{
			cout << "Error\t" << e.what() << '\n' << '\n'<<endl;
			skip = true;
		}
		if (!skip)
		{
			cout << "Введено выражение: " << AE.GetInfix();
			cout << "\nВ постфиксной форме: " << AE.PrintPostfix();
			while (proceed)
			{
				sz = (*Names).GetSize();
				for (i = 2; i < sz; i++)
				{
					cout << "\nВведите значение переменной " << (*Names)[i] <<" : ";
					cin >> tmp;
					variable::Init(i, tmp);
				}
				res = AE.Calculate();
				cout << "\nРезультат операции: ";
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
					cout << "\n\nПосчитать выражение для других значений переменных? Y/N ";
					cin >> c;
				} while (c != 'Y' && c != 'y' && c != 'N' && c != 'n');
				if (c == 'n' || c == 'N')
					proceed = false;
			}
			do
			{
				cout << "\n\nПосчитать другое выражение? Y/N ";
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
