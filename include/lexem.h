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

class operation : public lexem
{
private:
	static char const* lst[];
	static size_t const lst_size;
	short int id;
	short int priority;
	short int arity;
	double GetVal() override { return 0.0; };
	void SetVal() override {};
	void SetPriority();
	void SetArity();
public:
	operation();
	operation(short int const _id);
	operation(operation const& A);
	~operation() = default;
	inline bool IsStmt() noexcept override { return true; };
	short int GetId() noexcept override final;
	std::string GetName() override final;
	static size_t StmtId(std::string const& s);
	short int GetPriority() noexcept;
	short int GetArity() noexcept;
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