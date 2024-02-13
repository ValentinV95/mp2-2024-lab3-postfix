#include "arithmetic.h"
#include <gtest.h>
TEST(TPostfixCreation, FromSingleNumber) {
	TPostfix postfix("12345");
	EXPECT_EQ("12345", postfix.get_infix());
	ASSERT_NO_THROW(postfix.to_postfix());
}

TEST(TPostfixCreation, FromValidExpression) {
	TPostfix postfix("1+2+3+4+5");
	ASSERT_NO_THROW(postfix.to_postfix());
}

TEST(TPostfixCreation, FromValidVariable) {
	TPostfix postfix("x1");
	ASSERT_NO_THROW(postfix.to_postfix());
}

TEST(TPostfixCreation, FromVariableAndNumber) {
	TPostfix postfix("x1+123");
	ASSERT_NO_THROW(postfix.to_postfix());
}


TEST(TPostfixCalculation, CalculateIsCorrect) {
	TPostfix postfix("1+2+3+4+5");
	map<string, double> v;
	postfix.to_postfix();
	EXPECT_NEAR(15.0, postfix.calculate(v), 0.01);
}

TEST(TPostfixCalculation, CalculateIsCorrectTwo) {
	TPostfix postfix("((2+3)*9-8)/5");
	map<string, double> v;
	postfix.to_postfix();
	EXPECT_NEAR(7.4, postfix.calculate(v), 0.01);
}

TEST(TPostfixErrorHandling, ThrowsWhenNumberIsDot) {
	TPostfix postfix(".");
	ASSERT_ANY_THROW(postfix.to_postfix());
}
