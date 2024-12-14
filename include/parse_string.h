#pragma once
#define _USE_MATH_DEFINES
#include "parse_digits.h"
#include "lexem.h"
#include <cmath>
#define en_l(a) (a>=97 && a<=122)	//english lower
#define en_u(a) (a>=65 && a<=90)	//english upper
#define _dig(a) (a>=48 && a<=57)	//digits
#define func(a) (a=="cos" || a=="sin" || a=="tan" || a=="cot")
#define _opers(a) (a>=42 && a<=47 && a!=46 && a!=44)
#define _opers_with_b(a) (_opers(a) || a==40 || a==41)
#define _right_symbols(a) (a!=44 && a>=40 && (!(a>=58 && a<=64)) && (!(a>=91 && a<=94)) && a!=96 && a<=122)

vector<lexem*> Main_Parser(std::string original);
//Остальные функции целенаправленно сокрыты