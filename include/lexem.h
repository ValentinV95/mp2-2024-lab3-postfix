#pragma once
#include "StringToDouble.h"

class Lexeme {
private: 
    int type_;
    std::string value_;
    double num;

public:
    Lexeme(int t = 0, const std::string& v = "");

    double number() const;

    void setnumber(double n);

    int type() const;

    std::string value() const;

    std::string toString() const;

    bool operator==(const Lexeme& other) const;

    bool operator!=(const Lexeme& other) const;

    int precedence() const;

private:
    std::string intToString(int t) const;
};