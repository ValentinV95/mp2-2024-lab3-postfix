// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"

// Тесты конструктора Lexem
TEST(LexemTests, ConstructorTest) {
    Lexem lex(NUMBER, "42", 0);
    EXPECT_EQ(lex.type, NUMBER);
    EXPECT_EQ(lex.value, "42");
    EXPECT_EQ(lex.priority, 0);
}

TEST(LexemTests, IsOperatorTest) {
    Lexem lex(OPERATOR, "+", 1);
    EXPECT_TRUE(lex.isOperator());
    EXPECT_FALSE(lex.isNumber());
}

TEST(LexemTests, IsNumberTest) {
    Lexem lex(NUMBER, "3.14", 0);
    EXPECT_TRUE(lex.isNumber());
    EXPECT_FALSE(lex.isOperator());
}

TEST(LexemTests, IsParenthesisTest) {
    Lexem leftParen(LEFT_PAREN, "(", 0);
    Lexem rightParen(RIGHT_PAREN, ")", 0);
    EXPECT_TRUE(leftParen.isParenthesis());
    EXPECT_TRUE(rightParen.isParenthesis());
}

// Тесты перегрузки операторов Lexem
TEST(LexemTests, StreamOperatorsTest) {
    Lexem lex(NUMBER, "5", 0);
    std::ostringstream os;
    os << lex;
    EXPECT_EQ(os.str(), "5");

    std::istringstream is("42");
    Lexem lexInput(NUMBER, "", 0);
    is >> lexInput;
    EXPECT_EQ(lexInput.value, "42");
}

TEST(PostfixConverterTests, ConstructorTest) {
    TDynamicVector<Lexem> tokens;
    tokens.push_back(Lexem(NUMBER, "2"));
    tokens.push_back(Lexem(OPERATOR, "+"));
    tokens.push_back(Lexem(NUMBER, "3"));

    PostfixConverter converter(tokens);
    EXPECT_NO_THROW(converter.toPostfix());
}

TEST(PostfixConverterTests, SimpleExpressionTest) {
    TDynamicVector<Lexem> tokens;
    tokens.push_back(Lexem(NUMBER, "2"));
    tokens.push_back(Lexem(OPERATOR, "+"));
    tokens.push_back(Lexem(NUMBER, "3"));

    PostfixConverter converter(tokens);
    converter.toPostfix();

    std::ostringstream os;
    converter.printPostfix(os);
    EXPECT_EQ(os.str(), "2 3 + \n");
}

TEST(PostfixConverterTests, ExpressionWithParentheses) {
    TDynamicVector<Lexem> tokens;
    tokens.push_back(Lexem(LEFT_PAREN, "("));
    tokens.push_back(Lexem(NUMBER, "2"));
    tokens.push_back(Lexem(OPERATOR, "+"));
    tokens.push_back(Lexem(NUMBER, "3"));
    tokens.push_back(Lexem(RIGHT_PAREN, ")"));
    tokens.push_back(Lexem(OPERATOR, "*"));
    tokens.push_back(Lexem(NUMBER, "4"));

    PostfixConverter converter(tokens);
    converter.toPostfix();

    std::ostringstream os;
    converter.printPostfix(os);
    EXPECT_EQ(os.str(), "2 3 + 4 * \n");
}

TEST(PostfixConverterTests, ComplexExpressionTest) {
    TDynamicVector<Lexem> tokens;
    tokens.push_back(Lexem(NUMBER, "5"));
    tokens.push_back(Lexem(OPERATOR, "*"));
    tokens.push_back(Lexem(LEFT_PAREN, "("));
    tokens.push_back(Lexem(NUMBER, "3"));
    tokens.push_back(Lexem(OPERATOR, "+"));
    tokens.push_back(Lexem(NUMBER, "2"));
    tokens.push_back(Lexem(RIGHT_PAREN, ")"));
    tokens.push_back(Lexem(OPERATOR, "-"));
    tokens.push_back(Lexem(NUMBER, "4"));

    PostfixConverter converter(tokens);
    converter.toPostfix();

    std::ostringstream os;
    converter.printPostfix(os);
    EXPECT_EQ(os.str(), "5 3 2 + * 4 - \n");
}

TEST(PostfixConverterTests, EmptyInputTest) {
    TDynamicVector<Lexem> tokens;
    PostfixConverter converter(tokens);
    EXPECT_NO_THROW(converter.toPostfix());

    std::ostringstream os;
    converter.printPostfix(os);
    EXPECT_EQ(os.str(), "\n");
}

TEST(PostfixConverterTests, InvalidParenthesesTest) {
    TDynamicVector<Lexem> tokens;
    tokens.push_back(Lexem(LEFT_PAREN, "("));
    tokens.push_back(Lexem(NUMBER, "2"));
    tokens.push_back(Lexem(OPERATOR, "+"));
    tokens.push_back(Lexem(NUMBER, "3"));
    // Пропущена правая скобка

}