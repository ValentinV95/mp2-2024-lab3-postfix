#pragma once
#include <iostream>
#include "vector.h"  
#include "lexem.h"
#include "StringToDouble.h"

bool isSpace_(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

bool isDigit_(char c) {
    return c >= '0' && c <= '9';
}

bool isOperator_(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool isFunctionOrVariable(const std::string& input, size_t pos) {
    return (input[pos] >= 'a' && input[pos] <= 'z') || (input[pos] >= 'A' && input[pos] <= 'Z') || input[pos] == '_';
}

bool isFunctionOrVariable(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

std::string parseNumber(const std::string& input, size_t& pos) {
    std::string number = "";
    if (input[pos] == '.') {
        number += input[pos++];
        while (pos < input.size()) {
            if (isDigit_(input[pos])) {
                number += input[pos];
            }
            else {
                break;
            }
            pos++;
        }
        if (pos + 2 < input.size() && input[pos] == 'e' || input[pos] == 'E') {
            if (input[pos + 1] == '+' || input[pos+1] == '-') {
                if (pos + 2 >= input.size() || !isDigit_(input[pos + 2])) {
                    throw std::logic_error("Invalid exponent format at position " + std::to_string(pos + 2));
                }
                if (isDigit_(input[pos + 2])) {
                    number += input[pos];
                    number += input[pos+1];
                    number += input[pos+2];
                    pos += 3;
                    while (pos < input.size() && isDigit_(input[pos])) {
                        number += input[pos];
                        pos++;
                    }
                    if (input[pos] == '.') {
                        throw std::logic_error("The power of a number can only be an integer at position " + std::to_string(pos));
                    }
                }
            }
        }
    }
    else if (isDigit_(input[pos])) {
        number += input[pos];
        pos += 1;
        while (pos < input.size() && isDigit_(input[pos])) {
            number += input[pos];
            pos++;
        }
        if (input[pos] == '.') {
            number += input[pos++];
            while (pos < input.size()) {
                if (isDigit_(input[pos])) {
                    number += input[pos];
                }
                else {
                    break;
                }
                pos++;
            }
        }
        if (pos + 2 < input.size() && input[pos] == 'e' || input[pos] == 'E') {
            if (input[pos + 1] == '+' || input[pos + 1] == '-') {
                if (isDigit_(input[pos + 2])) {
                    number += input[pos];
                    number += input[pos + 1];
                    number += input[pos + 2];
                    pos += 3;
                    while (pos < input.size() && isDigit_(input[pos])) {
                        number += input[pos];
                        pos++;
                    }
                    if (input[pos] == '.') {
                        throw std::logic_error("The power of a number can only be an integer at position " + std::to_string(pos));
                    }
                }
            }
        }
    }
    return number;
}

size_t findFirstOf(const std::string& str, const std::string& chars) {
    for (size_t i = 0; i < str.size(); ++i) {
        for (size_t j = 0; j < chars.size(); ++j) {
            if (str[i] == chars[j]) {
                return i;
            }
        }
    }
    return std::string::npos; 
}

std::string parseFunction(const std::string& input, size_t& pos) {
    std::string function_name;
    int ind = pos;
    while (pos < input.size() && (isFunctionOrVariable(input, pos) || isDigit_(input[pos]))) {
        auto c = input[pos];
        if (isDigit_(c) && ind == pos) {
            throw std::logic_error("Var and func can't start with a digit at position " + std::to_string(pos));
        }
        function_name += input[pos];
        pos++;
    }
    return function_name;
}

Vector<Lexeme> parser(const std::string& input) {
    Vector<std::pair<std::string, double>> variables;
    Vector<Lexeme> lexems;
    size_t pos = 0;
    for (int i = 0; i < input.size(); i++) {
        auto c = input[i];
        if (!isDigit_(c) && !isSpace_(c) && !isOperator_(c) && !isFunctionOrVariable(c) && c != '(' && c != ')' && c!='.') {
            throw std::logic_error("Invalid symbol in position " + std::to_string(i));
        }
    }
    while (pos < input.size()) {
        while (pos < input.size() && isSpace_(input[pos])) {
            pos++;
        }
        if (pos >= input.size()) {
            break; 
        }

        if (pos < input.size() && (isDigit_(input[pos]) || input[pos] == '.')) {
            lexems.push_back(Lexeme(1, parseNumber(input, pos)));
        }
        
        else if (isOperator_(input[pos])) {
            if (lexems.getsize() && (lexems.back().type() == 1 || lexems.back().type() == 6 || lexems.back().type()==4))
            lexems.push_back(Lexeme(2, std::string(1, input[pos]))); 
            else  lexems.push_back(Lexeme(7, std::string(1, input[pos])));
            pos++;
        }
       
        else if (input[pos] == '(') {
            lexems.push_back(Lexeme(3, "(")); 
            pos++;
        }

        else if (input[pos] == ')') {
            lexems.push_back(Lexeme(4, ")")); 
            pos++;
        }
   
        else if (isFunctionOrVariable(input, pos)) {
            int t = 6;
            std::string function_name = parseFunction(input, pos);
            if (function_name == "log" || function_name == "exp" || function_name == "sin" || function_name == "cos" || function_name == "tan" || function_name == "cot" || function_name == "sec" || function_name == "csc") {
                t = 5;
            }
            lexems.push_back(Lexeme(t, function_name));
            if(t==6){
                bool f = 0;
                for (int i = 0; i < variables.getsize(); i++) {
                    if (function_name == variables[i].first) {
                        f = 1;
                        lexems.back().setnumber(variables[i].second);
                        break;
                    }
                }
                if (!f) {
                    std::string var;
                    std::cout << "Enter the value of the variable " << function_name << std::endl;
                    getline(std::cin, var);
                    variables.push_back({function_name, StringToDouble_1(var)});
                    lexems.back().setnumber(variables.back().second);
                }
            }
        }
        else {
            throw std::logic_error("Unexpected error at position " + std::to_string(pos));
        }
    }
    return lexems;
}
