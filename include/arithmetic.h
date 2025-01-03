#pragma once
#include "rpn.h"

class Expression_ {
private:
    Vector<Lexeme> lexeme; 
    Stack<double> stack;
    Vector<Lexeme> postfix;
    bool postfix_flag;
    bool lexeme_flag;

public:

    Expression_(const Vector<Lexeme>&, bool _ = 0 );

    double evaluate();
};