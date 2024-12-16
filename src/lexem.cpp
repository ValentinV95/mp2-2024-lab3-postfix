#include "lexem.h"

//ID
// 0 - base class
// 1 - constant
// -1 - operand class
// 2 - variable
// 3,-3,4,-4,8 - sin,cos,tan,cot,exp
// -2 - unar -
// 5,-5,6,-6 - -,+,*,/
// 7,-7 - (,)

lexem::lexem(const std::string& v_, size_t pos) : value(v_), position(pos), isOp(false), ID(0) {};
lexem::~lexem() {position = 0;isOp = 0;ID = 0;}
bool lexem::isOperation() { return isOp; }
int lexem::Get_Lexem_ID() { return ID; }
size_t lexem::GetPos() { return position; }
std::string lexem::Get_VAL_NAME() { return value; }
void lexem::print(bool isTesting)const { if (isTesting)std::cout << value << " "; else { std::cout << value; } }
bool lexem::isFunction() { return false; }
void lexem::setValue_(const double& _v) { throw j_error("cant setValue() for this class"); };
double lexem::getValue() const { throw j_error("cant setValue() for this class"); }
bool lexem::isConstanta() { return NULL; }

operand::operand(const std::string& _s, size_t _p, double _v) : lexem::lexem(_s, _p), value_d(_v) { isConst = false; ID = -1; };
operand::~operand() {value_d = 0;isConst = 0;}
double operand::getValue()const { return value_d; }
void operand::setValue_(const double& _v) { value_d = _v; };
bool operand::isConstanta() { return isConst; }

operation::operation(const std::string& _s, size_t _p, char _pr, bool _unar, bool _u, int id) : lexem::lexem(_s, _p), unar(_unar), uti(_u) {
	isOp = true; priority = _pr;
	if (id != 0) {
		ID = id;
	}
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
operation::~operation() {uti = false;unar = 0;}
bool operation::isUtility() { return uti; }
bool operation::isUnar() { return unar; }
int operation::getPriotiry() { return priority; }

constant::constant(const std::string& _s, size_t _p, double _v) : operand::operand(_s, _p, _v) { isConst = true; ID = 1; };
constant::~constant() {};

variable::variable(const std::string& _s, size_t _p, double _v, bool _isFunc) : operand::operand(_s, _p, _v), isFunc(_isFunc) {
	if (isFunc) {
		if (_s == "sin") {
			ID = 3;
		}
		else if (_s == "cos") {
			ID = -3;
		}
		else if (_s == "tan") {
			ID = 4;
		}
		else if (_s == "cot") {
			ID = -4;
		}
		else if (_s == "exp") {
			ID = 8;
		}
	}
	else {
		ID = 2;
}};
variable::~variable() { isFunc = 0; }
bool variable::isFunction(){ return isFunc; }