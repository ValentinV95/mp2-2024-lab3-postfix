#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "stack.h"

using namespace std;
class TPostfix
{
    string infix, postfix;
    string operands;
    string* line;
    size_t length;
    Stack<double> numbers;
    double res;
public:
    ~TPostfix();
    TPostfix(string str);
    string getInfix() const;
    string getPostfix() const;
    double getResult() const;
    int priority(string operation);
    bool isOperand(const char& symbol);
    void toLexems();
    void toPostfix();
    void valueofvar();
    double toDouble(string number);
    void calculate();
};
