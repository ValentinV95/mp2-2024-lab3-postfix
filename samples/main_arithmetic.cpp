// реализация пользовательского приложения

#include "arithmetic.h"
#include <iostream>
#include <string>
#include <iomanip>

int main()
{
	TPostfix p;
	std::string trash;
	std::cout << "Arythmetic expression evaluator.\n"
				 "Enter (q)uit to exit the program or (h)elp for available features\n";

	while (true)
	{
		try
		{
			std::cout << "> ";
			std::string s;
			std::getline(std::cin, s);
			if (s == "q" || s == "quit") break;
			else if (s == "h" || s == "help")
			{
				std::cout << "List of available system commands:\n"
							 "vars - prints list of existing variables.\n"
							 "clear - clears list of variables.\n"
							 "help - prints this message (can be also done by typing h).\n"
							 "quit - quits the program (can be also done by typing q).\n\n"
							 "List of available functions: sin, cos, tan, asin, acos, atan, exp, ln, sqrt\n"
							 "Usage of functions: [function_name] [operand] (you can enter a single operand without parenthesis, separating"
							 " it from the function token with a space, i.e. sin 1.)\n\n"
							 "List of available operators: +, -, *, /, ^ (exponentiation)\n"
							 "Pre-defined variables: e, pi\n\n"
							 "You can assign variables by writing:\n"
							 "[variable_name] = [value] or [variable_name] = [expression]\n"
							 "Multiple assignment can be processed. Check that your variable name is valid (i.e. it is not e, pi, function name etc.)\n"; continue;
			}

			else if (s == "vars")
			{
				for (auto& v : p.getVariables())
					std::cout << std::setprecision(15) << v.first << ": " << v.second << std::endl;
			}

			else if (s == "clear") { p.clearVariables(); }
			else if (s == "") { continue; }
			else std::cout << std::setprecision(15) << p.evaluate(s) << std::endl;
		}

		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}
