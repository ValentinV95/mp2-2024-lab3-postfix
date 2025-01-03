#include <gtest.h>
#include "rpn.h"

TEST(ToRPNTests, SimpleAddition) {
    Vector<Lexeme> infix;
    infix.push_back(Lexeme(1, "3")); 
    infix.push_back(Lexeme(2, "+"));
    infix.push_back(Lexeme(1, "4")); 

    Vector<Lexeme> expected;
    expected.push_back(Lexeme(1, "3"));
    expected.push_back(Lexeme(1, "4"));
    expected.push_back(Lexeme(2, "+"));

    EXPECT_EQ(toRPN(infix), expected);
}

TEST(ToRPNTests, SimpleSubtraction) {
    Vector<Lexeme> infix;
    infix.push_back(Lexeme(1, "5"));
    infix.push_back(Lexeme(2, "-"));
    infix.push_back(Lexeme(1, "2"));

    Vector<Lexeme> expected;
    expected.push_back(Lexeme(1, "5"));
    expected.push_back(Lexeme(1, "2"));
    expected.push_back(Lexeme(2, "-"));

    EXPECT_EQ(toRPN(infix), expected);
}

TEST(ToRPNTests, SimpleMultiplication) {
    Vector<Lexeme> infix;
    infix.push_back(Lexeme(1, "2"));
    infix.push_back(Lexeme(2, "*"));
    infix.push_back(Lexeme(1, "3"));

    Vector<Lexeme> expected;
    expected.push_back(Lexeme(1, "2"));
    expected.push_back(Lexeme(1, "3"));
    expected.push_back(Lexeme(2, "*"));

    EXPECT_EQ(toRPN(infix), expected);
}

TEST(ToRPNTests, SimpleDivision) {
    Vector<Lexeme> infix;
    infix.push_back(Lexeme(1, "8"));
    infix.push_back(Lexeme(2, "/"));
    infix.push_back(Lexeme(1, "4"));

    Vector<Lexeme> expected;
    expected.push_back(Lexeme(1, "8"));
    expected.push_back(Lexeme(1, "4"));
    expected.push_back(Lexeme(2, "/"));

    EXPECT_EQ(toRPN(infix), expected);
}

TEST(ToRPNTests, MixedOperators) {
    Vector<Lexeme> infix;
    infix.push_back(Lexeme(1, "3"));
    infix.push_back(Lexeme(2, "+"));
    infix.push_back(Lexeme(1, "4"));
    infix.push_back(Lexeme(2, "*"));
    infix.push_back(Lexeme(1, "2"));

    Vector<Lexeme> expected;
    expected.push_back(Lexeme(1, "3"));
    expected.push_back(Lexeme(1, "4"));
    expected.push_back(Lexeme(1, "2"));
    expected.push_back(Lexeme(2, "*"));
    expected.push_back(Lexeme(2, "+"));

    EXPECT_EQ(toRPN(infix), expected);
}

TEST(ToRPNTests, Parentheses) {
    Vector<Lexeme> infix;
    infix.push_back(Lexeme(3, "("));
    infix.push_back(Lexeme(1, "1"));
    infix.push_back(Lexeme(2, "+"));
    infix.push_back(Lexeme(1, "2"));
    infix.push_back(Lexeme(4, ")"));

    Vector<Lexeme> expected;
    expected.push_back(Lexeme(1, "1"));
    expected.push_back(Lexeme(1, "2"));
    expected.push_back(Lexeme(2, "+"));

    EXPECT_EQ(toRPN(infix), expected);
}

TEST(ToRPNTests, NestedParentheses) {
    Vector<Lexeme> infix;
    infix.push_back(Lexeme(3, "("));
    infix.push_back(Lexeme(3, "("));
    infix.push_back(Lexeme(1, "3"));
    infix.push_back(Lexeme(2, "+"));
    infix.push_back(Lexeme(1, "4"));
    infix.push_back(Lexeme(4, ")"));
    infix.push_back(Lexeme(2, "*"));
    infix.push_back(Lexeme(1, "2"));
    infix.push_back(Lexeme(4, ")"));
    Vector<Lexeme> expected;
    expected.push_back(Lexeme(1, "3"));
    expected.push_back(Lexeme(1, "4"));
    expected.push_back(Lexeme(2, "+"));
    expected.push_back(Lexeme(1, "2"));
    expected.push_back(Lexeme(2, "*"));
    EXPECT_EQ(toRPN(infix), expected);
}

TEST(ToRPNTests, MismatchedParentheses) {
    Vector<Lexeme> infix;
    infix.push_back(Lexeme(3, "("));
    infix.push_back(Lexeme(1, "3"));
    infix.push_back(Lexeme(2, "+"));
    infix.push_back(Lexeme(1, "4"));
    EXPECT_THROW(toRPN(infix), std::runtime_error);
}

TEST(ToRPNTests, Exponentiation) {
    Vector<Lexeme> infix;
    infix.push_back(Lexeme(1, "2"));
    infix.push_back(Lexeme(2, "^"));
    infix.push_back(Lexeme(1, "3"));
    Vector<Lexeme> expected;
    expected.push_back(Lexeme(1, "2"));
    expected.push_back(Lexeme(1, "3"));
    expected.push_back(Lexeme(2, "^"));
    EXPECT_EQ(toRPN(infix), expected);
}

TEST(ToRPNTests, ComplexExpression) {
    Vector<Lexeme> infix;
    infix.push_back(Lexeme(1, "5"));
    infix.push_back(Lexeme(2, "-"));
    infix.push_back(Lexeme(3, "("));
    infix.push_back(Lexeme(1, "3"));
    infix.push_back(Lexeme(2, "+"));
    infix.push_back(Lexeme(1, "4"));
    infix.push_back(Lexeme(4, ")"));
    Vector<Lexeme> expected;
    expected.push_back(Lexeme(1, "5"));
    expected.push_back(Lexeme(1, "3"));
    expected.push_back(Lexeme(1, "4"));
    expected.push_back(Lexeme(2, "+"));
    expected.push_back(Lexeme(2, "-"));
    EXPECT_EQ(toRPN(infix), expected);
}

TEST(ToRPNTests, MultipleOperators) {
    Vector<Lexeme> infix;
    infix.push_back(Lexeme(1, "1"));
    infix.push_back(Lexeme(2, "+"));
    infix.push_back(Lexeme(1, "2"));
    infix.push_back(Lexeme(2, "*"));
    infix.push_back(Lexeme(1, "3"));
    Vector<Lexeme> expected;
    expected.push_back(Lexeme(1, "1"));
    expected.push_back(Lexeme(1, "2"));
    expected.push_back(Lexeme(1, "3"));
    expected.push_back(Lexeme(2, "*"));
    expected.push_back(Lexeme(2, "+"));
    EXPECT_EQ(toRPN(infix), expected);
}

TEST(ToRPNTests, SingleNumber) {
    Vector<Lexeme> infix;
    infix.push_back(Lexeme(1, "42"));
    Vector<Lexeme> expected;
    expected.push_back(Lexeme(1, "42"));
    EXPECT_EQ(toRPN(infix), expected);
}

TEST(ToRPNTests, EmptyInput) {
    Vector<Lexeme> infix;
    infix.push_back(Lexeme(0, ""));
    Vector<Lexeme> expected;
    expected.push_back(Lexeme(0, ""));
    EXPECT_EQ(toRPN(infix), expected);
}

TEST(ToRPNTests, MultipleParentheses) {
    Vector<Lexeme> infix;
    infix.push_back(Lexeme(3, "("));
    infix.push_back(Lexeme(1, "1"));
    infix.push_back(Lexeme(2, "+"));
    infix.push_back(Lexeme(3, "("));
    infix.push_back(Lexeme(1, "2"));
    infix.push_back(Lexeme(2, "*"));
    infix.push_back(Lexeme(1, "3"));
    infix.push_back(Lexeme(4, ")"));
    infix.push_back(Lexeme(4, ")"));
    Vector<Lexeme> expected;
    expected.push_back(Lexeme(1, "1"));
    expected.push_back(Lexeme(1, "2"));
    expected.push_back(Lexeme(1, "3"));
    expected.push_back(Lexeme(2, "*"));
    expected.push_back(Lexeme(2, "+"));
    EXPECT_EQ(toRPN(infix), expected);
}

TEST(ToRPNTests, OperatorPrecedence) {
    Vector<Lexeme> infix;
    infix.push_back(Lexeme(1, "1"));
    infix.push_back(Lexeme(2, "+"));
    infix.push_back(Lexeme(1, "2"));
    infix.push_back(Lexeme(2, "*"));
    infix.push_back(Lexeme(1, "3"));
    Vector<Lexeme> expected;
    expected.push_back(Lexeme(1, "1"));
    expected.push_back(Lexeme(1, "2"));
    expected.push_back(Lexeme(1, "3"));
    expected.push_back(Lexeme(2, "*"));
    expected.push_back(Lexeme(2, "+"));
    EXPECT_EQ(toRPN(infix), expected);
}

TEST(ToRPNTests, ComplexWithParentheses) {
    Vector<Lexeme> infix;
    infix.push_back(Lexeme(3, "("));
    infix.push_back(Lexeme(1, "1"));
    infix.push_back(Lexeme(2, "+"));
    infix.push_back(Lexeme(3, "("));
    infix.push_back(Lexeme(1, "2"));
    infix.push_back(Lexeme(2, "*"));
    infix.push_back(Lexeme(1, "3"));
    infix.push_back(Lexeme(4, ")"));
    infix.push_back(Lexeme(4, ")"));
    Vector<Lexeme> expected;
    expected.push_back(Lexeme(1, "1"));
    expected.push_back(Lexeme(1, "2"));
    expected.push_back(Lexeme(1, "3"));
    expected.push_back(Lexeme(2, "*"));
    expected.push_back(Lexeme(2, "+"));
    EXPECT_EQ(toRPN(infix), expected);
}

TEST(ToRPNTests, MultipleOperatorsWithParentheses) {
    Vector<Lexeme> infix;
    infix.push_back(Lexeme(3, "("));
    infix.push_back(Lexeme(1, "1"));
    infix.push_back(Lexeme(2, "+"));
    infix.push_back(Lexeme(3, "("));
    infix.push_back(Lexeme(1, "2"));
    infix.push_back(Lexeme(2, "*"));
    infix.push_back(Lexeme(1, "3"));
    infix.push_back(Lexeme(4, ")"));
    infix.push_back(Lexeme(4, ")"));
    Vector<Lexeme> expected;
    expected.push_back(Lexeme(1, "1"));
    expected.push_back(Lexeme(1, "2"));
    expected.push_back(Lexeme(1, "3"));
    expected.push_back(Lexeme(2, "*"));
    expected.push_back(Lexeme(2, "+"));
    EXPECT_EQ(toRPN(infix), expected);
}

TEST(ToRPNTests, NestedOperators) {
    Vector<Lexeme> infix;
    infix.push_back(Lexeme(3, "("));
    infix.push_back(Lexeme(1, "1"));
    infix.push_back(Lexeme(2, "+"));
    infix.push_back(Lexeme(3, "("));
    infix.push_back(Lexeme(1, "2"));
    infix.push_back(Lexeme(2, "*"));
    infix.push_back(Lexeme(1, "3"));
    infix.push_back(Lexeme(4, ")"));
    infix.push_back(Lexeme(4, ")"));
    Vector<Lexeme> expected;
    expected.push_back(Lexeme(1, "1"));
    expected.push_back(Lexeme(1, "2"));
    expected.push_back(Lexeme(1, "3"));
    expected.push_back(Lexeme(2, "*"));
    expected.push_back(Lexeme(2, "+"));
    EXPECT_EQ(toRPN(infix), expected);
}

TEST(ToRPNTests, ComplexExpressionWithDivision) {
    Vector<Lexeme> infix;
    infix.push_back(Lexeme(1, "10"));
    infix.push_back(Lexeme(2, "/"));
    infix.push_back(Lexeme(1, "2"));
    infix.push_back(Lexeme(2, "+"));
    infix.push_back(Lexeme(1, "3"));
    Vector<Lexeme> expected;
    expected.push_back(Lexeme(1, "10"));
    expected.push_back(Lexeme(1, "2"));
    expected.push_back(Lexeme(2, "/"));
    expected.push_back(Lexeme(1, "3"));
    expected.push_back(Lexeme(2, "+"));
    EXPECT_EQ(toRPN(infix), expected);
}

TEST(ToRPNTests, MultipleOperatorsWithDifferentPrecedence) {
    Vector<Lexeme> infix;
    infix.push_back(Lexeme(1, "3"));
    infix.push_back(Lexeme(2, "+"));
    infix.push_back(Lexeme(1, "4"));
    infix.push_back(Lexeme(2, "*"));
    infix.push_back(Lexeme(1, "2"));
    infix.push_back(Lexeme(2, "-"));
    infix.push_back(Lexeme(1, "1"));
    Vector<Lexeme> expected;
    expected.push_back(Lexeme(1, "3"));
    expected.push_back(Lexeme(1, "4"));
    expected.push_back(Lexeme(1, "2"));
    expected.push_back(Lexeme(2, "*"));
    expected.push_back(Lexeme(2, "+"));
    expected.push_back(Lexeme(1, "1"));
    expected.push_back(Lexeme(2, "-"));
    EXPECT_EQ(toRPN(infix), expected);
}

TEST(ToRPNTests, ComplexExpressionWithAllOperators) {
    Vector<Lexeme> infix;
    infix.push_back(Lexeme(1, "5"));
    infix.push_back(Lexeme(2, "+"));
    infix.push_back(Lexeme(1, "3"));
    infix.push_back(Lexeme(2, "*"));
    infix.push_back(Lexeme(1, "2"));
    infix.push_back(Lexeme(2, "-"));
    infix.push_back(Lexeme(1, "1"));
    Vector<Lexeme> expected;
    expected.push_back(Lexeme(1, "5"));
    expected.push_back(Lexeme(1, "3"));
    expected.push_back(Lexeme(1, "2"));
    expected.push_back(Lexeme(2, "*"));
    expected.push_back(Lexeme(2, "+"));
    expected.push_back(Lexeme(1, "1"));
    expected.push_back(Lexeme(2, "-"));
    EXPECT_EQ(toRPN(infix), expected);
}

TEST(ToRPNTests, ComplexExpressionWithNegativeNumbers) {
    Vector<Lexeme> infix;
    infix.push_back(Lexeme(1, "-5"));
    infix.push_back(Lexeme(2, "+"));
    infix.push_back(Lexeme(1, "3"));
    infix.push_back(Lexeme(2, "*"));
    infix.push_back(Lexeme(1, "2"));
    Vector<Lexeme> expected;
    expected.push_back(Lexeme(1, "-5"));
    expected.push_back(Lexeme(1, "3"));
    expected.push_back(Lexeme(1, "2"));
    expected.push_back(Lexeme(2, "*"));
    expected.push_back(Lexeme(2, "+"));
    EXPECT_EQ(toRPN(infix), expected);
}

TEST(ToRPNTests, ComplexExpressionWithNegativeAndParentheses) {
    Vector<Lexeme> infix;
    infix.push_back(Lexeme(3, "("));
    infix.push_back(Lexeme(1, "-5"));
    infix.push_back(Lexeme(2, "+"));
    infix.push_back(Lexeme(1, "3"));
    infix.push_back(Lexeme(4, ")"));
    infix.push_back(Lexeme(2, "*"));
    infix.push_back(Lexeme(1, "2"));
    Vector<Lexeme> expected;
    expected.push_back(Lexeme(1, "-5"));
    expected.push_back(Lexeme(1, "3"));
    expected.push_back(Lexeme(2, "+"));
    expected.push_back(Lexeme(1, "2"));
    expected.push_back(Lexeme(2, "*"));
    EXPECT_EQ(toRPN(infix), expected);
}