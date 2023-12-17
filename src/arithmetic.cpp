// реализация функций и классов для вычисления арифметических выражений

#include "arithmetic.h"

TPostfix::TPostfix(string new_infix)
{
	size = new_infix.size();
	infix = new_infix;
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
			if (i == 0 || (i + 1) == size || !isDigit(infix[i - 1]) && infix[i - 1] != ')')
			{
				error += "Operation was installed in wrong position. We have error in position ";
				error += i + 1 + '0';
				throw invalid_argument(error.c_str());
				
			}

			data[lexnumber] = infix[i];
			lexnumber++;
			continue;
			
		}

		else if (infix[i] == '-')
		{
			if ((i + 1) == size)
			{
				error += "Operation was installed in wrong position. We have error in position ";
				error += i + 1 + '0';
				throw invalid_argument(error.c_str());

			}

			if (i == 0 || (!isDigit(infix[i - 1]) && infix[i - 1] != ')'))
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
			{
				error += "Opening bracket was installed in wrong position. We have error in position ";
				error += i + 1 + '0';
				throw invalid_argument(error.c_str());

			}

			if (i != 0 && (infix[i - 1] >= '0' && infix[i - 1] <= '9' || infix[i - 1] == ')'))
			{
				error += "There is no operation. We have error in position ";
				error += i + 1 + '0';
				throw invalid_argument(error.c_str());

			}

			data[lexnumber] = infix[i];
			lexnumber++;
			summ_brackets++;

			continue;
		}

		else if (infix[i] == ')')
		{
			if (i == 0 || (!isDigit(infix[i - 1]) && infix[i - 1] != ')'))
			{
				error += "Closing bracket was installed in wrong position. We have error in position ";
				error += i + 1 + '0';
				throw invalid_argument(error.c_str());
			}

			data[lexnumber] = infix[i];
			lexnumber++;
			summ_brackets--;

			if (summ_brackets < 0)
			{
				error += "Closing bracket was installed in wrong position. We have error in position ";
				error += i + 1 + '0';
				throw invalid_argument(error.c_str());
			}

			continue;
		}

		else if (i != 0 && infix[i - 1] == ')')
		{
			error += "There is no operation. We have error in position ";
			error += i + 1 + '0';
			throw invalid_argument(error.c_str());
		}

		else if (infix[i] >= 'a' && infix[i] <= 'z')
		{
			if (i != 0 && infix[i - 1] >= '0')
			{
				error += "There is no operation between a number and a variable. We have error in position ";
				error += i + 1 + '0';
				throw invalid_argument(error.c_str());
			}

			if (i + 1 != size && infix[i + 1] == '.')
			{
				error += "The dot can't be placed after the variable. We have error in position ";
				error += i + 1 + '0';
				throw invalid_argument(error.c_str());
			}

			data[lexnumber] = infix[i];
			lexnumber++;
			continue;
		}

		else if (infix[i] >= '0' && infix[i] <= '9')
		{
			if (i != 0 && infix[i - 1] >= 'a' && infix[i - 1] <= 'z')
			{
				error += "There is no operation between a number and a variable. We have error in position ";
				error += i + 1 + '0';
				throw invalid_argument(error.c_str());
			}

			else if (i + 1 == size || (!isDigit(infix[i + 1]) && infix[i + 1] != '.'))
			{
				data[lexnumber] += infix[i];
				lexnumber++;
			}

			else data[lexnumber] += infix[i];
			continue;
		}

		else if (infix[i] == 'E')
		{
			if (i + 1 == size || i == 0 || !isDigit(infix[i - 1]) && infix[i - 1] != '.' || !isDigit(infix[i + 1]) && infix[i + 1] != '-')
			{
				error += "Wrong exponentional notation. We have error in position ";
				error += i + 1 + '0';
				throw invalid_argument(error.c_str());
			}

			else
				data[lexnumber] += infix[i];
			continue;
		}

		else if (infix[i] == '.')
		{
			if (i == 0 || (i + 1) == size || !isDigit(infix[i - 1]) || !isDigit(infix[i + 1]) && infix[i + 1] != 'E')
			{
				error += "Number must be in math form. We have error in position ";
				error += i + 1 + '0';
				throw invalid_argument(error.c_str());
			}

			else
				data[lexnumber] += infix[i];
			continue;
		}

		else
		{
			error += "There is a foreign creature... We have error in position ";
			error += i + 1 + '0';
			throw invalid_argument(error.c_str());
		}
	}

	if (summ_brackets != 0)
	{
		error += "Opening bracket was installed in wrong position. We have error in position ";
		throw invalid_argument(error.c_str());
	}

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

size_t TPostfix::getPriority(string operat) const
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

void TPostfix::toPostfix() //converting infix to postfix
{
	size_t psize = 0;
	string* pform = new string[size];
	TStack<string> operations;

	for (size_t i = 0; i < size; i++)
	{
		if (data[i] < "0" || data[i] == "~")
		{
			if (data[i] == "(")
				operations.push(data[i]);

			else if (data[i] == ")")
			{
				while ((operations.top() != "("))
					pform[psize++] = operations.pop();

				operations.pop();
			}

			else
			{
				if (!(data[i] == "~"))
				{
					while ((!operations.isEmpty()) && (getPriority(operations.top()) >= getPriority(data[i])))
						pform[psize++] = operations.pop();
				}

				operations.push(data[i]);
			}
		}

		else pform[psize++] = data[i];
	}

	while (!operations.isEmpty())
		pform[psize++] = operations.pop();

	size = psize;

	for (size_t i = 0; i < size; i++)
	{
		data[i] = pform[i];
		postfix += pform[i];
	}

	delete[] pform;
}

double TPostfix::string_in_double(string number) //сonverting a string to a double
{
	double double_number = 0.0, sign = 1.0, e_double = 0.0;
	int flag = 0, k = 0, dot = 0;   //k - the number of digits after the dot
	string e_num;

	for (size_t i = 0; i < number.size(); i++)
	{
		if (dot > 1)
		{
			error += "There is can't be more than one dot in the number. We have error in position ";
			error += i + 1 + '0';
			throw invalid_argument(error.c_str());
		}

		if (number[i] == '~')
		{
			if (i != 0)
			{
				error += "Minus can't stay in this place. We have error in position ";
				error += i + 1 + '0';
				throw invalid_argument(error.c_str());
			}

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
				{
					error += "Exponential notation contains foreign characters. We have error in position ";
					error += i + 1 + '0';
					throw invalid_argument(error.c_str());
				}
			}

			e_double = string_in_double(e_num);

			break;
		}

		if ((number[i] < '0') || (number[i] > '9'))
		{
			error += "Inccorect symbol. We have error in position ";
			error += i + 1 + '0';
			throw invalid_argument(error.c_str());
		}

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
			{
				error += "Division by zero isn't possible. We have error in position ";
				error += i + '0';
				throw invalid_argument(error.c_str());
			}

			tmp = numbers.pop();
			tmp = numbers.pop() / tmp;
			numbers.push(tmp);
		}

		else if (data[i] == "~")
		{
			tmp = numbers.pop();
			numbers.push(-tmp);
		}

		else numbers.push(string_in_double(data[i]));
	}

	result = numbers.pop();
}

string TPostfix::getPostfix() const
{
	return postfix;
}

string TPostfix::getInfix() const
{
	return infix;
}

double TPostfix::getResult() const
{
	return result;
}

bool TPostfix::isDigit(const char& elem)
{
	if ((elem <= '9' && elem >= '0') || elem == '.' || elem >= 'a' && elem <= 'z' || elem == 'E')
		return true;
	return false;
}

TPostfix::~TPostfix()
{
	delete[] data;
}
