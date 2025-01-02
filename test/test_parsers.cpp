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
	s = "0.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001e+999";
	ASSERT_NO_THROW(NumParse(s));
	s = "3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333.0e-10";
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
	act = -2e+307 * 1000.0;
	d = NumParse(s);
	EXPECT_DOUBLE_EQ(d, act);
	s = "12512512514555";
	act = 12512512514555;
	d = NumParse(s);
	EXPECT_DOUBLE_EQ(d, act);
	s = "1.01010101010e+1";
	act = 1.01010101010e+1;
	d = NumParse(s);
	EXPECT_DOUBLE_EQ(d, act);
	s = "118E+0";
	act = 118e+0;
	d = NumParse(s);
	EXPECT_DOUBLE_EQ(d, act);
	s = "118E-000";
	act = 118e-0;
	d = NumParse(s);
	EXPECT_DOUBLE_EQ(d, act);
	s = "2.2250738585072014E-308";
	act = 2.2250738585072014E-308;
	d = NumParse(s);
	EXPECT_DOUBLE_EQ(d, act);
	s = "1.7976931348623158E+308";
	act = 1.7976931348623158E+308;
	d = NumParse(s);
	EXPECT_DOUBLE_EQ(d, act);
	s = "-1.7976931348623159E+308";
	act = -INFINITY;
	d = NumParse(s);
	EXPECT_DOUBLE_EQ(d, act);
	s = "0.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001e+999";
	act = 0.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001e+999;
	d = NumParse(s);
	EXPECT_DOUBLE_EQ(d, act);
	s = "3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333.0e-10";
	act = 3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333.0e-10;
	d = NumParse(s);
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

TEST(NumParse, throws_when_unexpected_symbol_encountered)
{
	string s{ "15.05.e+2" };
	ASSERT_ANY_THROW(NumParse(s));
	s = "15.05.15e+2";
	ASSERT_ANY_THROW(NumParse(s));
	s = "15.0515eE+2";
	ASSERT_ANY_THROW(NumParse(s));
	s = "15.0515e+-2";
	ASSERT_ANY_THROW(NumParse(s));
	s = "15.0515e-+2";
	ASSERT_ANY_THROW(NumParse(s));
	s = "15.0515e++2";
	ASSERT_ANY_THROW(NumParse(s));
	s = "15.0515e--2";
	ASSERT_ANY_THROW(NumParse(s));
	s = "15.0515e+2e-2";
	ASSERT_ANY_THROW(NumParse(s));
	s = "15.05*15e+2";
	ASSERT_ANY_THROW(NumParse(s));
}




TEST(MainParse, can_parse_single_operand)
{
	string s{ "abc" };
	Vec<lexem*> VL;
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 1);
	EXPECT_EQ((dynamic_cast<variable*>(VL[0]))->GetName(), "abc");
	s = "_VL";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 1);
	EXPECT_EQ((dynamic_cast<variable*>(VL[0]))->GetName(), "_VL");
	s = "i_13";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 1);
	EXPECT_EQ((dynamic_cast<variable*>(VL[0]))->GetName(), "i_13");
	s = "pi";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 1);
	EXPECT_EQ((dynamic_cast<variable*>(VL[0]))->GetName(), "pi");
	s = "0.16e+4";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 1);
	EXPECT_EQ((dynamic_cast<constant*>(VL[0]))->GetVal(), 0.16e+4);
	s = "-0.16e+4";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 1);
	EXPECT_EQ((dynamic_cast<constant*>(VL[0]))->GetVal(), -0.16e+4);
}

TEST(MainParse, throws_when_encountered_unexpected_symbol)
{
	string s{ "abc ." };
	Vec<lexem*> VL;
	ASSERT_ANY_THROW(VL = MainParse(s));
	s = "abc.";
	ASSERT_ANY_THROW(VL = MainParse(s));
	s = "abc%3";
	ASSERT_ANY_THROW(VL = MainParse(s));
	s = "ab $";
	ASSERT_ANY_THROW(VL = MainParse(s));
	s = "#abc";
	ASSERT_ANY_THROW(VL = MainParse(s));

}

TEST(MainParse, throws_when_variable_has_letters_after_index)
{
	string s{ "abc35D" };
	Vec<lexem*> VL;
	ASSERT_ANY_THROW(VL = MainParse(s));
}

TEST(MainParse, throws_when_there_is_no_space_between_numbers)
{
	string s{ "12.35e+4012.16" };
	Vec<lexem*> VL;
	ASSERT_ANY_THROW(VL = MainParse(s));
	s = "25.1635.12";
	ASSERT_ANY_THROW(VL = MainParse(s));
}

TEST(MainParse, can_parse_math_operations)
{
	string s{ "a + b" };
	Vec<lexem*> VL;
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 3);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "a");
	EXPECT_EQ(dynamic_cast<variable*>(VL[1])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<operation*>(VL[2])->GetId(), 2);
	s = "-b";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 2);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<operation*>(VL[1])->GetId(), 7);
	s = "e ^ x";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 3);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "e");
	EXPECT_EQ(dynamic_cast<variable*>(VL[1])->GetName(), "x");
	EXPECT_EQ(dynamic_cast<operation*>(VL[2])->GetId(), 6);
}

TEST(MainParse, ignores_any_spaces)
{
	string s{ "    a   +  b            " };
	Vec<lexem*> VL;
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 3);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "a");
	EXPECT_EQ(dynamic_cast<variable*>(VL[1])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<operation*>(VL[2])->GetId(), 2);
	s = "-     b";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 2);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<operation*>(VL[1])->GetId(), 7);
}

TEST(MainParse, handles_multiple_unary_minuses)
{
	string s{ "---  --- - b" };
	Vec<lexem*> VL;
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 2);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<operation*>(VL[1])->GetId(), 7);
	s = "--b";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 1);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "b");
	s = "a--b";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 4);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "a");
	EXPECT_EQ(dynamic_cast<variable*>(VL[1])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<operation*>(VL[2])->GetId(), 7);
	EXPECT_EQ(dynamic_cast<operation*>(VL[3])->GetId(), 3);
	s = "a+--b";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 3);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "a");
	EXPECT_EQ(dynamic_cast<variable*>(VL[1])->GetName(), "b");
	s = "--- 2.0e+2";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 1);
	EXPECT_EQ(dynamic_cast<constant*>(VL[0])->GetVal(), -200.0);
}

TEST(MainParse, handles_prioryties_of_operations)
{
	string s{ "a+b*c" };
	Vec<lexem*> VL;
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 5);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "a");
	EXPECT_EQ(dynamic_cast<variable*>(VL[1])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<variable*>(VL[2])->GetName(), "c");
	EXPECT_EQ(dynamic_cast<operation*>(VL[3])->GetId(), 4);
	EXPECT_EQ(dynamic_cast<operation*>(VL[4])->GetId(), 2);
	s = "a*b+c";;
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 5);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "a");
	EXPECT_EQ(dynamic_cast<variable*>(VL[1])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<operation*>(VL[2])->GetId(), 4);
	EXPECT_EQ(dynamic_cast<variable*>(VL[3])->GetName(), "c");
	EXPECT_EQ(dynamic_cast<operation*>(VL[4])->GetId(), 2);
	s = "a+-5.0+c1*c2*c3";;
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 9);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "a");
	EXPECT_EQ(dynamic_cast<constant*>(VL[1])->GetVal(), -5.0);
	EXPECT_EQ(dynamic_cast<operation*>(VL[2])->GetId(), 2);
	EXPECT_EQ(dynamic_cast<variable*>(VL[3])->GetName(), "c1");
	EXPECT_EQ(dynamic_cast<variable*>(VL[4])->GetName(), "c2");
	EXPECT_EQ(dynamic_cast<operation*>(VL[5])->GetId(), 4);
	EXPECT_EQ(dynamic_cast<variable*>(VL[6])->GetName(), "c3");
	EXPECT_EQ(dynamic_cast<operation*>(VL[7])->GetId(), 4);
	EXPECT_EQ(dynamic_cast<operation*>(VL[8])->GetId(), 2);
	s = "a-b/c^d";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 7);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "a");
	EXPECT_EQ(dynamic_cast<variable*>(VL[1])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<variable*>(VL[2])->GetName(), "c");
	EXPECT_EQ(dynamic_cast<variable*>(VL[3])->GetName(), "d");
	EXPECT_EQ(dynamic_cast<operation*>(VL[4])->GetId(), 6);
	EXPECT_EQ(dynamic_cast<operation*>(VL[5])->GetId(), 5);
	EXPECT_EQ(dynamic_cast<operation*>(VL[6])->GetId(), 3);
	s = "a^b/c^d";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 7);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "a");
	EXPECT_EQ(dynamic_cast<variable*>(VL[1])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<operation*>(VL[2])->GetId(), 6);
	EXPECT_EQ(dynamic_cast<variable*>(VL[3])->GetName(), "c");
	EXPECT_EQ(dynamic_cast<variable*>(VL[4])->GetName(), "d");
	EXPECT_EQ(dynamic_cast<operation*>(VL[5])->GetId(), 6);
	EXPECT_EQ(dynamic_cast<operation*>(VL[6])->GetId(), 5);
	s = "a^b/c+d";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 7);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "a");
	EXPECT_EQ(dynamic_cast<variable*>(VL[1])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<operation*>(VL[2])->GetId(), 6);
	EXPECT_EQ(dynamic_cast<variable*>(VL[3])->GetName(), "c");
	EXPECT_EQ(dynamic_cast<operation*>(VL[4])->GetId(), 5);
	EXPECT_EQ(dynamic_cast<variable*>(VL[5])->GetName(), "d");
	EXPECT_EQ(dynamic_cast<operation*>(VL[6])->GetId(), 2);
	s = "-a^4.0";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 4);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "a");
	EXPECT_EQ(dynamic_cast<constant*>(VL[1])->GetVal(), 4.0);
	EXPECT_EQ(dynamic_cast<operation*>(VL[2])->GetId(), 6);
	EXPECT_EQ(dynamic_cast<operation*>(VL[3])->GetId(), 7);
	s = "a^b^c";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 5);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "a");
	EXPECT_EQ(dynamic_cast<variable*>(VL[1])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<operation*>(VL[2])->GetId(), 6);
	EXPECT_EQ(dynamic_cast<variable*>(VL[3])->GetName(), "c");
	EXPECT_EQ(dynamic_cast<operation*>(VL[4])->GetId(), 6);
}

TEST(MainParse, handles_brackets)
{
	string s{ "(x)" };
	Vec<lexem*> VL;
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 1);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "x");
	s = "-(2.0)";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 2);
	EXPECT_EQ(dynamic_cast<constant*>(VL[0])->GetVal(), 2.0);
	EXPECT_EQ(dynamic_cast<operation*>(VL[1])->GetId(), 7);
	s = "(-2.0)";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 1);
	EXPECT_EQ(dynamic_cast<constant*>(VL[0])->GetVal(), -2.0);
	s = "-(a+b)";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 4);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "a");
	EXPECT_EQ(dynamic_cast<variable*>(VL[1])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<operation*>(VL[2])->GetId(), 2);
	EXPECT_EQ(dynamic_cast<operation*>(VL[3])->GetId(), 7);
	s = "(a+b)*17";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 5);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "a");
	EXPECT_EQ(dynamic_cast<variable*>(VL[1])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<operation*>(VL[2])->GetId(), 2);
	EXPECT_EQ(dynamic_cast<constant*>(VL[3])->GetVal(), 17.0);
	EXPECT_EQ(dynamic_cast<operation*>(VL[4])->GetId(), 4);
	s = "a^(b^c)";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 5);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "a");
	EXPECT_EQ(dynamic_cast<variable*>(VL[1])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<variable*>(VL[2])->GetName(), "c");
	EXPECT_EQ(dynamic_cast<operation*>(VL[3])->GetId(), 6);
	EXPECT_EQ(dynamic_cast<operation*>(VL[4])->GetId(), 6);
	s = "a+b*c^(d+f*g^h)";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 13);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "a");
	EXPECT_EQ(dynamic_cast<variable*>(VL[1])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<variable*>(VL[2])->GetName(), "c");
	EXPECT_EQ(dynamic_cast<variable*>(VL[3])->GetName(), "d");
	EXPECT_EQ(dynamic_cast<variable*>(VL[4])->GetName(), "f");
	EXPECT_EQ(dynamic_cast<variable*>(VL[5])->GetName(), "g");
	EXPECT_EQ(dynamic_cast<variable*>(VL[6])->GetName(), "h");
	EXPECT_EQ(dynamic_cast<operation*>(VL[7])->GetId(), 6);
	EXPECT_EQ(dynamic_cast<operation*>(VL[8])->GetId(), 4);
	EXPECT_EQ(dynamic_cast<operation*>(VL[9])->GetId(), 2);
	EXPECT_EQ(dynamic_cast<operation*>(VL[10])->GetId(), 6);
	EXPECT_EQ(dynamic_cast<operation*>(VL[11])->GetId(), 4);
	EXPECT_EQ(dynamic_cast<operation*>(VL[12])->GetId(), 2);
	s = "(a+b)*c^(d+f*g^h)";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 13);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "a");
	EXPECT_EQ(dynamic_cast<variable*>(VL[1])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<operation*>(VL[2])->GetId(), 2);
	EXPECT_EQ(dynamic_cast<variable*>(VL[3])->GetName(), "c");
	EXPECT_EQ(dynamic_cast<variable*>(VL[4])->GetName(), "d");
	EXPECT_EQ(dynamic_cast<variable*>(VL[5])->GetName(), "f");
	EXPECT_EQ(dynamic_cast<variable*>(VL[6])->GetName(), "g");
	EXPECT_EQ(dynamic_cast<variable*>(VL[7])->GetName(), "h");
	EXPECT_EQ(dynamic_cast<operation*>(VL[8])->GetId(), 6);
	EXPECT_EQ(dynamic_cast<operation*>(VL[9])->GetId(), 4);
	EXPECT_EQ(dynamic_cast<operation*>(VL[10])->GetId(), 2);
	EXPECT_EQ(dynamic_cast<operation*>(VL[11])->GetId(), 6);
	EXPECT_EQ(dynamic_cast<operation*>(VL[12])->GetId(), 4);
	s = "-a^(b^c)";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 6);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "a");
	EXPECT_EQ(dynamic_cast<variable*>(VL[1])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<variable*>(VL[2])->GetName(), "c");
	EXPECT_EQ(dynamic_cast<operation*>(VL[3])->GetId(), 6);
	EXPECT_EQ(dynamic_cast<operation*>(VL[4])->GetId(), 6);
	EXPECT_EQ(dynamic_cast<operation*>(VL[5])->GetId(), 7);
}

TEST(MainParse, handles_multiple_consecutive_brackets)
{
	string s{ "(((x)))" };
	Vec<lexem*> VL;
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 1);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "x");
	s = "(((a-b)*c)^d)";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 7);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "a");
	EXPECT_EQ(dynamic_cast<variable*>(VL[1])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<operation*>(VL[2])->GetId(), 3);
	EXPECT_EQ(dynamic_cast<variable*>(VL[3])->GetName(), "c");
	EXPECT_EQ(dynamic_cast<operation*>(VL[4])->GetId(), 4);
	EXPECT_EQ(dynamic_cast<variable*>(VL[5])->GetName(), "d");
	EXPECT_EQ(dynamic_cast<operation*>(VL[6])->GetId(), 6);
	s = "-(-(-(a)))";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 4);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "a");
	EXPECT_EQ(dynamic_cast<operation*>(VL[1])->GetId(), 7);
	EXPECT_EQ(dynamic_cast<operation*>(VL[2])->GetId(), 7);
	EXPECT_EQ(dynamic_cast<operation*>(VL[3])->GetId(), 7);
	s = "-(-(-(a*-b)+-c))";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 10);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "a");
	EXPECT_EQ(dynamic_cast<variable*>(VL[1])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<operation*>(VL[2])->GetId(), 7);
	EXPECT_EQ(dynamic_cast<operation*>(VL[3])->GetId(), 4);
	EXPECT_EQ(dynamic_cast<operation*>(VL[4])->GetId(), 7);
	EXPECT_EQ(dynamic_cast<variable*>(VL[5])->GetName(), "c");
	EXPECT_EQ(dynamic_cast<operation*>(VL[6])->GetId(), 7);
	EXPECT_EQ(dynamic_cast<operation*>(VL[7])->GetId(), 2);
	EXPECT_EQ(dynamic_cast<operation*>(VL[8])->GetId(), 7);
	EXPECT_EQ(dynamic_cast<operation*>(VL[9])->GetId(), 7);
}

TEST(MainParse, can_parse_functions)
{
	string s{ "log(x)" };
	Vec<lexem*> VL;
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 2);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "x");
	EXPECT_EQ(dynamic_cast<operation*>(VL[1])->GetId(), 9);
	s = "cos(pi)";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 2);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "pi");
	EXPECT_EQ(dynamic_cast<operation*>(VL[1])->GetId(), 14);
}

TEST(MainParse, can_parse_expressions_with_similar_to_func_operand_names)
{
	string s{ "sin(sin1)" };
	Vec<lexem*> VL;
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 2);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "sin1");
	EXPECT_EQ(dynamic_cast<operation*>(VL[1])->GetId(), 10);
}

TEST(MainParse, can_parse_function_compositions)
{
	string s{ "sin(log(x))" };
	Vec<lexem*> VL;
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 3);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "x");
	EXPECT_EQ(dynamic_cast<operation*>(VL[1])->GetId(), 9);
	EXPECT_EQ(dynamic_cast<operation*>(VL[2])->GetId(), 10);
	s = "acoth(abs(y))";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 3);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "y");
	EXPECT_EQ(dynamic_cast<operation*>(VL[1])->GetId(), 8);
	EXPECT_EQ(dynamic_cast<operation*>(VL[2])->GetId(), 25);
}

TEST(MainParse, can_parse_compositions_of_functions_and_operations)
{
	string s{ "-tan(a^b)" };
	Vec<lexem*> VL;
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 5);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "a");
	EXPECT_EQ(dynamic_cast<variable*>(VL[1])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<operation*>(VL[2])->GetId(), 6);
	EXPECT_EQ(dynamic_cast<operation*>(VL[3])->GetId(), 18);
	EXPECT_EQ(dynamic_cast<operation*>(VL[4])->GetId(), 7);
	s = "p^log(-atan(h))";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 6);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "p");
	EXPECT_EQ(dynamic_cast<variable*>(VL[1])->GetName(), "h");
	EXPECT_EQ(dynamic_cast<operation*>(VL[2])->GetId(), 19);
	EXPECT_EQ(dynamic_cast<operation*>(VL[3])->GetId(), 7);
	EXPECT_EQ(dynamic_cast<operation*>(VL[4])->GetId(), 9);
	EXPECT_EQ(dynamic_cast<operation*>(VL[5])->GetId(), 6);
	s = "cos(x)^sin(y)";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 5);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "x");
	EXPECT_EQ(dynamic_cast<operation*>(VL[1])->GetId(), 14);
	EXPECT_EQ(dynamic_cast<variable*>(VL[2])->GetName(), "y");
	EXPECT_EQ(dynamic_cast<operation*>(VL[3])->GetId(), 10);
	EXPECT_EQ(dynamic_cast<operation*>(VL[4])->GetId(), 6);
}

TEST(MainParse, throws_when_there_is_no_operation_between_operand_and_function_or_operand)
{
	string s{ "abc35 sin(x)" };
	Vec<lexem*> VL;
	ASSERT_ANY_THROW(VL = MainParse(s));
	s = "cot(y) x";
	ASSERT_ANY_THROW(VL = MainParse(s));
	s = "z x";
	ASSERT_ANY_THROW(VL = MainParse(s));
	s = "sinh(z) cosh(x)";
	ASSERT_ANY_THROW(VL = MainParse(s));
}

TEST(MainParse, throws_when_there_is_no_operation_between_operand_and_opening_bracket)
{
	string s{ "asinn(b)" };
	Vec<lexem*> VL;
	ASSERT_ANY_THROW(VL = MainParse(s));
}

TEST(MainParse, throws_when_brackets_contain_nothing)
{
	string s{ "()" };
	Vec<lexem*> VL;
	ASSERT_ANY_THROW(VL = MainParse(s));
	s = "sin()";
	ASSERT_ANY_THROW(VL = MainParse(s));
}

TEST(MainParse, throws_when_operation_has_no_operand_to_the_left_or_right)
{
	string s{ "+b" };
	Vec<lexem*> VL;
	ASSERT_ANY_THROW(VL = MainParse(s));
	s = "a-b+";
	ASSERT_ANY_THROW(VL = MainParse(s));
	s = "acos(a*)";
	ASSERT_ANY_THROW(VL = MainParse(s));
	s = "acos(/c)";
	ASSERT_ANY_THROW(VL = MainParse(s));
	s = "acos(d)+";
	ASSERT_ANY_THROW(VL = MainParse(s));
}

TEST(MainParse, throws_when_function_arguement_is_out_of_brackets)
{
	string s{ "sin a" };
	Vec<lexem*> VL;
	ASSERT_ANY_THROW(VL = MainParse(s));
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
}