#include "arithmetic.h"
#include <gtest.h>

TEST(TCalc, FromSingleNumber) {
	TCalc calc("12345");
	EXPECT_EQ("12345", calc.get_infix());
	ASSERT_NO_THROW(calc.to_postfix());
}

TEST(TCalc, FromValidExpression) {
	TCalc calc("1+2+3+4+5");
	ASSERT_NO_THROW(calc.to_postfix());
}

TEST(TCalc, FromValidVariable) {
	TCalc calc("x1");
	ASSERT_NO_THROW(calc.to_postfix());
}

TEST(TCalc, FromVariableAndNumber) {
	TCalc calc("x1+123");
	ASSERT_NO_THROW(calc.to_postfix());
}

TEST(TCalc, CalculateIsCorrect) {
	TCalc calc("1+2+3+4+5");
	map<string, double> v;
	calc.to_postfix();
	EXPECT_NEAR(15.0, calc.calculate(v), 0.01);
}

TEST(TCalc, CalculateIsCorrectTwo) {
	TCalc calc("((2+3)*9-8)/5");
	map<string, double> v;
	calc.to_postfix();
	EXPECT_NEAR(7.4, calc.calculate(v), 0.01);
}

TEST(TCalc, ThrowsWhenNumberIsDot) {
	TCalc calc(".");
	ASSERT_ANY_THROW(calc.to_postfix());
}
