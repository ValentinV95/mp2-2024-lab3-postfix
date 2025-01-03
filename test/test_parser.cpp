#include <gtest.h>
#include "Pars.h"

TEST(IsSpaceTest, HandlesSpaces) {
    EXPECT_TRUE(isSpace_(' '));
    EXPECT_TRUE(isSpace_('\t'));
    EXPECT_TRUE(isSpace_('\n'));
    EXPECT_TRUE(isSpace_('\r'));
    EXPECT_FALSE(isSpace_('a'));
    EXPECT_FALSE(isSpace_('1'));
    EXPECT_FALSE(isSpace_('+'));
}

TEST(IsDigitTest, HandlesDigits) {
    EXPECT_TRUE(isDigit_('0'));
    EXPECT_TRUE(isDigit_('5'));
    EXPECT_TRUE(isDigit_('9'));
    EXPECT_FALSE(isDigit_('a'));
    EXPECT_FALSE(isDigit_(' '));
    EXPECT_FALSE(isDigit_('.'));
}

TEST(IsOperatorTest, HandlesOperators) {
    EXPECT_TRUE(isOperator_('+'));
    EXPECT_TRUE(isOperator_('-'));
    EXPECT_TRUE(isOperator_('*'));
    EXPECT_TRUE(isOperator_('/'));
    EXPECT_FALSE(isOperator_('a'));
    EXPECT_FALSE(isOperator_('1'));
    EXPECT_FALSE(isOperator_(' '));
}

TEST(IsFunctionTest, HandlesFunctions) {
    EXPECT_TRUE(isFunctionOrVariable("sin", 0));
    EXPECT_TRUE(isFunctionOrVariable("cos", 0));
    EXPECT_TRUE(isFunctionOrVariable("log", 0));
    EXPECT_FALSE(isFunctionOrVariable("1sin", 0));
    EXPECT_TRUE(isFunctionOrVariable("sin1", 0));
    EXPECT_FALSE(isFunctionOrVariable("1", 0));
}


TEST(ParseNumberTest, HandlesNumbers) {
    std::string input = "123.45e-6";
    size_t pos = 0;
    EXPECT_EQ(parseNumber(input, pos), "123.45e-6");
    EXPECT_EQ(pos, input.size());

    input = "42";
    pos = 0;
    EXPECT_EQ(parseNumber(input, pos), "42");
    EXPECT_EQ(pos, input.size());
}

TEST(FindFirstOfTest, HandlesFindFirstOf) {
    EXPECT_EQ(findFirstOf("hello", "e"), 1);
    EXPECT_EQ(findFirstOf("hello", "z"), std::string::npos);
    EXPECT_EQ(findFirstOf("hello", "l"), 2);
}

TEST(ParseFunctionTests, ValidFunctionNames) {
    std::string input = "sin cos tan log exp";
    size_t pos = 0;

    EXPECT_EQ(parseFunction(input, pos), "sin");
    EXPECT_EQ(pos, 3); 
    pos++;
    EXPECT_EQ(parseFunction(input, pos), "cos");
    EXPECT_EQ(pos, 7);
    pos++;
    EXPECT_EQ(parseFunction(input, pos), "tan");
    EXPECT_EQ(pos, 11); 
    pos++;
    EXPECT_EQ(parseFunction(input, pos), "log");
    EXPECT_EQ(pos, 15); 
    pos++;
    EXPECT_EQ(parseFunction(input, pos), "exp");
    EXPECT_EQ(pos, 19);
}

TEST(ParseFunctionTests, FunctionWithDigits) {
    std::string input = "func1 func2";
    size_t pos = 0;

    EXPECT_EQ(parseFunction(input, pos), "func1");
    EXPECT_EQ(pos, 5);
    pos++;
    EXPECT_EQ(parseFunction(input, pos), "func2");
    EXPECT_EQ(pos, 11); 
}

TEST(ParseFunctionTests, MixedCharacters) {
    std::string input = "myFunction1 anotherFunc2";
    size_t pos = 0;

    EXPECT_EQ(parseFunction(input, pos), "myFunction1");
    EXPECT_EQ(pos, 11); 
    pos++;
    EXPECT_EQ(parseFunction(input, pos), "anotherFunc2");
    EXPECT_EQ(pos, 24); 
}

TEST(ParseFunctionTests, EmptyInput) {
    std::string input = "";
    size_t pos = 0;

    EXPECT_EQ(parseFunction(input, pos), "");
    EXPECT_EQ(pos, 0); 
}

TEST(parseFunctionTests, ValidVariableNames) {
    std::string input = "var1 var_2 varName";
    size_t pos = 0;

    EXPECT_EQ(parseFunction(input, pos), "var1");
    EXPECT_EQ(pos, 4); 
    pos++;
    EXPECT_EQ(parseFunction(input, pos), "var_2");
    EXPECT_EQ(pos, 10); 
    pos++;
    EXPECT_EQ(parseFunction(input, pos), "varName");
    EXPECT_EQ(pos, 18); 
}

TEST(parseFunctionTests, MixedCharacters) {
    std::string input = "var1_2 varName_3";
    size_t pos = 0;

    EXPECT_EQ(parseFunction(input, pos), "var1_2");
    EXPECT_EQ(pos, 6);
    pos++;
    EXPECT_EQ(parseFunction(input, pos), "varName_3");
    EXPECT_EQ(pos, 16); 
}

TEST(ParserTests, SimpleExpressions) {
    std::string input = "3 + 4";
    Vector<Lexeme> lexems = parser(input);

    EXPECT_EQ(lexems.getsize(), 3);
    EXPECT_EQ(lexems[0].type(), 1); 
    EXPECT_EQ(lexems[0].number(), 3);
    EXPECT_EQ(lexems[1].type(), 2); 
    EXPECT_EQ(lexems[1].value(), "+");
    EXPECT_EQ(lexems[2].type(), 1);
    EXPECT_EQ(lexems[2].number(), 4);
}

TEST(ParserTests, FunctionParsing) {
    std::string input = "sin(3.14)";
    Vector<Lexeme> lexems = parser(input);

    EXPECT_EQ(lexems.getsize(), 4); 
    EXPECT_EQ(lexems[0].type(), 5); 
    EXPECT_EQ(lexems[0].value(), "sin");
    EXPECT_EQ(lexems[1].type(), 3); 
    EXPECT_EQ(lexems[1].value(), "(");
    EXPECT_EQ(lexems[2].type(), 1); 
    EXPECT_EQ(lexems[2].value(), "3.14");
    EXPECT_EQ(lexems[3].type(), 4);
    EXPECT_EQ(lexems[3].value(), ")");
}

TEST(ParserTests, MixedInput) {
    std::string input = "2 + 3.14 * sin(0)";
    Vector<Lexeme> lexems = parser(input);

    EXPECT_EQ(lexems.getsize(), 8); 
    EXPECT_EQ(lexems[0].type(), 1); 
    EXPECT_EQ(lexems[0].value(), "2");
    EXPECT_EQ(lexems[1].type(), 2); 
    EXPECT_EQ(lexems[1].value(), "+");
    EXPECT_EQ(lexems[2].type(), 1); 
    EXPECT_EQ(lexems[2].number(), 3.14);
    EXPECT_EQ(lexems[3].type(), 2);
    EXPECT_EQ(lexems[3].value(), "*");
    EXPECT_EQ(lexems[4].type(), 5); 
    EXPECT_EQ(lexems[4].value(), "sin");
    EXPECT_EQ(lexems[5].type(), 3);
    EXPECT_EQ(lexems[5].value(), "(");
    EXPECT_EQ(lexems[6].type(), 1); 
    EXPECT_EQ(lexems[6].value(), "0");
    EXPECT_EQ(lexems[7].type(), 4); 
    EXPECT_EQ(lexems[7].value(), ")");
}

TEST(ParserTests, InvalidCharacter) {
    std::string input = "3 + @";
    EXPECT_ANY_THROW(parser(input));
}