#include "arithmetic.h"
#include <stdexcept>
#include <cmath>

// Конструктор Lexem
Lexem::Lexem(LexemType t, const std::string& v, int p)
    : type(t), value(v), priority(p) {}

// Проверка, является ли оператором
bool Lexem::isOperator() const {
    return type == OPERATOR;
}

// Проверка, является ли функцией (sin, cos, ...)
bool Lexem::isFunction() const {
    return type == FUNCTION;
}

// Проверка, является ли скобкой
bool Lexem::isParenthesis() const {
    return type == LEFT_PAREN  type == RIGHT_PAREN;
}

// Проверка, является ли числом
bool Lexem::isNumber() const {
    return type == NUMBER;
}

// Оператор вывода
std::ostream& operator<<(std::ostream& os, const Lexem& lexem) {
    os << lexem.value;
    return os;
}

// Оператор ввода
std::istream& operator>>(std::istream& is, Lexem& lexem) {
    std::string value;
    is >> value;

    // Логика для определения типа лексемы
    if (value == "+"  value == "-"   value == "*"  value == "/") {
        lexem.type = OPERATOR;
    }
    else if (value == "sin"  value == "cos"  value == "tg"  value == "ctg") {
        lexem.type = FUNCTION;
    }
    else if (value == "(") {
        lexem.type = LEFT_PAREN;
    }
    else if (value == ")") {
        lexem.type = RIGHT_PAREN;
    }
    else { // Число
        lexem.type = NUMBER;
    }

    lexem.value = value;
    lexem.priority = 0; // Можно настроить приоритет, если нужно

    return is;
}

// Конструктор PostfixConverter
PostfixConverter::PostfixConverter(const TDynamicVector<Lexem>& tokens)
    : infixTokens(tokens) {}

// Получение приоритета оператора
int PostfixConverter::getPriority(const Lexem& op) const {
    if (op.type == OPERATOR) {
        if (op.value == "+"  op.value == "-") return 1;
        if (op.value == "*"  op.value == "/") return 2;
    }
    if (op.type == FUNCTION) {
        return 3; // Функции всегда имеют самый высокий приоритет
    }
    return 0;
}

// Преобразование в постфиксную нотацию
void PostfixConverter::toPostfix() {
    TDynamicVector<Lexem> stack;
    for (size_t i = 0; i < infixTokens.size(); ++i) {
        Lexem token = infixTokens[i];  // Создаем копию объекта (не const!)

        if (token.isNumber()) {
            postfixTokens.push_back(token);
        }
        else if (token.isFunction()) {
            stack.push_back(token);
        }
        else if (token.isOperator()) {
            if (token.value == "-" && (i == 0  infixTokens[i - 1].isOperator()
                infixTokens[i - 1].type == LEFT_PAREN)) {
                // Если минус унарный, меняем приоритет в копии
                token.priority = 3;  // Устанавливаем более высокий приоритет для унарного минуса
                stack.push_back(token);
            }
            else {
                // Для обычного оператора
                while (!stack.empty() && getPriority(stack.back()) >= getPriority(token)) {
                    postfixTokens.push_back(stack.back());
                    stack.pop_back();
                }
                stack.push_back(token);
            }
        }
        else if (token.type == LEFT_PAREN) {
            stack.push_back(token);
        }
        else if (token.type == RIGHT_PAREN) {
            while (!stack.empty() && stack.back().type != LEFT_PAREN) {
                postfixTokens.push_back(stack.back());
                stack.pop_back();
            }
            if (stack.empty()) {
                throw std::invalid_argument("Mismatched parentheses: missing left parenthesis");
            }
            stack.pop_back(); // Убираем левую скобку из стека
        }
    }

    while (!stack.empty()) {
        if (stack.back().type == LEFT_PAREN) {
            throw std::invalid_argument("Mismatched parentheses: missing right parenthesis");
        }
        postfixTokens.push_back(stack.back());
        stack.pop_back();
    }
}

// Вывод постфиксного выражения
void PostfixConverter::printPostfix(std::ostream& os) const {
    for (size_t i = 0; i < postfixTokens.size(); ++i) {
        os << postfixTokens[i] << " ";
    }
    os << std::endl;
}

// Вычисление результата
double PostfixConverter::evaluate() const {
    TDynamicVector<double> stack;

    // Перебираем все лексемы в постфиксной записи
    for (size_t i = 0; i < postfixTokens.size(); ++i) {
        const Lexem& token = postfixTokens[i];

        if (token.isNumber()) {
            // Если токен — это число, преобразуем его в double и пушим в стек
            stack.push_back(std::stod(token.value));
        }
        else if (token.isFunction()) {
            // Если токен — это функция
            if (stack.empty()) {
                throw std::invalid_argument("Insufficient arguments for function");
            }
            double arg = stack.back();
            stack.pop_back();

            // Выполняем функцию с аргументом
            if (token.value == "sin") {
                stack.push_back(std::sin(arg));
            }
            else if (token.value == "cos") {
                stack.push_back(std::cos(arg));
            }
            else if (token.value == "tg") {
                stack.push_back(std::tan(arg));
            }
            else if (token.value == "ctg") {
                // Для ctg - деление на ноль
                if (std::tan(arg) == 0.0) {
                    throw std::invalid_argument("Division by zero in ctg function");
                }
                stack.push_back(1.0 / std::tan(arg));
            }
            else {
                throw std::invalid_argument("Unknown function: " + token.value);
            }
        }
        else if (token.isOperator()) {
            // Если токен — это оператор
            if (stack.size() < 2 && token.value != "-") {
                throw std::invalid_argument("Insufficient arguments for operator");
            }

            if (token.value == "-") {
                // Унарный минус
                if (stack.size() == 0  (stack.size() == 1 && token.priority == 3)) {
                    // Если стек пуст или мы только что встретили унарный минус
                    double operand = stack.back();
                    stack.pop_back();
                    stack.push_back(-operand);  // Применяем унарный минус
                }
                else {
                    // Бинарный минус
                    double b = stack.back();
                    stack.pop_back();
                    double a = stack.back();
                    stack.pop_back();
                    stack.push_back(a - b);
                }
            }
            else {
                // Бинарные операторы: +, *, /
                double b = stack.back();
                stack.pop_back();
                double a = stack.back();
                stack.pop_back();

                if (token.value == "+") {
                    stack.push_back(a + b);
                }
                else if (token.value == "*") {
                    stack.push_back(a * b);
                }
                else if (token.value == "/") {
                    if (b == 0.0) {
                        throw std::invalid_argument("Division by zero");
                    }
                    stack.push_back(a / b);
                }
                else {
                    throw std::invalid_argument("Unknown operator: " + token.value);
                }
            }
        }
    }

    // Если в стеке остался не один элемент, это ошибка
    if (stack.size() != 1) {
        throw std::invalid_argument("Invalid expression");
    }

    // Возвращаем результат, который остался в стеке
    return stack.back();
}