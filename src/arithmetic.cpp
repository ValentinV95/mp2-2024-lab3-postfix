#include "arithmetic.h"

TPostfix::~TPostfix()
{
	delete[] var;
	delete[] setOfLexems;
	var = nullptr;
	setOfLexems = nullptr;
	operands = "";
	infix = "";
	postfix = "";
	lexemSize = 0;
}

TPostfix::TPostfix(string& str): infix(str)
{
		size_t size = infix.size();
		check();
		setOfLexems = new string[size]();
		toLexems();
		var = new string[varSize];
		int lineSize = 0;
		for (size_t i = 0; i < operands.length(); i++)
			if (operands[i] != ' ')
				var[lineSize].push_back(operands[i]);
			else
			{
				lineSize++;
			}
		toPostfix();
}

void TPostfix::setInfix(string& str)
{
	postfix = "";
	infix = "";
	operands = "";
	infix = str;
	size_t size = infix.size();
	check();
	string* SetOfLexems_new = new string[size]();
	delete[] setOfLexems;
	setOfLexems = SetOfLexems_new;
	toLexems();
	string* var_new = new string[varSize];
	delete[] var;
	var = var_new;
	int lineSize = 0;
	for (size_t i = 0; i < operands.length(); i++)
		if (operands[i] != ' ')
			var[lineSize].push_back(operands[i]);
		else
		{
			lineSize++;
		}
	toPostfix();
}

string TPostfix::getInfix() const
{
	return infix;
}

string TPostfix::getPostfix() const
{
	return postfix;
}

string TPostfix::getOperands() const
{
	return operands;
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

bool TPostfix::isOperation(const char& x) 
{
	return (x == '+' || x == '-' || x == '*' || x == '/');
}

bool TPostfix::isOperand(const char& symbol)
{
	return ((symbol < char(91) && symbol > char(64)) || (symbol > char(96) && symbol < char(123)) || symbol == ' ');
}

bool TPostfix::isDigitOrPoint(const char& symbol)
{
	return ((symbol <= '9' && symbol >= '0') || symbol == '.');
}

void TPostfix::toLexems()
{
	string line;
	int lineSize = 0;
	size_t infixLength = infix.size();
	lexemSize = 0;
	for (size_t i = 0; i < infixLength; i++)
	{
		line.clear();
		while (!isOperation(infix[i]) && i < infixLength)
		{
			if (infix[i] == '(' || infix[i] == ')')
				setOfLexems[lexemSize++] = infix[i++];
			if (isOperand(infix[i]))
			{
				while (!isOperation(infix[i]) && i < infixLength && infix[i] != '(' && infix[i] != ')')
				{
					setOfLexems[lexemSize].push_back(infix[i]);
					line.push_back(infix[i++]);
				}
				if (operands.find(line) == -1)
				{
					line.push_back(' ');
					operands += line;
					lineSize++;
					line.clear();
				}
				lexemSize++;
			}
			if (isDigitOrPoint(infix[i]))
			{
				while ((!(isOperation(infix[i]) || infix[i] == '(' || infix[i] == ')') || infix[i - 1] == 'e') && i < infixLength)
					setOfLexems[lexemSize].push_back(infix[i++]);
				lexemSize++;
			}
		}
		if (isOperation(infix[i]))
			if ((infix[i] == '-') && (i == 0 || infix[i - 1] == '(' || isOperation(infix[i - 1]))) 
				setOfLexems[lexemSize++] = '~';
			else 
				setOfLexems[lexemSize++] = infix[i];
	}
	varSize = lineSize;
}

void TPostfix::check()
{
	int openbracket = 0;
	int closebracket = 0;
	int breckets = 0;
	size_t infixLength = infix.size();
	string error = "Incorrect element: ";
	string cursor = "<<";
	if (!(infix.empty()))
	{
		if ((!isOperand(infix[0])) && (!isDigitOrPoint(infix[0])) && (infix[0] != '-') && (infix[0] != '('))
		{
			error += infix[0];
			error += cursor;
			throw invalid_argument(error.c_str());
		}
		if (infix[0] == '(')
			breckets++;
		for (int i = 0; i < infix.size() - 1; i++) 
		{
			if ((i < infixLength - 1) && (isDigitOrPoint(infix[i])))
			{
				int elem = i - 1;
				string line;
				int e = 0;
				int point = 0;
				size_t lineLength = line.size();
				size_t counte = line.find('e');
				size_t countpoint = line.find('.');
				while ((infix[i] != '*') && (infix[i] != '/') && (infix[i] != ')') && (infix[i] != '(') && (i < infixLength))
				{
					line.push_back(infix[i]);
					if (infix[i] == 'e') e++;
					if (infix[i] == '.') point++;
					error += infix[i++];
				}
				if (e > 1 || point > 1 || counte < countpoint)
				{
					error += cursor + "Extra symbol";
					throw invalid_argument(error.c_str());
				}
				if (line[lineLength - 1] == 'e')
				{
					error += cursor + "Extra symbol";
					throw invalid_argument(error.c_str());
				}
				for (int j = 0; j < lineLength; j++)
					if (!(isDigitOrPoint(line[j]) || line[j] == '+' || line[j] == '-' || line[j] == 'e'))
					{
						error += cursor + "Extra symbol in a digit";
						throw invalid_argument(error.c_str());
					}
				if (elem > 0 && (infix[elem] == '/' && line == "0"))
				{
					error += cursor + "Division by zero is impossible";
					throw invalid_argument(error.c_str());
				}
				if (infix[i] == '(')
				{
					error += infix[i];
					error += cursor;
					throw invalid_argument(error.c_str());
				}
			}
			if (i < infixLength - 1 && isOperand(infix[i]))
			{
				string line;
				size_t lineLength = line.size();
				while (!(isOperation(infix[i]) || infix[i] == ')' || infix[i] == '(' || infix[i] == ' ') && i < infixLength) 
				{
					if (infix[i] == ' ')
					{
						error += cursor + "Don't use spaces";
						throw invalid_argument(error.c_str());
					}
					line.push_back(infix[i]);
					error += infix[i++];
				}
				for (int j = 0; j < lineLength; j++)
					if (!(isDigitOrPoint(line[j]) || isOperand(line[j])))
					{
						error += cursor + "Incorrect name of var";
						throw invalid_argument(error.c_str());
					}
				if (infix[i] == '(')
				{
					error += infix[i];
					error += cursor;
					throw invalid_argument(error.c_str());
				}
			}
			if (i < infixLength - 1 && infix[i] == ')') 
			{
				error += infix[i];
				breckets--;
				if (breckets < 0)
				{
					error += cursor + "Ectra brecket";
					throw invalid_argument(error.c_str());
				}
				if ((!isOperation(infix[i + 1])) && infix[i + 1] != ')')
				{
					error += infix[i + 1];
					error += cursor + "Something is missing";
					throw invalid_argument(error.c_str());
				}
			}
			if (i < infixLength - 1 && isOperation(infix[i])) 
			{
				error += infix[i];
				if ((!isOperand(infix[i + 1])) && (!isDigitOrPoint(infix[i + 1])) && infix[i + 1] != '(') 
				{
					error += infix[i + 1];
					error += cursor + "Here should be digit, var or '('";
					throw invalid_argument(error.c_str());
				}
			}
			if (i < infixLength - 1 && infix[i] == '(') 
			{
				error += infix[i];
				breckets++;
				if (infix[i + 1] != '-' && infix[i + 1] != '(' && (!isDigitOrPoint(infix[i + 1])) && (!isOperand(infix[i + 1]))) 
				{
					error += infix[i + 1];
					error += cursor + "Here should be digit, var, unary minus or '('";
					throw invalid_argument(error.c_str());
				}
			}
		}
		error += infix[infixLength - 1];
		if (!(isDigitOrPoint(infix[infixLength - 1]) || isOperand(infix[infixLength - 1]) || infix[infixLength - 1] == ')')) 
		{
			error += cursor + "Here should be digit, var or ')'";
			throw invalid_argument(error.c_str());
		}
		if (infix.length() > 1 && infix[infixLength - 1] == '0' && infix[infixLength - 2] == '/')
		{
			error += cursor + "Division by zero is impossible";
			throw invalid_argument(error.c_str());
		}
		for (int i = 0; i < infixLength; i++) 
		{
			if (infix[i] == '(') openbracket++;
			if (infix[i] == ')') closebracket++;
		}
		if (openbracket != closebracket) 
		{
			error += cursor + "Here are not enough brackets";
			throw invalid_argument(error.c_str());
		}
	}
}

void TPostfix::toPostfix()
{
	Stack<string> stack; 
	for (int i = 0; i < lexemSize; i++)
	{
		if (setOfLexems[i][0] == '(')
		{
			stack.push(setOfLexems[i]);
		}
		else if (setOfLexems[i][0] == ')')
		{
			while (stack.top()[0] != '(')
				postfix += stack.pop() + " ";
			stack.pop(); 
		}
		else if (setOfLexems[i][0] == '+' || setOfLexems[i][0] == '-')
		{
			while (!stack.isEmpty() && priority(stack.top()) > 0)
				postfix += stack.pop() + " ";
			stack.push(setOfLexems[i]); 
		}
		else if (setOfLexems[i][0] == '*' || setOfLexems[i][0] == '/')
		{
			while (!stack.isEmpty() && priority(stack.top()) > 1)
				postfix += stack.pop() + " ";
			stack.push(setOfLexems[i]); 
		}
		else if (setOfLexems[i][0] == '~')
		{
			stack.push(setOfLexems[i]);
		}
		else
		{
			postfix += setOfLexems[i] + " ";
		}
	}
	while (!stack.isEmpty())
		postfix += stack.pop() + " ";
}

double TPostfix::toDouble(string number)
{
	double res = 0.0;
	double sign = 1.0;
	size_t n = number.size();
	int pospoint = 0;
	int pose = 0;

	for (int i = 0; i < n; i++)
	{
		if (number[i] == '.')
			pospoint = i;
		if (number[i] == 'e')
			pose = i;
	}

	if (pospoint != 0)
	{
		double beforepoint = 0, afterpoint = 0;
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
		res = beforepoint + afterpoint;
	}

	if (pose != 0)
	{
		double beforee = 0.0, aftere = 0.0;
		string beforee_s, aftere_s;
		for (size_t i = 0; i < pose; i++) { beforee_s += number[i]; }
		for (size_t i = pose + 1; i < n; i++) { aftere_s += number[i]; }
		beforee = toDouble(beforee_s);
		aftere = toDouble(aftere_s);
		if (aftere > 0)
			res = beforee * pow(10.0, aftere);
		else {
			res = beforee;
			for (size_t i = 0; i < (-1.0 * aftere); i++)
			{
				res /= 10;
			}
		}
	}
	else if (pospoint == 0 && pose == 0)
	{
		if (number[0] == '~' || number[0] == '-') 
		{
			for (int i = 1; i < n; i++) 
			{
				res = res * 10.0 + static_cast<double>(number[i] - '0');
			}
			res *= -1.0;
		}
		else 
		{
			for (size_t i = 0; i < number.size(); i++) 
			{
				res = res * 10.0 + static_cast<double>(number[i] - '0');
			}
		}
	}
	return res;
}

void TPostfix::valueofvars()
{
	double* varValue = new double[varSize];
	cout << "Write value for vars:" << endl;
	for (int i = 0; i < varSize; i++)
	{
		string str;
		cout << var[i] << " = ";
		cin >> str;
		varValue[i] = toDouble(str);
	}
}

double TPostfix::calculate()
{
	valueofvars();
	Stack<double> stack;
	double eps = pow(10, -20);
	for (size_t i = 0; i < postfix.size(); i++)
	{
		string line;
		while (postfix[i] != ' ')
			line.push_back(postfix[i++]);

		if (isOperand(line[0]))
		{
			int ind = -1;
			int j = 0;
			while (ind < 0)
				if (var[j] == line)
					ind = j++;
				else j++;
			stack.push(varValue[ind]);
		}

		if (isOperation(line[0]))
		{
			double var1, var2;
			var2 = stack.pop();
			var1 = stack.pop();
			if (line[0]=='+')
				stack.push(var1 + var2);
			if (line[0] == '-')
				stack.push(var1 - var2);
			if (line[0] == '*')
				stack.push(var1 * var2);
			if (line[0] == '/')
				if (abs(var2) < eps)
					throw runtime_error("The division by zero is impossible");
				else
					stack.push(var1 / var2);
		}

		if (line[0] == '~')
		{
			double var;
			var = stack.pop();
			stack.push(var * (-1));
		}

		if (isDigitOrPoint(line[0]))
		{
			double var = toDouble(line);
			stack.push(var);
		}
	}
	delete[] varValue;
	return stack.pop();
}


#include <iostream>
#include "Header1.h"

int main()
{
    cout << "Hello, before you will use this calculator, you should read some rules: \n";
    cout << "You can use 4 operations: addition +, subsrtaction -, multiplication *, division / \n";
    cout << "Don't use spaces in your line \n";
    cout << "You can denote vars by letters, digits and points \n";
    cout << "You should put a point instead of a comma in floating point numbers \n";
    cout << "You should avoid extra or misssing elements, be careful \n ";
    cout << endl;
    string line;
    cout << "Enter the arifmetic expression: \n";
    cin >> line;
    string error;
    while (true)
    {
        try
        {
            for (int i = 0; i < line.size(); i++)
            {
                error += line[i];
                if (line[i] == ' ')
                {
                    error += "Don't forget, you can't use spaces in yor line";
                    throw invalid_argument(error.c_str());
                }
            }
            int choice;
            cout << "Do you want to calculate? \n";
            cout << "1. Yes \n";
            cout << "2. No \n";
            cin >> choice;
            if (choice == 1)
            {
                TPostfix mathexp(line);
                double res = mathexp.calculate();
                cout << "The result: " << res << "\n";
                cout << "Do you want to calculate? \n";
                cout << "1. Yes \n";
                cout << "2. No \n";
            }
            if (choice == 2)
            {
                        break;
            }
        }
        catch (exception& e) 
        {
            cout << e.what() << endl << endl;
        }
    }
    return 0;
}

