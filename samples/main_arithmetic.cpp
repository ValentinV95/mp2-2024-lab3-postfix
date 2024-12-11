// реализация пользовательского приложения
#include "parse_digits.h"
#include "parse_string.h"
#include <iostream>
#include <iomanip>

int main()
{
	
	while (true) {

		std::string s;
		
		getline(std::cin, s);
		if (s == "exit") {
			break;
		}
		Main_Parser(s);
	}
	
}
