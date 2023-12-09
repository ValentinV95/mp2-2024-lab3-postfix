// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"

TEST(Arithmetic, can_create_postfix_to_infix)
{
	string str = "x+y";
	ASSERT_NO_THROW(Arithmetic s(str));
}

TEST(Arithmetic, can_correct_create_postfix_to_infix)
{
	string str = "x+y";
	string correct = "x y + ";
	Arithmetic s(str);
	EXPECT_EQ(correct, s.getPostfix());
}

TEST(Arithmetic, can_correct_create_postfix_to_infix_with_unary_minus)
{
	string str = "-(x+(-y))";
	string correct = "x y ~ + ~ ";
	Arithmetic s(str);
	EXPECT_EQ(correct, s.getPostfix());
}

TEST(Arithmetic, can_correct_create_postfix_to_infix_with_operation_with_different_priorities)
{
	string str = "-(x+y)*z";
	string correct = "x y + z * ~ ";
	Arithmetic s(str);
	EXPECT_EQ(correct, s.getPostfix());
}

TEST(Arithmetic, can_correct_create_postfix_to_infix_with_long_variable_names)
{
	string str = "-(_xt+y_b)*z1k";
	string correct = "_xt y_b + z1k * ~ ";
	Arithmetic s(str);
	EXPECT_EQ(correct, s.getPostfix());
}

TEST(Arithmetic, can_correct_create_postfix_to_infix_with_double)
{
	string str = "-(x+y)*8.9";
	string correct = "x y + 8.9 * ~ ";
	Arithmetic s(str);
	EXPECT_EQ(correct, s.getPostfix());
}

TEST(Arithmetic, can_correct_create_postfix_to_infix_with_double_first_point)
{
	string str = "-(x+y)*.9";
	string correct = "x y + .9 * ~ ";
	Arithmetic s(str);
	EXPECT_EQ(correct, s.getPostfix());
}

TEST(Arithmetic, can_correct_create_postfix_to_infix_with_double_with_e)
{
	string str = "-(x+y)*8.e-4";
	string correct = "x y + 8.e-4 * ~ ";
	Arithmetic s(str);
	EXPECT_EQ(correct, s.getPostfix());
}

TEST(Arithmetic, cant_create_postfix_to_infix_with_space)
{
	string str = "-(x+y)* 8.9";
	ASSERT_ANY_THROW(Arithmetic s(str));
}

TEST(Arithmetic, cant_create_postfix_to_infix_with_wrong_first_symbol)
{
	string str = "*(x+y)*8.9";
	ASSERT_ANY_THROW(Arithmetic s(str));
}

TEST(Arithmetic, cant_create_postfix_to_infix_with_wrong_symbol)
{
	string str = "(x+y%)*8.9";
	ASSERT_ANY_THROW(Arithmetic s(str));
}

TEST(Arithmetic, cant_create_postfix_to_infix_with_wrong_name_of_variable_or_index_without_mul)
{
	string str = "(x+5y)*8.9";
	ASSERT_ANY_THROW(Arithmetic s(str));
}

TEST(Arithmetic, cant_create_postfix_to_infix_with_no_operation_between_breakets)
{
	string str = "(x+5y)(8.9*z)";
	ASSERT_ANY_THROW(Arithmetic s(str));
}

TEST(Arithmetic, cant_create_postfix_to_infix_with_two_operations_together)
{
	string str = "(x+-y)*8.9";
	ASSERT_ANY_THROW(Arithmetic s(str));
}

TEST(Arithmetic, cant_create_postfix_to_infix_with_different_count_of_brackets)
{
	string str = "x+y)*(8.9";
	ASSERT_ANY_THROW(Arithmetic s(str));
}

TEST(Arithmetic, cant_create_postfix_to_infix_with_wrong_first_brackets)
{
	string str = ")(x+y)*(8.9";
	ASSERT_ANY_THROW(Arithmetic s(str));
}

TEST(Arithmetic, cant_create_postfix_to_infix_with_wrong_last_symbol)
{
	string str = "(x+y)*8.9/";
	ASSERT_ANY_THROW(Arithmetic s(str));
}

TEST(Arithmetic, can_get_operands)
{
	string str = "x+y";
	string correct = "x y ";
	Arithmetic s(str);
	EXPECT_EQ(correct, s.getOperands());
}

TEST(Arithmetic, can_get_long_operands)
{
	string str = "xn1+yn2";
	string correct = "xn1 yn2 ";
	Arithmetic s(str);
	EXPECT_EQ(correct, s.getOperands());
}

TEST(Arithmetic, can_get_long_operands_with_the_same_first_symbol)
{
	string str = "xn1+yn2+xn2";
	string correct = "xn1 yn2 xn2 ";
	Arithmetic s(str);
	EXPECT_EQ(correct, s.getOperands());
}

TEST(Arithmetic, can_get_operands_without_repeate)
{
	string str = "xn1+yn2*yn2";
	string correct = "xn1 yn2 ";
	Arithmetic s(str);
	EXPECT_EQ(correct, s.getOperands());
}

TEST(Arithmetic, can_get_infix)
{
	string str = "x+y";
	string correct = "x+y";
	Arithmetic s(str);
	EXPECT_EQ(correct, s.getInfix());
}

TEST(Arithmetic, can_correct_make_double_from_string_with_dote)
{
	string str = "-(x+y)*8.9";
	Arithmetic s(str);
	double doub = 8.9;
	EXPECT_EQ(doub, s.makeDouble("8.9"));
}

TEST(Arithmetic, can_correct_make_double_from_string_without_dote)
{
	string str = "-(x+y)*8.9";
	Arithmetic s(str);
	double doub = 89;
	EXPECT_EQ(doub, s.makeDouble("89"));
}

TEST(Arithmetic, can_correct_make_double_from_string_without_end)
{
	string str = "-(x+y)*8.9";
	Arithmetic s(str);
	double doub = 8.;
	EXPECT_EQ(doub, s.makeDouble("8."));
}

TEST(Arithmetic, can_correct_make_double_from_string_without_start)
{
	string str = "-(x+y)";
	Arithmetic s(str);
	double doub = .90;
	EXPECT_EQ(doub, s.makeDouble(".90"));
}

TEST(Arithmetic, can_correct_make_double_from_string_with_e_positive)
{
	string str = "-(x+y)*8.9";
	Arithmetic s(str);
	double doub = 1.e+10;
	EXPECT_EQ(doub, s.makeDouble("1.e10"));
}

TEST(Arithmetic, can_correct_make_double_from_string_with_e_negativ)
{
	string str = "-(x+y)*8.9";
	Arithmetic s(str);
	double doub = 4.e-2;
	EXPECT_EQ(doub, s.makeDouble("4.e-2"));
}

TEST(Arithmetic, can_correct_make_negative_double_from_string_with_e_negativ)
{
	string str = "-(x+y)*8.9";
	Arithmetic s(str);
	double doub = 4.6e-2;
	EXPECT_EQ(doub, s.makeDouble("4.6e-2"));
}


TEST(Arithmetic, can_get_priorytets_of_operations)
{
	string str = "x+y";
	Arithmetic s(str);
	EXPECT_EQ(1, s.priority('+'));
	EXPECT_EQ(1, s.priority('-')); 
	EXPECT_EQ(2, s.priority('*'));
	EXPECT_EQ(2, s.priority('/'));
}

TEST(Arithmetic, can_spot_user_operations)
{
	string str = "x+y";
	Arithmetic s(str);
	EXPECT_EQ(true, s.isOperation('+'));
	EXPECT_EQ(true, s.isOperation('-'));
	EXPECT_EQ(true, s.isOperation('*'));
	EXPECT_EQ(true, s.isOperation('/'));
	EXPECT_EQ(false, s.isOperation('f'));
	EXPECT_EQ(false, s.isOperation('~'));
}



