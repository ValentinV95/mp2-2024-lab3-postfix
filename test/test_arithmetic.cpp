// тесты для вычисления арифметических выражений

#include "arithmetic.h"
#include <gtest.h>
#include <cmath>

// Проверка работоспособности
TEST(TPostfix, can_evaluate)
{
	TPostfix tp;
	ASSERT_NO_THROW(tp.evaluate("2+2"));
}

TEST(TPostfix, cant_process_empty_string)
{
	TPostfix tp;
	ASSERT_ANY_THROW(tp.evaluate(""));
	ASSERT_ANY_THROW(tp.evaluate("\n"));
	ASSERT_ANY_THROW(tp.evaluate("\t"));
}

TEST(TPostfix, can_evaluate_strings_with_spaces)
{
	TPostfix tp;
	EXPECT_NEAR(4.0, tp.evaluate("\t2 +\n2"), 1e-7);
}

TEST(TPostfix, throws_on_unexpected_token)
{
	TPostfix tp;
	ASSERT_ANY_THROW(tp.evaluate("sfhfsjhfsbdg"));
	ASSERT_ANY_THROW(tp.evaluate("4,0"));
	ASSERT_ANY_THROW(tp.evaluate("1x"));
	ASSERT_ANY_THROW(tp.evaluate("x"));
	ASSERT_ANY_THROW(tp.evaluate("x+1"));
	ASSERT_ANY_THROW(tp.evaluate("sin(,)"));
	ASSERT_ANY_THROW(tp.evaluate("4_+1"));
	ASSERT_ANY_THROW(tp.evaluate("с"));
}

// Проверка работоспособности операций
TEST(TPostfix, can_add)
{
	TPostfix tp;
	EXPECT_NEAR(4.0, tp.evaluate("2+2"), 1e-7);
}

TEST(TPostfix, can_subtract)
{
	TPostfix tp;
	EXPECT_NEAR(0.0, tp.evaluate("2-2"), 1e-7);
}

TEST(TPostfix, can_multiply)
{
	TPostfix tp;
	EXPECT_NEAR(40.0, tp.evaluate("2*20"), 1e-7);
}

TEST(TPostfix, can_divide)
{
	TPostfix tp;
	EXPECT_NEAR(1.0, tp.evaluate("2/2"), 1e-7);
}

TEST(TPostfix, can_raise_to_power)
{
	TPostfix tp;
	EXPECT_NEAR(8.0, tp.evaluate("2^3"), 1e-7);
}

TEST(TPostfix, can_use_unary_minus)
{
	TPostfix tp;
	EXPECT_NEAR(-3.0, tp.evaluate("-3"), 1e-7);
}

TEST(TPostfix, can_use_functions)
{
	TPostfix tp;
	EXPECT_NEAR(std::exp(1), tp.evaluate("exp 1"), 1e-7);
	EXPECT_NEAR(std::exp(1), tp.evaluate("exp(1)"), 1e-7);
}

// Проверка ввода чисел
TEST(TPostfix, can_enter_number_with_point)
{
	TPostfix tp;
	ASSERT_NEAR(2.123, tp.evaluate("2.123"), 1e-7);
	ASSERT_NEAR(0.123, tp.evaluate("0.123"), 1e-7);
}

TEST(TPostfix, can_enter_numbers_with_only_point)
{
	TPostfix tp;
	ASSERT_NEAR(0.1, tp.evaluate(".1"), 1e-7);
}

TEST(TPostfix, can_enter_number_with_exp)
{
	TPostfix tp;
	ASSERT_NEAR(0.1, tp.evaluate("1.0e-1"), 1e-7);
	ASSERT_NEAR(10.0, tp.evaluate("1.0e+1"), 1e-7);
	ASSERT_NEAR(123.0, tp.evaluate("1.23e+2"), 1e-7);
}

TEST(TPostfix, can_enter_big_numbers)
{
	TPostfix tp;
	ASSERT_NEAR(1e+20, tp.evaluate("100000000000000000000"), 1.0);
	ASSERT_NEAR(1e+20, tp.evaluate("1.0e+20"), 1.0);
	ASSERT_NEAR(1e+20, tp.evaluate("1.e+20"), 1.0);
}

TEST(TPostfix, invalid_numbers_input_cases)
{
	TPostfix tp;
	ASSERT_ANY_THROW(tp.evaluate("."));
	ASSERT_ANY_THROW(tp.evaluate("1.2.3"));
	ASSERT_ANY_THROW(tp.evaluate("1.2e"));
	ASSERT_ANY_THROW(tp.evaluate("1.2e+"));
	ASSERT_ANY_THROW(tp.evaluate("1.2e+0"));
	ASSERT_ANY_THROW(tp.evaluate("1.2e+3.0"));
	ASSERT_ANY_THROW(tp.evaluate("1.2e+3e+4"));
}

// Правильность размещения чисел
TEST(TPostfix, cant_put_two_numbers_together)
{
	TPostfix tp;
	ASSERT_ANY_THROW(tp.evaluate("34 4"));
}

TEST(TPostfix, cant_put_number_after_right_parenthesis)
{
	TPostfix tp;
	ASSERT_ANY_THROW(tp.evaluate("3+(4+7)7"));
	ASSERT_ANY_THROW(tp.evaluate("3(4+7)+7"));
}

// Правильность размещения переменных
TEST(TPostfix, cant_put_variables_together)
{
	TPostfix tp;
	tp.evaluate("x=4");
	tp.evaluate("y=4");
	ASSERT_ANY_THROW(tp.evaluate("x x"));
	ASSERT_ANY_THROW(tp.evaluate("x y"));
	ASSERT_ANY_THROW(tp.evaluate("y x"));
}

TEST(TPostfix, cant_put_variable_and_number_together)
{
	TPostfix tp;
	tp.evaluate("x=4");
	ASSERT_ANY_THROW(tp.evaluate("x 4"));
	ASSERT_ANY_THROW(tp.evaluate("4 x"));
	ASSERT_ANY_THROW(tp.evaluate("4x"));
}

// Размещение скобок
TEST(TPostfix, throws_error_on_unmatched_parenthesis)
{
	TPostfix tp;
	ASSERT_ANY_THROW(tp.evaluate("()"));
	ASSERT_ANY_THROW(tp.evaluate("(1+(2+3)"));
	ASSERT_ANY_THROW(tp.evaluate("(1+2+3))"));
	ASSERT_ANY_THROW(tp.evaluate("1)+2(+3"));
}

TEST(TPostfix, parenthesis_with_multiplication_and_addition)
{
	TPostfix tp;
	ASSERT_NEAR(16.0, tp.evaluate("2*(3+5)"), 1e-7);
}

TEST(TPostfix, parenthesis_with_subtraction_and_multiplication)
{
	TPostfix tp;
	ASSERT_NEAR(0.0, tp.evaluate("(5-5)*2"), 1e-7);
}

TEST(TPostfix, parenthesis_with_division_and_addition)
{
	TPostfix tp;
	ASSERT_NEAR(3.5, tp.evaluate("(4+3)/2"), 1e-7);
}

TEST(TPostfix, parenthesis_with_division_and_subtraction)
{
	TPostfix tp;
	ASSERT_NEAR(0.5, tp.evaluate("(4-3)/2"), 1e-7);
}

TEST(TPostfix, parenthesis_with_functions)
{
	TPostfix tp;
	ASSERT_NEAR(std::sin(2+2)+2, tp.evaluate("sin(2+2)+2"), 1e-7);
}

TEST(TPostfix, parenthesis_with_unary_minus)
{
	TPostfix tp;
	ASSERT_NEAR(-4.0, tp.evaluate("-(7-3)"), 1e-7);
	ASSERT_NEAR(-10.0, tp.evaluate("-(7+3)"), 1e-7);
	ASSERT_NEAR(-21.0, tp.evaluate("-(7*3)"), 1e-7);
	ASSERT_NEAR(-2.0, tp.evaluate("-(6/3)"), 1e-7);
	ASSERT_NEAR(-std::sin(1), tp.evaluate("-sin 1"), 1e-7);
	ASSERT_NEAR(9.0, tp.evaluate("(-3)^2"), 1e-7);
}

TEST(TPostfix, parenthesis_with_exponentiation)
{
	TPostfix tp;
	ASSERT_NEAR(4096.0, tp.evaluate("(2^3)^4"), 1e-7);
	ASSERT_NEAR(0.75, tp.evaluate("sin(pi/3)^2"), 1e-7);
	ASSERT_NEAR(std::sin(std::pow(3.1415926535897932384626433 / 3.0, 2)), tp.evaluate("sin((pi/3)^2)"), 1e-7);
}

TEST(TPostfix, parenthesis_multiplication_and_division)
{
	TPostfix tp;
	ASSERT_NEAR(6.0, tp.evaluate("3/2*4"), 1e-7);
	ASSERT_NEAR(0.375, tp.evaluate("3/(2*4)"), 1e-7);
}

TEST(TPostfix, can_handle_many_parenthesis)
{
	TPostfix tp;
	ASSERT_NEAR(1.0, tp.evaluate("3+((((2/(-2)))+((2/(-2)))))"), 1e-7);
}

// Порядок операций
TEST(TPostfix, multiplication_precedence)
{
	TPostfix tp;
	ASSERT_NEAR(41.0, tp.evaluate("2*3+5*7"), 1e-7);
	ASSERT_NEAR(15.0, tp.evaluate("5*5-5*2"), 1e-7);
}

TEST(TPostfix, division_precedence)
{
	TPostfix tp;
	ASSERT_NEAR(3.0, tp.evaluate("5/2+1/2"), 1e-7);
	ASSERT_NEAR(2.0, tp.evaluate("5/2-1/2"), 1e-7);
}

TEST(TPostfix, function_precedence)
{
	TPostfix tp;
	ASSERT_NEAR(std::sin(2.0)+1.0, tp.evaluate("sin 2 + 1"), 1e-7);
}

TEST(TPostfix, exponentiation_precedence)
{
	TPostfix tp;
	ASSERT_NEAR(-9, tp.evaluate("-3^2"), 1e-7);
	ASSERT_NEAR(-2, tp.evaluate("-1^1-1"), 1e-7);
	ASSERT_NEAR(0.0192, tp.evaluate("12*5^-4"), 1e-7);
}

TEST(TPostfix, exponentiation_goes_from_right_to_left)
{
	TPostfix tp;
	EXPECT_NEAR(2417851639229258349412352.0, tp.evaluate("2^3^4"), 1.0);
}

TEST(TPostfix, can_evaluate_complex_expression)
{
	TPostfix tp;
	EXPECT_NEAR(1/std::sqrt(3) * (0.1e+7 * 5.3 + 1) * 5.3 + 1.05 * tan(3.1415926535897932384626433 / 6) - log(2.71828182845904523536) / 152.4 * 3 / 4, tp.evaluate("1/sqrt(3)*(0.1e+7*5.3+1)*5.3+1.05*tan(pi/6)-ln(e)/152.4*3/4"), 1e-7);
}

// Размещение операций
TEST(TPostfix, can_put_unary_minus_after_operand)
{
	TPostfix tp;
	EXPECT_NEAR(0.0, tp.evaluate("6+-6"), 1e-7);
	EXPECT_NEAR(-36.0, tp.evaluate("6*-6"), 1e-7);
	EXPECT_NEAR(-1.0, tp.evaluate("6/-6"), 1e-7);
	EXPECT_NEAR(std::pow(6.0, -6.0), tp.evaluate("6^-6"), 1e-7);
}

TEST(TPostfix, cant_put_operator_without_operands)
{
	TPostfix tp;
	ASSERT_ANY_THROW(tp.evaluate("/"));
	ASSERT_ANY_THROW(tp.evaluate("sin"));
}

TEST(TPostfix, check_missing_operands)
{
	TPostfix tp;
	ASSERT_ANY_THROW(tp.evaluate("3+"));
	ASSERT_ANY_THROW(tp.evaluate("+3"));
}

// Проверка присваивания
TEST(TPostfix, can_assign_variables)
{
	TPostfix tp;
	EXPECT_EQ(4.0, tp.evaluate("x=4.0"));
}

TEST(TPostfix, can_assign_multiple_variables)
{
	TPostfix tp;
	tp.evaluate("z=y=x=4.0");
	ASSERT_EQ(4.0, tp.evaluate("x"));
	ASSERT_EQ(4.0, tp.evaluate("y"));
	ASSERT_EQ(4.0, tp.evaluate("z"));
}

TEST(TPostfix, can_assign_multiple_variables_from_expression)
{
	TPostfix tp;
	tp.evaluate("z=y=x=4-1");
	ASSERT_EQ(3.0, tp.evaluate("x"));
	ASSERT_EQ(3.0, tp.evaluate("y"));
	ASSERT_EQ(3.0, tp.evaluate("z"));
}

TEST(TPostfix, each_variable_has_own_value)
{
	TPostfix tp;
	tp.evaluate("y=x=4");
	tp.evaluate("x=2");
	ASSERT_EQ(2.0, tp.evaluate("x"));
	ASSERT_EQ(4.0, tp.evaluate("y"));
}

TEST(TPostfix, can_use_variables)
{
	TPostfix tp;
	tp.evaluate("x=5");
	ASSERT_NEAR(6.0, tp.evaluate("x+1"), 1e-7);
}

TEST(TPostfix, can_clear_variables)
{
	TPostfix tp;
	tp.evaluate("x=4");
	tp.clearVariables();
	ASSERT_ANY_THROW(tp.evaluate("x"));
}

TEST(TPostfix, cant_assign_to_expression)
{
	TPostfix tp;
	ASSERT_ANY_THROW(tp.evaluate("2-x=4"));
}

TEST(TPostfix, cant_assign_with_nothing)
{
	TPostfix tp;
	ASSERT_ANY_THROW(tp.evaluate("x="));
}

TEST(TPostfix, cant_assign_with_uninitialized_variable)
{
	TPostfix tp;
	ASSERT_ANY_THROW(tp.evaluate("x=x0"));
}