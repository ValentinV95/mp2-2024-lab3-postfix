#include <gtest.h>
#include "arithmetic.h"

TEST(Expression_Test, SimpleAddition) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "2"));
    lexemes.push_back(Lexeme(1, "3"));
    lexemes.push_back(Lexeme(2, "+"));
    Expression_ expr(lexemes, true);
    EXPECT_DOUBLE_EQ(expr.evaluate(), 5);
}

TEST(Expression_Test, SimpleSubtraction) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "5"));
    lexemes.push_back(Lexeme(1, "3"));
    lexemes.push_back(Lexeme(2, "-"));
    Expression_ expr(lexemes, true);
    EXPECT_DOUBLE_EQ(expr.evaluate(), 2);
}

TEST(Expression_Test, SimpleMultiplication) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "4"));
    lexemes.push_back(Lexeme(1, "2"));
    lexemes.push_back(Lexeme(2, "*"));
    Expression_ expr(lexemes, true);
    EXPECT_DOUBLE_EQ(expr.evaluate(), 8);
}

TEST(Expression_Test, SimpleDivision) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "8"));
    lexemes.push_back(Lexeme(1, "2"));
    lexemes.push_back(Lexeme(2, "/"));
    Expression_ expr(lexemes, true);
    EXPECT_DOUBLE_EQ(expr.evaluate(), 4);
}

TEST(Expression_Test, DivisionByZero) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "5"));
    lexemes.push_back(Lexeme(1, "0"));
    lexemes.push_back(Lexeme(2, "/"));
    Expression_ expr(lexemes, true);
    EXPECT_THROW(expr.evaluate(), std::runtime_error);
}

TEST(Expression_Test, Exponentiation) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "2"));
    lexemes.push_back(Lexeme(1, "3"));
    lexemes.push_back(Lexeme(2, "^"));
    Expression_ expr(lexemes, true);
    EXPECT_DOUBLE_EQ(expr.evaluate(), 8);
}

TEST(Expression_Test, LogFunction) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "1"));
    lexemes.push_back(Lexeme(5, "log"));
    Expression_ expr(lexemes, true);
    EXPECT_DOUBLE_EQ(expr.evaluate(), 0);
}

TEST(Expression_Test, ExpFunction) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "0"));
    lexemes.push_back(Lexeme(5, "exp"));
    Expression_ expr(lexemes, true);
    EXPECT_DOUBLE_EQ(expr.evaluate(), 1);
}

TEST(Expression_Test, SinFunction) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "0"));
    lexemes.push_back(Lexeme(5, "sin"));
    Expression_ expr(lexemes, true);
    EXPECT_DOUBLE_EQ(expr.evaluate(), 0);
}

TEST(Expression_Test, CosFunction) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "0"));
    lexemes.push_back(Lexeme(5, "cos"));
    Expression_ expr(lexemes, true);
    EXPECT_DOUBLE_EQ(expr.evaluate(), 1);
}

TEST(Expression_Test, TanFunction) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "0"));
    lexemes.push_back(Lexeme(5, "tan"));
    Expression_ expr(lexemes, true);
    EXPECT_DOUBLE_EQ(expr.evaluate(), 0);
}

TEST(Expression_Test, CotFunction) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "1"));
    lexemes.push_back(Lexeme(5, "cot"));
    Expression_ expr(lexemes, true);
    EXPECT_DOUBLE_EQ(expr.evaluate(), 1 / tan(1));
}

TEST(Expression_Test, SecFunction) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "0"));
    lexemes.push_back(Lexeme(5, "sec"));
    Expression_ expr(lexemes, true);
    EXPECT_DOUBLE_EQ(expr.evaluate(), 1);
}

TEST(Expression_Test, CscFunction) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "1"));
    lexemes.push_back(Lexeme(5, "csc"));
    Expression_ expr(lexemes, true);
    EXPECT_DOUBLE_EQ(expr.evaluate(), 1 / sin(1));
}

TEST(Expression_Test, InsufficientValuesForOperator) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(2, "+"));
    Expression_ expr(lexemes, true);
    EXPECT_THROW(expr.evaluate(), std::runtime_error);
}

TEST(Expression_Test, TooManyValuesAfterEvaluation) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "1"));
    lexemes.push_back(Lexeme(1, "2"));
    lexemes.push_back(Lexeme(2, "+"));
    lexemes.push_back(Lexeme(1, "3"));
    Expression_ expr(lexemes, true);
    EXPECT_THROW(expr.evaluate(), std::runtime_error);
}

TEST(Expression_Test, ComplexExpression_) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "3"));
    lexemes.push_back(Lexeme(1, "4"));
    lexemes.push_back(Lexeme(2, "*"));
    lexemes.push_back(Lexeme(1, "2"));
    lexemes.push_back(Lexeme(2, "+"));
    Expression_ expr(lexemes, true);
    EXPECT_DOUBLE_EQ(expr.evaluate(), 14);
}

TEST(Expression_Test, NestedFunctions) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "0"));
    lexemes.push_back(Lexeme(5, "sin"));
    lexemes.push_back(Lexeme(5, "exp"));
    Expression_ expr(lexemes, true);
    EXPECT_DOUBLE_EQ(expr.evaluate(), 1);
}

TEST(Expression_Test, NegativeNumber) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "-3"));
    lexemes.push_back(Lexeme(1, "2"));
    lexemes.push_back(Lexeme(2, "+"));
    Expression_ expr(lexemes, true);
    EXPECT_DOUBLE_EQ(expr.evaluate(), -1);
}

TEST(Expression_Test, MultipleOperators) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "2"));
    lexemes.push_back(Lexeme(1, "3"));
    lexemes.push_back(Lexeme(2, "+"));
    lexemes.push_back(Lexeme(1, "4"));
    lexemes.push_back(Lexeme(2, "*"));
    Expression_ expr(lexemes, true);
    EXPECT_DOUBLE_EQ(expr.evaluate(), 20);
}

TEST(Expression_Test, LargeNumbers) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "1000000"));
    lexemes.push_back(Lexeme(1, "2000000"));
    lexemes.push_back(Lexeme(2, "+"));
    Expression_ expr(lexemes, true);
    EXPECT_DOUBLE_EQ(expr.evaluate(), 3000000);
}

TEST(Expression_Test, SmallNumbers) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "0.0001"));
    lexemes.push_back(Lexeme(1, "0.0002"));
    lexemes.push_back(Lexeme(2, "+"));
    Expression_ expr(lexemes, true);
    EXPECT_DOUBLE_EQ(expr.evaluate(), 0.0003);
}

TEST(Expression_Test, ZeroInput) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "0"));
    lexemes.push_back(Lexeme(1, "0"));
    lexemes.push_back(Lexeme(2, "+"));
    Expression_ expr(lexemes, true);
    EXPECT_DOUBLE_EQ(expr.evaluate(), 0);
}

TEST(Expression_Test, MixedOperations) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "2"));
    lexemes.push_back(Lexeme(1, "3"));
    lexemes.push_back(Lexeme(2, "*"));
    lexemes.push_back(Lexeme(1, "4"));
    lexemes.push_back(Lexeme(2, "+"));
    Expression_ expr(lexemes, true);
    EXPECT_DOUBLE_EQ(expr.evaluate(), 10);
}

TEST(Expression_Test, InvalidOperator) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "2"));
    lexemes.push_back(Lexeme(1, "3"));
    lexemes.push_back(Lexeme(2, "&"));
    Expression_ expr(lexemes, true);
    EXPECT_THROW(expr.evaluate(), std::runtime_error);
}

TEST(Expression_Test, InvalidFunction) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "2"));
    lexemes.push_back(Lexeme(5, "invalidFunction"));
    Expression_ expr(lexemes, true);
    EXPECT_THROW(expr.evaluate(), std::runtime_error);
}

TEST(Expression_Test, EmptyExpression_) {
    Vector<Lexeme> lexemes;
    Expression_ expr(lexemes, true);
    EXPECT_THROW(expr.evaluate(), std::runtime_error);
}

TEST(Expression_Test, SingleNumber) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "42"));
    Expression_ expr(lexemes, true);
    EXPECT_DOUBLE_EQ(expr.evaluate(), 42);
}

TEST(Expression_Test, SingleNegativeNumber) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "-42"));
    Expression_ expr(lexemes, true);
    EXPECT_DOUBLE_EQ(expr.evaluate(), -42);
}

TEST(Expression_Test, SingleFunction) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "1"));
    lexemes.push_back(Lexeme(5, "sin"));
    Expression_ expr(lexemes, true);
    EXPECT_DOUBLE_EQ(expr.evaluate(), sin(1));
}

TEST(Expression_Test, MultipleFunctions) {
    Vector<Lexeme> lexemes;
    lexemes.push_back(Lexeme(1, "1"));
    lexemes.push_back(Lexeme(5, "sin"));
    lexemes.push_back(Lexeme(5, "exp"));
    Expression_ expr(lexemes, true);
    EXPECT_DOUBLE_EQ(expr.evaluate(), exp(sin(1)));
}