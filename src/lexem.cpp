#pragma once
#include "lexem.h"
#include "cmath"

char const* operation::lst[] = {"(", ")", "+", "-", "*", "/", "^", "-", "abs", "log", "sin", "asin", "sinh", "asinh", "cos", "acos", "cosh", "acosh", "tan", "atan", "tanh", "atanh", "cot", "acot", "coth", "acoth"};
size_t const operation::lst_size = 26;
Vec<double> variable::_Val;
Vec <string> variable::_Name;


operation::operation()
{
	id = -1;
	priority = 0;
	arity = 0;
}
operation::operation(short int const _id)
{
	id = _id;
	if (id < 0 || id >= lst_size)
		throw exception("Wrong operation ID");
	SetPriority();
	SetArity();
}
operation::operation(operation const& A)
{
	id = A.id;
	priority = A.priority;
	arity = A.arity;
}
size_t operation::StmtId(string const& s)
{
	size_t _id = -1, i = 0;
	for (; (i < lst_size) && (_id == -1); i++)
		if (s == lst[i])
			_id = i;
	return _id;
}
short int operation::GetId() const noexcept
{
	return id;
}
string operation::GetName() const
{
	string _name;
	if (id == -1)
		throw std::runtime_error("No string assigned to operation");
	_name = operation::lst[id];
	return _name;
}
void operation::SetPriority()
{
	priority = 0;
	if (id == 2 || id == 3)
		priority = 1;
	else if (id == 4 || id == 5)
		priority = 2;
	else if (id == 6)
		priority = 3;
	else if (id >= 7)
		priority = 4;
	return;
}
short int operation::GetPriority() const noexcept
{
	return priority;
}
void operation::SetArity()
{
	arity = 0;
	if (id >= 2 && id <= 6)
		arity = 2;
	else if (id >= 7)
		arity = 1;
	return;
}
short int operation::GetArity() const noexcept
{
	return arity;
}
ostream& operation::PrintS(ostream& ostr) const
{
	ostr << GetName();
	return ostr;
}





constant::constant() : val(0.0) {}
constant::constant(double const d) : val(d) {}
constant::constant(constant const& C) : val(C.val) {}
ostream& constant::PrintS(ostream& ostr) const
{
	ostr << GetVal();
	return ostr;
}





void variable::primeInit()
{
	if (_Name.Is_Empty())
	{
		_Name.push_back("pi");
		_Name.push_back("e");
		_Val.push_back(acos(-1.0));
		_Val.push_back(exp(1.0));
	}
	return;
}
void variable::AddVar(string const& s)
{
	_Name.push_back(s);
	_Val.push_back(0.0);
	id = _Name.GetSize() - 1;
}
variable::variable() : id(-1)
{
	primeInit();
}
variable::variable(string const& s) : id(-1)
{
	primeInit();
	if (_Name.GetSize() == 1026)
		throw overflow_error("Maximum of variables is reached");
	if (s.length()>16)
		throw length_error("Too long variable name");
	size_t sz = _Name.GetSize();
	for (size_t i = 0; i < sz && id == -1; i++)
	{
		if (s == _Name[i])
			id = i;
	}
	if (id == -1)
		AddVar(s);
}
variable::variable(variable const& V) : id(V.id) {}
double variable::GetVal() const
{
	if (id == -1)
		throw underflow_error("No value is assigned to default variable");
	return _Val[id];
}
string const& variable::GetName() const
{
	if (id == -1)
		throw underflow_error("No name is assigned to default variable");
	return _Name[id];
}
void variable::Init(short int _id, double val)
{
	_Val[_id] = val;
	return;
}
ostream& variable::PrintS(ostream& ostr) const
{
	ostr << GetName();
	return ostr;
}
