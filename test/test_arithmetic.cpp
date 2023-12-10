// тесты для вычисления арифметических выражений

#include "arithmetic.h"
#include <gtest.h>

TEST(TPostfix, can_create_TPostfix_from_valid_string) {
	ASSERT_NO_THROW (TPostfix str("1"));
}

TEST(TPostfix, throws_when_number_is_invalid) {
	ASSERT_ANY_THROW(TPostfix str("."));
	ASSERT_ANY_THROW(TPostfix str("1.2.3"));
	ASSERT_ANY_THROW(TPostfix str("e+1"));
	ASSERT_ANY_THROW(TPostfix str("1.2e"));
	ASSERT_ANY_THROW(TPostfix str("1.2e+"));
	ASSERT_ANY_THROW(TPostfix str("1.2e+0"));
	ASSERT_ANY_THROW(TPostfix str("1.2e+1.5"));
	ASSERT_ANY_THROW(TPostfix str("1.2e+1e+2"));
}

TEST(TPostfix, throws_when_brackets_next_to_each_other) {
	ASSERT_ANY_THROW (TPostfix str("()"));
}

TEST(TPostfix, throws_when_different_number_of_opening_and_closing_brackets) {
	ASSERT_ANY_THROW (TPostfix str("((5)-3"));
}

TEST(TPostfix, throws_when_brackets_are_placed_incorrectly) {
	ASSERT_ANY_THROW(TPostfix str("5)+(3"));
}

TEST(TPostfix, throws_when_after_function_there_are_no_brackets) {
	ASSERT_ANY_THROW(TPostfix str("sin6"));
}

TEST(TPostfix, throws_when_two_operators_stays_in_a_row) {
	ASSERT_ANY_THROW(TPostfix str("3+-2"));
}

TEST(TPostfix, throws_when_variable_name_is_invalid) {
	ASSERT_ANY_THROW(TPostfix str("xf"));
	ASSERT_ANY_THROW(TPostfix str("xx"));
	ASSERT_ANY_THROW(TPostfix str("123x"));
	ASSERT_ANY_THROW(TPostfix str("x1.2"));
	ASSERT_ANY_THROW(TPostfix str("x1e"));
}

TEST(TPostfix, throws_when_string_is_invalid) {
	ASSERT_ANY_THROW(TPostfix str("abcdefg"));
}

TEST(TPostfix, throws_when_two_operators_stays_in_row) {
	ASSERT_ANY_THROW(TPostfix str("3+-2"));
}

TEST(TPostfix, throws_when_string_ends_with_an_operator) {
	ASSERT_ANY_THROW(TPostfix str("3+"));
}

TEST(TPostfix, throws_when_string_starts_with_an_operator_excluding_minus) {
	ASSERT_ANY_THROW(TPostfix str("+3"));
}

TEST(TPostfix, throws_when_after_closing_brackets_stays_an_operand) {
	ASSERT_ANY_THROW(TPostfix str("(3+2)5"));
}

TEST(TPostfix, throws_when_before_closing_brackets_stays_an_operator) {
	ASSERT_ANY_THROW(TPostfix str("(3+)"));
}

TEST(TPostfix, throws_when_before_opening_brackets_stays_an_operand) {
	ASSERT_ANY_THROW(TPostfix str("2(3)"));
}

TEST(TPostfix, throws_when_after_opening_brackets_stays_an_operator) {
	ASSERT_ANY_THROW(TPostfix str("(+3)"));
}

TEST(TPostfix, throws_when_between_functions_and_other_operand_there_are_no_operators) {
	ASSERT_ANY_THROW(TPostfix str("5sin(0)"));
}

TEST(TPostfix, can_count_TPostfix) {
	TPostfix str("1");
	ASSERT_NO_THROW(str.count());
}

TEST(TPostfix, count_from_valid_namber_is_correct) {
	TPostfix str("0.24e+2");
	EXPECT_EQ(true, str.count()-24< pow(10,-8));
}

TEST(TPostfix, count_is_correct) {
	TPostfix str("3+10-2*6/(-3)+((5))-(-sin(1))+tan(3)-cos(2)*cot(1)+log(2)*exp(1)");
	EXPECT_EQ(true, str.count()-(3 + 10 - 2 * 6 / (-3) + 5 - (-sin(1)) + tan(3) - cos(2) * 1 / tan(1) + log(2) * exp(1))< pow(10,-8));
}