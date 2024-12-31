#include "simple_math.h"

double ADD(operand const* lhs, operand const* rhs)
{
	double a = lhs->GetVal(), b = rhs->GetVal();
	return a + b;
}

double SUB(operand const* lhs, operand const* rhs)
{
	double a = lhs->GetVal(), b = rhs->GetVal();
	return a - b;
}

double MUL(operand const* lhs, operand const* rhs)
{
	double a = lhs->GetVal(), b = rhs->GetVal();
	return a * b;
}

double DIV(operand const* lhs, operand const* rhs)
{
	double a = lhs->GetVal(), b = rhs->GetVal();
	return a / b;
}

double POW(operand const* lhs, operand const* rhs)
{
	double a = lhs->GetVal(), b = rhs->GetVal();
	return pow(a,b);
}

double NEG(operand const* arg)
{
	double a = arg->GetVal();
	return -a;
}

double ABS(operand const* arg)
{
	double a = arg->GetVal();
	return fabs(a);
}

double LOG(operand const* arg)
{
	double a = arg->GetVal();
	return log(a);
}

double SIN(operand const* arg)
{
	double a = arg->GetVal();
	return sin(a);
}

double ASIN(operand const* arg)
{
	double a = arg->GetVal();
	return asin(a);
}

double SINH(operand const* arg)
{
	double a = arg->GetVal();
	return sinh(a);
}

double ASINH(operand const* arg)
{
	double a = arg->GetVal();
	return asinh(a);
}

double COS(operand const* arg)
{
	double a = arg->GetVal();
	return cos(a);
}

double ACOS(operand const* arg)
{
	double a = arg->GetVal();
	return acos(a);
}

double COSH(operand const* arg)
{
	double a = arg->GetVal();
	return cosh(a);
}

double ACOSH(operand const* arg)
{
	double a = arg->GetVal();
	return acosh(a);
}

double TAN(operand const* arg)
{
	double a = arg->GetVal();
	return tan(a);
}

double ATAN(operand const* arg)
{
	double a = arg->GetVal();
	return atan(a);
}

double TANH(operand const* arg)
{
	double a = arg->GetVal();
	return tanh(a);
}

double ATANH(operand const* arg)
{
	double a = arg->GetVal();
	return atanh(a);
}

double COT(operand const* arg)
{
	double a = arg->GetVal();
	return 1.0/tan(a);
}

double ACOT(operand const* arg)
{
	double a = arg->GetVal();
	return asin(1.0)- atan(a);
}

double COTH(operand const* arg)
{
	double a = arg->GetVal();
	return 1.0/tanh(a);
}

double ACOTH(operand const* arg)
{
	double a = arg->GetVal();
	return log((a+1)/(a-1))/2.0;	// atanh(1.0/a) has significant error
}