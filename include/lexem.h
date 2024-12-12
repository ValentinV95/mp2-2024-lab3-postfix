#pragma once
#include <string>

//ID
// 0 - base class
// 1 - contant
// -1 - operand class
// 2 - variable
// 3,-3,4,-4 - sin,cos,tan,cot
// -2 - unar -
// 5,-5,6,-6 - -,+,*,/
// 7,-7 - (,)
class lexem {
protected:
	size_t position;
	std::string value;
	bool isOp;
	int ID;
public:
	lexem(const std::string& v_, size_t pos) : value(v_), position(pos),isOp(false),ID(0) {};
	bool isOperation() { return isOp; }
	virtual bool isUtility() { return NULL; };
	virtual bool isUnar() { return NULL; };
	virtual bool isFunction() { return NULL; }
	virtual void setValue_(const double& _v) {};
	virtual void setValue_(const double& _v)const {};
	virtual double getValue()const { return 0.0; }
	virtual bool isConstanta() { return NULL; }
	int Get_Lexem_ID() { return ID; }
	void print(bool isTesting = false)const { if (isTesting)std::cout << value << " "; else { std::cout << value; } }
};

class operand : public lexem {
protected:
	double value_d;
	bool isConst;
public:
	operand(const std::string& _s, int _p, double _v) : lexem::lexem(_s, _p), value_d(_v) { isConst = false; ID = -1; };
	virtual double getValue()const override{ return value_d; }
};
class operation : public lexem {
private:
	bool uti;
	char priority;
	bool unar;
public:
	operation(const std::string& _s, int _p, char _pr, bool _unar = 0, bool _u = 0) : lexem::lexem(_s, _p), unar(_unar), uti(_u) { isOp = true; priority = _pr; 
	if (value == "-") {
		if (unar) {
			ID = -2;
		}
		else {
			ID = 5;
		}
	}
	else if (value == "+") {
		ID = -5;
	}
	else if (value == "*") {
		ID = 6;
	}
	else if (value == "/") {
		ID = -6;
	}
	else if (value == "(") {
		ID = 7;
	}
	else if (value == ")") {
		ID = -7;
	}
	
	};
	bool isUtility() override{ return uti; }
	bool isUnar() override{ std::cout << "iAM\n"; return unar; }
	int getPriotiry() { return priority; }
};
class constant : public operand{
public:
	constant(const std::string& _s, int _p, double _v) : operand::operand(_s, _p, _v) { isConst = true; ID = 1; };
	double getValue()const override{ return value_d; }
	bool isConstanta()override { return true; }
	void setValue_(const double& _v) override{ value_d = _v; };
};
class variable : public operand {
private:
	bool isFunc;
	double negative;
	std::string field;
public:
	variable(const std::string& _s, int _p, double _v = 0.0,bool _isFunc=false,const std::string& field_ = "hah",double neg=1.0) : operand::operand(_s, _p, _v), isFunc(_isFunc),field(field_),negative(neg) {
		if (isFunc) {
			if (field == "sin") {
				ID = 3;
			}
			else if (field == "cos") {
				ID = -3;
			}
			else if (field == "tan") {
				ID = 4;
			}
			else if (field == "cot") {
				ID = -4;
			}
		}
		else {
			ID = 2;
		}
	
	};
	bool isFunction()override { return isFunc; }
	void setValue_(const double& _v) { value_d = _v; };
	double getValue()const override{ return value_d; }
	bool isConstanta() override{ return false; }
};