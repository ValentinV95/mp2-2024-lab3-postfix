#include "lexem.h"

Lexeme::Lexeme(int t, const std::string& v) {
    type_ = t;
    value_ = v;
    if (type_ == 1) {
        num = StringToDouble_1(v);
    }
    else {
        num = 0.0;
    }
}

double Lexeme::number() const {
    return num;
}

void Lexeme::setnumber(double n) {
    num = n;
}

int Lexeme::type() const {
    return type_;
}

std::string Lexeme::value() const {
    return value_;
}

std::string Lexeme::toString() const {
    return "Type: " + intToString(type_) + ", Value: " + value_;
}

bool Lexeme::operator==(const Lexeme& other) const {
    return (type_ == other.type_) && (value_ == other.value_);
}

bool Lexeme::operator!=(const Lexeme& other) const {
    return !(*this == other);
}

int Lexeme::precedence() const {
    if (type_ == 2) {
        if (value_ == "+" || value_ == "-") return 1;
        if (value_ == "*" || value_ == "/") return 2;
        if (value_ == "^") return 3;
    }
    else if (type_ == 7) {
        return 1;
    }
    return 0;
}
std::string Lexeme::intToString(int t) const {
        switch (t) {
        case 0: return "UNKNOWN";
        case 1: return "NUMBER";
        case 2: return "OPERATOR";
        case 3: return "LEFT";
        case 4: return "RIGHT";
        case 5: return "FUNCTION";
        case 6: return "VARIABLE";
        case 7: return "UNAR MINUS";
        default: return "UNKNOWN";
        }
}
