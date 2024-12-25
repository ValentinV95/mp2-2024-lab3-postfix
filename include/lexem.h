#pragma once
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "datavec.h"

class lexem
{
public:
	virtual bool IsStmt() = 0;
	virtual ostream& Print() = 0;
};

class operation : public lexem
{
private:
	static char const* lst[];
	static size_t const lst_size;
	short int id;
	short int priority;
	short int arity;
	void SetPriority();
	void SetArity();
public:
	operation();
	operation(short int const _id);
	operation(operation const& A);
	~operation() = default;
	inline bool IsStmt() noexcept override { return true; };
	short int GetId() noexcept;
	string GetName();
	static size_t StmtId(string const& s);
	short int GetPriority() noexcept;
	short int GetArity() noexcept;
	ostream& Print() override;
};

class operand : public lexem
{
public:
	virtual bool IsConst() = 0;
	virtual double GetVal() = 0;
	inline bool IsStmt() noexcept override final { return false; };
};

class constant : public operand
{
private:
	double val;
public:
	using operand::IsStmt;
	inline bool IsConst() noexcept override { return true; };
	constant();
	constant(double const d);
	constant(constant const& C);
	~constant() = default;
	double GetVal() noexcept override { return val; };
	ostream& Print();
};

class variable : public operand
{
private:
	short int id;
	static Vec<double> _Val;
	static Vec <string> _Name;
	void AddVar(string const& s);
	void primeInit();
public:
	using operand::IsStmt;
	inline bool IsConst() noexcept override { return false; };
	variable();
	variable(string const& s);
	variable(variable const& Var);
	short int GetId() noexcept { return id; };
	double GetVal() override;
	string GetName();
	static void Init(short int id, double val);
	ostream& Print();
};