// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"

TEST(TPostfix, can_create_postfix_to_infix)
{
	string str = "x+y";
	ASSERT_NO_THROW(TPostfix s(str));
}

TEST(TPostfix, correct_create_postfix_to_infix)
{
	TPostfix str = "1+2";
	str.toPostfix();
	EXPECT_EQ("12+", str.getPostfix());
}

TEST(TPostfix, can_correct_get_infix)
{
	string str = "x+y";
	TPostfix s(str);
	EXPECT_EQ(str, s.getInfix());
}

TEST(TPostfix, sum_operation_in_wrong_position)
{
	string str = "x++y";
	ASSERT_ANY_THROW(TPostfix s(str));
}

TEST(TPostfix, sub_operation_in_wrong_position)
{
	string str = "x+y-";
	ASSERT_ANY_THROW(TPostfix s(str));
}

TEST(TPostfix, mult_operation_in_wrong_position)
{
	string str = "*x*y";
	ASSERT_ANY_THROW(TPostfix s(str));
}

TEST(TPostfix, div_operation_in_wrong_position)
{
	string str = "s//y";
	ASSERT_ANY_THROW(TPostfix s(str));
}

TEST(TPostfix, point_in_wrong_position)
{
	string str = "x.+y";
	ASSERT_ANY_THROW(TPostfix s(str));
}

TEST(TPostfix, E_in_wrong_position)
{
	string str = "x+Ey";
	ASSERT_ANY_THROW(TPostfix s(str));
}

TEST(TPostfix, can_correct_unarnyminus)
{
	TPostfix str("---x+y");
	str.toPostfix();
	EXPECT_EQ("x~~~y+", str.getPostfix());
}

TEST(TPostfix, can_correct_convertation_string_to_number)
{
	string str = "44";
	TPostfix doublestr(str);
	EXPECT_EQ(44, doublestr.toDouble("44"));
}

TEST(TPostfix, can_correct_convertation_string_with_point_to_number)
{
	string str = "44.5";
	TPostfix doublestr(str);
	EXPECT_EQ(44.5, doublestr.toDouble("44.5"));
}

TEST(TPostfix, can_correct_convertation_string_with_dot_and_E_to_number)
{
	string str = "44.5E1";
	TPostfix doublestr(str);
	EXPECT_EQ(445, doublestr.toDouble("44.5E1"));
}

TEST(TPostfix, can_correct_sum)
{
	double str = 44.5 + 4;
	TPostfix s("44.5+4");
	s.toPostfix();
	s.calculate();
	EXPECT_EQ(s.getResult(), str);
}

TEST(TPostfix, can_correct_sub)
{
	double str = 44.5 - 4;
	TPostfix s("44.5-4");
	s.toPostfix();
	s.calculate();
	EXPECT_EQ(s.getResult(), str);
}

TEST(TPostfix, can_correct_mult)
{
	double str = 44.5 * 4;
	TPostfix s("44.5*4");
	s.toPostfix();
	s.calculate();
	EXPECT_EQ(s.getResult(), str);
}

TEST(TPostfix, impossible_div_by_zero)
{
	TPostfix str("44.5 / 0");
	str.toPostfix();
	ASSERT_ANY_THROW(str.calculate());
}
