// реализация функций и классов для вычисления арифметических выражений

#include "arithmetic.h"

TPostfix::TPostfix() //конструктор присваивания
{
	size = 0;
	infix = "";
	postfix = "";
	result = 0.0;
	data = new string[size]();
}

TPostfix::TPostfix(string new_infix)
{
	size = new_infix.size();
	infix = new_infix;
	postfix = "";
	result = 0.0;
	data = new string[size]();

	toLexem();
}

void TPostfix::setTPostfix(string infix_new) //задать строку
{
	delete[] data;

	infix = infix_new;
	size = infix_new.size();
	postfix = "";
	result = 0.0;

	data = new string[size]();

	toLexem();
}

void TPostfix::toLexem() //перевод выражения в массив лексем
{
	int summ_brackets = 0; //проверка на количество открывающихся и закрывающихся скобок
	size_t lexnumber = 0; //размер массива лексем

	for (size_t i = 0; i < size; i++)
	{
		if (infix[i] == '+' || infix[i] == '*' || infix[i] == '/')
		{
			if (i == 0 || (i + 1) == size || (infix[i - 1] < '0' && infix[i - 1] != ')'))
				throw invalid_argument("Operation was installed in wrong position");

			data[lexnumber] = infix[i]; //отдельная лексема
			lexnumber++;
			continue;
		}

		else if (infix[i] == '-')
		{
			if ((i + 1) == size)
				throw invalid_argument("Operation was installed in wrong position");

			if (i == 0 || (infix[i - 1] < '0' && infix[i - 1] != ')')) //проверка на унарный минус
			{
				data[lexnumber] = '~';
				lexnumber++;
			}

			else if (infix[i - 1] == 'E') //отрицательная степень
			{
				data[lexnumber] += '~';
			}

			else
			{
				data[lexnumber] = infix[i];
				lexnumber++;
			}
			continue;
		}

		else if (infix[i] == '(')
		{
			if (i + 1 == size)
				throw invalid_argument("Opening bracket was installed in wrong position");

			if(i != 0 && (infix[i - 1] > '0' || infix[i - 1] == ')'))
				throw invalid_argument("There is no operation");

			data[lexnumber] = infix[i];
			lexnumber++;
			summ_brackets++;
			continue;
		}

		else if (infix[i] == ')')
		{
			if (i == 0 || (infix[i - 1] < '0' && infix[i - 1] != ')'))
				throw invalid_argument("Closing bracket was installed in wrong position");

			data[lexnumber] = infix[i];
			lexnumber++;
			summ_brackets--;
			continue;
		}

		else if (i != 0 && infix[i - 1] == ')')
			throw invalid_argument("There is no operation");

		else if (infix[i] >= 'a' && infix[i] <= 'z') //работа с переменными
		{
			if (i != 0 && infix[i - 1] >= '0') //если между числом и переменной нет операции
				throw invalid_argument("There is no operation between a number and a variable");
			
			if (i + 1 != size && infix[i + 1] == '.') //если после переменной стоит точка
				throw invalid_argument("The dot can't be placed after the variable");
				
			data[lexnumber] = infix[i];
			lexnumber++;
			continue;
		}

		else if (infix[i] >= '0' && infix[i] <= '9') //работа числами
		{
			if (i != 0 && infix[i - 1] >= 'a' && infix[i - 1] <= 'z') //если нет операции между числом и переменной
				throw invalid_argument("There is no operation between a number and a variable");

			else if (i + 1 == size || (infix[i + 1] < '0' && infix[i + 1] != '.')) //он собирает число из строки "infix" и добавляет его в массив "data" до тех пор, пока не достигнет символа, который не является цифрой или точкой, или пока не достигнет конца строки "infix".
			{ 
				data[lexnumber] += infix[i]; //продолжение числа
				lexnumber++;
			}

			else data[lexnumber] += infix[i];
			continue;
		} 

		else if (infix[i] == 'E') //работа с экспонентой
		{
			if (i + 1 == size || i == 0 || infix[i - 1] < '0' && infix[i - 1] != '.' || infix[i + 1] < '0' && infix[i + 1] != '-')
				throw invalid_argument("Error, wrong exponentional notation");

			else 
				data[lexnumber] += infix[i];
			continue;
		}

		else if (infix[i] == '.') //работа с точкой
		{
			if (i == 0 || (i + 1) == size || infix[i - 1] < '0' || infix[i - 1] > '9' || infix[i + 1] < '0' || infix[i + 1] > '9' && infix[i + 1] != 'E')
				throw invalid_argument("Number must be in math form");
			
			else
				data[lexnumber] += infix[i];
			continue;
		}

		else //если инородное существо
			throw invalid_argument("There is a foreign creature...");
	}

	if (summ_brackets != 0) //если число открывающихся и закрывающихся скобок не совпадают
		throw range_error("Opening and closing brackets must to have equal number");

	size = lexnumber;
}

void TPostfix::value_of_variable() //присвоить значение переменной
{
	string operand, value;

	for (size_t i = 0; i < size; i++)
	{
		if (data[i] >= "a" && data[i] <= "z")
		{
			value = data[i];
			cout << "\n" << "Enter a value for " << value << " : ";
			cin >> operand;

			for (size_t j = i; j < size; j++)
				if (this->data[j] == value)
					this->data[j] = operand;
		}
	}
}

size_t TPostfix::getPriority(string operat) //получить приоритет для операций
{
	if (operat == "+" || operat == "-")
		return 1;
	else if (operat == "*" || operat == "/")
		return 2;
	else if (operat == "~")
		return 3;
	else 
		return 0;
}

void TPostfix::toPostfix() //Преобразование инфиксной формы в постфиксную
{ 
	size_t psize = 0;
	string* pform = new string[size];

	for (size_t i = 0; i < size; i++)
	{
		if (data[i] >= "0" && data[i] <= "9")
		{
			pform[psize] = data[i];
			psize++;
			continue;
		}
			
		else if (data[i] == "(")
		{
			operations.push(data[i]); //текущая операция (data[i]) добавляется в стек операций.
			continue;
		}

		else if (data[i] == ")")
		{
			while ((operations.top() != "("))  //пока верхний элемент не равен откр скобки
			{
				pform[psize] = operations.pop(); //достаём элементы из стэка и присваиваем в постифк запись
				psize++;
			}
			operations.pop(); //извлекаем из стэка скобку
			continue;
		}

		else if (data[i] == "~")
			operations.push(data[i]);

		else 
		{//если стэк не пуст, приоритет операции на вершине стека не превосходит приоритет текущей операции
			while (!operations.isEmpty() && (getPriority(operations.top()) >= getPriority(data[i])))
			{
				pform[psize] = operations.pop(); //извлекается элемент из стека операций (operations.pop()) и добавляется в массив postfixform.
				psize++;
			}
			operations.push(data[i]);
		}
	}

	while (!operations.isEmpty()) //пока стэк не пуст
	{
		pform[psize] = operations.pop();
		psize++;
	} //извлекаются оставшиеся операции из стека operations. 
	// Цикл продолжается, пока стек не станет пустым

	size = psize;

	for (size_t i = 0; i < size; i++)
	{
		data[i] = pform[i];
		postfix += pform[i];
	} //значения из массива pform копируются обратно в исходный массив data.
	// + добавляются к строке postfix для последующего использования.
}

double TPostfix::toСonverter(string number) //конвертор стоки в дабл
{
	double double_number = 0.0, sign = 1.0, e_double = 0.0;
	int flag = 0, k = 0, dot = 0;
	string e_num;

	for (size_t i = 0; i < number.size(); i++)
	{
		if (dot > 1) //если в числе более одной точки
			throw runtime_error("More than 1 dot");

		if (number[i] == '~')
		{
			if (i != 0) //если минус стоит не перед числом
				throw runtime_error("Minus can't stay in this place");

			sign = -1.0;
			continue;
		}

		if (number[i] == '.')
		{
			flag = 1;
			dot++;
			continue;
		}

		if (number[i] == 'E')
		{
			for (size_t j = i + 1; j < number.size(); j++)
			{
				if ((number[j] >= '0' && number[j] <= '9') || number[j] == '~' || number[j] == '-') //если после Е стоит число или минус
					e_num += number[j]; //кладём этот элемент в строку
				else
					throw invalid_argument("Exponential notation contains foreign characters");
			}

			e_double = toСonverter(e_num); //преобразуем

			break;
		}

		if ((number[i] < '0') || (number[i] > '9'))
			throw invalid_argument("Inccorect symbol");

		if (flag) k++; //считает, сколько цифр после запятой

		double_number = double_number * 10.0 + static_cast<double>(number[i] - '0'); //сравнение аски кодов элементов
	}

	for (int i = 0; i < k; i++)
		double_number /= 10.0;

	if (sign == -1.0)
		double_number *= sign;

	double_number *= pow(10.0, e_double);

	return double_number;
}

void TPostfix::toCalculate() //калькулятор
{
	value_of_variable();

	double tmp;
	double exp = pow(10, -20);

	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == "+")
		{
			tmp = numbers.pop(); //достаёт из стэка верхний элемент
			tmp = numbers.pop() + tmp; //прибавляет к нему следующий элемент из стэка
			numbers.push(tmp);  //отправляет новое значение обратно в стэк
		}

		else if (data[i] == "-")
		{
			tmp = numbers.pop();
			tmp = numbers.pop() - tmp;
			numbers.push(tmp);
		}

		else if (data[i] == "*")
		{
			tmp = numbers.pop();
			tmp = numbers.pop() * tmp;
			numbers.push(tmp);
		}

		else if (data[i] == "/")
		{
			if (abs(numbers.top()) < exp)
				throw domain_error("Division by zero isn't possible");

			tmp = numbers.pop();
			tmp = numbers.pop() / tmp;
			numbers.push(tmp);
		}

		else if (data[i] == "~")
		{
			tmp = numbers.pop();
			numbers.push(-tmp);
		}

		else numbers.push(toСonverter(data[i])); //число преобразуется в дабл и добавляется в стэк
	}

	result = numbers.pop(); //в результат записывается последний элемент из стэка
}

string TPostfix::getPostfix() //получить постфиксную форму записи в строке
{
	return postfix;
}

string TPostfix::getInfix() //получить инфиксную форму записи в строке
{
	return infix;
}

double TPostfix::getResult() //получить результат вычисления в дабл
{
	return result;
}

TPostfix::~TPostfix() //деструктор
{
	delete[] data;
}