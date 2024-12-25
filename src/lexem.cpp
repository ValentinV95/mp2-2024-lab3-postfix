#pragma once
#include "lexem.h"
char const* operation::lst[] = {"(", ")", "+", "-", "*", "/", "^", "-", "abs", "log", "sin", "asin", "sinh", "asinh", "cos", "acos", "cosh", "acosh", "tan", "atan", "tanh", "atanh"};
size_t const operation::lst_size = 22;

operation::operation()
{
	id = -1;
	priority = 0;
	arity = 0;
}
operation::operation(short int const _id)
{
	id = _id;
	if (id < 0 || id >= 22)
		throw std::exception("Wrong operation ID");
	SetPriority();
	SetArity();
}
operation::operation(operation const& A)
{
	id = A.id;
	priority = A.priority;
	arity = A.arity;
}
size_t operation::StmtId(std::string const& s)
{
	size_t _id = -1, i = 0;
	for (; (i < lst_size) && (_id == -1); i++)
		if (s == lst[i])
			_id = i;
	return _id;
}
short int operation::GetId() noexcept
{
	return id;
}
std::string operation::GetName()
{
	std::string _name;
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
short int operation::GetPriority() noexcept
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
short int operation::GetArity() noexcept
{
	return arity;
}

constant::constant() : val(0.0) {}
constant::constant(double const d) : val(d) {}
constant::constant(constant const& C) : val(C.val) {}
