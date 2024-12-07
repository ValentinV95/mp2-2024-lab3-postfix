#pragma once
#include <string>
class lexem {
protected:
	size_t position;
	std::string value;
	bool isOp;
public:
	lexem(const std::string& v_, size_t pos) : value(v_), position(pos),isOp(false) {};
};

class operand : protected lexem {
protected:
	double value;
	bool isConst;
public:
	operand(const std::string& _s, int _p, double _v) : lexem::lexem(_s, _p), value(_v) { isConst = false; };
};
class operation : private lexem {
private:
	char priority;
public:
	operation(const std::string& _s, int _p, char _pr) : lexem::lexem(_s, _p) { isOp = true; priority = _pr; };
};
class constant : private operand{
public:
	constant(const std::string& _s, int _p, double _v) : operand::operand(_s, _p, _v) { isConst = true; };
};
class variable : private operand {
private:
	bool isFunc;
	std::string field;
public:
	variable(const std::string& _s, int _p, double _v = 0.0,bool _isFunc=false,const std::string& field_ = "hah") : operand::operand(_s, _p, _v), isFunc(_isFunc),field(field_) {};
};