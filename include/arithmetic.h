// объявление функций и классов для вычисления арифметических выражений
#pragma once
#include "stack.h"
#include <string>
#include <vector>
#include <cmath>

#define logic std::logic_error("Invalid bracket sequence");

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

bool isfunc(std::string c) {
    return (c == "cos" || c == "sin");
}

int precedence(std::string op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    return 0;
}

bool isOperator(std::string c) {
    return (c == "+" || c == "-" || c == "*" || c == "/" || c == "^");
}

template <typename T>
class TPostfix {
public:
    bool is_rpn = 0;
    std::vector<std::string> post;
    std::string infix;
    std::vector<std::pair<std::string, std::string>> var;
    TPostfix(std::string expression = "") {
        for (int i = 0; i < expression.size(); i++)
            if (expression[i] != ' ')
                infix.push_back(expression[i]);
    }

    void print_rpn() {
        if (is_rpn == 0)
            throw std::logic_error("RPN wasn't made");
        for (std::string z : post)
            std::cout << z << ' ';
        std::cout << '\n';
    }

    void print_infix() {
        std::cout << infix << '\n';
    }

    void ToPostfix() {
        is_rpn = 1;
        TStack<char> operators; // Стек для операторов
        std::string number, name; // Для хранения текущего числа
        std::string per;
        int cnt = 0; //число скобок
        int signs = 0; //число знаков
        int unar = 0;
        //for (char infix[i] : infix) {
        for (int i=0;i<infix.size();i++){
            bool is_var = 0;
            if (std::isdigit(infix[i])) {
                while (std::isdigit(infix[i]) || infix[i] == '.') {
                    number += infix[i]; // Собирать число
                    i++;
                }
                if (infix[i] == 'e') {
                    i++;
                    number += 'e';
                    if (infix[i] == '-') {
                        number += '-';
                        i++;
                    }
                    while (std::isdigit(infix[i])) {
                        number += infix[i];
                        i++;
                    }
                }
            }

            while (infix[i] >= 'a' && infix[i] <= 'z') {
                per += infix[i];
                i++;
            }

            if (per == "sin" || per == "cos") {
                std::string s;
                int cnt = 1;
                for (i = i + 1;; i++) {
                    cnt += (infix[i] == '(');
                    cnt -= (infix[i] == ')'); //чтобы считать композицию sin(sin(...))
                    if (cnt == 0)
                        break;
                    s += infix[i];
                }
                TPostfix<T> func(s);
                func.ToPostfix();
                T num = func.simple_calc();
                if (per == "sin")
                    post.push_back(std::to_string(sin(num)));
                if (per == "cos")
                    post.push_back(std::to_string(cos(num)));
                per.clear();
                i++;
            }
            if (!per.empty()) {
                post.push_back(per);
                var.push_back({ per, "0" });
                per.clear();
            }

            if (!number.empty()) {
                if (unar == 1)
                    post.push_back("-" + number);
                else
                    post.push_back(number); // Добавить число в выход
                number.clear(); // Очистить
                unar = 0;
            }

            if (i == infix.size())
                break;

            if (infix[i] == '(') {
                cnt++;
                operators.push(infix[i]); // Если открывающая скобка, помещаем в стек
            }
            else if (infix[i] == ')') {
                if (cnt==0)
                    throw logic;
                cnt--;
                // Пока есть операторы и не дошли до открывающей скобки
                while (!operators.isEmpty() && operators.top() != '(') {
                    post.push_back(std::string(1, operators.top()));
                    operators.pop();
                }
                operators.pop(); // Удаляем '('
            }
            else {
                // Для всех операторов
                char top = operators.top();
                while (!operators.isEmpty() && precedence(operators.top()) >= precedence(infix[i])) {
                    post.push_back(std::string(1, operators.top()));
                    operators.pop();
                }
                if (infix[i] == '-' && (i==0 || infix[i-1] == '(')) {
                    unar = 1;
                }
                else if (isOperator(infix[i])){
                    operators.push(infix[i]); // Добавляем текущий оператор в стек
                }
            }
            if (cnt < 0)
                throw logic;
        }

        if (cnt != 0)
            throw logic;

        while (!operators.isEmpty()) {
            post.push_back(std::string(1, operators.pop()));
        }
    }
    T simple_calc() {
        TStack<std::string> operators;
        TStack<T> nums;
        if (var.size() > 0) {
            std::cout << "Print the value of the variables:\n";
            for (int i = 0; i < var.size(); i++) {
                std::cout << var[i].first << ": ";
                std::cin >> var[i].second;
            }
        }
        for (int i = 0; i < post.size(); i++) {
            if (isOperator(post[i])) {
                std::string oper = post[i];
                T a, b;
                a = nums.pop();
                b = nums.pop();
                if (oper == "+")
                    nums.push(b + a);
                else if (oper == "-")
                    nums.push(b - a);
                else if (oper == "*")
                    nums.push(b * a);
                else if (oper == "/")
                    nums.push(b / a);
                else if (oper == "^")
                    nums.push(pow(b, a));
            }
            else {
                std::string val = post[i];
                if (post[i][0] >= 'a' && post[i][0] <= 'z') {
                    for (int j = 0; j < var.size(); j++)
                        if (var[j].first == post[i])
                            val = var[j].second;
                }
                //nums.push(static_cast<T>(std::stod(val))); 
                double integer = 0.0;
                double real = 0.0;
                int i = 0, znak = 0;
                if (val[i] == '-') {
                    znak = 1;
                    i++;
                }
                for (; i < val.size() && val[i]!='.' && val[i]!='e'; i++) {
                    integer = integer * 10 + (val[i] - '0');
                }
                
                if (val[i] == '.') {
                    i++;
                    double del = 10;
                    for (; i < val.size() && val[i]!='e'; i++, del *= 10) {
                        real = real + (val[i] - '0') / del;
                    }
                }
                //i++;
                int power = 0;
                if (val[i] == 'e') {
                    i++;
                    int znak = 0;
                    if (val[i] == '+')
                        i++;
                    if (val[i] == '-') {
                        znak = 1;
                        i++;
                    }             
                    for (; i < val.size(); i++) {
                        power = power * 10 + (val[i] - '0');
                    }
                    power = pow(-1, znak) * power;
                }
                nums.push(static_cast<T>(pow(-1, znak) * (real + integer) * pow(10, power)));
            }
        }
        return nums.top();
    }
};