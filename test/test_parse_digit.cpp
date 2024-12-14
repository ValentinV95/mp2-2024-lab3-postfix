#include "gtest.h"
#include "parse_digits.h"

TEST(parse_digit, can_reverse_string)
{
	std::string s = "abc",k;
	ASSERT_NO_THROW(k=my_reverse(s));
	ASSERT_EQ(k,"cba");
}
TEST(parse_digit, can_reverse_empty_string)
{
	std::string s = "",k;
	ASSERT_NO_THROW(k=my_reverse(s));
	ASSERT_EQ(k, "");
}
TEST(parse_digit, can_posi_int_to_String)
{
	int a = 1232;
	std::string k;
	ASSERT_NO_THROW(k=my_to_String(a));
	ASSERT_EQ(k, "1232");
}
TEST(parse_digit, can_0_int_to_String)
{
	int a = 0;
	std::string k;
	ASSERT_NO_THROW(k = my_to_String(a));
	ASSERT_EQ(k, "0");
}
TEST(parse_digit, can_neg_int_to_String)
{
	int a = -1233;
	std::string k;
	ASSERT_NO_THROW(k = my_to_String(a));
	ASSERT_EQ(k, "-1233");
}
TEST(parse_digit, simple_int)
{
	std::string s = "123";
	double res = 0;
	ASSERT_NO_THROW(res = parser(s));
	ASSERT_EQ(res, 123);
}
TEST(parse_digit, simple_negative_int)
{
	std::string s = "-123";
	double res = 0;
	ASSERT_NO_THROW(res = parser(s));
	ASSERT_EQ(res, -123);
}
TEST(parse_digit, simple_int_e_plus)
{
	std::string s = "123e+3";
	double res = 0;
	ASSERT_NO_THROW(res = parser(s));
	ASSERT_EQ(res, 123000);
}
TEST(parse_digit, simple_negative_int_e_plus)
{
	std::string s = "-123e+3";
	double res = 0;
	ASSERT_NO_THROW(res = parser(s));
	ASSERT_EQ(res, -123000);
}
TEST(parse_digit, simple_int_e_minus)
{
	std::string s = "123e-3";
	double res = 0;
	ASSERT_NO_THROW(res = parser(s));
	ASSERT_EQ(res, 0.123);
}
TEST(parse_digit, simple_negative_int_e_minus)
{
	std::string s = "-123e-3";
	double res = 0;
	ASSERT_NO_THROW(res = parser(s));
	ASSERT_EQ(res, -0.123);
}
TEST(parse_digit, simple_double)
{
	std::string s = "123.2";
	double res = 0;
	ASSERT_NO_THROW(res = parser(s));
	ASSERT_EQ(res, 123.2);
}
TEST(parse_digit, simple_negative_double)
{
	std::string s = "-123.2";
	double res = 0;
	ASSERT_NO_THROW(res = parser(s));
	ASSERT_EQ(res, -123.2);
}
TEST(parse_digit, double_with_digits_after_point_len_greater_1)
{
	std::string s = "123.221345423";
	double res = 0;
	ASSERT_NO_THROW(res = parser(s));
	ASSERT_EQ(res, 123.221345423);
}
TEST(parse_digit, negative_double_with_digits_after_point_len_greater_1)
{
	std::string s = "-123.221345423";
	double res = 0;
	ASSERT_NO_THROW(res = parser(s));
	ASSERT_EQ(res, -123.221345423);
}
TEST(parse_digit, pos_double_with_e_plus_1_digit_)
{
	std::string s = "123.23e+3";
	double res = 0;
	ASSERT_NO_THROW(res = parser(s));
	ASSERT_EQ(res, 123230);
}
TEST(parse_digit, pos_double_with_E_plus)
{
	std::string s = "123.23E+3";
	double res = 0;
	ASSERT_NO_THROW(res = parser(s));
	ASSERT_EQ(res, 123230);
}
TEST(parse_digit, pos_double_with_E_minus)
{
	std::string s = "123.23E-3";
	double res = 0;
	ASSERT_NO_THROW(res = parser(s));
	ASSERT_EQ(res, 0.123230);
}
TEST(parse_digit, neg_double_with_e_plus_1_digit_)
{
	std::string s = "-123.23e+3";
	double res = 0;
	ASSERT_NO_THROW(res = parser(s));
	ASSERT_EQ(res, -123230);
}
TEST(parse_digit, pos_double_with_e_plus_more_digit_)
{
	std::string s = "123.23e+10";
	double res = 0;
	ASSERT_NO_THROW(res = parser(s));
	ASSERT_EQ(res, 1232300000000);
}
TEST(parse_digit, neg_double_with_e_plus_more_digit_)
{
	std::string s = "-123.23e+10";
	double res = 0;
	ASSERT_NO_THROW(res = parser(s));
	ASSERT_EQ(res, -1232300000000);
}
TEST(parse_digit, pos_double_with_e_minus_1_digit_)
{
	std::string s = "123.23e-3";
	double res = 0;
	ASSERT_NO_THROW(res = parser(s));
	ASSERT_EQ(res, 0.123230);
}
TEST(parse_digit, neg_double_with_e_minus_1_digit_)
{
	std::string s = "-123.23e-3";
	double res = 0;
	ASSERT_NO_THROW(res = parser(s));
	ASSERT_EQ(res, -0.123230);
}
TEST(parse_digit, pos_double_with_e_minus_more_digit_)
{
	std::string s = "123.23e-10";
	double res = 0;
	ASSERT_NO_THROW(res = parser(s));
	ASSERT_EQ(res, 0.000000012323);
}
TEST(parse_digit, neg_double_with_e_minus_more_digit_)
{
	std::string s = "-123.23e-10";
	double res = 0;
	ASSERT_NO_THROW(res = parser(s));
	ASSERT_EQ(res, -0.000000012323);
}
TEST(parse_digit, pos_double_start_with_point)
{
	std::string s = ".23e-10";
	double res = 0;
	ASSERT_NO_THROW(res = parser(s));
	ASSERT_EQ(res, 0.000000000023);
}
TEST(parse_digit, neg_double_start_with_point)
{
	std::string s = "-.23e-10";
	double res = 0;
	ASSERT_NO_THROW(res = parser(s));
	ASSERT_EQ(res, -0.000000000023);
}
TEST(parse_digit, cant_start_with_plus)
{
	std::string s = "+3";
	ASSERT_ANY_THROW(parser(s));
}
TEST(parse_digit, cant_start_with_sym)
{
	std::string s = "w3";
	ASSERT_ANY_THROW(parser(s));
}
TEST(parse_digit, cant_include_sym_non_e_E_aft_dig_start)
{
	std::string s = "3r";
	ASSERT_ANY_THROW(parser(s));
}
TEST(parse_digit, can_E_aft_st)
{
	std::string s = "3E+1";
	double res = 0;
	ASSERT_NO_THROW(res= parser(s));
	ASSERT_EQ(res, 30);
}
TEST(parse_digit, cant_second_point_next_first)
{
	std::string s = "3..3";
	ASSERT_ANY_THROW(parser(s));
}
TEST(parse_digit, cant_second_point_aft_digits)
{
	std::string s = "3.3.32";
	ASSERT_ANY_THROW(parser(s));
}
TEST(parse_digit, cant_without_plus_or_minus_e)
{
	std::string s = "3.0e2";
	ASSERT_ANY_THROW(parser(s));
}
TEST(parse_digit, cant_e_after_point)
{
	std::string s = "3.e+2";
	ASSERT_ANY_THROW(parser(s));
}
TEST(parse_digit, cant_empty_string)
{
	std::string s = "";
	ASSERT_ANY_THROW(parser(s));
}
TEST(parse_digit, cant_space_string_1)
{
	std::string s = " ";
	ASSERT_ANY_THROW(parser(s));
}
TEST(parse_digit, cant_space_string_2)
{
	std::string s = "1.3e +3";
	ASSERT_ANY_THROW(parser(s));
}
TEST(parse_digit, cant_space_string_3)
{
	std::string s = "1. 3e+3";
	ASSERT_ANY_THROW(parser(s));
}
TEST(parse_digit, cant_space_string_4)
{
	std::string s = "1.3 e+3";
	ASSERT_ANY_THROW(parser(s));
}
TEST(parse_digit, cant_space_end)
{
	std::string s = "1.3e+3 ";
	ASSERT_ANY_THROW(parser(s));
}
TEST(parse_digit, cant_more_one_minus_starts)
{
	std::string s = "--1";
	ASSERT_ANY_THROW(parser(s));
}
TEST(parse_digit, can_parse_minus_0)
{
	std::string s = "-0";
	double res = 0;
	ASSERT_NO_THROW(res = parser(s));
	ASSERT_EQ(-0, res);
}