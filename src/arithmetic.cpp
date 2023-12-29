#include "arithmetic.h"

TPostfix::~TPostfix()
{
	delete[] line;
}

TPostfix::TPostfix(string str)
{
	length = str.length();
	infix = str;
	postfix = "";
	res = 0.0;
	line = new string[length]();
	toLexems();
}

void TPostfix::toLexems()
{
	int brackets = 0;
	size_t lexemnumber = 0;
	string error = "Incorrect expression: ";
	string cursor = " -> ";
	for (size_t i = 0; i < length; i++)
	{
		if (infix[i] == '+' || infix[i] == '*' || infix[i] == '/')
		{
			if (i == 0)
			{
				error += "Operation " + cursor + infix[i] + " can't be the first element";
				throw invalid_argument(error.c_str());
			}
			else if (i + 1 == length)
			{
				error += "Operation " + cursor + infix[i] + " can't be the last element";
				throw invalid_argument(error.c_str());
			}
			else if (!isOperand(infix[i - 1]) && infix[i - 1] != ')')
			{
				error += "Operation " + cursor + infix[i] + " must be preceded by a digit, operand, or closing bracket";
				throw invalid_argument(error.c_str());
			}
			line[lexemnumber] = infix[i];
			lexemnumber++;
			continue;
		}
		else if (infix[i] == '-')
		{
			if (i + 1 == length)
			{
				error += "Operation " + cursor + infix[i] + " can't be the last element";
				throw invalid_argument(error.c_str());
			}
			if (i == 0 || (!isOperand(infix[i - 1]) && infix[i - 1] != ')'))
			{
				line[lexemnumber] = '~';
				lexemnumber++;
			}
			else if (infix[i - 1] == 'E')
			{
				line[lexemnumber] += '~';
			}
			else
			{
				line[lexemnumber] = infix[i];
				lexemnumber++;
			}
			continue;
		}
		else if (infix[i] == '(')
		{
			if (i + 1 == length)
			{
				error += "Opening bracket " + cursor + infix[i] + " can't be the last element";
				throw invalid_argument(error.c_str());
			}
			if (i != 0 && (infix[i - 1] >= '0' && infix[i - 1] <= '9' || infix[i - 1] == ')'))
			{
				error += "Opening bracket " + cursor + infix[i] + " must have operation before";
				throw invalid_argument(error.c_str());
			}
			line[lexemnumber] = infix[i];
			lexemnumber++;
			brackets++;
			continue;
		}
		else if (infix[i] == ')')
		{
			if (i == 0)
			{
				error += "Closing bracket " + cursor + infix[i] + " can't be the first element";
				throw invalid_argument(error.c_str());
			}
			if (!isOperand(infix[i-1]) && infix[i - 1] != ')')
			{
				error += "Closing bracket " + cursor + infix[i] + " must have digit, operand or closing bracket before";
				throw invalid_argument(error.c_str());
			}
			line[lexemnumber] = infix[i];
			lexemnumber++;
			brackets--;
			if (brackets < 0)
			{
				error += "Missing or extra bracket " + cursor + infix[i];
				throw invalid_argument(error.c_str());
			}
			continue;
		}
		else if (i != 0 && infix[i - 1] == ')')
		{
			error += "Closing bracket " + cursor + infix[i] + " must have operation before";
			throw invalid_argument(error.c_str());
		}
		else if (infix[i] >= '0' && infix[i] <= '9')
		{
			if (i != 0 && infix[i - 1] >= 'a' && infix[i - 1] <= 'z')
			{
				error += "Missing operation before " + cursor + infix[i];
				throw invalid_argument(error.c_str());
				throw invalid_argument(error.c_str());
			}
			else if (i + 1 == length || (!isOperand(infix[i + 1]) && infix[i + 1] != '.'))
			{
				line[lexemnumber] += infix[i];
				lexemnumber++;
			}
			else line[lexemnumber] += infix[i];
			continue;
		}
		else if (infix[i] >= 'a' && infix[i] <= 'z')
		{
			if (i != 0 && infix[i - 1] >= '0')
			{
				error += "Missing operation before " + cursor + infix[i] ;
				throw invalid_argument(error.c_str());
			}
			if (i + 1 != length && infix[i + 1] == '.')
			{
				error += "After varriable " + cursor + infix[i]+" can't be point";
				throw invalid_argument(error.c_str());
			}
			line[lexemnumber] = infix[i];
			lexemnumber++;
			continue;
		}
		else if (infix[i] == 'E')
		{
			if (i + 1 == length || i == 0 || !isOperand(infix[i - 1]) && infix[i - 1] != '.' || !isOperand(infix[i + 1]) && infix[i + 1] != '-')
			{
				error += "Incorrect record of the number " + cursor + infix[i];
				throw invalid_argument(error.c_str());
			}
			else
				line[lexemnumber] += infix[i];
			continue;
		}
		else if (infix[i] == '.')
		{
			if (i == 0 || (i + 1) == length || !isOperand(infix[i - 1]) || !isOperand(infix[i + 1]) && infix[i + 1] != 'E')
			{
				error += "In this calculator the point can be only in record of the number " + cursor + infix[i];
				throw invalid_argument(error.c_str());
			}
			else
				line[lexemnumber] += infix[i];
			continue;
		}
		else
		{
			error += "Unidentified element " + cursor + infix[i];
			throw invalid_argument(error.c_str());
		}
	}
	if (brackets != 0)
	{
		error += "Amount of closing and openning brackets doesn't match " ;
		throw invalid_argument(error.c_str());
	}
	length = lexemnumber;
}
 
void TPostfix::toPostfix()
{
	Stack<string> stack;
	for (int i = 0; i < length; i++)
	{
		if (line[i] == "(")
		{
			stack.push(line[i]);
		}
		else if (line[i] == ")")
		{
			while (stack.top() != "(")
				postfix += stack.pop() + " ";
			stack.pop();
		}
		else if (line[i] == "+" || line[i] == "-")
		{
			while (!stack.isEmpty() && priority(stack.top()) > 0)
				postfix += stack.pop() + " ";
			stack.push(line[i]);
		}
		else if (line[i] == "*" || line[i] == "/")
		{
			while (!stack.isEmpty() && priority(stack.top()) > 1)
				postfix += stack.pop() + " ";
			stack.push(line[i]);
		}
		else if (line[i] == "~")
		{
			stack.push(line[i]);
		}
		else
		{
			postfix += line[i] + " ";
		}
	}
	while (!stack.isEmpty())
		postfix += stack.pop() + " ";
}

void TPostfix::valueofvar() 
{
	string var, value;
	for (size_t i = 0; i < length; i++)
	{
		if (line[i] >= "a" && line[i] <= "z")
		{
			value = line[i];
			cout << "\n" << "Enter a value for " << value << " : ";
			cin >> var;
			for (size_t j = i; j < length; j++)
				if (this->line[j] == value)
					this->line[j] = var;
		}
	}
}

double TPostfix::toDouble(string number)
{
	double doublenumber = 0.0;
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
		double beforepoint = 0.0;
		double afterpoint = 0.0;
		string beforepoint_s, afterpoint_s;
		for (size_t i = 0; i < pospoint; i++)
		{
			beforepoint_s += number[i];
		}
		for (size_t i = pospoint + 1; i < n; i++)
		{
			afterpoint_s += number[i];
		}
		beforepoint = toDouble(beforepoint_s);
		afterpoint = toDouble(afterpoint_s);
		afterpoint /= pow(10, afterpoint_s.size());
		doublenumber = beforepoint + afterpoint;
	}

	if (pose != 0)
	{
		double beforee = 0.0;
		double aftere = 0.0;
		string beforee_s, aftere_s;
		for (size_t i = 0; i < pose; i++) { beforee_s += number[i]; }
		for (size_t i = pose + 1; i < n; i++) { aftere_s += number[i]; }
		beforee = toDouble(beforee_s);
		aftere = toDouble(aftere_s);
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
			for (int i = 1; i < n; i++)
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

void TPostfix::calculate()
{
	valueofvar();
	string errorr = " ";
	string curs = " -> ";
	double tmp;
	double exp = pow(10, -20);
	for (size_t i = 0; i < length; i++)
	{
		if (line[i] == "+")
		{
			tmp = numbers.pop();
			tmp = tmp + numbers.pop();
			numbers.push(tmp);
		}
		else if (line[i] == "-")
		{
			tmp = numbers.pop();
			tmp = numbers.pop() - tmp;
			numbers.push(tmp);
		}
		else if (line[i] == "*")
		{
			tmp = numbers.pop();
			tmp = tmp * numbers.pop();
			numbers.push(tmp);
		}
		else if (line[i] == "/")
		{
			if (abs(numbers.pop()) < exp)
			{
				errorr += "Division by zero is impossible"+curs+line[i];
				throw invalid_argument(errorr.c_str());
			}
			tmp = numbers.pop();
			tmp = numbers.pop() / tmp;
			numbers.push(tmp);
		}
		else if (line[i] == "~")
		{
			tmp = numbers.pop();
			numbers.push(-tmp);
		}
		else numbers.push(toDouble(line[i]));
	}
	res = numbers.pop();
}

double TPostfix::getResult() const
{
	return res;
}

string TPostfix::getInfix() const
{
	return infix;
}

string TPostfix::getPostfix() const
{
	return postfix;
}

int TPostfix::priority(string operation)
{
	if (operation == "(" || operation == ")")
		return 0;
	else if (operation == "+" || operation == "-")
		return 1;
	else if (operation == "*" || operation == "/")
		return 2;
	else if (operation == "~")
		return 3;
	else
		return -1;
}

bool TPostfix::isOperand(const char& symbol)
{
	if ((symbol >= '0' && symbol <= '9') || symbol == '.' || (symbol >= 'a' && symbol <= 'z') || symbol == 'E')
		return true;
	return false;
}
