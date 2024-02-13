#include "arithmetic.h"

TCalc::~TCalc()
{
	delete[] stroka;
}

TCalc::TCalc(string str)
{
	ln = str.size();
	infix = str;
	postfix = "";
	result = 0.0;
	stroka = new string[ln]();
	Lexems();
}


string TCalc::getInfix() const
{
	return infix;
}

string TCalc::getPostfix() const
{
	return postfix;
}
double TCalc::getResult() const
{
	return result;
}

void TCalc::Lexems()
{
	int brackets = 0;
	size_t lexem = 0;
	string error = "Incorrect expression: ";

	for (size_t i = 0; i < ln; i++)
	{
		char currentChar = infix[i];

		if (Operand(currentChar))
		{
			stroka[lexem] = currentChar;
			lexem++;

			if (i == 0)
			{
				error += currentChar + " cannot be the first element";
				throw invalid_argument(error.c_str());
			}
			else if (i + 1 == ln)
			{
				error += currentChar + " cannot be the last element";
				throw invalid_argument(error.c_str());
			}
			else if (!Operand(infix[i - 1]) && infix[i - 1] != ')')
			{
				error += currentChar + " must be preceded by a digit, operand, or closing bracket";
				throw invalid_argument(error.c_str());
			}
		}
		else if (currentChar == '-')
		{
			if (i + 1 == ln)
			{
				error += currentChar + " cannot be the last element";
				throw invalid_argument(error.c_str());
			}

			if (i == 0 || (!Operand(infix[i - 1]) && infix[i - 1] != ')'))
			{
				stroka[lexem] = '~';
				lexem++;
			}
			else if (infix[i - 1] == 'E')
			{
				stroka[lexem] += '~';
			}
			else
			{
				stroka[lexem] = currentChar;
				lexem++;
			}
		}
		else if (infix[i] == '(')
		{
			if (i + 1 == ln)
			{
				
					error += infix[i] + " не может быть последним";
					throw invalid_argument(error.c_str());
				
			}
			if (i != 0 && (infix[i - 1] >= '0' && infix[i - 1] <= '9' || infix[i - 1] == ')'))
			{
				error += infix[i] + "сначала должна быть проведена операция";
				throw invalid_argument(error.c_str());
			}
			stroka[lexem] = infix[i];
			lexem++;
			brackets++;
			continue;
		}
		else if (infix[i] == ')')
		{
			if (i == 0)
			{
				
					error += infix[i] + " не может быть первым";
					throw invalid_argument(error.c_str());
				
			}
			if (!Operand(infix[i - 1]) && infix[i - 1] != ')')
			{
				error += infix[i] + " должна содержать цифру, операнд или закрывающую скобку перед";
				throw invalid_argument(error.c_str());
			}
			stroka[lexem] = infix[i];
			lexem++;
			brackets--;
			if (brackets < 0)
			{
				error += "Лишняя скобка " + infix[i];
				throw invalid_argument(error.c_str());
			}
			continue;
		}
		else if (i != 0 && infix[i - 1] == ')')
		{
			error += infix[i] + "сначала должна быть проведена операция";
			throw invalid_argument(error.c_str());
		}
		else if (infix[i] >= '0' && infix[i] <= '9')
		{
			if (i != 0 && infix[i - 1] >= 'a' && infix[i - 1] <= 'z')
			{
				error += "Потеря операции " +  infix[i];
				throw invalid_argument(error.c_str());
			}
			else if (i + 1 == ln || (!Operand(infix[i + 1]) && infix[i + 1] != '.'))
			{
				stroka[lexem] += infix[i];
				lexem++;
			}
			else stroka[lexem] += infix[i];
			continue;
		}
		else if (infix[i] == 'E')
		{
			if (i + 1 == ln || i == 0 || !Operand(infix[i - 1]) && infix[i - 1] != '.' || !Operand(infix[i + 1]) && infix[i + 1] != '-')
			{
				error += "Неверная запись номера " + infix[i];
				throw invalid_argument(error.c_str());
			}
			else
				stroka[lexem] += infix[i];
			continue;
		}
		else if (infix[i] >= 'a' && infix[i] <= 'z')
		{
			if (i != 0 && infix[i - 1] >= '0')
			{
				error += "Потеря операции " + infix[i];
				throw invalid_argument(error.c_str());
			}
			if (i + 1 != ln && infix[i + 1] == '.')
			{
				error += "Не может быть точки после переменной " + infix[i];
				throw invalid_argument(error.c_str());
			}
			stroka[lexem] = infix[i];
			lexem++;
			continue;
			}
		else if (infix[i] == '.')
		{
			if (i == 0 || (i + 1) == ln || !Operand(infix[i - 1]) || !Operand(infix[i + 1]) && infix[i + 1] != 'E')
			{
				error += "Точка вне числа " + infix[i];
				throw invalid_argument(error.c_str());
			}
			else
				stroka[lexem] += infix[i];
			continue;
		}
		else
		{
			error += "Unidentified element " + infix[i];
			throw invalid_argument(error.c_str());
		}
	}
	if (brackets != 0)
	{
		error += "Количество закрывающих и открывающих скобок не совпадает ";
		throw invalid_argument(error.c_str());
	}
	ln = lexem;
}

void TCalc::Postfix()
{
	size_t psize = 0;
	string* pf = new string[ln];
	TStack<string> oper;
	for (int i = 0; i < ln; i++)
	{
		if (stroka[i] < "0" || stroka[i] == "~")
		{
			if (stroka[i] == "(")
			{
				oper.Push(stroka[i]);
			}
			else if (stroka[i] == ")")
			{
				while (oper.Top() != "(")
					pf[psize++] = oper.Pop();
				oper.Pop();
			}
			else
			{
				if (!(stroka[i] == "~"))
				{
					while ((!oper.IsEmpty()) && (priority(oper.Top()) >= priority(stroka[i])))
						pf[psize++] = oper.Pop();
				}
				oper.Push(stroka[i]);
			}
		}
		else pf[psize++] = stroka[i];
	}
	while (!oper.IsEmpty())
		pf[psize++] = oper.Pop();
	ln = psize;
	for (size_t i = 0; i < ln; i++)
	{
		stroka[i] = pf[i];
		postfix += pf[i];
	}
	delete[] pf;
}

void TCalc::valueofvar()
{
	string var, val;
	for (size_t i = 0; i < ln; i++)
	{
		if (stroka[i] >= "a" && stroka[i] <= "z")
		{
			val = stroka[i];
			cout << "\n" << "Enter a value for " << val<< " : ";
			cin >> var;
			for (size_t j = i; j < ln; j++)
				if (this->stroka[j] == val)
					this->stroka[j] = var;
		}
	}
}

double TCalc::Double(string number)
{
	double doublenumber{};
	double sign = 1.0;
	size_t n = number.size();
	size_t pospoint = 0;
	size_t pose = 0;

	for (size_t i = 0; i < n; i++)
	{
		if (number[i] == '.')
			pospoint = i;
		if (number[i] == 'E')
			pose = i;
	}

	if (pospoint != 0)
	{
		double beforepoint{};
		double afterpoint{};
		string beforepoint_s, afterpoint_s;
		for (size_t i = 0; i < pospoint; i++)
		{
			beforepoint_s += number[i];
		}
		for (size_t i = pospoint + 1; i < n; i++)
		{
			afterpoint_s += number[i];
		}
		beforepoint = Double(beforepoint_s);
		afterpoint = Double(afterpoint_s);
		afterpoint /= pow(10, afterpoint_s.size());
		doublenumber = beforepoint + afterpoint;
	}

	if (pose != 0)
	{
		double beforee{};
		double aftere{};
		string beforee_s, aftere_s;
		for (size_t i = 0; i < pose; i++) { beforee_s += number[i]; }
		for (size_t i = pose + 1; i < n; i++) { aftere_s += number[i]; }
		beforee = Double(beforee_s);
		aftere = Double(aftere_s);
		if (aftere > 0)
			doublenumber = beforee * pow(10.0, aftere);
		else {
			doublenumber = beforee;
			for (size_t i = 0; i < (-1.0 * aftere); i++)
			{
				doublenumber /= 10;
			}
		}
	}
	else if (pospoint == 0 && pose == 0)
	{
		if (number[0] == '~' || number[0] == '-')
		{
			for (size_t i = 1; i < n; i++)
			{
				doublenumber = doublenumber * 10.0 + static_cast<double>(number[i] - '0');
			}
			doublenumber *= -1.0;
		}
		else
		{
			for (size_t i = 0; i < number.size(); i++)
			{
				doublenumber = doublenumber * 10.0 + static_cast<double>(number[i] - '0');
			}
		}
	}
	return doublenumber;
}

bool TCalc::Operand(const char& symbol)
{
	if ((symbol >= '0' && symbol <= '9') || symbol == '.' || (symbol >= 'a' && symbol <= 'z') || symbol == 'E')
		return true;
	return false;
}

void TCalc::Calc()
{
	valueofvar();
	string errorr = " ";
	double tmp;
	double exp = pow(10, -20);
	for (size_t i = 0; i < ln; i++)
	{
		if (stroka[i] == "+")
		{
			tmp = numbers.Pop();
			tmp = tmp + numbers.Pop();
			numbers.Push(tmp);
		}
		else if (stroka[i] == "-")
		{
			tmp = numbers.Pop();
			tmp = numbers.Pop() - tmp;
			numbers.Push(tmp);
		}
		else if (stroka[i] == "*")
		{
			tmp = numbers.Pop();
			tmp = tmp * numbers.Pop();
			numbers.Push(tmp);
		}
		else if (stroka[i] == "/")
		{
			if (abs(numbers.Pop()) < exp)
			{
				errorr += "Невозможно деление на 0" + stroka[i];
				throw invalid_argument(errorr.c_str());
			}
			tmp = numbers.Pop();
			tmp = numbers.Pop() / tmp;
			numbers.Push(tmp);
		}
		else if (stroka[i] == "~")
		{
			tmp = numbers.Pop();
			numbers.Push(-tmp);
		}
		else numbers.Push(Double(stroka[i]));
	}
	result = numbers.Pop();
}



int TCalc::priority(string operation)
{
	if (operation == "+" || operation == "-")
		return 1;
	else if (operation == "*" || operation == "/")
		return 2;
	else if (operation == "~")
		return 3;
	else
		return 0;
}


