// тесты для вычисления арифметических выражений

#include "arithmetic.h"
#include <gtest.h>

TEST(TPostfix, can_get_correct_infix) {
	TPostfix postfix("12345");
	EXPECT_EQ("12345", postfix.get_infix());
}

TEST(TPostfix, can_create_TPostfix_from_valid_expression) {
	TPostfix postfix("12345");
	ASSERT_NO_THROW(postfix.to_postfix());
}

TEST(TPostfix, can_create_TPostfix_from_valid_variable) {
	TPostfix postfix("x1");
	ASSERT_NO_THROW(postfix.to_postfix());
}

TEST(TPostfix, can_create_with_variable_and_number) {
	TPostfix postfix("x1+123");
	ASSERT_NO_THROW(postfix.to_postfix());
}

TEST(TPostfix, calculate_is_correct) {
	TPostfix postfix("1+2+3+4+5");
	map<string, double> v;
	postfix.to_postfix();
	EXPECT_EQ(15, postfix.calculate(v));
}

TEST(TPostfix, can_create_TPostfix_is_valid_expression) {
	TPostfix postfix("1+2+3+4+5");
	ASSERT_NO_THROW(postfix.to_postfix());
}

TEST(TPostfix, throws_when_several_dot) {
	TPostfix postfix("1.2.3.4.5");
	ASSERT_ANY_THROW(postfix.to_postfix());
}

TEST(TPostfix, throws_when_there_is_nothing_after_e) {
	TPostfix postfix("1.234e");
	ASSERT_ANY_THROW(postfix.to_postfix());
}

TEST(TPostfix, throws_when_only_sign_after_e) {
	TPostfix postfix("1.234e-");
	ASSERT_ANY_THROW(postfix.to_postfix());
}

TEST(TPostfix, throws_when_it_is_not_natural_after_e) {
	TPostfix postfix("1.234e1.23");
	ASSERT_ANY_THROW(postfix.to_postfix());
}

TEST(TPostfix, throws_when_several_e) {
	TPostfix postfix("1.234e5e6");
	ASSERT_ANY_THROW(postfix.to_postfix());
}

TEST(TPostfix, throws_when_number_starts_with_e) {
	TPostfix postfix("e6");
	ASSERT_ANY_THROW(postfix.to_postfix());
}

TEST(TPostfix, throws_when_nothing_inside_the_brackets) {
	TPostfix postfix("()");
	ASSERT_ANY_THROW(postfix.to_postfix());
}

TEST(TPostfix, throws_when_no_opening_bracket) {
	TPostfix postfix("6+2)");
	ASSERT_ANY_THROW(postfix.to_postfix());
}

TEST(TPostfix, throws_when_no_closing_bracket) {
	TPostfix postfix("(6+2");
	ASSERT_ANY_THROW(postfix.to_postfix());
}

TEST(TPostfix, throws_when_variable_is_not_correct) {
	TPostfix postfix("xabc");
	ASSERT_ANY_THROW(postfix.to_postfix());
}

TEST(TPostfix, throws_when_operation_after_operation) {
	TPostfix postfix("12+-*345");
	ASSERT_ANY_THROW(postfix.to_postfix());
}