// объявление функций и классов для вычисления арифметических выражений

#include "stack.h"
#include <vector>
#include <map>
#include <cmath>
#include <string>

class TPostfix {
	std::vector<std::string> RPN;
	
	std::string Error_string(const std::string& s, int i); //Метод выделяющий первый ошибочный элемент в строке
	
	int get_prior(const std::string& s) noexcept; //Получить приоритет операции, если это не операция, возвращает 0
	
	int TPostfix::get_prior(char c) noexcept; //аналогичная функция для символов

	double valid(const std::string& s); //Метод, превращающий строку, которая уже проверена на корректность, в число
	
	std::string number_check(const std::string& s, int& i); //Метод принимает обрабатываемую строку и индекс, с которого начинается число и проверяет его на корректность, возвращая его
public:
	TPostfix(const std::string& s); //Преобразовать строку в постфиксную форму записи, если это возможно
	
	double count(); //Посчитать строку, хранящуюся в элементе класса
};