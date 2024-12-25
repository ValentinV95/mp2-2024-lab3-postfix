#pragma once
#include <string>

class Lexeme {
private: 
    int type_;
    std::string value_;
    double num;
public:
    Lexeme(int t = 0, const std::string& v = "") : type_(t), value_(v) {}
    
    double number() {
        return num;
    }

    void setnumber(double n) {
        num = n;
    }

    int type() const {
        return type_;
    }

    std::string value() const {
        return value_;
    }

    std::string toString() const {
        return "Type: " + intToString(type_) + ", Value: " + value_;
    }

    bool operator==(const Lexeme& other) const {
        return (type_ == other.type_) && (value_ == other.value_);
    }

    bool operator!=(const Lexeme& other) const {
        return !(*this == other);
    }

    int precedence() const {
        if (type_ == 2) { 
            if (value_ == "+" || value_ == "-") return 1;
            if (value_ == "*" || value_ == "/") return 2;
            if (value_ == "^") return 3; 
        }
        return 0; 
    }

private:
    std::string intToString(int t) const {
        switch (t) {
        case 1: return "NUMBER";
        case 2: return "OPERATOR";
        case 3: return "LEFT";
        case 4: return "RIGHT";
        case 5 : return "FUNCTION";
        case 6: return "VARIABLE";
        default: return "UNKNOWN";
        }
    }
};