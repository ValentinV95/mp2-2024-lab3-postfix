#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "stack.h"

using namespace std;
class TPostfix
{
    string infix, postfix;
    string operands;
    string* var;
    string* setOfLexems;
    double* varValue;
    int lexemSize;
    int varSize;

public:
    ~TPostfix();
    TPostfix(string& str);
    void setInfix(string& str);
    string getInfix() const;
    string getPostfix() const;
    string getOperands() const;
    int priority(string operation);
    bool isOperation(const char& x);
    bool isOperand(const char& symbol);
    bool isDigitOrPoint(const char& symbol);
    void toLexems();
    void check();
    void toPostfix();
    double toDouble(string number);
    void valueofvars();
    double calculate();
};
