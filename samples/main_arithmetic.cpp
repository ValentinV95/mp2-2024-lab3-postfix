#include "Pars.h"
#include <iostream>
#include "arithmetic.h"
#include <iomanip>

int main()
{
	try {
		std::string s;
		getline(std::cin, s);
		Vector<Lexeme> v = parser(s);
		for (int i = 0; i < v.getsize(); i++) {
			std::cout << v[i].value() << "  ";
		}
		std::cout << std::endl;
		Expression_ e(v);
		double r = e.evaluate();
		std::cout << std::fixed << std::setprecision(15) << r << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
