#pragma once
#include "Poliz.h"
#include <cmath>
#include <stdexcept>

class Arithmetik {
private:
    Poliz poliz;

public:
    Arithmetik(std::string str = "") : poliz(str) {} 
    ~Arithmetik() = default;

    void setVar(int n, double k) {
        poliz.SetVar(n, k);
    }

    double calculate() {
        double left, right;
        Table table = poliz.Getvariables();
        Stack<double> st(poliz.GetCount());

        for (int i = 0; i < poliz.GetCount(); i++) {
            double val = table.searchInfo(poliz[i]);
            if (val != -1) {
                st.push(val);
            }
            else {
                if (st.is_empty()) {
                    throw std::runtime_error("Not enough operands in stack.");
                }
                right = st.pop();

                if (st.is_empty()) {
                    throw std::runtime_error("Not enough operands in stack.");
                }
                left = st.pop();

                if (poliz[i] == "+") {
                    st.push(left + right);
                }
                else if (poliz[i] == "-") {
                    st.push(left - right);
                }
                else if (poliz[i] == "*") {
                    st.push(left * right);
                }
                else if (poliz[i] == "^") {
                    st.push(pow(left, right));
                }
                else if (poliz[i] == "/") {
                    if (right == 0) {
                        throw std::runtime_error("Division by zero.");
                    }
                    st.push(left / right);
                }
                else {
                    throw std::runtime_error("Unknown operator: " + poliz[i]);
                }
            }
        }

        if (st.is_empty()) {
            throw std::runtime_error("Stack is empty after calculations.");
        }

        return st.pop();
    }

    Table getVariables() {
        return poliz.Getvariables();
    }
};