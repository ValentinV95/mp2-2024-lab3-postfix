#include <iostream>
#include <string>
#include "vector.h"
#include "stack.h"
#include "lexem.h"
#include <stdexcept>

Vector<Lexeme> toRPN(Vector<Lexeme> infix) {
    Vector<Lexeme> postfix;
    Stack<Lexeme> opStack;

    for (int i = 0; i < infix.getsize(); i++) {
        const auto& lex = infix[i];
        if (lex.type() == 1) {
            postfix.push_back(lex);
        }
        else if (lex.type() == 2) {
            while (!opStack.isEmpty() && opStack.top().precedence() >= lex.precedence()) {
                postfix.push_back(opStack.top());
                opStack.pop();
            }
            opStack.push(lex);
        }
        else if (lex.type() == 3) {
            opStack.push(lex);
        }
        else if (lex.type() == 4) {
            while (!opStack.isEmpty() && opStack.top().type() != 3) {
                postfix.push_back(opStack.top());
                opStack.pop();
            }
            if (!opStack.isEmpty() && opStack.top().type() == 3) {
                opStack.pop();
            }
            else {
                throw std::runtime_error("Mismatched parentheses");
            }
        }
        else {
            postfix.push_back(lex);
        }
    }

    while (!opStack.isEmpty()) {
        if (opStack.top().type() == 3) {
            throw std::runtime_error("Mismatched parentheses");
        }
        postfix.push_back(opStack.top());
        opStack.pop();
    }

    return postfix;
}