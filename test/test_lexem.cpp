#include <gtest.h>
#include "lexem.h"

TEST(LexemeTest, ConstructorTest) {
    Lexeme lexeme(1, "1");
    EXPECT_EQ(lexeme.type(), 1);
    EXPECT_EQ(lexeme.value(), "1");
}

TEST(LexemeTest, SetNumberTest) {
    Lexeme lexeme(1, "1");
    lexeme.setnumber(3.14);
    EXPECT_DOUBLE_EQ(lexeme.number(), 3.14);
}

TEST(LexemeTest, ToStringTest) {
    Lexeme lexeme(1, "1");
    EXPECT_EQ(lexeme.toString(), "Type: NUMBER, Value: 1");
}

TEST(LexemeTest, TypeToStringOperator) {
    Lexeme lexeme(2, "+");
    EXPECT_EQ(lexeme.toString(), "Type: OPERATOR, Value: +");
}

TEST(LexemeTest, TypeToStringLeft) {
    Lexeme lexeme(3, "(");
    EXPECT_EQ(lexeme.toString(), "Type: LEFT, Value: (");
}

TEST(LexemeTest, TypeToStringRight) {
    Lexeme lexeme(4, ")");
    EXPECT_EQ(lexeme.toString(), "Type: RIGHT, Value: )");
}

TEST(LexemeTest, TypeToStringFunction) {
    Lexeme lexeme(5, "sin");
    EXPECT_EQ(lexeme.toString(), "Type: FUNCTION, Value: sin");
}

TEST(LexemeTest, TypeToStringVariable) {
    Lexeme lexeme(6, "x");
    EXPECT_EQ(lexeme.toString(), "Type: VARIABLE, Value: x");
}

TEST(LexemeTest, TypeToStringUnknown) {
    Lexeme lexeme(99, "unknown");
    EXPECT_EQ(lexeme.toString(), "Type: UNKNOWN, Value: unknown");
}

TEST(LexemeTest, SetNumberNegativeTest) {
    Lexeme lexeme(1, "-3.0");
    lexeme.setnumber(-5.0);
    EXPECT_DOUBLE_EQ(lexeme.number(), -5.0);
}

TEST(LexemeTest, SetNumberZeroTest) {
    Lexeme lexeme(1, "0.0");
    lexeme.setnumber(0.0);
    EXPECT_DOUBLE_EQ(lexeme.number(), 0.0);
}

TEST(LexemeTest, TypeTest) {
    Lexeme lexeme(1, "1");
    EXPECT_EQ(lexeme.type(), 1);
}

TEST(LexemeTest, ValueTest) {
    Lexeme lexeme(1, "1");
    EXPECT_EQ(lexeme.value(), "1");
}

TEST(LexemeTest, MultipleLexemesTest) {
    Lexeme lexeme1(1, "a");
    Lexeme lexeme2(2, "+");
    Lexeme lexeme3(3, "(");
    EXPECT_EQ(lexeme1.toString(), "Type: NUMBER, Value: a");
    EXPECT_EQ(lexeme2.toString(), "Type: OPERATOR, Value: +");
    EXPECT_EQ(lexeme3.toString(), "Type: LEFT, Value: (");
}

TEST(LexemeTest, TypeBoundaryTest) {
    Lexeme lexeme(0, "boundary");
    EXPECT_EQ(lexeme.toString(), "Type: UNKNOWN, Value: boundary");
}

TEST(LexemeTest, LargeNumberTest) {
    Lexeme lexeme(1, "large");
    lexeme.setnumber(1e10);
    EXPECT_DOUBLE_EQ(lexeme.number(), 1e10);
}

TEST(LexemeTest, SmallNumberTest) {
    Lexeme lexeme(1, "small");
    lexeme.setnumber(1e-10);
    EXPECT_DOUBLE_EQ(lexeme.number(), 1e-10);
}

TEST(LexemeTest, StringValueWithSpacesTest) {
    Lexeme lexeme(1, "value with spaces");
    EXPECT_EQ(lexeme.value(), "value with spaces");
}

TEST(LexemeTest, TypeTestWithDifferentValues) {
    Lexeme lexeme(2, "operator");
    EXPECT_EQ(lexeme.type(), 2);
    EXPECT_EQ(lexeme.value(), "operator");
}

TEST(LexemeTest, TypeTestWithNegativeValue) {
    Lexeme lexeme(1, "-5");
    EXPECT_EQ(lexeme.type(), 1);
    EXPECT_EQ(lexeme.value(), "-5");
}

TEST(LexemeTest, PrecedenceOperators) {
    Lexeme plus(2, "+");
    Lexeme minus(2, "-");
    Lexeme multiply(2, "*");
    Lexeme divide(2, "/");
    Lexeme power(2, "^");

    EXPECT_EQ(plus.precedence(), 1);
    EXPECT_EQ(minus.precedence(), 1);
    EXPECT_EQ(multiply.precedence(), 2);
    EXPECT_EQ(divide.precedence(), 2);
    EXPECT_EQ(power.precedence(), 3);
}

TEST(LexemeTest, PrecedenceNonOperators) {
    Lexeme number(1, "5");
    Lexeme leftParen(3, "(");
    Lexeme rightParen(4, ")");

    EXPECT_EQ(number.precedence(), 0);
    EXPECT_EQ(leftParen.precedence(), 0);
    EXPECT_EQ(rightParen.precedence(), 0);
}

TEST(LexemeTest, PrecedenceUnknownType) {
    Lexeme unknown(7, "unknown");

    EXPECT_EQ(unknown.precedence(), 0);
}

TEST(LexemeTest, EqualityOperator) {
    Lexeme lexeme1(1, "1");
    Lexeme lexeme2(1, "1");
    Lexeme lexeme3(2, "+");
    Lexeme lexeme4(1, "2");

    EXPECT_TRUE(lexeme1 == lexeme2); 
    EXPECT_FALSE(lexeme1 == lexeme3);
    EXPECT_FALSE(lexeme1 == lexeme4); 
}

TEST(LexemeTest, InequalityOperator) {
    Lexeme lexeme1(1, "1");
    Lexeme lexeme2(1, "1");
    Lexeme lexeme3(2, "+");
    Lexeme lexeme4(1, "2");

    EXPECT_FALSE(lexeme1 != lexeme2);
    EXPECT_TRUE(lexeme1 != lexeme3);
    EXPECT_TRUE(lexeme1 != lexeme4);
}