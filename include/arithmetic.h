// ���������� ������� � ������� ��� ���������� �������������� ���������

#ifndef ARITHMETIC_H
#define ARITHMETIC_H


#include <iostream>
#include <string>
#include <cmath>
#include "TDynamicVector.h"

//������������ ��� ����� ������
enum LexemType {
	NUMBER = 1, VARIABLE, FUNCTION, OPERATOR = 5, UNARY_MINUS = -2, LEFT_PAREN = 7, RIGHT_PAREN = -7
};

//����� lexem

struct Variable {
	std::string name;
	double value;
};


class Lexem {
public:
	LexemType type;
	std::string value;
	int priority;

	Lexem(LexemType t = NUMBER, const std::string& v = "", int p = 0);
	bool isOperator() const;
	bool isFunction() const;
	bool isParenthesis() const;
	bool isNumber() const;
	bool isUnary() const;
	bool isVariable() const;  // ����� ����� ��� �������� ����������

	// ���������� ���������� ����� � ������
	friend std::ostream& operator<<(std::ostream& os, const Lexem& lexem);
	friend std::istream& operator>>(std::istream& is, Lexem& lexem);
};

//����� ��� �������������� � �������� �������



class PostfixConverter {
private:
	TDynamicVector<Lexem> infixTokens;
	TDynamicVector<Lexem> postfixTokens;
	TDynamicVector<Variable> variables;  // ��� �������� ����������

	int getPriority(const Lexem& op) const;

public:
	PostfixConverter(const TDynamicVector<Lexem>& tokens);
	void setVariables(const TDynamicVector<Variable>& vars);  // ���������� ����������
	void toPostfix();
	void printPostfix(std::ostream& os = std::cout) const;
	double simpleStringToDouble(const std::string& str);
	double evaluate();
};

#endif