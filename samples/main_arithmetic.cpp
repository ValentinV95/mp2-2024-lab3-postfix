
#include <iostream>
#include "arithmetic.h"
#include <stdexcept>


TDynamicVector<Lexem> tokenizeExpression(const char* expression) {
    TDynamicVector<Lexem> tokens;
    size_t length = std::strlen(expression);
    bool isPreviousOperator = true;  // Считываем как унарный минус, если он идет первым

    for (size_t i = 0; i < length; ++i) {
        char currentChar = expression[i];
        Lexem token;

        if (currentChar >= '0' && currentChar <= '9') {
            // Считываем число, в том числе с плавающей запятой и научной нотацией
            size_t j = i;
            bool hasDecimalPoint = false;
            bool hasExponent = false;

            // Считываем цифры до точки или экспонента
            while (j < length && (expression[j] >= '0' && expression[j] <= '9' || expression[j] == '.')) {
                if (expression[j] == '.') {
                    if (hasDecimalPoint) break;  // Если точка уже была, завершаем
                    hasDecimalPoint = true;
                }
                j++;
            }

            // Обрабатываем экспоненциальную часть (e или E)
            if (j < length && (expression[j] == 'e' || expression[j] == 'E')) {
                hasExponent = true;
                j++;  // Пропускаем 'e' или 'E'

                // Пропускаем знак экспоненты
                if (j < length && (expression[j] == '+' || expression[j] == '-')) {
                    j++;
                }

                // Считываем цифры экспоненты
                while (j < length && expression[j] >= '0' && expression[j] <= '9') {
                    j++;
                }
            }

            token.value = std::string(expression + i, j - i);
            token.type = NUMBER;
            tokens.push_back(token);
            i = j - 1;
            isPreviousOperator = false;
        }
        else if (currentChar == '-' || currentChar == '+' || currentChar == '*' || currentChar == '/') {
            // Это оператор
            token.value = std::string(1, currentChar);
            if (isPreviousOperator && currentChar == '-') {
                token.type = UNARY_MINUS;  // Унарный минус
            }
            else {
                token.type = OPERATOR;  // Обычный оператор
            }
            tokens.push_back(token);
            isPreviousOperator = true;  // Следующий символ может быть числом или переменной
        }
        else if (currentChar == '(') {
            token.value = "(";
            token.type = LEFT_PAREN;
            tokens.push_back(token);
            isPreviousOperator = true;  // После открывающей скобки может идти оператор
        }
        else if (currentChar == ')') {
            token.value = ")";
            token.type = RIGHT_PAREN;
            tokens.push_back(token);
            isPreviousOperator = false;  // После закрывающей скобки не может быть оператора
        }
        else if (currentChar >= 'a' && currentChar <= 'z' || currentChar >= 'A' && currentChar <= 'Z') {
            // Считываем переменные
            size_t j = i;
            while (j < length && (expression[j] >= 'a' && expression[j] <= 'z' || expression[j] >= 'A' && expression[j] <= 'Z')) ++j;
            token.value = std::string(expression + i, j - i);
            token.type = VARIABLE;
            tokens.push_back(token);
            i = j - 1;
            isPreviousOperator = false;
        }
        else {
            // Пропускаем все остальные символы (например, пробелы)
        }
    }

    return tokens;
}

int main() noexcept {
    char expression[256];
    TDynamicVector<Variable> variables;

    // Ввод переменных
    int numVars;
    std::cout << "Enter the number of variables: ";
    std::cin >> numVars;

    // Проверка на отрицательное число
    if (numVars < 0) {
        std::cerr << "Error: Number of variables cannot be negative!" << std::endl;
        return 1;
    }

    if (std::cin.fail()) {
        std::cerr << "Error: Invalid input!" << std::endl;
        return 1;
    }


    // Если переменных больше 0, пропускаем символ новой строки
    if (numVars > 0) {
        std::cin.ignore();  // Пропускаем символ новой строки после ввода числа
    }

    for (size_t i = 0; i < numVars; ++i) {
        Variable var;
        std::cout << "Enter variable name: ";
        std::cin >> var.name;
        std::cout << "Enter variable value: ";
        std::cin >> var.value;

        if (std::cin.fail()) {
            std::cerr << "Error: Invalid variable value input!" << std::endl;
            return 1;
        }

        variables.push_back(var);
    }

    // После ввода переменных очищаем буфер, чтобы избежать лишних символов новой строки
    std::cin.ignore();  // Очистка буфера перед вводом выражения

    // Ввод арифметического выражения
    std::cout << "Enter an arithmetic expression: ";
    std::cin.getline(expression, 256);  // Считываем строку с выражением

    // Проверка на пустое выражение
    if (expression[0] == '\0') {
        std::cerr << "Error: Empty expression!" << std::endl;
        return 1;
    }

    // Токенизируем строку
    TDynamicVector<Lexem> tokens = tokenizeExpression(expression);

    // Проверка полученных токенов
    if (tokens.size() == 0) {
        std::cerr << "Error: No tokens generated! Expression might be invalid." << std::endl;
        return 1;
    }

    /*
    // Отладочная информация о токенах
   std::cout << "Tokens generated: " << std::endl;
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
        case UNARY_MINUS:
            std::cout << "UNARY_MIN";
            break;
        default:
            std::cout << "UNKNOWN";
            break;
        }
        std::cout << std::endl;
    }
    */


    // Создаём объект для преобразования в постфиксную запись
    PostfixConverter converter(tokens);

    try {
        // Преобразуем выражение в постфиксную нотацию
        converter.toPostfix();

        // Устанавливаем переменные в PostfixConverter
        converter.setVariables(variables);

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