#pragma once
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
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
	s = "_VL";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 1);
	EXPECT_EQ((dynamic_cast<variable*>(VL[0]))->GetName(), "_VL");
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
	s = "i_13";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 1);
	EXPECT_EQ((dynamic_cast<variable*>(VL[0]))->GetName(), "i_13");
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
	s = "pi";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 1);
	EXPECT_EQ((dynamic_cast<variable*>(VL[0]))->GetName(), "pi");
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
	s = "0.16e+4";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 1);
	EXPECT_EQ((dynamic_cast<constant*>(VL[0]))->GetVal(), 0.16e+4);
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
	s = "-0.16e+4";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 1);
	EXPECT_EQ((dynamic_cast<constant*>(VL[0]))->GetVal(), -0.16e+4);
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
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
	variable::GetValVec().clear();
	variable::GetNameVec().clear();

}

TEST(MainParse, throws_when_variable_has_letters_after_index)
{
	string s{ "abc35D" };
	Vec<lexem*> VL;
	ASSERT_ANY_THROW(VL = MainParse(s));
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
}


TEST(MainParse, throws_when_there_is_no_space_between_numbers)
{
	string s{ "12.35e+4012.16" };
	Vec<lexem*> VL;
	ASSERT_ANY_THROW(VL = MainParse(s));
	s = "25.1635.12";
	ASSERT_ANY_THROW(VL = MainParse(s));
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
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
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
	s = "-b";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 2);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<operation*>(VL[1])->GetId(), 7);
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
	s = "e ^ x";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 3);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "e");
	EXPECT_EQ(dynamic_cast<variable*>(VL[1])->GetName(), "x");
	EXPECT_EQ(dynamic_cast<operation*>(VL[2])->GetId(), 6);
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
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
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
	s = "-     b";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 2);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<operation*>(VL[1])->GetId(), 7);
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
}

TEST(MainParse, handles_multiple_unary_minuses)
{
	string s{ "---  --- - b" };
	Vec<lexem*> VL;
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 2);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<operation*>(VL[1])->GetId(), 7);
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
	s = "--b";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 1);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "b");
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
	s = "a--b";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 4);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "a");
	EXPECT_EQ(dynamic_cast<variable*>(VL[1])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<operation*>(VL[2])->GetId(), 7);
	EXPECT_EQ(dynamic_cast<operation*>(VL[3])->GetId(), 3);
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
	s = "a+--b";
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 3);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "a");
	EXPECT_EQ(dynamic_cast<variable*>(VL[1])->GetName(), "b");
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
}

TEST(MainParse, handles_prioriites_of_operations)
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
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
	s = "a*b+c";;
	ASSERT_NO_THROW(VL = MainParse(s));
	EXPECT_EQ(VL.GetSize(), 5);
	EXPECT_EQ(dynamic_cast<variable*>(VL[0])->GetName(), "a");
	EXPECT_EQ(dynamic_cast<variable*>(VL[1])->GetName(), "b");
	EXPECT_EQ(dynamic_cast<operation*>(VL[2])->GetId(), 4);
	EXPECT_EQ(dynamic_cast<variable*>(VL[3])->GetName(), "c");
	EXPECT_EQ(dynamic_cast<operation*>(VL[4])->GetId(), 2);
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
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
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
}

TEST(MainParse, throws_8)
{

}

TEST(MainParse, throws_9)
{

}

TEST(MainParse, throws_when_there_is_no_operation_between_operand_and_function_or_operand)
{
	string s{ "abc35 sin" };
	Vec<lexem*> VL;
	ASSERT_ANY_THROW(VL = MainParse(s));
}

TEST(MainParse, _end)
{
	variable::GetValVec().clear();
	variable::GetNameVec().clear();
}