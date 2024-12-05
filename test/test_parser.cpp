#include "parser.h"
#include <gtest.h>

TEST(parser, good_parser_test_0)
{
	double eps = 1e-21;
	EXPECT_EQ(true, abs(parser("123e+1")-123e+1)<eps);
}

TEST(parser, good_parser_test_1)
{
	double eps = 1e-19;
	EXPECT_EQ(true, abs(parser("123321") - 123321.0) < eps);
}

TEST(parser, good_parser_test_2)
{
	double eps = 1e-25;
	EXPECT_EQ(true, abs(parser("1.111111111") - 1.111111111) < eps);
}

TEST(parser, good_parser_test_3)
{
	double eps = 1e-29;
	EXPECT_EQ(true, abs(parser("000.0005") - 000.0005) < eps);
}


TEST(parser, good_parser_test_4)
{
	double eps = 1e-31;
	EXPECT_EQ(true, abs(parser("0.000005") - 0.000005) < eps);
}

TEST(parser, good_parser_test_5)
{
	double eps = 1e-28;
	EXPECT_EQ(true, abs(parser("-00.001") - -00.001) < eps);
}

TEST(parser, good_parser_test_6)
{
	double eps = 1e-21;
	EXPECT_EQ(true, abs(parser("-123.321e+1") - -123.321e+1) < eps);
}

TEST(parser, good_parser_test_7)
{
	double eps = 1e-21;
	EXPECT_EQ(true, abs(parser("-123.321E+1") - -123.321e+1) < eps);
}


TEST(parser, good_parser_test_8)
{
	double eps = 1e-20;
	EXPECT_EQ(true, abs(parser("-123.321e-7") - -123.321e-7) < eps);
}

TEST(parser, good_parser_test_9)
{
	double eps = 1e-27;
	EXPECT_EQ(true, abs(parser("-.05") - -.05) < eps);
}

TEST(parser, bad_parser_test_0)
{
	ASSERT_ANY_THROW(parser("123.e+1"));
}

TEST(parser, bad_parser_test_1)
{
	ASSERT_ANY_THROW(parser("123e-"));
}

TEST(parser, bad_parser_test_2)
{
	ASSERT_ANY_THROW(parser("-"));
}

TEST(parser, bad_parser_test_3)
{
	ASSERT_ANY_THROW(parser("-e"));
}

TEST(parser, bad_parser_test_4)
{
	ASSERT_ANY_THROW(parser("e"));
}

TEST(parser, bad_parser_test_5)
{
	ASSERT_ANY_THROW(parser("e+4"));
}

TEST(parser, bad_parser_test_6)
{
	ASSERT_ANY_THROW(parser("e"));
}

TEST(parser, bad_parser_test_7)
{
	ASSERT_ANY_THROW(parser("-123..321e+1"));
}

TEST(parser, bad_parser_test_8)
{
	ASSERT_ANY_THROW(parser("-123.32.1e+1"));
}

TEST(parser, bad_parser_test_9)
{
	ASSERT_ANY_THROW(parser("-123.32.1e+"));
}

TEST(parser, bad_parser_test_10)
{
	ASSERT_ANY_THROW(parser("--123.321e+1"));
}