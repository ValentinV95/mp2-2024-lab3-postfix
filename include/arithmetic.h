#pragma once
#include "lexem.h"
#include "simple_math.h"

class ArithmeticExpression
{
private:
	string infix;
	Vec<lexem*> postfix;
	void ToPostfix();
public:
	ArithmeticExpression();
	ArithmeticExpression(string const& s);
	ArithmeticExpression(ArithmeticExpression const& AE);
	ArithmeticExpression(ArithmeticExpression&& AE);
	ArithmeticExpression& operator = (ArithmeticExpression const& AE);
	ArithmeticExpression& operator = (ArithmeticExpression&& AE);
	friend void swap(ArithmeticExpression& lhs, ArithmeticExpression& rhs)
	{
		swap(lhs.infix, rhs.infix);
		swap(lhs.postfix, rhs.postfix);
		return;
	}
	string GetInfix() const;
	void Rebuild(string const& s);
	/*friend ostream& operator << (ostream& ostr, ArithmeticExpression const& AE)
	{
		ostr << AE.PrintPostfix();
		return ostr;
	}
	friend istream& operator >> (istream& istr, ArithmeticExpression& AE)
	{
		string s;
		istr >> s;
		AE.Rebuild(s);
		return istr;
	}*/
	string PrintPostfix() const;
	double Calculate() const;
	Vec<lexem*>* GetPostfix() { return &postfix; };
};