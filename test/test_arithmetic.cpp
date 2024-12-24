// тесты для вычисления арифметических выражений
#pragma once
#include <gtest.h>
#include "arithmetic.h"

TEST(TPostfix, cant_print_rpn_before_postfix_method) {
	TPostfix<double> d("1");
	ASSERT_ANY_THROW(d.print_rpn());
}
TEST(TPostfix, can_print_rpn_after_postfix_method) {
	TPostfix<double> d("1");
	d.ToPostfix();
	ASSERT_NO_THROW(d.print_rpn());
}
TEST(TPostfix, can_print_infix_method) {
	TPostfix<double> d("1+3");
	ASSERT_NO_THROW(d.print_infix());
}
TEST(TPostfix, _1) {
	TPostfix<double> d("1+3");
	double res = 0.0;
	ASSERT_NO_THROW(d.ToPostfix());
	ASSERT_NO_THROW(res = d.simple_calc());
	ASSERT_EQ(res, 4.0);
}
TEST(TPostfix, _2) {
	TPostfix<double> d("1 + (-1)");
	double res = 0.0;
	ASSERT_NO_THROW(d.ToPostfix());
	ASSERT_NO_THROW(res = d.simple_calc());
	ASSERT_EQ(res, 0.0);
}
TEST(TPostfix, _3) {
	TPostfix<double> d("-1+1");
	double res = 0.0;
	ASSERT_NO_THROW(d.ToPostfix());
	ASSERT_NO_THROW(res = d.simple_calc());
	ASSERT_EQ(res, 0.0);
}
TEST(TPostfix, _4) {
	TPostfix<double> d("(-1)+(-1)");
	double res = 0.0;
	ASSERT_NO_THROW(d.ToPostfix());
	ASSERT_NO_THROW(res = d.simple_calc());
	ASSERT_EQ(res, -2.0);
}
TEST(TPostfix, invalid_arythmetic_expression_1) {
	TPostfix<double> d("1 ++ 1");
	d.ToPostfix();
	ASSERT_ANY_THROW(d.simple_calc());
}
TEST(TPostfix, invalid_arythmetic_expression_2) {
	TPostfix<double> d("1 +- 1");
	d.ToPostfix();
	ASSERT_ANY_THROW(d.simple_calc());
}
TEST(TPostfix, invalid_arythmetic_expression_3) {
	TPostfix<double> d("1 -- 1");
	d.ToPostfix();
	ASSERT_ANY_THROW(d.simple_calc());
}
TEST(TPostfix, invalid_parenthesis_sequence_1) {
	TPostfix<double> d(")");
	ASSERT_ANY_THROW(d.ToPostfix());
}
TEST(TPostfix, invalid_parenthesis_sequence_2) {
	TPostfix<double> d("(");
	ASSERT_ANY_THROW(d.ToPostfix());
}
TEST(TPostfix, calc_exp_1) {
	TPostfix<double> d("1e5");
	d.ToPostfix();
	double res = d.simple_calc();
	ASSERT_EQ(res == 1e5, 1);
}
TEST(TPostfix, calc_exp_2) {
	TPostfix<double> d("1e-5");
	d.ToPostfix();
	double res = d.simple_calc();
	ASSERT_EQ(res == 1e-5, 1);
}
TEST(TPostfix, calc_sin_1) {
	TPostfix<double> d("sin(0)");
	d.ToPostfix();
	double res = d.simple_calc();
	ASSERT_EQ(res == sin(0), 1);
}
TEST(TPostfix, calc_sin_2) {
	TPostfix<double> d("sin(sin(0))");
	d.ToPostfix();
	double res = d.simple_calc();
	ASSERT_EQ(res == sin(sin(0)), 1);
}