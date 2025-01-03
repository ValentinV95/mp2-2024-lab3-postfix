#include <gtest.h>
#include "StringToDouble.h"

TEST(StringToDouble_1Test, ValidInteger) {
    EXPECT_DOUBLE_EQ(StringToDouble_1("123"), 123.0);
    EXPECT_DOUBLE_EQ(StringToDouble_1("0"), 0.0);
    EXPECT_DOUBLE_EQ(StringToDouble_1("-456"), -456.0);
}

TEST(StringToDouble_1Test, ValidFloatingPoint) {
    EXPECT_DOUBLE_EQ(StringToDouble_1("123.456"), 123.456);
    EXPECT_DOUBLE_EQ(StringToDouble_1("-123.456"), -123.456);
    EXPECT_DOUBLE_EQ(StringToDouble_1("0.001"), 0.001);
}

TEST(StringToDouble_1Test, ValidScientificNotation) {
    EXPECT_DOUBLE_EQ(StringToDouble_1("1e+3"), 1000.0);
    EXPECT_DOUBLE_EQ(StringToDouble_1("1E-3"), 0.001);
    EXPECT_DOUBLE_EQ(StringToDouble_1("1.5e-2"), 0.015);
    EXPECT_DOUBLE_EQ(StringToDouble_1("-2.5E+2"), -250.0);
    ASSERT_ANY_THROW(StringToDouble_1("1e3"));
    ASSERT_ANY_THROW(StringToDouble_1("1E3"));
}

TEST(StringToDouble_1Test, ValidMixedNotation) {
    EXPECT_DOUBLE_EQ(StringToDouble_1("123.45e+2"), 12345.0);
    EXPECT_DOUBLE_EQ(StringToDouble_1("-123.45E-2"), -1.2345);
}

TEST(StringToDouble_1Test, InvalidInput) {
    EXPECT_THROW(StringToDouble_1("abc"), std::logic_error);
    EXPECT_THROW(StringToDouble_1("123e"), std::logic_error);
    EXPECT_THROW(StringToDouble_1("123e+"), std::logic_error);
    EXPECT_THROW(StringToDouble_1("123e-"), std::logic_error);
    EXPECT_THROW(StringToDouble_1("1.2.3"), std::logic_error);
    EXPECT_THROW(StringToDouble_1("1.2e3.4"), std::logic_error);
}

TEST(StringToDouble_1Test, EdgeCases) {
    EXPECT_DOUBLE_EQ(StringToDouble_1("0.0"), 0.0);
    EXPECT_DOUBLE_EQ(StringToDouble_1("-0.0"), -0.0);
    EXPECT_DOUBLE_EQ(StringToDouble_1("1e+0"), 1.0);
    EXPECT_DOUBLE_EQ(StringToDouble_1("-1e+0"), -1.0);
}

TEST(StringToDouble_1Test, LargeNumbers) {
    EXPECT_DOUBLE_EQ(StringToDouble_1("1e+10"), 10000000000.0);
    EXPECT_DOUBLE_EQ(StringToDouble_1("1E+20"), 1e20);
    EXPECT_DOUBLE_EQ(StringToDouble_1("-1e+30"), -1e30);
}

TEST(StringToDouble_1Test, SmallNumbers) {
    EXPECT_DOUBLE_EQ(StringToDouble_1("1e-10"), 1e-10);
    EXPECT_DOUBLE_EQ(StringToDouble_1("1E-20"), 1e-20);
    EXPECT_DOUBLE_EQ(StringToDouble_1("-1e-30"), -1e-30);
}

TEST(StringToDouble_1Test, MixedSigns) {
    EXPECT_DOUBLE_EQ(StringToDouble_1("-1.5e+3"), -1500.0);
    EXPECT_DOUBLE_EQ(StringToDouble_1("2.5e-2"), 0.025);
}

TEST(StringToDouble_1Test, SingleDigit) {
    EXPECT_DOUBLE_EQ(StringToDouble_1("7"), 7.0);
    EXPECT_DOUBLE_EQ(StringToDouble_1("-3"), -3.0);
}

TEST(StringToDouble_1Test, ZeroInScientificNotation) {
    EXPECT_DOUBLE_EQ(StringToDouble_1("0e+10"), 0.0);
    EXPECT_DOUBLE_EQ(StringToDouble_1("0E-10"), 0.0);
}

TEST(StringToDouble_1Test, InvalidCharacters) {
    EXPECT_THROW(StringToDouble_1("123a"), std::logic_error);
    EXPECT_THROW(StringToDouble_1("12.3.4"), std::logic_error);
}

TEST(StringToDouble_1Test, EmptyString) {
    EXPECT_THROW(StringToDouble_1(""), std::logic_error);
}

TEST(StringToDouble_1Test, OnlySpaces) {
    EXPECT_THROW(StringToDouble_1("   "), std::logic_error);
}

TEST(StringToDouble_1Test, ValidNegativeScientificNotation) {
    EXPECT_DOUBLE_EQ(StringToDouble_1("-1.5e-3"), -0.0015);
}

TEST(StringToDouble_1Test, ValidPositiveScientificNotation) {
    EXPECT_DOUBLE_EQ(StringToDouble_1("1.5e+3"), 1500.0);
}

TEST(StringToDouble_1Test, ValidNegativeFloatingPoint) {
    EXPECT_DOUBLE_EQ(StringToDouble_1("-0.123"), -0.123);
}

TEST(StringToDouble_1Test, ValidPositiveFloatingPoint) {
    EXPECT_DOUBLE_EQ(StringToDouble_1("0.123"), 0.123);
}

TEST(StringToDouble_1Test, ValidIntegerWithLeadingZeros) {
    EXPECT_DOUBLE_EQ(StringToDouble_1("000123"), 123.0);
    EXPECT_DOUBLE_EQ(StringToDouble_1("-000123"), -123.0);
}

TEST(StringToDouble_1Test, ValidFloatingPointWithLeadingZeros) {
    EXPECT_DOUBLE_EQ(StringToDouble_1("000123.456"), 123.456);
    EXPECT_DOUBLE_EQ(StringToDouble_1("-000123.456"), -123.456);
}

TEST(StringToDouble_1Test, ValidScientificNotationWithLeadingZeros) {
    EXPECT_DOUBLE_EQ(StringToDouble_1("0001e+3"), 1000.0);
    EXPECT_DOUBLE_EQ(StringToDouble_1("-0001E-3"), -0.001);
}

TEST(StringToDouble_1Test, ValidNegativeFloatingPointWithLeadingZeros) {
    EXPECT_DOUBLE_EQ(StringToDouble_1("-0000.123"), -0.123);
}

TEST(StringToDouble_1Test, ValidPositiveFloatingPointWithLeadingZeros) {
    EXPECT_DOUBLE_EQ(StringToDouble_1("0000.123"), 0.123);
}