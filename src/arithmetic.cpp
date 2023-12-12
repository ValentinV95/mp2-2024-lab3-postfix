// реализация функций и классов для вычисления арифметических выражений
#include "arithmetic.h"

Arithmetic::~Arithmetic()
{
	delete[] SetOfLexems;
	delete[] variables;
	variables = nullptr;
	SetOfLexems = nullptr;
	operands = ""; 
	postfix = ""; 
	infix = ""; 
	lexemSize = 0; 
	lexemSize = 0;
}

Arithmetic::Arithmetic(string& str): infix(str)
{
	int size = infix.length();
	infixCheck();
	SetOfLexems = new string[size]();
	Parser();
	variables = new string[variableSize];
	int nameSize = 0;
	for (size_t i = 0; i < operands.length(); i++)
		if (operands[i] != ' ')
			variables[nameSize].push_back(operands[i]);
		else
		{
			nameSize++;
		}
	makePostfix();
}

void Arithmetic::setInfix(string& str)
{
	postfix = "";
	infix = "";
	operands = "";
	infix = str;
	int size = infix.length();
	infixCheck();

	string* SetOfLexems_new = new string[size]();
	delete[] SetOfLexems;
	SetOfLexems = SetOfLexems_new;

	Parser();

	string* variables_new = new string[variableSize];
	delete[] variables;
	variables = variables_new;

	int nameSize = 0;
	for (size_t i = 0; i < operands.length(); i++)
		if (operands[i] != ' ')
			variables[nameSize].push_back(operands[i]);
		else
		{
			nameSize++;
		}
	makePostfix();
}

string Arithmetic::getInfix() const
{
	return infix;
}

string Arithmetic::getPostfix() const
{
	return postfix;
}

string Arithmetic::getOperands() const
{
	return operands;
}

int Arithmetic::priority(const char& operation)
{
	if (operation == '(' || operation == ')') return 0;
	if (operation == '+' || operation == '-') return 1;
	if (operation == '*' || operation == '/') return 2;
	if (operation == '~') return 3;
	else return -1;
}

bool Arithmetic::isOperation(const char& x)
{
	if (x == '+' || x == '-' || x == '*' || x == '/')
		return true;
	return false;
}

void Arithmetic::Parser()
{
	string name;
	int nameSize=0;
	lexemSize = 0;
	for (size_t i = 0; i < infix.length(); i++)
	{
		name.clear();//to find lexems
		while (!isOperation(infix[i]) && i < infix.length())
		{
			if (infix[i] == '(' || infix[i] == ')')
				SetOfLexems[lexemSize++] = infix[i++];
			if (isOperand(infix[i])) //if it`s variable
			{
				while (!isOperation(infix[i])&& i < infix.length()&& infix[i]!='(' && infix[i] != ')')//if variables have long names
				{
					SetOfLexems[lexemSize].push_back(infix[i]);
					name.push_back(infix[i++]);
				}
				if (operands.find(name)==-1)//if this variable is new
				{
					name.push_back(' ');
					operands += name;
					nameSize++;
					name.clear();
				}
				lexemSize++;
			}
			if (isDigit(infix[i])) //if it`s a number
			{
				while ((!(isOperation(infix[i]) || infix[i] == '(' || infix[i] == ')') || infix[i - 1] == 'e') && i < infix.length())
					SetOfLexems[lexemSize].push_back(infix[i++]);
				lexemSize++;
			}
		}
		if (isOperation(infix[i]))
			if ((infix[i] == '-') && (i == 0 || infix[i - 1] == '(' || isOperation(infix[i - 1]))) SetOfLexems[lexemSize++] = '~';//to find unary operation
			else SetOfLexems[lexemSize++] = infix[i];
	}
	variableSize = nameSize;
	
}

void Arithmetic::makePostfix()
{
	TDynamicStack<string> st;


	for (int i = 0; i < lexemSize; i++)
	{
		switch (SetOfLexems[i][0]) {
		case '(':
		{
			st.push(SetOfLexems[i]);
			break;
		}
		case ')':
		{
			while (st.top()[0] != '(')
				postfix += st.pop() + " ";
			st.pop();
			break;
		}
		case '+':case '-':
		{
			while ((!st.isEmpty()) && (priority(st.top()[0]) > 0))
				postfix += st.pop() + " ";
			st.push(SetOfLexems[i]);
			break;
		}
		case '*': case'/':
		{
			while ((!st.isEmpty()) && (priority(st.top()[0]) > 1))
				postfix += st.pop() + " ";
			st.push(SetOfLexems[i]);
			break;
		}
		case '~':
		{
			st.push(SetOfLexems[i]);
			break;
		}
		default:
		{
			postfix += SetOfLexems[i] + " ";
		}
		}
	}
	while(!(st.isEmpty()))
		postfix += st.pop()+ " ";

}

bool Arithmetic::isOperand(const char& first_symbol)
{
	if ((first_symbol < char(91) && first_symbol>char(64)) || (first_symbol > char(96) && first_symbol < char(123)) || first_symbol == '_')
		return true;
	return false;
}

bool Arithmetic::isDigit(const char& first_symbol)
{
	if ((first_symbol <= '9' && first_symbol>= '0') || first_symbol == '.')
		return true;
	return false;
}

void Arithmetic::infixCheck()
{
	string error ("Unexpected element: ");
	string arrow = " <- ";
	int open = 0, close = 0;
	int breckets = 0;

	if ((!isOperand(infix[0])) && (!isDigit(infix[0])) && infix[0] != '(' && infix[0] != '-')
	{
		error += infix[0];
		error += arrow;
		throw invalid_argument(error.c_str());
	}
	if (infix[0] == '(')
		breckets++;
	for (size_t i = 0; i < infix.length() - 1; i++) {

		if (i < infix.length() - 1 && isDigit(infix[i])) {
			int op = i-1;
			string name;
			while (((!isOperation(infix[i])) && infix[i] != ')' && infix[i] != '(') && (i < infix.length()))
			{
				name.push_back(infix[i]);
				error += infix[i++];
			}
			
			for (size_t j = 0; j < name.length(); j++)
				if (!(isDigit(name[j]) || name[j] == 'e'|| name[j] == '+' || name[j] == '-'))
				{
					error += arrow + "The mistake in a digit";
					throw invalid_argument(error.c_str());
				}
			if (infix[op]== '/' && name == "0")
			{
				error += arrow + "Division by zero isn`t correct";
				throw invalid_argument(error.c_str());
			}
			if (infix[i] == '(')
			{
				error += infix[i];
				error += arrow;
				throw invalid_argument(error.c_str());

			}

		}

		if (i < infix.length() - 1 && isOperand(infix[i])) {
			string name;
			while (!(isOperation(infix[i]) || infix[i] == ')' || infix[i] == '(' || infix[i]==' ') && i < infix.length()) {

				if (infix[i]==' ')
				{
					error += arrow + "You shold not use spaces";
					throw invalid_argument(error.c_str());
				}
				name.push_back(infix[i]);
				error += infix[i++];
			}
			for (size_t j = 0; j < name.length(); j++)
				if (!(isDigit(name[j]) || isOperand(name[j])))
				{
					error += arrow + "The mistake in the name of variable";
					throw invalid_argument(error.c_str());
				}
			if (infix[i] == '(')
			{
				error += infix[i];
				error += arrow;
				throw invalid_argument(error.c_str());
			}
		}

		if (i < infix.length() - 1 && infix[i] == ')') {
			error += infix[i];
			breckets--;
			if (breckets < 0)
			{
				error += arrow + "Wrong brecket";
				throw invalid_argument(error.c_str());
			}
			if ((!isOperation(infix[i+1])) && infix[i+1] != ')')
			{
				error += infix[i+1];
				error += arrow + "Here should be an operation";
				throw invalid_argument(error.c_str());
			}
		}

		if (i < infix.length() - 1 && isOperation(infix[i])) {
				error += infix[i];
				if ((!isOperand(infix[i+1])) && (!isDigit(infix[i+1])) && infix[i+1] != '(') {
					error += infix[i + 1];
					error +=  arrow + "Here should be digit, variable or '('";
					throw invalid_argument(error.c_str());
				}
		}

		if (i < infix.length() - 1 && infix[i] == '(') {
			error += infix[i];
			breckets++;
			if (infix[i+1] != '-' && infix[i+1] != '(' && (!isDigit(infix[i+1])) && (!isOperand(infix[i+1]))) {
				error += infix[i+1];
				error += arrow + "Here should be digit, variable,unary minus or '('";
				throw invalid_argument(error.c_str());
			}
		}


	}

	error += infix[infix.length() - 1];
	if (!(isDigit(infix[infix.length() - 1]) || isOperand(infix[infix.length() - 1]) || infix[infix.length() - 1] == ')')) {
		error += arrow + "Here should be digit, veriable or ')'";
		throw invalid_argument(error.c_str());
	}
	if (infix[infix.length() - 1] == '0' && infix[infix.length() - 2] == '/')
	{
		error += arrow + "Division by zero isn`t correct";
		throw invalid_argument(error.c_str());
	}


	for (size_t i = 0; i < infix.length(); i++) {
		if (infix[i] == '(') open++;
		if (infix[i] == ')') close++;
	}


	if (open != close) {
		error += arrow + "Here should be more closed breckets";
		throw invalid_argument(error.c_str());
	}


}

double Arithmetic::calculate()
{
	double* variableMeanings = new double[variableSize];
	cout << "Give the meaning of variables to calculate:" << endl;
	for (int i = 0; i < variableSize; i++)
	{
		string str;
		cout << variables[i] << " = ";
		cin >> str;
		variableMeanings[i]=makeDouble(str);
	}

	TDynamicStack<double> st;
	double eps = pow(10, -20);

	for (size_t i = 0; i < postfix.size(); i++)
	{
		string name;
		while (postfix[i] != ' ')
			name.push_back(postfix[i++]);

		if (isOperand(name[0]))//is variable
		{
			int ind = -1;
			int j = 0;
			while (ind < 0)
				if (variables[j] == name)
					ind = j++;
				else j++;
			st.push(variableMeanings[ind]);
		}
		
		if (isOperation(name[0]))
		{
			double val1, val2;
			val2 = st.pop();
			val1 = st.pop();
			switch (name[0])
			{
			case '+':
				st.push(val1 + val2);
				break;
			case '-':
				st.push(val1 - val2);
				break;
			case '*':
				st.push(val1 * val2);
				break;
			case '/':
				if (abs(val2) < eps)
					throw runtime_error ("There is division by zero, it isn't possible");
				else
					st.push(val1 / val2);
				break;
			}
		}

		if (name[0] == '~')
		{
			double val;
			val = st.pop();
			st.push(val * (-1));
		}

		if (isDigit(name[0]))//is a number
		{
			double val = makeDouble(name);
			st.push(val);
		}
	}
	delete[] variableMeanings;
	return st.pop();

}

double Arithmetic::makeDouble(string str)
{
	double res = 0.0, sign = 1.0;


	if (str.find('.') != -1 && str.find('e') == -1) {//there is dot

		double beforepoint = 0, afterpoint = 0;
		string beforepoint_s, afterpoint_s;
		size_t p = str.find('.');//position of the dot

		for (size_t i = 0; i < p; i++) { beforepoint_s += str[i]; }
		for (size_t i = p + 1; i < str.size(); i++) { afterpoint_s += str[i]; }

		beforepoint = makeDouble(beforepoint_s);
		afterpoint = makeDouble(afterpoint_s);

		afterpoint /= pow(10,afterpoint_s.size());

		res = beforepoint + afterpoint;

	}

	else if (str.find('e') !=-1) {//there is e

		double beforeE = 0.0, afterE = 0.0;
		string beforeE_s, afterE_s;

		size_t p = str.find('e');

		for (size_t i = 0; i < p; i++) { beforeE_s += str[i]; }
		for (size_t i = p + 1; i < str.size(); i++) { afterE_s += str[i]; }

		beforeE = makeDouble(beforeE_s);
		afterE = makeDouble(afterE_s);

		if (afterE > 0) res = beforeE * pow(10.0, afterE);
		else {
			res = beforeE;
			for (size_t i = 0; i < (-1.0 * afterE); i++) { res /= 10; }
		}
	}

	else { //no dot, no e

		if (str[0] == '~' || str[0] == '-') {

			for (size_t i = 1; i < str.size(); i++) {
				res = res * 10.0 + static_cast<double>(str[i] - '0');
			}
			res *= -1.0;
		}

		else {

			for (size_t i = 0; i < str.size(); i++) {
				res = res * 10.0 + static_cast<double>(str[i] - '0');
			}
		}
	}

	return res;
}