#pragma once
#include "j_error.h"
#include <string>
#include <iostream>
class lexem {
protected:
	size_t position;
	std::string value;
	bool isOp;
	int ID;
public:
	lexem(const std::string& v_, size_t pos);
	virtual ~lexem();
	bool isOperation();
	virtual bool isFunction();
	virtual void setValue_(const double& _v);
	virtual double getValue()const;
	virtual bool isConstanta();
	int Get_Lexem_ID();
	size_t GetPos();
	void print(bool isTesting = false) const;
	std::string Get_VAL_NAME();
};

class operand : public lexem {
protected:
	double value_d;
	bool isConst;
public:
	operand(const std::string& _s, size_t _p, double _v);
	virtual ~operand();
	double getValue()const override;
	void setValue_(const double& _v)override;
	bool isConstanta()override;
};
class operation : public lexem {
private:
	bool uti;
	char priority;
	bool unar;
public:
	operation(const std::string& _s, size_t _p, char _pr, bool _unar = 0, bool _u = 0, int id = 0);
	virtual ~operation();
	bool isUtility();
	bool isUnar();
	int getPriotiry();
};
class constant : public operand{
public:
	constant(const std::string& _s, size_t _p, double _v);
	~constant();
};
class variable : public operand {
private:
	bool isFunc;
	std::string field;
public:
	variable(const std::string& _s, size_t _p, double _v = 0.0, bool _isFunc = false);
	~variable();
	bool isFunction()override;
};