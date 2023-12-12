#include <gtest.h>
#include "arithmetic.h"

TEST(Arithmetic, can_create_postfix_from_infix)
{
    string str = "-(2+3)*2/3+sin(2)";
    ASSERT_NO_THROW(Arithmetic s(str));
}

TEST(Arithmetic, can_correct_create_postfix_to_infix)
{
    string str = "sin(x1+2)*2+3-4*(-1)";
    vector<string> correct;
    correct.push_back("x1");
    correct.push_back("2");
    correct.push_back("+");
    correct.push_back("sin");
    correct.push_back("2");
    correct.push_back("*");
    correct.push_back("3");
    correct.push_back("+");
    correct.push_back("4");
    correct.push_back("1");
    correct.push_back("~");
    correct.push_back("*");
    correct.push_back("-");
    Arithmetic s(str);
    EXPECT_EQ(correct, s.GetPostfix());
}

TEST(Arithmetic, can_correct_create_postfix_to_infix_with_unar_minus)
{
    string str = "-(x1*x2)";
    vector<string> correct;
    correct.push_back("x1");
    correct.push_back("x2");
    correct.push_back("*");
    correct.push_back("~");
    Arithmetic s(str);
    EXPECT_EQ(correct, s.GetPostfix());
}

TEST(Arithmetic, cant_create_postfix_to_infix_with_wrong_first_symbol)
{
    string str = "*(x1+x1)+13";
    Arithmetic s(str);
    ASSERT_ANY_THROW(s.Calculate());
}

TEST(Arithmetic, cant_create_postfix_to_infix_with_wrong_last_symbol)
{
    string str = "(x1+x1)+13.8q";
    ASSERT_ANY_THROW(Arithmetic s(str););
}

TEST(Arithmetic, cant_create_postfix_to_infix_with_wrong_symbol)
{
    string str = "son(x1)";
    ASSERT_ANY_THROW(Arithmetic s(str));
}

TEST(Arithmetic, cant_create_postfix_to_infix_with_wrong_nums_of_bracket_symbol)
{
    string str = "(x1+x1)+ 13.8(";
    ASSERT_ANY_THROW(Arithmetic s(str));
}

TEST(Arithmetic, can_correct_create_double_from_string_just_nums)
{
    string str = "32";
    Arithmetic s(str);
    EXPECT_EQ(32, s.StringToDouble(str));
}

TEST(Arithmetic, can_correct_create_double_from_string_just_nums_with_dot)
{
    string str = "32.4";
    Arithmetic s(str);
    EXPECT_EQ(32.4, s.StringToDouble(str));
}

TEST(Arithmetic, can_correct_create_double_from_string_just_nums_with_e)
{
    string str = "32e3";
    Arithmetic s(str);
    EXPECT_EQ(32000, s.StringToDouble(str));
}

TEST(Arithmetic, can_correct_create_double_from_string_just_nums_with_dot_and_e)
{
    string str = "32.2e2";
    Arithmetic s(str);
    EXPECT_EQ(3220, s.StringToDouble(str));
}

TEST(Arithmetic, can_correct_create_double_from_string_just_nums_with_dot_and_minusE)
{
    string str = "32.2e-2";
    Arithmetic s(str);
    EXPECT_EQ(0.322, s.StringToDouble(str));
}

TEST(Arithmetic, cant_calculate_with_one_multiply_operands)
{
    string str = "2*";
    Arithmetic s(str);
    ASSERT_ANY_THROW(s.Calculate());
}

TEST(Arithmetic, cant_calculate_with_no_cos_operands)
{
    string str = "cos()";
    ASSERT_ANY_THROW(Arithmetic s(str));
}

TEST(Arithmetic, can_get_correct_res_without_xes)
{
    string str = "3+2";
    Arithmetic s(str);
    EXPECT_EQ(5, s.Calculate());
}

TEST(Arithmetic, cant_calculate_with_wrong_sympols)
{
    string str = "+abcd";
    ASSERT_ANY_THROW(Arithmetic s(str));
}

TEST(Arithmetic, cant_calculate_without_sign_before_x)
{
    string str = "3x1";
    ASSERT_ANY_THROW(Arithmetic s(str););
}

TEST(Arithmetic, can_correct_create_double_from_string_dot_with_num)
{
    string str = ".32";
    Arithmetic s(str);
    EXPECT_EQ(0.32, s.StringToDouble(str));
}

TEST(Arithmetic, can_correct_create_double_from_string_dot_with_num_and_e)
{
    string str = ".32e2";
    Arithmetic s(str);
    EXPECT_EQ(32, s.StringToDouble(str));
}


