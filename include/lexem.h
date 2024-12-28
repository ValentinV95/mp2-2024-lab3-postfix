#pragma once
#include <iostream>
#include <sstream>
#include "datavec.h"

class lexem
{
public:
	virtual bool IsStmt() const = 0;
	virtual ostream& PrintS(ostream& ostr) const = 0;
	friend ostream& operator<<(ostream& ostr, lexem const& A)
	{
		return A.PrintS(ostr);
	}
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
	inline bool IsStmt() const noexcept override { return true; };
	short int GetId() const noexcept;
	string GetName() const;
	static size_t StmtId(string const& s);
	short int GetPriority() const noexcept;
	short int GetArity() const noexcept;
	ostream& PrintS(ostream& ostr) const override;
	friend ostream& operator<<(ostream& ostr, operation const& A)
	{
		return A.PrintS(ostr);
	};
};

class operand : public lexem
{
public:
	virtual bool IsConst() const = 0;
	virtual double GetVal() const noexcept = 0;
	inline bool IsStmt() const noexcept override final { return false; };
	friend ostream& operator<<(ostream& ostr, operand const& A)
	{
		return A.PrintS(ostr);
	}
};

class constant : public operand
{
private:
	double val;
public:
	using operand::IsStmt;
	inline bool IsConst() const noexcept override { return true; };
	constant();
	constant(double const d);
	constant(constant const& C);
	~constant() = default;
	double GetVal() const noexcept override { return val; };
	ostream& PrintS(ostream& ostr) const override;
	friend ostream& operator<<(ostream& ostr, constant const& A)
	{
		return A.PrintS(ostr);
	}

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
	inline bool IsConst() const noexcept override { return false; };
	variable();
	variable(string const& s);
	variable(variable const& Var);
	short int GetId() noexcept { return id; };
	double GetVal() const noexcept override;
	string const& GetName() const;
	static void Init(short int id, double val);
	ostream& PrintS(ostream& ostr) const override;
	friend ostream& operator<<(ostream& ostr, variable const& A)
	{
		return A.PrintS(ostr);
	}
	static Vec<double>& const GetValVec() { return _Val; }		//  For tests only
	static Vec<string>& const GetNameVec() { return _Name; }		//  For tests only
};