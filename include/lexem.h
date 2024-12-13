#pragma once
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
	bool isOperation();
	virtual bool isUtility();
	virtual bool isUnar();
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
	operand(const std::string& _s, int _p, double _v);
	double getValue()const override;
};
class operation : public lexem {
private:
	bool uti;
	char priority;
	bool unar;
public:
	operation(const std::string& _s, int _p, char _pr, bool _unar = 0, bool _u = 0, int id = 0);
	bool isUtility() override;
	bool isUnar() override;
	int getPriotiry();
};
class constant : public operand{
public:
	constant(const std::string& _s, int _p, double _v);
	double getValue()const override;
	bool isConstanta()override;
	void setValue_(const double& _v) override;
};
class variable : public operand {
private:
	bool isFunc;
	std::string field;
public:
	variable(const std::string& _s, int _p, double _v = 0.0, bool _isFunc = false, const std::string& field_ = "hah");
	bool isFunction()override;
	void setValue_(const double& _v) override;
	double getValue()const override;
	bool isConstanta() override;
};