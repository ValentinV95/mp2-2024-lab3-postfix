#include "parsers.h"
#include "expr_err.h"
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
	Vec<lexem*> VL, RES;
	Vec<operation*> StmBuff;
	MyStack<operand*> SOp;
	MyStack<operation*> SStmt;
	MyStack<lexem*> LBuff;
	lexem* ltmp = nullptr/*, ** _VL = VL.GetData(), ** _RES = RES.GetData(), ** _LBuff = LBuff.GetData()->GetData()*/;
	operand* lhs = nullptr, * rhs = nullptr/*, ** _SOp = SOp.GetData()->GetData()*/;
	operation* stm = nullptr, * _stm = nullptr/*, ** _StmBuff = StmBuff.GetData(), ** _SStmt = SStmt.GetData()->GetData()*/;
	string tmp{ "" };
	double res=0.0;
	bool unary_minus = false, prev_is_operand = false, prev_is_func = false;
	size_t sz = s.size(), i = 0, j = 0, k = 0, ret = 0, foo = 0;
	short int id, prior, arity;
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
				VL.push_back(new operation(id));
			}
			else 
			{
				if (prev_is_operand)
					throw expression_error("No operation between operands at " + to_string(ret - 1) + " position");
				if (prev_is_func)
					throw expression_error("Function arguement must be placed in brackets at " + to_string(ret - 1) + " position");
				prev_is_operand = true;
				VL.push_back(new variable(tmp));
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
				else i++;
			}
			prev_is_func = false;
			prev_is_operand = true;
			try
			{
				res = NumParse(tmp);
			}
			catch (expression_error e) { 
				throw expression_error(string(e.what()) + " at " + to_string(ret - 1) + " position"); }
			VL.push_back(new constant(res));
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
				VL.push_back(new operation(0));
				i++;
			}
			else if (s[i] == ')')
			{
				if (prev_is_func)
					throw expression_error("Arguement required for function at " + to_string(ret - 1) + " position");
				if (!prev_is_operand)
					if (VL.Top()->IsStmt() && dynamic_cast<operation*>(VL.Top())->GetId() == 0)
						throw expression_error("Brackets may not be epty at " + to_string(ret - 1) + " position");
					else { throw expression_error("Operand required at " + to_string(ret - 1) + " position"); }
				VL.push_back(new operation(1));
				prev_is_operand = true;
				i++;
			}
			else if (IsMathOp(s[i]))
			{
				if (prev_is_func)
					throw expression_error("Arguement required for function at " + to_string(ret - 1) + " position");
				if (prev_is_operand)
				{
					id = operation::StmtId(s[i]);
					VL.push_back(new operation(id));
					prev_is_operand = false;
					i++;
				}
				else
				{
					if (s[i] == '-')
					{
						unary_minus = true;
						i++;
						while (s[i] == '-' || s[i] == ' ')
						{
							if (s[i] == '-')
								unary_minus = !unary_minus;
							i++;
						}
						if (IsMathOp(s[i]))
							throw expression_error("Unexpected math operation at" + to_string(ret - 1) + " position");
						if ((IsLetter(s[i]) || s[i] == '(') && unary_minus)
						{
							VL.push_back(new operation(7));
							unary_minus = false;
						}
					}
					else
						throw expression_error("Unexpected math operation at" + to_string(ret - 1) + " position");
				}
			}
		}
		else if (s[i] == ' ')
			i++;
		else { throw expression_error("Unexpected symbol encountered at " + to_string(i) + " position"); }
	}
	if (prev_is_func)
		throw expression_error("Arguement required for function at the end of expression");
	if (!prev_is_operand)
		throw expression_error("Operand required at the end of expression");
	sz = VL.GetSize();
	i = 0;
	for (; i < sz; i++)
	{
		if (!VL[i]->IsStmt())
		{
			rhs = dynamic_cast<operand*>(VL[i]);
			SOp.Push(dynamic_cast<operand*>(rhs));
		}
		else
		{
			stm = dynamic_cast<operation*>(VL[i]);
			if (stm->GetId() == 0)
				SStmt.Push(stm);
			else if (stm->GetId() == 1)
			{
				k = 0;
				_stm = SStmt.Top();
				SStmt.Pop();
				while (_stm->GetId() != 0)
				{
					rhs = SOp.Top();
					if (_stm->GetArity() == 1)
					{
						if (!rhs->IsConst() && dynamic_cast<variable*>(rhs)->GetId() == -1)		// Arg is implicit
						{
							if (_stm->GetId() == 7 && !StmBuff.Is_Empty() && StmBuff.Top()->GetId() == 6)	// This needed for correct parsing of unary minus and '^'
								StmBuff.push_back(_stm);
							else
								RES.push_back(_stm);
						}
						else																	// Arg is explicit
						{
							SOp.Pop();
							RES.push_back(rhs);
							SOp.Push(new variable());
							RES.push_back(_stm);
						}
					}
					else			// If arity == 2
					{
						SOp.Pop();
						lhs = SOp.Top();
						if (!lhs->IsConst() && dynamic_cast<variable*>(lhs)->GetId() == -1)			// lhs is implicit
						{
							if (!rhs->IsConst() && dynamic_cast<variable*>(rhs)->GetId() == -1)		// rhs is implicit
							{
								StmBuff.push_back(_stm);
								k++;
							}
							else																	// rhs is explicit
							{
								RES.push_back(rhs);
								RES.push_back(_stm);
							}
						}
						else																		// lhs is explicit
						{
							SOp.Pop();
							if (!rhs->IsConst() && dynamic_cast<variable*>(rhs)->GetId() == -1)		// rhs is implicit
							{
								for (j = 1 + k; j; j--)
								{
									ltmp = RES.Top();
									LBuff.Push(ltmp);
									if (ltmp->IsStmt())
										j += dynamic_cast<operation*>(ltmp)->GetArity();
									RES.pop_back();
								}
								k = 0;
								RES.push_back(lhs);
								StmBuff.push_back(_stm);
							}
							else																	// rhs is explicit
							{
								RES.push_back(lhs);
								RES.push_back(rhs);
								RES.push_back(_stm);
							}
							SOp.Push(new variable());
						}
					}
					_stm = SStmt.Top();
					SStmt.Pop();
				}
				while (!LBuff.Is_Empty())
				{
					RES.push_back(LBuff.Top());
					LBuff.Pop();
				}
				for (j = 0, k = StmBuff.GetSize(); j < k; j++)
					RES.push_back(StmBuff[j]);
				StmBuff.clear();
			}
			else		// Is MathOp
			{
				if (SStmt.Is_Empty())
					SStmt.Push(stm);
				else
				{
					prior = stm->GetPriority();
					_stm = SStmt.Top();
					if (prior > _stm->GetPriority())
						SStmt.Push(stm);
					else
					{
						k = 0;
						while (!SStmt.Is_Empty() && _stm->GetPriority() >= prior)
						{
							SStmt.Pop();
							rhs = SOp.Top();
							if (_stm->GetArity() == 1)
							{
								if (!rhs->IsConst() && dynamic_cast<variable*>(rhs)->GetId() == -1)		// Arg is implicit
								{
									if (_stm->GetId() == 7 && !StmBuff.Is_Empty() && StmBuff.Top()->GetId() == 6)	// This needed for correct parsing of unary minus and '^'
										StmBuff.push_back(_stm);
									else
										RES.push_back(_stm);
								}
								else																	// Arg is explicit
								{
									SOp.Pop();
									RES.push_back(rhs);
									SOp.Push(new variable());
									RES.push_back(_stm);
								}
							}
							else			// If arity == 2
							{
								SOp.Pop();
								lhs = SOp.Top();
								if (!lhs->IsConst() && dynamic_cast<variable*>(lhs)->GetId() == -1)			// lhs is implicit
								{
									if (!rhs->IsConst() && dynamic_cast<variable*>(rhs)->GetId() == -1)		// rhs is implicit
									{
										StmBuff.push_back(_stm);
										k++;
									}
									else																	// rhs is explicit
									{
										RES.push_back(rhs);
										RES.push_back(_stm);
									}
								}
								else																		// lhs is explicit
								{
									SOp.Pop();
									if (!rhs->IsConst() && dynamic_cast<variable*>(rhs)->GetId() == -1)		// rhs is implicit
									{
										for (j = 1 + k; j; j--)
										{
											ltmp = RES.Top();
											LBuff.Push(ltmp);
											if (ltmp->IsStmt())
												j += dynamic_cast<operation*>(ltmp)->GetArity();
											RES.pop_back();
										}
										k = 0;
										RES.push_back(lhs);
										StmBuff.push_back(_stm);
									}
									else																	// rhs is explicit
									{
										RES.push_back(lhs);
										RES.push_back(rhs);
										RES.push_back(_stm);
									}
									SOp.Push(new variable());
								}
							}
							if(!SStmt.Is_Empty())
							{
								_stm = SStmt.Top();
							}
						}
						while (!LBuff.Is_Empty())
						{
							RES.push_back(LBuff.Top());
							LBuff.Pop();
						}
						for (j = 0, k = StmBuff.GetSize(); j < k; j++)
							RES.push_back(StmBuff[j]);
						SStmt.Push(stm);
						StmBuff.clear();
					}
				}
			}
		}
	}
	k = 0;
	while (!SStmt.Is_Empty())
	{
		_stm = SStmt.Top();
		rhs = SOp.Top();
		SStmt.Pop();
		if (_stm->GetArity() == 1)
		{
			if (!rhs->IsConst() && dynamic_cast<variable*>(rhs)->GetId() == -1)		// Arg is implicit
			{
				if (_stm->GetId() == 7 && !StmBuff.Is_Empty() && StmBuff.Top()->GetId() == 6)	// This needed for correct parsing of unary minus and '^'
					StmBuff.push_back(_stm);
				else
					RES.push_back(_stm);
			}
			else																	// Arg is explicit
			{
				SOp.Pop();
				RES.push_back(rhs);
				SOp.Push(new variable());
				RES.push_back(_stm);
			}
		}
		else			// If arity == 2
		{
			SOp.Pop();
			lhs = SOp.Top();
			if (!lhs->IsConst() && dynamic_cast<variable*>(lhs)->GetId() == -1)			// lhs is implicit
			{
				if (!rhs->IsConst() && dynamic_cast<variable*>(rhs)->GetId() == -1)		// rhs is implicit
				{
					StmBuff.push_back(_stm);
					k++;
				}
				else																	// rhs is explicit
				{
					RES.push_back(rhs);
					RES.push_back(_stm);
				}
			}
			else																		// lhs is explicit
			{
				SOp.Pop();
				if (!rhs->IsConst() && dynamic_cast<variable*>(rhs)->GetId() == -1)		// rhs is implicit
				{
					for (j = 1 + k; j; j--)
					{
						ltmp = RES.Top();
						LBuff.Push(ltmp);
						if (ltmp->IsStmt())
							j += dynamic_cast<operation*>(ltmp)->GetArity();
						RES.pop_back();
					}
					k = 0;
					RES.push_back(lhs);
					StmBuff.push_back(_stm);
				}
				else																	// rhs is explicit
				{
					RES.push_back(lhs);
					RES.push_back(rhs);
					RES.push_back(_stm);
				}
				SOp.Push(new variable());
			}

		}
	}
	while (!LBuff.Is_Empty())
	{
		RES.push_back(LBuff.Top());
		LBuff.Pop();
	}
	for (j = 0, k = StmBuff.GetSize(); j < k; j++)
		RES.push_back(StmBuff[j]);
	StmBuff.clear();
	rhs = SOp.Top();
	if (!rhs->IsConst() && dynamic_cast<variable*>(rhs)->GetId() == -1)
	{

	}
	else
		RES.push_back(rhs);
	SOp.Pop();
	return RES;
}