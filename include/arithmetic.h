// объявление функций и классов для вычисления арифметических выражений

#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "stack.h"

using namespace std;

class TPostfix
{
private:
	class Lexeme
	{
	public:
		int type_of_lex; //1 - бинарная операция, 2 - '(', 3 - ')',
		//4 - переменная, 5 - унарный минус, 6 - функция: 6, 1 - sin;
		//6, 2 - cos; 6, 3 - tan; 6, 4 - exp; 6, 5 - ln; 7 - число
		void* lex;
		size_t pos=0; //индекс операнда (по умолчанию = 0)
		Lexeme() noexcept { //Лишние копирования?
			lex = nullptr;
			type_of_lex = 0;
			pos = 0;
		}

		Lexeme(const Lexeme& rv) : type_of_lex(rv.type_of_lex), pos(rv.pos) {
			lex = rv.lex;
		}

		template <typename T>
		Lexeme(int t_of_l, T op, size_t position=0) : type_of_lex(t_of_l), pos(position)
		{
			lex = new T(op);
		}

		Lexeme& operator=(const Lexeme & rv)
		{
			if (this == &rv)
				return *this;
			lex = rv.lex;
			pos = rv.pos;
			type_of_lex = rv.type_of_lex;
			return *this;
		}
	};

	Lexeme* Rev_Pol_Notation;  //ОПЗ
	Lexeme* copy_Rev_Pol_Notation;  //копия ОПЗ
	int* arr_num_variable; //массив с номерами переменных
	double* arr_value_variable;//массив со значениями переменных
	size_t i = 0, ind_RPN = 0, cap_RPN, ind_variable = 0, cap_variable;
	TStack <Lexeme> ops;	   //stack лексем

public:

	TPostfix(string& inp);							//Вызвать, когда хочется преобразовать инфиксное выражение в постфиксное, но не знаешь, как
	void duplicate_RPN(bool RPN_to_copyRPN);		//Вызвать, когда хочется скопировать ОПЗ
	void insert_result(const Lexeme& lex);			//Вызвать, когда хочется внести очередную лексему в ОПЗ, но не знаешь, как
	void insert_variable(int xi);					//Вызвать, когда хочется внести очередную переменную в массив оных, но не знаешь, как
	void asker();									//Вызвать, когда хочется узнать значения переменных, но не знаешь, как
	size_t Get_ind_variable();						//Вызвать, когда хочется узнать количество переменных, но не знаешь, как
	double count();									//Вызвать, когда хочется подсчитать результат, но не знаешь, как
};