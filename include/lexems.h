#include <string>
#include "myvector.h"
#pragma once

class lexem {
private:
	std::string sym;
	int pos;
public:
	lexem(const std::string& s, int p);
	const std::string& getSym() const noexcept;
	const int& getPos() const noexcept;
	virtual bool isOperation() = 0;
	virtual ~lexem();
};

class operation : public lexem {
	int priority;
	int operandsCount;
	static myVector<std::string> availableOperations;
	static myVector<int> priotities;
	static myVector<int> vOperandsCount;
	static myVector<bool> vCanBeAfterOperand;
public:
	static void fillOperations();
	bool static isOperation(const std::string& s);
	bool static canBeAfterOperand(const std::string& s);
	operation(const std::string& s, int p);
	bool isOperation() noexcept override final;
	int getPriority() noexcept;
	int getOperandsCount() noexcept;
	double execute(const myVector<double>& operands);
	virtual ~operation();
};

class operand : public lexem {
protected:
	double value;
public:
	operand(const std::string& s, int p);
	double getValue() noexcept;
	bool isOperation() noexcept override final;
	virtual void fillValue() = 0;
	virtual ~operand();
};

class constant : public operand {
public:
	constant(const std::string& s, int p);
	void fillValue() override;
	virtual ~constant();
};

class variable : public operand {
public:
	static myVector<std::string> vectorOfVariablesNames;
	static myVector<double> VectorOfVariablesValues;
	void fillValue() override;
	variable(const std::string& s, int p);
	virtual ~variable();
};