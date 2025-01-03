#include "arithmetic.h"

Expression_::Expression_(const Vector<Lexeme>& lexeme_, bool flag) {
    if (flag) {
        postfix_flag = true;
        lexeme_flag = false;
        postfix = lexeme_;
    }
    else {
        postfix_flag = false;
        lexeme_flag = true;
        lexeme = lexeme_;
    }
}

double Expression_::evaluate() {
    if (lexeme_flag && !postfix_flag) {
        postfix = toRPN(lexeme); 
    }
    double result; 

    for (int i = 0; i < postfix.getsize(); i++) {
        const auto& lex = postfix[i];
        if (lex.type() == 1 || lex.type() == 6) { 
            stack.push(lex.number());
            continue;
        }
        else if (lex.type() == 7) {
            if (stack.size() < 1) {
                throw std::runtime_error("Insufficient values in expression for operator: " + lex.value() + " at position " + std::to_string(i));
            }
            double a = stack.top();
            stack.pop();
            result = -a;
        }
        else if (lex.type() == 2) { 
            if (stack.size() < 2) {
                throw std::runtime_error("Insufficient values in expression for operator: " + lex.value() + " at position " + std::to_string(i));
            }
            double b = stack.top();
            stack.pop();
            double a = stack.top();
            stack.pop();

            if (lex.value() == "+") {
                result = a + b;
            }
            else if (lex.value() == "-") {
                result = a - b;
            }
            else if (lex.value() == "*") {
                result = a * b;
            }
            else if (lex.value() == "/") {
                if (b == 0) {
                    throw std::runtime_error("Division by zero at position " + std::to_string(i));
                }
                result = a / b;
            }
            else if (lex.value() == "^") {
                result = pow(a,b);
            }
            else {
                throw std::runtime_error("Unknown operator: " + lex.value() + " at position " + std::to_string(i));
            }
        }
        else if (lex.type() == 5) { 
            const double a = stack.top();
            stack.pop(); 
            if (lex.value() == "log") {
                result = log(a);
            }
            else if (lex.value() == "exp") {
                result = exp(a);
            }
            else if (lex.value() == "sin") {
                result = sin(a);
            }
            else if (lex.value() == "cos") {
                result = cos(a);
            }
            else if (lex.value() == "tan") {
                result = tan(a);
            }
            else if (lex.value() == "cot") {
                result = 1.0 / tan(a);
            }
            else if (lex.value() == "sec") {
                result = 1.0 / cos(a);
            }
            else if (lex.value() == "csc") {
                result = 1.0 / sin(a);
            }
            else {
                throw std::runtime_error("Unknown function: " + lex.value() + " at position " + std::to_string(i));
            }
        }
        stack.push(result); 
    }

    if (stack.size() != 1) {
        throw std::runtime_error("The user input has too many values after evaluation at position " + std::to_string(postfix.getsize()));
    }

    return stack.top(); 
};

