#pragma once
#include "lexem.h"
#include <cmath>
double ADD(operand const* lhs, operand const* rhs);
double SUB(operand const* lhs, operand const* rhs);
double MUL(operand const* lhs, operand const* rhs);
double DIV(operand const* lhs, operand const* rhs);
double POW(operand const* lhs, operand const* rhs);
double NEG(operand const* arg);
double ABS(operand const* arg);
double LOG(operand const* arg);
double SIN(operand const* arg);
double ASIN(operand const* arg);
double SINH(operand const* arg);
double ASINH(operand const* arg);
double COS(operand const* arg);
double ACOS(operand const* arg);
double COSH(operand const* arg);
double ACOSH(operand const* arg);
double TAN(operand const* arg);
double ATAN(operand const* arg);
double TANH(operand const* arg);
double ATANH(operand const* arg);
double COT(operand const* arg);
double ACOT(operand const* arg);
double COTH(operand const* arg);
double ACOTH(operand const* arg);