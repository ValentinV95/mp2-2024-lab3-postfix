
#include "arithmetic.h"
#include <cmath>      // Для математических функций, например, для sin(), cos(), sqrt()
#include <stdexcept>  // Для исключений, например, для std::invalid_argument

// Функция для проверки, является ли символ цифрой
bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

// Реализация конструктора Lexem
Lexem::Lexem(LexemType t, const std::string& v, int p) : type(t), value(v), priority(p) {}

bool Lexem::isOperator() const {
    return type == OPERATOR;
}

bool Lexem::isFunction() const {
    return type == FUNCTION;
}

bool Lexem::isVariable() const {
    return type == VARIABLE;
}

bool Lexem::isNumber() const {
    return type == NUMBER;
}

bool Lexem::isUnary() const {
    return type == UNARY_MINUS;
}

bool Lexem::isParenthesis() const {
    return type == LEFT_PAREN || type == RIGHT_PAREN;
}

// Перегрузка оператора вывода
std::ostream& operator<<(std::ostream& os, const Lexem& lexem) {
    os << lexem.value;
    return os;
}

// Перегрузка оператора ввода
std::istream& operator>>(std::istream& is, Lexem& lexem) {
    std::string value;
    is >> value;

    // Логика для определения типа лексемы

    if (value == "-" &&
        (lexem.value.empty() || lexem.value.back() == '(' ||
            lexem.value.back() == '+' || lexem.value.back() == '-' ||
            lexem.value.back() == '*' || lexem.value.back() == '/')) {
        lexem.type = UNARY_MINUS; // Унарный минус
    }
    else if (value == "+" || value == "-" || value == "*" || value == "/") {
        lexem.type = OPERATOR; // Бинарный оператор
    }
    else if (value == "sin" || value == "cos" || value == "tg" || value == "ctg") {
        lexem.type = FUNCTION;
    }
    else if (value == "(") {
        lexem.type = LEFT_PAREN;
    }
    else if (value == ")") {
        lexem.type = RIGHT_PAREN;
    }
    else if (value.size() > 0 && (value[0] >= 'a' && value[0] <= 'z') || (value[0] >= 'A' && value[0] <= 'Z') || value[0] == '_') {
        lexem.type = VARIABLE; // Переменная
    }
    else {
        lexem.type = NUMBER; // Число
    }

    lexem.value = value;
    lexem.priority = 0;
    return is;
}

// Реализация класса PostfixConverter
PostfixConverter::PostfixConverter(const TDynamicVector<Lexem>& tokens) : infixTokens(tokens) {}

int PostfixConverter::getPriority(const Lexem& op) const {
    if (op.isUnary()) return 3;  // Унарный минус имеет самый высокий приоритет
    if (op.value == "+" || op.value == "-") return 1;
    if (op.value == "*" || op.value == "/") return 2;
    return 0;
}

void PostfixConverter::toPostfix() {

    TDynamicVector<Lexem> stack;

    for (const Lexem& token : infixTokens) {
        if (token.isNumber()) {
            // Если это число, добавляем в постфикс
            postfixTokens.push_back(token);
        }
        else if (token.isVariable()) {
            // Если это переменная, добавляем в постфикс
            postfixTokens.push_back(token);
        }
        else if (token.isOperator()) {
            // Если это оператор, обрабатываем с учетом приоритетов
            while (!stack.empty() && stack.back().type != LEFT_PAREN &&
                getPriority(stack.back()) >= getPriority(token)) {
                postfixTokens.push_back(stack.back());
                stack.pop_back();
            }
            stack.push_back(token);
        }
        else if (token.isUnary()) {
            // Унарный минус, например, обработаем как оператор
            stack.push_back(token);
        }
        else if (token.isParenthesis()) {
            // Обработка скобок
            if (token.type == LEFT_PAREN) {
                stack.push_back(token);
            }
            else {
                while (!stack.empty() && stack.back().type != LEFT_PAREN) {
                    postfixTokens.push_back(stack.back());
                    stack.pop_back();
                }
                stack.pop_back();  // Убираем открывающую скобку
            }
        }
    }

    // Добавляем все оставшиеся операторы в стек в конец
    while (!stack.empty()) {
        postfixTokens.push_back(stack.back());
        stack.pop_back();
    }
}


void PostfixConverter::printPostfix(std::ostream& os) const {
    for (const Lexem& token : postfixTokens) {
        os << token.value << " ";
    }
    os << std::endl;
}
// Преобразование строки в число
double PostfixConverter::simpleStringToDouble(const std::string& str) {
    double result = 0.0;
    bool isNegative = false;
    size_t i = 0;

    // Обработка отрицательных чисел
    if (str[i] == '-') {
        isNegative = true;
        i++;
    }
    else if (str[i] == '+') {
        i++;
    }

    // Обработка целой части
    while (i < str.length() && isDigit(str[i])) {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    // Обработка десятичной точки и дробной части
    if (i < str.length() && str[i] == '.') {
        i++;
        double decimalPlace = 0.1;
        while (i < str.length() && isDigit(str[i])) {
            result += (str[i] - '0') * decimalPlace;
            decimalPlace /= 10;
            i++;
        }
    }

    // Обработка экспоненты
    if (i < str.length() && (str[i] == 'e' || str[i] == 'E')) {
        i++;
        bool expIsNegative = false;
        if (i < str.length() && str[i] == '-') {
            expIsNegative = true;
            i++;
        }
        else if (i < str.length() && str[i] == '+') {
            i++;
        }

        int exponent = 0;
        while (i < str.length() && isDigit(str[i])) {
            exponent = exponent * 10 + (str[i] - '0');
            i++;
        }

        // Применяем экспоненту
        double expValue = 1.0;
        for (int j = 0; j < exponent; ++j) {
            expValue *= 10.0;

        }
        if (expIsNegative) {
            result /= expValue;
        }
        else {
            result *= expValue;
        }
    }

    // Применяем знак минус, если необходимо
    if (isNegative) {
        result = -result;
    }

    return result;
}

void PostfixConverter::setVariables(const TDynamicVector<Variable>& vars) {
    variables = vars;  // Копируем переменные
}

// Метод для вычисления выражения
double PostfixConverter::evaluate() {
    TDynamicVector<double> stack;

    for (const Lexem& token : postfixTokens) {
        if (token.isNumber()) {
            stack.push_back(simpleStringToDouble(token.value));
        }
        else if (token.isVariable()) {
            auto it = std::find_if(variables.begin(), variables.end(),
                [&token](const Variable& var) { return var.name == token.value; });

            if (it != variables.end()) {
                stack.push_back(it->value);
            }
            else {
                throw std::invalid_argument("Undefined variable: " + token.value);
            }
        }
        else if (token.isUnary()) {
            if (stack.empty()) throw std::invalid_argument("Insufficient arguments for unary minus");
            double operand = stack.back();
            stack.pop_back();
            stack.push_back(-operand);
        }
        else if (token.isOperator()) {
            if (stack.size() < 2) throw std::invalid_argument("Insufficient arguments for operator");
            double right = stack.back(); stack.pop_back();
            double left = stack.back(); stack.pop_back();

            if (token.value == "+") stack.push_back(left + right);
            else if (token.value == "-") stack.push_back(left - right);
            else if (token.value == "*") stack.push_back(left * right);
            else if (token.value == "/") {
                if (right == 0) throw std::invalid_argument("Division by zero");
                stack.push_back(left / right);
            }
        }
    }

    if (stack.size() != 1) throw std::invalid_argument("Invalid expression");
    return stack.back();
}