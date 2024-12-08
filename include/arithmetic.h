// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#pragma once

#include <string>
#include <math.h>
#include "Vector.h"
#include "stack.h"
#include "inputException.h"

class lexem
{
private:
	size_t initPos;
public:
	lexem(int initPos);
	~lexem() { }
	virtual int what() const noexcept = 0;
	size_t getInitPos() const noexcept;
};

class operand : public lexem
{
protected:
	double value;
public:
	operand(const double& var, int initPos);
	~operand() { }
	int what() const noexcept override;
	double getValue() const noexcept;
};

class varible : public operand
{
private:
	std::string nameVar;
	bool setValue;
	using operand::value;
public:
	varible(const std::string& name, int initPos);
	~varible() { }
	int what() const noexcept override;
	void initValue(const double& val);
	std::string getName() const noexcept;
};

class operation : public lexem
{
private:
	char op;
	int priority;
public:
	operation(const char& op, int initPos);
	~operation() { }
	int what() const noexcept override;
	char getOperation() const noexcept;
	int getPriority() const noexcept;
};

double calcArithmetic(const Vector<lexem*>& lx);

Vector<lexem*> toPostfix(const Vector<lexem*>& lx);

double ToOperand(const std::string& str);

Vector<lexem*> parsingLexem(const std::string& expression);

Vector<std::string> getVarNames(Vector<lexem*>& lx);

void inputVar(Vector<lexem*>& lx);

void deleteLx(Vector<lexem*>& lx);