#include "rpn.h"

Vector<Lexeme> toRPN(Vector<Lexeme> infix) {
    Vector<Lexeme> postfix;
    Stack<Lexeme> opStack;

    for (int i = 0; i < infix.getsize(); i++) {
        const auto& lex = infix[i];

        if (lex.type() == 1) {
            postfix.push_back(lex);
        }

        else if (lex.type() == 2 || lex.type() == 7) {
            while (!opStack.isEmpty() && opStack.top().precedence() >= lex.precedence() && lex.type() != 7) {
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
                throw std::runtime_error("Mismatched parentheses at position " + std::to_string(i));
            }

            if (!opStack.isEmpty() && (opStack.top().type() == 5)) {
                postfix.push_back(opStack.top());
                opStack.pop();
            }
        }

        else if (lex.type() == 5) { 
            opStack.push(lex); 
        }

        else {
            postfix.push_back(lex);
        }
    }

    while (!opStack.isEmpty()) {
        if (opStack.top().type() == 3) {
            throw std::runtime_error("Mismatched parentheses at the end of input");
        }
        postfix.push_back(opStack.top());
        opStack.pop();
    }

    return postfix;
}
