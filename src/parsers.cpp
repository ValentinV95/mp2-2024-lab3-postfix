#include "parsers.h"
#include "expr_err.h"
#include "simple_math.h"
#define IsLetter(c)		(( 'a' <= c && c <= 'z' ) || ( 'A' <= c && c <= 'Z' ) || c == '_')
#define IsDigit(c)		('0' <= c && c <= '9')
#define IsMathOp(c)		((c=='*') || (c=='+') || (c=='-') || (c=='/') || (c=='^'))
#define IsMath(c)		((c=='*') || (c=='+') || (c=='-') || (c=='/') || (c=='^') || (c=='(') || (c==')'))

double ToDouble(char c)
{
	return static_cast<double>(c - '0');
}

unsigned int ToInt(char c)
{
	return static_cast<unsigned int>(c - '0');
}

double POW(unsigned long long pw)
{
	double a = 10.0;
	double tmp = a, res=1.0;
	unsigned long long int _tmp = 1;
	for (int i = 0; i < 64 && _tmp <= pw; i++)
	{
		if (_tmp & pw)
			res *= tmp;
		tmp *= tmp;
		_tmp <<= 1;
	}
	return res;
}

string PreParse(string const& s)
{
	string s_res("");
	size_t i = 0, sz = s.size();
	int bracket_counter = 0;
	bool sp_prev = false;
	while (s[i] == ' ' && i<sz)
		i++;
	for (; i < sz; i++)
	{
		if (s[i] == ' ')
			sp_prev = true;
		else
		{
			if (s[i] == '(')
				bracket_counter++;
			else if (s[i] == ')')
				bracket_counter--;
			if (sp_prev)
			{
				s_res += ' ';
				sp_prev = false;
			}
			s_res += s[i];
		}
		if (bracket_counter < 0)
			throw expression_error("No oppening bracket for ) at " + to_string(i + 1) + " symbol");
	}
	if (bracket_counter > 0)
		throw expression_error(to_string(bracket_counter) + " closing brackets are missing");
	return s_res;
}

double NumParse(string const& s)
{
	string normal{ "" };
	double res = 0.0, sign = 1.0;
	int pow = 0, foo = 0, pow_s = 1;
	size_t i = 0, sz = s.size();
	if (s[0] == '-')
	{
		sign = -1.0;
		i++;
	}
	if (s[i] == '.')
		throw expression_error("Real number can't begin without explicit integer part");
	while (i < sz && s[i] == '0')
		i++;
	while (i < sz && IsDigit(s[i]))
	{
		if (normal.size() < 17)
			normal += s[i];
		else
			foo += 1;
		i++;
	}
	if (i < sz && s[i] == '.')
	{
		i++;
		if (i == sz || !IsDigit(s[i]))
			throw expression_error("Fractional part must follow '.' in real numbers");
	}
	if (normal == "")
		while (i < sz && s[i] == '0')
		{
			i++;
			foo -= 1;
		}
	while (i < sz && IsDigit(s[i]))
	{
		if (normal.size() < 17)
		{
			normal += s[i];
			foo -= 1;
		}
		i++;
	}
	for (int j = 0, tmp = normal.size(); j < tmp; j++)
	{
		res *= 10;
		res += ToDouble(normal[j]);
	}
	res /= POW(normal.size() - 1);
	foo += normal.size() - 1;
	if (i < sz && (s[i] == 'e' || s[i] == 'E'))
	{
		i++;
		if (i < sz && (s[i] == '+' || s[i] == '-'))
		{
			if (s[i] == '+')
				pow_s = 1;
			else { pow_s = -1; };
			i++;
			if(i==sz)
				throw expression_error("Number has no digits in exponential part");
			while (i < sz && s[i] == '0')
				i++;
			while (i < sz && IsDigit(s[i]))
			{
				pow *= 10;
				pow += ToInt(s[i]);
				i++;
				if (i != sz && pow > 65536)
					throw expression_error("Too large power");
			}
			if (pow == 0)
				pow_s = 1;
		}
		else { throw expression_error("If number has exponential part it must have explicit sign of power"); };
	}
	if (i < sz)
		throw expression_error("Unexpected symbol encountered in number");
	pow = pow_s * pow + foo;
	if (pow * pow_s < 0)
		pow_s *= -1;
	pow = pow * pow_s;
	if (pow_s == 1)
		res *= POW(pow);
	else
		res /= POW(pow);
	res *= sign;
	return res;
}

Vec<lexem*> MainParse(string const& s)
{
	double (*binary[5]) (operand const* , operand const*) = { ADD, SUB, MUL, DIV, POW };
	double (*unary[19]) (operand const*) = { NEG, ABS, LOG, SIN, ASIN, SINH, ASINH, COS, ACOS, COSH, ACOSH, TAN, ATAN, TANH, ATANH, COT, ACOT, COTH, ACOTH };
	Vec<lexem*> VL;
	MyStack<operand*> SOp;
	MyStack<operation*> SStmt;
	operand* lhs = nullptr, * rhs = nullptr;
	operation* stm = nullptr;
	string tmp{ "" };
	double res=0.0;
	bool unary_minus_candidate = false, unary_minus = false, prev_is_operand = false, prev_is_func = false;
	size_t sz = s.size(), i = 0, ret = 0;
	int id, prior;
	while (i < sz)
	{
		if (IsLetter(s[i]))
		{
			tmp = "";
			ret = i;
			while (i < sz && IsLetter(s[i]))
			{
				tmp += s[i];
				i++;
			}
			while (i < sz && IsDigit(s[i]))
			{
				tmp += s[i];
				i++;
			}
			if (i < sz && IsLetter(s[i]))
				throw expression_error("Invalid variable form at " + to_string(ret) + " position");
			id = operation::StmtId(tmp);
			if (id != -1)
			{
				if (prev_is_operand)
					throw expression_error("No operation between operand and function at " + to_string(ret - 1) + " position");
				if (prev_is_func)
					throw expression_error("Previous function must have an arguement at " + to_string(ret - 1) + " position");
				prev_is_func = true;
				SStmt.Push(new operation(id));
			}
			else 
			{
				if (prev_is_operand)
					throw expression_error("No operation between operands at " + to_string(ret - 1) + " position");
				if (prev_is_func)
					throw expression_error("Function arguement must be placed in brackets at " + to_string(ret - 1) + " position");
				prev_is_operand = true;
				SOp.Push(new variable(tmp));
			}
		}
		else if (IsDigit(s[i]))
		{
			tmp = "";
			ret = i;
			if (prev_is_operand)
				throw expression_error("No operation between operands at " + to_string(ret) + " position");
			if (prev_is_func)
				throw expression_error("No operation between operand and function at " + to_string(ret - 1) + " position");
			if (unary_minus)
			{
				tmp += '-';
				unary_minus = false;
			}
			while (i < sz && (IsDigit(s[i]) || s[i] == '.' || s[i] == 'e' || s[i] == 'E'))
			{
				tmp += s[i];
				if (s[i] == 'e' || s[i] == 'E')
				{
					i++;
					if (i < sz && (s[i] == '+' || s[i] == '-'))
					{
						tmp += s[i];
						i++;
					}
				}
				i++;
			}
			prev_is_func = false;
			prev_is_operand = true;
			try
			{
				res = NumParse(tmp);
			}
			catch (expression_error e) { 
				throw expression_error(string(e.what()) + " at " + to_string(ret - 1) + " position"); }
			SOp.Push(new constant(res));
		}
		else if (IsMath(s[i]))
		{
			ret = i;
			if (s[i] == '(')
			{
				if (prev_is_operand)
					throw expression_error("No operation between operand and '(' at " + to_string(ret - 1) + " position");
				prev_is_operand = false;
				prev_is_func = false;
				SStmt.Push(new operation(0));
				i++;
			}
			else if (s[i] == ')')
			{
				if (!prev_is_operand)
					if (SStmt.Top()->GetId() == 0)
						throw expression_error("Brackets may not be epty at " + to_string(ret - 1) + " position");
					else { throw expression_error("Operand required at " + to_string(ret - 1) + " position"); }
				if (prev_is_func)
					throw expression_error("Arguement required for function at " + to_string(ret - 1) + " position");
				stm = SStmt.Top();
				SStmt.Pop();
				while (stm->GetId() != 0)
				{
					if (stm->GetArity() == 1)
					{
						rhs = SOp.Top();
						if (rhs->IsConst())
						{
							SOp.Pop();
							id = stm->GetId();
							res = unary[id - 7](rhs);
							SOp.Push(new constant(res));
						}
						else
						{
							if (dynamic_cast<variable*>(rhs)->GetId() != -1)
							{
								SOp.Pop();
								VL.push_back(rhs);
								SOp.Push(new variable());
							}
							VL.push_back(stm);
						}
					}
					else
					{

					}
					stm = SStmt.Top();
					SStmt.Pop();
				}
				prev_is_operand = true;
				i++;
			}
			else if (IsMathOp(s[i]))
			{
				if (prev_is_func)
					throw expression_error("Arguement required for function at " + to_string(ret - 1) + " position");
				if (prev_is_operand)
				{

				}
			}
		}
		else if (s[i] == ' ')
			i++;
		else { throw expression_error("Unexpected symbol encountered at " + to_string(i) + " position"); }
	}
	while (!SStmt.Is_Empty())
	{
		stm = SStmt.Top();
		SStmt.Pop();
		rhs = SOp.Top();
		SOp.Pop();
		if (stm->GetArity() == 2)
		{
			lhs = SOp.Top();
			SOp.Pop();
			VL.push_back(lhs);
		}
		VL.push_back(rhs);
		VL.push_back(stm);
	}
	if (VL.Is_Empty() && !SOp.Is_Empty())
	{
		rhs = SOp.Top();
		SOp.Pop();
		VL.push_back(rhs);
	}
	return VL;
}