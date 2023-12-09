// реализация функций и классов для вычисления арифметических выражений

#include "arithmetic.h"

TPostfix::TPostfix()
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

void TPostfix::setTPostfix(string infix_new)
{
	delete[] data;

	infix = infix_new;
	size = infix_new.size();
	postfix = "";
	result = 0.0;

	data = new string[size]();

	toLexem();
}

void TPostfix::toLexem() //converting an expression into lexem mas
{
	int summ_brackets = 0;
	size_t lexnumber = 0;

	for (size_t i = 0; i < size; i++)
	{
		if (infix[i] == '+' || infix[i] == '*' || infix[i] == '/')
		{
			if (i == 0 || (i + 1) == size || (infix[i - 1] < '0' && infix[i - 1] != ')'))
				throw invalid_argument("Operation was installed in wrong position");

			data[lexnumber] = infix[i];
			lexnumber++;
			continue;
		}

		else if (infix[i] == '-')
		{
			if ((i + 1) == size)
				throw invalid_argument("Operation was installed in wrong position");

			if (i == 0 || (infix[i - 1] < '0' && infix[i - 1] != ')'))
			{
				data[lexnumber] = '~';
				lexnumber++;
			}

			else if (infix[i - 1] == 'E')
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

		else if (infix[i] >= 'a' && infix[i] <= 'z')
		{
			if (i != 0 && infix[i - 1] >= '0')
				throw invalid_argument("There is no operation between a number and a variable");
			
			if (i + 1 != size && infix[i + 1] == '.')
				throw invalid_argument("The dot can't be placed after the variable");
				
			data[lexnumber] = infix[i];
			lexnumber++;
			continue;
		}

		else if (infix[i] >= '0' && infix[i] <= '9')
		{
			if (i != 0 && infix[i - 1] >= 'a' && infix[i - 1] <= 'z')
				throw invalid_argument("There is no operation between a number and a variable");

			else if (i + 1 == size || (infix[i + 1] < '0' && infix[i + 1] != '.'))
			{ 
				data[lexnumber] += infix[i]; //продолжение числа
				lexnumber++;
			}

			else data[lexnumber] += infix[i];
			continue;
		} 

		else if (infix[i] == 'E')
		{
			if (i + 1 == size || i == 0 || infix[i - 1] < '0' && infix[i - 1] != '.' || infix[i + 1] < '0' && infix[i + 1] != '-')
				throw invalid_argument("Error, wrong exponentional notation");

			else 
				data[lexnumber] += infix[i];
			continue;
		}

		else if (infix[i] == '.')
		{
			if (i == 0 || (i + 1) == size || infix[i - 1] < '0' || infix[i - 1] > '9' || infix[i + 1] < '0' || infix[i + 1] > '9' && infix[i + 1] != 'E')
				throw invalid_argument("Number must be in math form");
			
			else
				data[lexnumber] += infix[i];
			continue;
		}

		else
			throw invalid_argument("There is a foreign creature...");
	}

	if (summ_brackets != 0)
		throw range_error("Opening and closing brackets must to have equal number");

	size = lexnumber;
}

void TPostfix::value_of_variable() //assign a value to a variable
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

size_t TPostfix::getPriority(string operat)
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

void TPostfix::toPostfix() //converting an infix to a postfix
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
			operations.push(data[i]);
			continue;
		}

		else if (data[i] == ")")
		{
			while ((operations.top() != "("))
			{
				pform[psize] = operations.pop();
				psize++;
			}
			operations.pop();
			continue;
		}

		else if (data[i] == "~")
			operations.push(data[i]);

		else 
		{
			while (!operations.isEmpty() && (getPriority(operations.top()) >= getPriority(data[i])))
			{
				pform[psize] = operations.pop();
				psize++;
			}
			operations.push(data[i]);
		}
	}

	while (!operations.isEmpty())
	{
		pform[psize] = operations.pop();
		psize++;
	}
	
	size = psize;

	for (size_t i = 0; i < size; i++)
	{
		data[i] = pform[i];
		postfix += pform[i];
	} 
}

double TPostfix::toСonverter(string number) //сonverting a string to a double
{
	double double_number = 0.0, sign = 1.0, e_double = 0.0;
	int flag = 0, k = 0, dot = 0;   //k - the number of digits after the dot
	string e_num;

	for (size_t i = 0; i < number.size(); i++)
	{
		if (dot > 1)
			throw runtime_error("More than 1 dot");

		if (number[i] == '~')
		{
			if (i != 0)
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
				if ((number[j] >= '0' && number[j] <= '9') || number[j] == '~' || number[j] == '-')
					e_num += number[j];
				else
					throw invalid_argument("Exponential notation contains foreign characters");
			}

			e_double = toСonverter(e_num);

			break;
		}

		if ((number[i] < '0') || (number[i] > '9'))
			throw invalid_argument("Inccorect symbol");

		if (flag) k++;

		double_number = double_number * 10.0 + static_cast<double>(number[i] - '0');
	}

	for (int i = 0; i < k; i++)
		double_number /= 10.0;

	if (sign == -1.0)
		double_number *= sign;

	double_number *= pow(10.0, e_double);

	return double_number;
}

void TPostfix::toCalculate() //calculations
{
	value_of_variable();

	double tmp;
	double exp = pow(10, -20);

	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == "+")
		{
			tmp = numbers.pop();
			tmp = numbers.pop() + tmp;
			numbers.push(tmp);
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

		else numbers.push(toСonverter(data[i]));
	}

	result = numbers.pop();
}

string TPostfix::getPostfix()
{
	return postfix;
}

string TPostfix::getInfix()
{
	return infix;
}

double TPostfix::getResult()
{
	return result;
}

TPostfix::~TPostfix()
{
	delete[] data;
}
