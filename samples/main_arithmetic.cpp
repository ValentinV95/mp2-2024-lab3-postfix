
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
        if (ch == ' ' || ch == '\t') {
            continue;
        }

        // Если это число (включая десятичные)
        if ((ch >= '0' && ch <= '9') || ch == '.') {
            tokenIndex = 0;
            while ((ch >= '0' && ch <= '9') || ch == '.') {
                token[tokenIndex++] = ch;
                ch = expr[++i];
            }
            --i; // Возвращаемся назад
            token[tokenIndex] = '\0';
            tokens.push_back(Lexem(NUMBER, token, 0)); // Число имеет приоритет 0
            prevWasOperatorOrParen = false;
        }
        // Если это переменная или функция
        else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            tokenIndex = 0;
            while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
                token[tokenIndex++] = ch;
                ch = expr[++i];
            }
            --i;
            token[tokenIndex] = '\0';

            // Проверяем, является ли это функцией (смотрим на следующий символ)
            if (expr[i + 1] == '(') {
                // Это функция, добавляем с типом FUNCTION
                tokens.push_back(Lexem(FUNCTION, token, 3)); // Функция имеет высокий приоритет
            }
            else {
                // Это переменная, добавляем с типом VARIABLE
                tokens.push_back(Lexem(VARIABLE, token, 0)); // Переменная
            }

            prevWasOperatorOrParen = false;
        }


        // Если это оператор
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            token[0] = ch;
            token[1] = '\0';

            // Проверяем, является ли это унарным минусом
            if (ch == '-' && (prevWasOperatorOrParen || tokens.empty())) {
                std::string num = "-"; // Начинаем собирать число с унарным минусом
                i++; // Сдвигаем на следующий символ
                while (i < strlen(expr) && ((expr[i] >= '0' && expr[i] <= '9') || expr[i] == '.')) {
                    num += expr[i++]; // Собираем цифры и точку, если они есть
                }
                --i; // Возвращаемся назад, чтобы не пропустить следующий символ в выражении
                tokens.push_back(Lexem(NUMBER, num, 0)); // Добавляем число с унарным минусом
                prevWasOperatorOrParen = false; // После числа не должно быть оператора
            }
            else {
                int priority = (ch == '+' || ch == '-') ? 1 : 2; // Приоритет: 1 для + и -, 2 для * и /
                tokens.push_back(Lexem(OPERATOR, token, priority)); // Бинарный оператор
                prevWasOperatorOrParen = true; // После оператора ожидаем число или скобку
            }
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
    TDynamicVector<Variable> variables;

    // Ввод переменных
    size_t numVars;
    std::cout << "Enter the number of variables: ";
    std::cin >> numVars;
    std::cin.ignore();

    for (size_t i = 0; i < numVars; ++i) {
        Variable var;
        std::cout << "Enter variable name: ";
        std::cin >> var.name;
        std::cout << "Enter variable value: ";
        std::cin >> var.value;
        variables.push_back(var);
    }

    std::cout << "Enter an arithmetic expression: ";
    std::cin.ignore();
    std::cin.getline(expression, 256);

    // Токенизируем строку
    // Токенизируем строку
    TDynamicVector<Lexem> tokens = tokenizeExpression(expression);

    // Проверка полученных токенов
    for (const auto& token : tokens) {
        std::cout << "Token: " << token.value << ", Type: ";

        // Определяем тип токена
        switch (token.type) {
        case NUMBER:
            std::cout << "NUMBER";
            break;
        case FUNCTION:
            std::cout << "FUNCTION";
            break;
        case VARIABLE:
            std::cout << "VARIABLE";
            break;
        case OPERATOR:
            std::cout << "OPERATOR";
            break;
        case LEFT_PAREN:
            std::cout << "LEFT_PAREN";
            break;
        case RIGHT_PAREN:
            std::cout << "RIGHT_PAREN";
            break;
        default:
            std::cout << "UNKNOWN";
            break;
        }
        std::cout << std::endl;
    }

    // Проверка на пустоту
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