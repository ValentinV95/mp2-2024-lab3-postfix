#include "arithmetic.h"
#include "parsers.h"
#include "simple_math.h"

ArithmeticExpression::ArithmeticExpression() : postfix(), infix{ "" } {}

ArithmeticExpression::ArithmeticExpression(string const& s)
{
	infix = PreParse(s);
	ToPostfix();
}

ArithmeticExpression::ArithmeticExpression(ArithmeticExpression const& AE) : postfix(AE.postfix), infix(AE.infix) {}

ArithmeticExpression::ArithmeticExpression(ArithmeticExpression&& AE) : postfix(), infix{""}
{
	swap(postfix, AE.postfix);
	swap(infix, AE.infix);
}

ArithmeticExpression& ArithmeticExpression::operator = (ArithmeticExpression const& AE)
{
	infix = AE.infix;
	postfix = AE.postfix;
	return *this;
}

ArithmeticExpression& ArithmeticExpression::operator = (ArithmeticExpression&& AE)
{
	swap(postfix, AE.postfix);
	swap(infix, AE.infix);
	return *this;
}



void ArithmeticExpression::ToPostfix()
{
	postfix = MainParse(infix);
	return;
}

void ArithmeticExpression::Rebuild(string const& s)
{
	infix = PreParse(s);
	postfix = MainParse(infix);
}

string ArithmeticExpression::GetInfix() const
{
	string s(infix);
	if (infix.empty())
		s = "No expression yet";
	return s;
}

string ArithmeticExpression::PrintPostfix() const
{
	size_t sz = postfix.GetSize()-1;
	size_t i = 0;
	string s;
	stringstream sstr;
	if(postfix[0])
	{
		for (; i < sz; i++)
			sstr << *postfix[i] << " ";
		sstr << *postfix[i];
	}
	getline(sstr, s);
	return s;
}

double ArithmeticExpression::Calculate() const
{
	if (!postfix.Is_Empty())
	{
		double (*unary[19]) (operand const*) = { NEG, ABS, LOG, SIN, ASIN, SINH, ASINH, COS, ACOS, COSH, ACOSH, TAN, ATAN, TANH, ATANH, COT, ACOT, COTH, ACOTH };
		double (*binary[6]) (operand const*, operand const*) = { ADD, SUB, MUL, DIV, POW };
		double res = 0.0, tmp;
		MyStack<operand*> SOp;
		operation* stm = nullptr;
		operand* rhs = nullptr, * lhs = nullptr;
		size_t i = 0, sz = postfix.GetSize();
		for (; i < sz; i++)
		{
			if (postfix[i]->IsStmt())
			{
				stm = dynamic_cast<operation*>(postfix[i]);
				rhs = SOp.Top();
				SOp.Pop();
				if (stm->GetArity() == 1)
				{
					tmp = unary[stm->GetId() - 7](rhs);
					SOp.Push(new constant(tmp));
				}
				else
				{
					lhs = SOp.Top();
					SOp.Pop();
					tmp = binary[stm->GetId() - 2](lhs, rhs);
					SOp.Push(new constant(tmp));
				}
			}
			else
				SOp.Push(dynamic_cast<operand*>(postfix[i]));
		}
		res = SOp.Top()->GetVal();
		SOp.Pop();

		return res;
	}
	else
		throw logic_error("Nothing to calculate");
}