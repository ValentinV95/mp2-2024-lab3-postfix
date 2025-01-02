#include <gtest.h>
#include "arithmetic.h"

TEST(ArithmeticExpression, can_be_created)
{
	ASSERT_NO_THROW(ArithmeticExpression AE);
}

TEST(ArithmeticExpression, is_empty_upon_default_creation)
{
	ArithmeticExpression AE;
	Vec<lexem*>* VL = AE.GetPostfix();
	stringstream sstr;
	string s;
	s = AE.GetInfix();
	EXPECT_EQ(s, "No expression yet");
	EXPECT_EQ(VL->GetSize(), 0);
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
}

TEST(ArithmeticExpression, can_be_created_with_string)
{
	ASSERT_NO_THROW(ArithmeticExpression AE("a+b"));
}

TEST(ArithmeticExpression, has_right_fields_upon_creation_by_string)
{
	ArithmeticExpression AE("a+b");
	string s(AE.GetInfix());
	Vec<lexem*>* VL = AE.GetPostfix();
	EXPECT_EQ(s, "a+b");
	EXPECT_EQ(VL->GetSize(), 3);
	EXPECT_EQ(dynamic_cast<variable*>((*VL)[0])->GetName(), "a");
	EXPECT_EQ(dynamic_cast<variable*>((*VL)[1])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<operation*>((*VL)[2])->GetId(), 2);
	ArithmeticExpression AE1("  2.45e-1   -b  ");
	s = AE1.GetInfix();
	VL = AE1.GetPostfix();
	EXPECT_EQ(s, "2.45e-1 -b");
	EXPECT_EQ(VL->GetSize(), 3);
	EXPECT_DOUBLE_EQ(dynamic_cast<constant*>((*VL)[0])->GetVal(), 2.45e-1);
	EXPECT_EQ(dynamic_cast<variable*>((*VL)[1])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<operation*>((*VL)[2])->GetId(), 3);
	ArithmeticExpression AE2("pi^sin( x ) ");
	s = AE2.GetInfix();
	VL = AE2.GetPostfix();
	EXPECT_EQ(s, "pi^sin( x )");
	EXPECT_EQ(VL->GetSize(), 4);
	EXPECT_EQ(dynamic_cast<variable*>((*VL)[0])->GetName(), "pi");
	EXPECT_EQ(dynamic_cast<variable*>((*VL)[1])->GetName(), "x");
	EXPECT_EQ(dynamic_cast<operation*>((*VL)[2])->GetId(), 10);
	EXPECT_EQ(dynamic_cast<operation*>((*VL)[3])->GetId(), 6);
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
}

TEST(ArithmeticExpression, can_be_rebuilt)
{
	ArithmeticExpression AE("a+b");
	Vec<lexem*>* VL = AE.GetPostfix();
	string s;
	AE.Rebuild("c*x");
	s = AE.GetInfix();
	EXPECT_EQ(s, "c*x");
	EXPECT_EQ(VL->GetSize(), 3);
	EXPECT_EQ(dynamic_cast<variable*>((*VL)[0])->GetName(), "c");
	EXPECT_EQ(dynamic_cast<variable*>((*VL)[1])->GetName(), "x");
	EXPECT_EQ(dynamic_cast<operation*>((*VL)[2])->GetId(), 4);
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
}

TEST(ArithmeticExpression, can_calculate_constant_expressions)
{
	ArithmeticExpression AE("25.0");
	double res;
	ASSERT_NO_THROW(res = AE.Calculate());
	EXPECT_DOUBLE_EQ(res, 25.0);
	AE.Rebuild("5.0+16.5^(2*-sin(1.0))");
	ASSERT_NO_THROW(res = AE.Calculate());
	EXPECT_DOUBLE_EQ(res, 5.0 + pow(16.5, 2.0 * -sin(1.0)));
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
}

TEST(ArithmeticExpression, can_calculate_expressions_with_pi_and_e_constants)
{
	ArithmeticExpression AE("pi*e");
	double res;
	ASSERT_NO_THROW(res = AE.Calculate());
	EXPECT_DOUBLE_EQ(res, 2.0 * asin(1.0) * exp(1.0));
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
}

TEST(ArithmeticExpression, can_calculate_expressions_with_initialised_variables)
{
	ArithmeticExpression AE("x*y/(e^(z-b))");
	double res;
	variable::Init(2, 2.5);
	variable::Init(3, -3.5);
	variable::Init(4, 0.25);
	variable::Init(5, 1);
	ASSERT_NO_THROW(res = AE.Calculate());
	EXPECT_DOUBLE_EQ(res, 2.5*-3.5/exp(0.25-1.0));
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
}

TEST(ArithmeticExpression, calculatin_default_AE_throws)
{
	ArithmeticExpression AE;
	ASSERT_ANY_THROW(AE.Calculate());
}

TEST(ArithmeticExpression, can_be_printed)
{
	ArithmeticExpression AE;
	string s(AE.GetInfix());
	EXPECT_EQ(s, "No expression yet");
	s = AE.PrintPostfix();
	EXPECT_EQ(s, "");
	AE.Rebuild("a / b");
	s = AE.GetInfix();
	EXPECT_EQ(s, "a / b");
	s = AE.PrintPostfix();
	EXPECT_EQ(s, "a b /");
}