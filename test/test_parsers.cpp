#include "parsers.h"
#include "expr_err.h"
#include <gtest.h>

TEST(PreParse, can_delete_spaces)
{
	string s{ "    ab   ( ) + ---        " }, r;
	ASSERT_NO_THROW(r = PreParse(s));
	EXPECT_EQ(r, "ab ( ) + ---");
}

TEST(PreParse, throws_when_no_opening_bracket_met)
{
	string s{ "ab(12+1))*(2+3)" }, r;
	ASSERT_ANY_THROW(PreParse(s));
	try
	{
		PreParse(s);
	}
	catch (expression_error e)
	{
		EXPECT_EQ(string(e.what()), "No oppening bracket for ) at 9 symbol");
	}
}

TEST(PreParse, throws_when_closing_brackets_are_missing)
{
	string s{ "ab(12+1*(2+3)" }, r;
	ASSERT_ANY_THROW(PreParse(s));
	try
	{
		PreParse(s);
	}
	catch (expression_error e)
	{
		EXPECT_EQ(string(e.what()), "1 closing brackets are missing");
	}
}

TEST(NumParse, can_convert_string_to_double)
{
	string s{ "-25.35E+2" };
	ASSERT_NO_THROW(NumParse(s));
	s = "00.015e-005";
	ASSERT_NO_THROW(NumParse(s));
	s = "-0.17000";
	ASSERT_NO_THROW(NumParse(s));
	s = "00.0e+10";
	ASSERT_NO_THROW(NumParse(s));
	s = "16.15";
	ASSERT_NO_THROW(NumParse(s));
	s = "2e+310";
	ASSERT_NO_THROW(NumParse(s));
	s = "-2e+310";
	ASSERT_NO_THROW(NumParse(s));
	s = "125125125125555";
	ASSERT_NO_THROW(NumParse(s));
}

TEST(NumParse, correctly_converts_to_double)
{
	string s{ "-25.35e+2" };
	double d, act = -25.35e+2;
	d = NumParse(s);
	EXPECT_DOUBLE_EQ(d, act);
	s = "00.015e-005";
	act = 0.015e-5;
	d = NumParse(s);
	EXPECT_DOUBLE_EQ(d, act);
	s = "-0.17000";
	act = -0.17;
	d = NumParse(s);
	EXPECT_DOUBLE_EQ(d, act);
	s = "00.0e+10";
	act = 0.0e+10;
	d = NumParse(s);
	EXPECT_DOUBLE_EQ(d, act);
	s = "16.15";
	act = 16.15;
	d = NumParse(s);
	EXPECT_DOUBLE_EQ(d, act);
	s = "2e+310";
	act = 2e+307*1000.0;
	d = NumParse(s);
	EXPECT_DOUBLE_EQ(d, act);
	s = "-2e+310";
	d = NumParse(s);
	act = -2e+307*1000.0;
	EXPECT_DOUBLE_EQ(d, act);
	s = "12512512514555";
	d = NumParse(s);
	act = 12512512514555;
	EXPECT_DOUBLE_EQ(d, act);
	s = "1.01010101010e+1";
	d = NumParse(s);
	act = 1.01010101010e+1;
	EXPECT_DOUBLE_EQ(d, act);
	s = "118E+0";
	d = NumParse(s);
	act = 118e+0;
	EXPECT_DOUBLE_EQ(d, act);
	s = "118E-000";
	d = NumParse(s);
	act = 118e-0;
	EXPECT_DOUBLE_EQ(d, act);
	s = "2.2250738585072014E-308";
	d = NumParse(s);
	act = 2.2250738585072014E-308;
	EXPECT_DOUBLE_EQ(d, act);
	s = "1.7976931348623158E+308";
	d = NumParse(s);
	act = 1.7976931348623158E+308;
	EXPECT_DOUBLE_EQ(d, act);
}

TEST(NumParse,throws_when_number_does_not_have_explicit_integer_part)
{
	string s{ ".15" };
	ASSERT_ANY_THROW(NumParse(s));
	s = "-.15";
	ASSERT_ANY_THROW(NumParse(s));
}
TEST(NumParse,throws_when_number_does_not_have_fraction_part_after_point)
{
	string s{ "15." };
	ASSERT_ANY_THROW(NumParse(s));
	s = "15.e+16";
	ASSERT_ANY_THROW(NumParse(s));
}
TEST(NumParse,throws_when_number_has_no_digits_in_exponential_part)
{
	string s{ "15.e+" };
	ASSERT_ANY_THROW(NumParse(s));
	s = "15.e-";
	ASSERT_ANY_THROW(NumParse(s));
}
TEST(NumParse,throws_when_power_is_too_large)
{
	string s{ "15.e+50000" };
	ASSERT_ANY_THROW(NumParse(s));
	s = "15.e-50000";
	ASSERT_ANY_THROW(NumParse(s));
}
TEST(NumParse,throws_when_there_is_no_sign_after_e)
{
	string s{ "15.e2" };
	ASSERT_ANY_THROW(NumParse(s));
	s = "15.E3";
	ASSERT_ANY_THROW(NumParse(s));
	s = "15.E";
	ASSERT_ANY_THROW(NumParse(s));
}