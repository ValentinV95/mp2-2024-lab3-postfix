// реализация пользовательского приложения
#include "arithmetic.h"

int main()
{
	string input;
	char recount = 'y';
	char again = 'y';
	setlocale(LC_ALL, "ru_RU.UTF-8");
	while (again == 'y')
	{
		try
		{
			recount = 'y';
			cout << "Введите выражение:" << endl << " · Доступны функции sin(), cos(), tan(), exp(), ln()"
				<< endl << " · Доступен ввод любого количества переменных вида x<натуральное_число>" << endl
				<< " · Любое количество пробелов в любом месте вводимого выражения не влияет на его результат" << endl
				<< " Для завершения ввода нажмите Enter" << endl;
			getline(cin, input);
			TPostfix T(input);
			while (recount == 'y')
			{
				switch (T.Get_ind_variable())
				{
				case 0: break;
				case 1:
				{
					cout << "Введите значение переменной x";
					break;
				}
				default:
				{
					cout << "Последовательно введите значения переменных " << endl << "x";
					break;
				}
				}
				T.asker();
				cout << " = " << T.count() << endl;
				if (T.Get_ind_variable() != 0)
				{
					cout << "Пересчитать с другими значениями? y/<любой другой> ";
					cin >> recount;
				}
				else recount = 'n';
			}
			cout << "Ввести другое выражение/завершить программу? y/<любой другой> ";
			cin >> again;
		}
		catch (const exception& e)
		{
			cout << e.what() << endl;
		}
	}
	return 0;
}
