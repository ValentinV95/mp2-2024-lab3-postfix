#pragma once
#include <string>
class lexem {
protected:
	size_t position;
	std::string value;
	bool isOp;
public:
	lexem(const std::string& v_, size_t pos) : value(v_), position(pos),isOp(false) {};
	bool isOperation() { return isOp; }
	virtual bool isUtility() { return NULL; };
	virtual bool isUnar() { return NULL; };
	virtual bool isFunction() { return NULL; }
	virtual void setValue_(const double& _v)const {};
	virtual double getValue()const { return 0.0; }
	void print()const { std::cout << value; }
};

class operand : public lexem {
protected:
	double value_d;
	bool isConst;
public:
	operand(const std::string& _s, int _p, double _v) : lexem::lexem(_s, _p), value_d(_v) { isConst = false; };
};
class operation : public lexem {
private:
	bool uti;
	char priority;
	bool unar;
public:
	operation(const std::string& _s, int _p, char _pr,bool _unar=0,bool _u=0) : lexem::lexem(_s, _p),unar(_unar),uti(_u) { isOp = true; priority = _pr; };
	bool isUtility() { return uti; }
	bool isUnar() { return unar; }
};
class constant : public operand{
public:
	constant(const std::string& _s, int _p, double _v) : operand::operand(_s, _p, _v) { isConst = true; };
	double getValue() { return value_d; }
	void setValue_(const double& _v) { value_d = _v; };
};
class variable : public operand {
private:
	bool isFunc;
	std::string field;
public:
	variable(const std::string& _s, int _p, double _v = 0.0,bool _isFunc=false,const std::string& field_ = "hah") : operand::operand(_s, _p, _v), isFunc(_isFunc),field(field_) {};
	bool isFunction() { return isFunc; }
	void setValue_(const double& _v) { value_d = _v; };
	double getValue() { return value_d; }
};