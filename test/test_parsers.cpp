#include "parsers.h"
#include "expr_err.h"
#include <gtest.h>

TEST(PreParse, can_delete_spaces)
{
	string s("    ab   ( ) + ---        "), r;
	ASSERT_NO_THROW(r = PreParse(s));
	EXPECT_EQ(r, "ab ( ) + ---");
}

TEST(PreParse, throws_when_no_opening_bracket_met)
{
	string s("ab(12+1))*(2+3)"), r;
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
	string s("ab(12+1*(2+3)"), r;
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