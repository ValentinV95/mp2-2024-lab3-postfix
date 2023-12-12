// òåñòû äëÿ âû÷èñëåíèÿ àðèôìåòè÷åñêèõ âûðàæåíèé

#include <gtest.h>
#include "arithmetic.h"

TEST(TPostfix, can_create_tpostfix_with_infix)
{
    string str = "a+b";

    ASSERT_NO_THROW(TPostfix tmp(str));
}

TEST(TPostfix, throw_when_unequal_quantity_of_brackets)
{
    string str1 = "(a+b))";
    string str2 = "((a+b)";
    string str3 = "((a+b))-c)";

    ASSERT_ANY_THROW(TPostfix tmp(str1));
    ASSERT_ANY_THROW(TPostfix tmp(str2));
    ASSERT_ANY_THROW(TPostfix tmp(str3));
}

TEST(TPostfix, throw_when_sum_operation_in_wrong_position)
{
    string str = "a++b";

    ASSERT_ANY_THROW(TPostfix tmp(str));
}

TEST(TPostfix, throw_when_dif_operation_in_wrong_position)
{
    string str = "a+b-";

    ASSERT_ANY_THROW(TPostfix tmp(str));
}

TEST(TPostfix, throw_when_mult_operation_in_wrong_position)
{
    string str = "*a*b";

    ASSERT_ANY_THROW(TPostfix tmp(str));
}

TEST(TPostfix, throw_when_div_operation_in_wrong_position)
{
    string str = "a//b";

    ASSERT_ANY_THROW(TPostfix tmp(str));
}

TEST(TPostfix, throw_when_operation_sign_is_omitted)
{
    string str1 = "ab+1";
    string str2 = "a+2b";
    ASSERT_ANY_THROW(TPostfix tmp(str1));
    ASSERT_ANY_THROW(TPostfix tmp(str2));
}

TEST(TPostfix, throw_when_point_in_wrong_position)
{
    string str = ".a+b";
    ASSERT_ANY_THROW(TPostfix tmp(str));
}

TEST(TPostfix, throw_when_E_in_wrong_position)
{
    string str = "a+Eb";
    ASSERT_ANY_THROW(TPostfix tmp(str));
}

TEST(TPostfix, can_correct_convertation_string_to_number)
{
    string str = "37";
    TPostfix new_str(str);
    EXPECT_EQ(37, new_str.string_in_double("37"));
}

TEST(TPostfix, can_correct_convertation_string_with_dot_to_number)
{
    string str = "37.7";
    TPostfix new_str(str);
    EXPECT_EQ(37.7, new_str.string_in_double("37.7"));
}

TEST(TPostfix, can_correct_convertation_string_with_dot_and_E_to_number)
{
    string str = "37.7E1";
    TPostfix new_str(str);
    EXPECT_EQ(377, new_str.string_in_double("37.7E1"));
}

TEST(TPostfix, can_correct_get_infix)
{
    string str = "a+b";
    TPostfix tmp(str);
    EXPECT_EQ(str, tmp.getInfix());
}

TEST(TPostfix, can_correct_converting_to_postfix_form_1)
{
    TPostfix str = "2+345";
    str.toPostfix();
    EXPECT_EQ("2345+", str.getPostfix());
}

TEST(TPostfix, can_correct_converting_to_postfix_form_2)
{
    TPostfix str("---5+3");
    str.toPostfix();
    EXPECT_EQ("5~~~3+", str.getPostfix());
}

TEST(TPostfix, can_correct_calculating_1)
{
    double temp = 37.7 + 1;
    TPostfix str("37.7+1");
    str.toPostfix();
    str.toCalculate();
    EXPECT_EQ(str.getResult(), temp);
}

TEST(TPostfix, can_correct_calculating_2)
{
    double temp = 7 - 5;
    TPostfix str("7-5");
    str.toPostfix();
    str.toCalculate();
    EXPECT_EQ(str.getResult(), temp);
}

TEST(TPostfix, can_correct_calculating_3)
{
    double temp = 3.1 * 2;
    TPostfix str("3.1*2");
    str.toPostfix();
    str.toCalculate();
    EXPECT_EQ(str.getResult(), temp);
}

TEST(TPostfix, can_correct_calculating_4)
{
    TPostfix str("8/0");
    str.toPostfix();
    ASSERT_ANY_THROW(str.toCalculate());
}
