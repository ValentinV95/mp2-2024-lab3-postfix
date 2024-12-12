// реализация функций и классов для вычисления арифметических выражений

#include "arithmetic.h"
#include "inputException.h"
#include <stdexcept>
#include <string>
#include <iostream>


lexem::lexem(int initPos) : initPos(initPos) { }

size_t lexem::getInitPos() const noexcept
{
	return initPos;
}

operand::operand(const double& var, int initPos) : lexem(initPos), value(var) { }

int operand::what() const noexcept
{
	return 0;
}

double operand::getValue() const noexcept
{
	return value;
}

varible::varible(const std::string& name, int initPos) : operand(0.0, initPos), nameVar(name), setValue(0) { }

int varible::what() const noexcept
{
	if (setValue)
	{
		return 0;
	}
	return -1;
}

void varible::initValue(const double& val)
{
	value = val;
	setValue = 1;
	return;
}

std::string varible::getName() const noexcept
{
	return nameVar;
}

operation::operation(const char& op, int initPos) : lexem(initPos), op(op)
{
	if (op == 'c' || op == 's' || op == 'l' || op == 'd' || op == 'q') priority = -1;
	if (op == '~') priority = 0;
	if (op == '*' || op == '/') priority = 1;
	if (op == '-' || op == '+') priority = 2;
	if (op == '(' || op == ')') priority = 3;
}

int operation::what() const noexcept
{
	return 1;
}

char operation::getOperation() const noexcept
{
	return op;
}

int operation::getPriority() const noexcept
{
	return priority;
}

//c - cos
//s - sin
//l - ln
//d - log2
//q - sqrt
double calcArithmetic(const Vector<lexem*>& lx)
{
	Stack<double> val;
	for (int i = 0; i < lx.length(); i++)
	{
		if (lx[i]->what() == 0)
		{
			val.push((dynamic_cast<operand*>(lx[i]))->getValue());
		}
		if (lx[i]->what() == 1)
		{
			operation* op = dynamic_cast<operation*>(lx[i]);
			if (op->getOperation() == '+' && val.length() >= 2)
			{
				double v1 = val.top();
				val.pop();
				double v2 = val.top();
				val.pop();
				val.push(v1 + v2);
			}
			else if (op->getOperation() == '-' && val.length() >= 2)
			{
				double v1 = val.top();
				val.pop();
				double v2 = val.top();
				val.pop();
				val.push(v2 - v1);
			}
			else if (op->getOperation() == '*' && val.length() >= 2)
			{
				double v1 = val.top();
				val.pop();
				double v2 = val.top();
				val.pop();
				val.push(v1 * v2);
			}
			else if (op->getOperation() == '/' && val.length() >= 2)
			{
				double v1 = val.top();
				val.pop();
				double v2 = val.top();
				val.pop();
				val.push(v2 / v1);
			}
			else if (op->getOperation() == 's' && val.length() >= 1)
			{
				double v1 = val.top();
				val.pop();
				val.push(sin(v1));
			}
			else if (op->getOperation() == 'c' && val.length() >= 1)
			{
				double v1 = val.top();
				val.pop();
				val.push(cos(v1));
			}
			else if (op->getOperation() == 'l' && val.length() >= 1)
			{
				double v1 = val.top();
				val.pop();
				val.push(log(v1));
			}
			else if (op->getOperation() == 'd' && val.length() >= 1)
			{
				double v1 = val.top();
				val.pop();
				val.push(log2(v1));
			}
			else if (op->getOperation() == 'q' && val.length() >= 1)
			{
				double v1 = val.top();
				val.pop();
				val.push(sqrt(v1));
			}
			else if (op->getOperation() == '~' && val.length() >= 1)
			{
				double v1 = val.top();
				val.pop();
				val.push(-v1);
			}
			else
			{
				throw inputException("the operand for this operation is lost", 1, lx[i]->getInitPos());
			}
		}
	}
	if (val.length() != 1) throw inputException("The operation was lost", 2, -1);
	return val.top();
}

Vector<lexem*> toPostfix(const Vector<lexem*>& lx)
{
	Stack<operation*> op;
	Vector<lexem*> postfix;
	for (int i = 0; i < lx.length(); i++)
	{
		if (lx[i]->what() == 0)
		{
			if (i - 1 >= 0 && lx[i - 1]->what() == 1 && (dynamic_cast<operation*>(lx[i - 1]))->getOperation() == ')')
			{
				deleteLx(postfix);
				throw inputException("the operation before this operand was skipped", 2, lx[i]->getInitPos());
			}
			postfix.push_back(new operand((dynamic_cast<operand*>(lx[i]))->getValue(), lx[i]->getInitPos()));
		}
		else if (lx[i]->what() == 1 && (dynamic_cast<operation*>(lx[i]))->getOperation() == '(')
		{
			if (lx.length() > i + 1 && lx[i + 1]->what() == 1 && ((dynamic_cast<operation*>(lx[i + 1]))->getPriority() == 1 || (dynamic_cast<operation*>(lx[i + 1]))->getPriority() == 2))
			{
				deleteLx(postfix);
				throw inputException("the operation before this operand was skipped", 2, lx[i + 1]->getInitPos());
			}
			if (i - 1 >= 0 && (lx[i - 1]->what() != 1 || (dynamic_cast<operation*>(lx[i - 1]))->getOperation() == ')'))
			{
				deleteLx(postfix);
				throw inputException("the operation before this operand was skipped", 2, lx[i]->getInitPos());
			}
			if (lx.length() > i + 1 && lx[i + 1]->what() == 1 && (dynamic_cast<operation*>(lx[i + 1]))->getOperation() == ')')
			{
				deleteLx(postfix);
				throw inputException("the expression in parentheses is lost", 7, lx[i]->getInitPos());
			}
			op.push(dynamic_cast<operation*>(lx[i]));
		}
		else if (lx[i]->what() == 1 && (dynamic_cast<operation*>(lx[i]))->getOperation() == ')')
		{
			if (i - 1 >= 0 && lx[i - 1]->what() == 1 && ((dynamic_cast<operation*>(lx[i - 1]))->getPriority() == 1 || (dynamic_cast<operation*>(lx[i - 1]))->getPriority() == 2 || (dynamic_cast<operation*>(lx[i - 1]))->getPriority() == 0))
			{
				deleteLx(postfix);
				throw inputException("the operation before this operand was skipped", 2, lx[i - 1]->getInitPos());
			}
			if (lx.length() < i + 1 && (lx[i + 1]->what() != 1 || ((dynamic_cast<operation*>(lx[i + 1]))->getPriority() != 1 && (dynamic_cast<operation*>(lx[i + 1]))->getPriority() != 2)))
			{
				deleteLx(postfix);
				throw inputException("the operation before this operand was skipped", 2, lx[i]->getInitPos());
			}
			if (op.empty())
			{
				deleteLx(postfix);
				throw inputException("there is no opening bracket for this closing bracket", 3, lx[i]->getInitPos());
			}
			while (op.top()->getOperation() != '(')
			{
				postfix.push_back(new operation(op.top()->getOperation(), op.top()->getInitPos()));
				op.pop();
				if (op.empty())
				{
					deleteLx(postfix);
					throw inputException("there is no opening bracket for this closing bracket", 3, lx[i]->getInitPos());
				}
			}
			op.pop();
		}
		else if (lx[i]->what() == 1)
		{
			operation* newOp = dynamic_cast<operation*>(lx[i]);
			if (newOp->getPriority() == -1 && (lx.length() <= i + 1 || lx[i + 1]->what() != 1 || (dynamic_cast<operation*>(lx[i + 1]))->getOperation() != '('))
			{
				deleteLx(postfix);
				throw inputException("the opening parenthesis for this function was skipped", 10, lx[i]->getInitPos());
			}
			if (newOp->getOperation() == '~' && i - 1 >= 0 && lx[i - 1]->what() == 1 && (dynamic_cast<operation*>(lx[i - 1]))->getOperation() == '-')
			{
				deleteLx(postfix);
				throw inputException("the opening parenthesis before the unary minus was skipped", 9, lx[i]->getInitPos());
			}
			if (newOp->getPriority() == -1 && i - 1 >= 0 && (lx[i - 1]->what() == 0 || (lx[i - 1]->what() == 1 && (dynamic_cast<operation*>(lx[i - 1]))->getOperation() == ')')))
			{
				deleteLx(postfix);
				throw inputException("the operation before this function was skipped", 8, lx[i]->getInitPos());
			}
			if ((newOp->getPriority() == 1 || newOp->getPriority() == 2) && lx.length() > i + 1 && (lx[i + 1]->what() == 1 && 
				(dynamic_cast<operation*>(lx[i + 1]))->getPriority() >= 1 && (dynamic_cast<operation*>(lx[i + 1]))->getOperation() != '('))
			{
				deleteLx(postfix);
				throw inputException("the operand for this operation is lost", 1, lx[i]->getInitPos());
			}
			while (!op.empty() && op.top()->getPriority() <= newOp->getPriority())
			{
				postfix.push_back(new operation(op.top()->getOperation(), op.top()->getInitPos()));
				op.pop();
			}
			op.push(newOp);
		}
	}
	while (!op.empty())
	{
		if (op.top()->getOperation() == '(')
		{
			deleteLx(postfix);
			throw inputException("there is no closing bracket for this opening bracket", 5, op.top()->getInitPos());
		}
		postfix.push_back(new operation(op.top()->getOperation(), op.top()->getInitPos()));
		op.pop();
	}
	return postfix;
}

double ToOperand(const std::string& str)
{
	int i = 0, sign2 = 0;
	double res = 0.0, c = 10, c2 = 0.0;
	bool flag1 = true, flag2 = true;
	for (; i < str.size(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			if (flag1)
			{
				res = res * c + str[i] - '0';
			}
			else if (!flag1 && flag2)
			{
				res = res + (str[i] - '0') * c;
				c = c * 0.1;
			}
			else if (!flag2)
			{
				c2 = c2 * c + str[i] - '0';
			}
		}
		else if (str[i] == '.' && flag1 && !(i == 0 && i + 1 < str.size() && (str[i + 1] == 'e' || str[i + 1] == 'E')) && !(i == 0 && str.size() == 1))
		{
			flag1 = false;
			c = 0.1;
		}
		else if ((str[i] == 'e' || str[i] == 'E') && i > 0 && (str[i - 1] >= '0' && str[i - 1] <= '9' || str[i - 1] == '.') && i != str.size() - 1)
		{
			flag1 = false;
			flag2 = false;
			c = 10;
		}
		else if (str[i] == '-' && sign2 == 0 && i > 0 && (str[i - 1] == 'e' || str[i - 1] == 'E') && i + 1 < str.size() && str[i + 1] >= '0' && str[i + 1] <= '9')
		{
			sign2 = -1;
		}
		else if (str[i] == '+' && sign2 == 0 && i > 0 && (str[i - 1] == 'e' || str[i - 1] == 'E') && i + 1 < str.size() && str[i + 1] >= '0' && str[i + 1] <= '9')
		{
			sign2 = 1;
		}
		else
		{
			throw inputException("a constant was entered incorrectly", 4, i);
		}
	}
	if (sign2 == 0) sign2 = 1;
	if (!flag2) res = res * pow(10, sign2 * c2);
	return res;
}

Vector<lexem*> parsingLexem(const std::string& expression)
{
	Vector<lexem*> lx;
	for (int i = 0; i < expression.size(); i++)
	{
		if (expression[i] == '(') lx.push_back(new operation('(', i));
		else if (expression[i] == ')') lx.push_back(new operation(')', i));
		else if (expression[i] == '*') lx.push_back(new operation('*', i));
		else if (expression[i] == '+') lx.push_back(new operation('+', i));
		else if (expression[i] == '/') lx.push_back(new operation('/', i));
		else if (expression[i] == '-')
		{
			if (lx.length() > 0 && (lx[lx.length() - 1]->what() != 1 || (lx[lx.length() - 1]->what() == 1 && (dynamic_cast<operation*>(lx[lx.length() - 1]))->getOperation() == ')'))) lx.push_back(new operation('-', i));
			else lx.push_back(new operation('~', i));
		}
		else if (expression[i] == 'c' && expression.substr(i, 3) == "cos") { lx.push_back(new operation('c', i)); i += 2; }
		else if (expression[i] == 's' && expression.substr(i, 3) == "sin") { lx.push_back(new operation('s', i)); i += 2; }
		else if (expression[i] == 'l' && expression.substr(i, 2) == "ln") { lx.push_back(new operation('l', i)); i += 1; }
		else if (expression[i] == 'l' && expression.substr(i, 4) == "log2") { lx.push_back(new operation('d', i)); i += 3; }
		else if (expression[i] == 's' && expression.substr(i, 4) == "sqrt") { lx.push_back(new operation('q', i)); i += 3; }
		else if (expression[i] == 'x')
		{
			i++;
			std::string varName = "x";
			while (expression[i] >= '0' && expression[i] <= '9')
			{
				varName = varName + std::to_string(expression[i] - '0');
				i++;
			}
			lx.push_back(new varible(varName, i - varName.size()));
			i--;
		}
		else if (expression[i] == '.' || (expression[i] >= '0' && expression[i] <= '9'))
		{
			bool f1 = true, f2 = false;
			size_t lenLex = 0;
			while (expression[i] == '.' || expression[i] == 'e' || expression[i] == 'E' || (expression[i] >= '0' && expression[i] <= '9') || ((expression[i] == '+' || expression[i] == '-') && f1 && f2))
			{
				lenLex++;
				if (expression[i] == '+' || expression[i] == '-') f1 = false;
				if (expression[i] == 'e' || expression[i] == 'E') f2 = true;
				i++;
			}
			i -= lenLex;
			std::string val = expression.substr(i, lenLex);
			try
			{
				lx.push_back(new operand(ToOperand(val), i));
			}
			catch (inputException ex)
			{
				deleteLx(lx);
				throw inputException("a constant was entered incorrectly", 4, ex.getPosLexemException() + i);
			}
			i += lenLex - 1;
		}
		else if (expression[i] != ' ')
		{
			deleteLx(lx);
			throw inputException("invalid character", 6, i);
		}
	}
	return lx;
}

Vector<std::string> getVarNames(Vector<lexem*>& lx)
{
	Vector<std::string> varNames;
	for (int i = 0; i < lx.length(); i++)
	{
		if (lx[i]->what() == -1)
		{
			std::string varName = (dynamic_cast<varible*>(lx[i]))->getName();
			bool fl = true;
			for (int j = 0; j < varNames.length(); j++)
			{
				if (varName == varNames[j])
				{
					fl = false;
					break;
				}
			}
			if (fl)
			{
				varNames.push_back(varName);
			}
		}
	}
	return varNames;
}

void inputVar(Vector<lexem*>& lx)
{
	Vector<std::string> varNames = getVarNames(lx);
	for (int i = 0; i < varNames.length(); i++)
	{
		double val;
		std::cout << varNames[i] << " = ";
		std::cin >> val;
		for (int j = 0; j < lx.length(); j++)
		{
			if (lx[j]->what() == -1 && (dynamic_cast<varible*>(lx[j]))->getName() == varNames[i])
			{
				(dynamic_cast<varible*>(lx[j]))->initValue(val);
			}
		}
	}
	return;
}

void deleteLx(Vector<lexem*>& lx) noexcept
{
	for (int i = 0; i < lx.length(); i++)
	{
		delete lx[i];
	}
	return;
}