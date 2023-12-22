// реализация пользовательского приложения

#include "arithmetic.h"
#include <map>

int main()
{
	string expression;
	vector<string> post;
	map<string, double> variables;
	string choice;
	cout << "You can enter an unlimited number of variables of the form 'x...'." << endl;
	cout << "You can enter numbers like '12.345e2', '12.345e-2'. " << endl;
	cout << "Available operations : '+', '-'(also unary minus), '*', '/'" << endl;
	cout << "Enter an arithmetic expression." << endl;
	getline(cin, expression);
	while (true) {
		try
		{
			TPostfix postfix(expression);
			cout << "calculate - calculate your expression" << endl;
			cout << "replacement - replacing variables" << endl;
			cout << "0 - end program" << endl;
			cout << "Choose an action: ";
			getline(cin, choice);
			cout << endl;
			if (choice == "0") {
				return 0;
			}
			else if (choice == "replacement") {
				int count;
				string new_variable;
				cout << "How many variables to replace?" << endl;
				cin >> count;
				for (int i = 0; i < count; i++) {
					cout << "Enter the variable you want to replace: " << endl;
					getline(getline(cin, new_variable), new_variable);
					cout << endl;
					if (variables.count(new_variable) > 0) {
						double value;
						cout << "Enter the " << new_variable << ": ";
						cin >> value;
						variables[new_variable] = value;
					}
					else {
						throw invalid_argument("There was no such variable!");
					}
				}
			}
			else if(choice == "calculate"){
				cout << "Your expression: " << postfix.get_infix() << endl;
				post = postfix.to_postfix();
				cout << "Your expression in postfix form: ";
				for (size_t i = 0; i < post.size(); i++) {
					cout << post[i] << " ";
				}
				cout << endl;
				cout << "Result of expression: " << postfix.calculate(variables) << endl;
			}
			else {
				cout << "wrong choice" << endl;
			}
			}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}

  return 0;
}
