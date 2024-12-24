#pragma once
#include <string>
#include <stdexcept>
#include "datavec.h"

class lexem
{
public:
	virtual short int GetId() = 0;
	virtual double GetVal() = 0;
	virtual void SetVal() = 0;
	virtual std::string GetName() = 0;
	virtual bool IsStmt() = 0;
};

class def_ops
{
protected:
	const char* lst[22];
	size_t lst_size;
public:
	def_ops() : lst{ "(", ")", "+", "-", "*", "/", "^", "-", "abs", "log", "sin", "asin", "sinh", "asinh", "cos", "acos", "cosh", "acosh", "tan", "atan", "tanh", "atanh" }, lst_size(22) {};
	size_t GetSize() { return lst_size; }
	const char** GetList() { return lst; }
};

class operation : public lexem
{
private:
	static def_ops Lst;
	static bool def_declared;
	short int id;
	short int priority;
	short int arity;
	double GetVal() override { return 0.0; };
	void SetVal() override {};
	void SetPriority()
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
	void SetArity()
	{
		arity = 0;
		if (id >= 2 && id <= 6)
			arity = 2;
		else if (id >= 7)
			arity = 1;
		return;
	}
public:
	operation()
	{
		id = -1;
		priority = 0;
		arity = 0;
		Lst = new def_ops _Lst();
	}
	operation(short int const _id)
	{
		id = _id;
		if (id < 0 || id >= 22)
			throw std::exception("Wrong operation ID");
		SetPriority();
		SetArity();
	}
	operation(operation const& A)
	{
		id = A.id;
		priority = A.priority;
		arity = A.arity;
	}
	~operation() = default;
	inline bool IsStmt() noexcept override { return true; };
	static size_t StmtId(std::string const& s)
	{
		size_t l_sz = Lst.GetSize();
		const char** l = Lst.GetList();
		size_t _id = -1, i = 0;
		for (; (i < l_sz) && (_id == -1); i++)
			if (s == l[i])
				_id = i;
		return _id;
	}
	short int GetId() noexcept
	{
		return id;
	}
	std::string GetName()
	{
		const char** l = Lst.GetList();
		std::string _name;
		if (id == -1)
			throw std::runtime_error("No string assigned to operation");
		_name = l[id];
		return _name;
	}
	short int GetPriority() noexcept
	{
		return priority;
	}
	short int GetArity() noexcept
	{
		return arity;
	}
};

class operand : public lexem
{
public:
	inline bool IsStmt() noexcept override final { return false; };
};

/*class constant : public operand
{
private:
	double val;
	short int GetId() override { return 0; };
	std::string GetName() override { return "\0"; };
public:
	using operand::IsStmt;
};*/