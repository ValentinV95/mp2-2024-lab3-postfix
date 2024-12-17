#include <iostream>
#include "arithmetic.h"

// Функция для разделения строки на лексемы
TDynamicVector<Lexem> tokenizeExpression(const char* expr) noexcept {
    TDynamicVector<Lexem> tokens;
    char token[256]; // Буфер для лексемы
    int tokenIndex = 0;
    bool prevWasOperatorOrParen = true; // Флаг для отслеживания унарного минуса

    for (size_t i = 0; expr[i] != '\0'; ++i) {
        char ch = expr[i];

        // Пропускаем пробелы
        if (ch == ' '  ch == '\t') {
            continue;
        }

        // Если это число (включая десятичные)
        if ((ch >= '0' && ch <= '9')  ch == '.') {
            tokenIndex = 0;
            while ((ch >= '0' && ch <= '9')  ch == '.') {
                token[tokenIndex++] = ch;
                ch = expr[++i];
            }
            --i; // Возвращаемся назад
            token[tokenIndex] = '\0';
            tokens.push_back(Lexem(NUMBER, token, 0)); // Число имеет приоритет 0
            prevWasOperatorOrParen = false;
        }
        // Если это функция (sin, cos, tg, ...)
        else if ((ch >= 'a' && ch <= 'z')  (ch >= 'A' && ch <= 'Z')) {
            tokenIndex = 0;
            while ((ch >= 'a' && ch <= 'z')  (ch >= 'A' && ch <= 'Z')) {
                token[tokenIndex++] = ch;
                ch = expr[++i];
            }
            --i;
            token[tokenIndex] = '\0';
            tokens.push_back(Lexem(FUNCTION, token, 3)); // Функция имеет высокий приоритет
            prevWasOperatorOrParen = true; // После функции ожидается аргумент
        }
        // Если это оператор
        else if (ch == '+'  ch == '-'  ch == '*'  ch == '/') {
            token[0] = ch;
            token[1] = '\0';

            // Проверяем, является ли это унарным минусом
            if (ch == '-' && prevWasOperatorOrParen) {
                tokens.push_back(Lexem(UNARY_MINUS, token, 3)); // Унарный минус с приоритетом 3
            }
            else {
                int priority = (ch == '+' || ch == '-') ? 1 : 2; // Приоритет: 1 для + и -, 2 для * и /
                tokens.push_back(Lexem(OPERATOR, token, priority));
            }
            prevWasOperatorOrParen = true; // После оператора или скобки ожидается число
        }
        // Если это скобка
        else if (ch == '(') {
            token[0] = ch;
            token[1] = '\0';
            tokens.push_back(Lexem(LEFT_PAREN, token, 0));
            prevWasOperatorOrParen = true; // После скобки ожидается выражение
        }
        else if (ch == ')') {
            token[0] = ch;
            token[1] = '\0';
            tokens.push_back(Lexem(RIGHT_PAREN, token, 0));
            prevWasOperatorOrParen = false; // После скобки не ожидается оператора
        }
        // Неизвестный символ
        else {
            std::cerr << "Unknown token: " << ch << std::endl;
            return tokens; // Возвращаем результат с ошибкой
        }
    }

    return tokens;
}

int main() noexcept {
    char expression[256];

    std::cout << "Enter an arithmetic expression: ";
    std::cin.getline(expression, 256);

    // Токенизируем строку
    TDynamicVector<Lexem> tokens = tokenizeExpression(expression);

    if (tokens.size() == 0) {
        std::cerr << "Error: No tokens generated!" << std::endl;
        return 1;
    }

    // Создаём объект для преобразования в постфиксную запись
    PostfixConverter converter(tokens);

    try {
        // Преобразуем выражение в постфиксную нотацию
        converter.toPostfix();

        // Печатаем результат
        std::cout << "Postfix notation: ";
        converter.printPostfix(std::cout);

        // Вычисляем результат
        double result = converter.evaluate();
        std::cout << "Result: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}