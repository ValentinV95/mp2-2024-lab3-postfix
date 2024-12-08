// тесты для вычисления арифметических выражений
#include <gtest.h>
#include "arithmetic.h"
#include "Vector.h"
#include <string>

double eps = 1e-14;

TEST(arithmetic, can_calculate_const1)
{
	std::string expression = "1.e+1";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - 1.e+1 < eps);
	ASSERT_NO_THROW(deleteLx(lx));
	ASSERT_NO_THROW(deleteLx(postfixLx));
}

TEST(arithmetic, can_calculate_const2)
{
	std::string expression = "1.e-1";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - 1.e-1 < eps);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, can_calculate_const3)
{
	std::string expression = "1.E+1";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - 1.e+1 < eps);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, can_calculate_const4)
{
	std::string expression = "1.E-1";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - 1.e-1 < eps);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, can_calculate_const5)
{
	std::string expression = "1e+1";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - 1.e+1 < eps);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, can_calculate_const6)
{
	std::string expression = "1e-1";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - 1.e-1 < eps);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, can_calculate_const7)
{
	std::string expression = "1E+1";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - 1.e+1 < eps);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, can_calculate_const8)
{
	std::string expression = "1E-1";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - 1.e-1 < eps);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, can_calculate_const9)
{
	std::string expression = "1E1";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - 1E1 < eps);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, can_calculate_const10)
{
	std::string expression = "1e1";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - 1e1 < eps);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, can_calculate_const11)
{
	std::string expression = ".1";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - .1 < eps);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, can_calculate_const12)
{
	std::string expression = "-.1";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - -.1 < eps);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, can_calculate_const13)
{
	std::string expression = "-5.e+1";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - -5.e+1 < eps);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, can_calculate_const14)
{
	std::string expression = "5.e+1";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - 5.e+1 < eps);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, cant_calculate_const1)
{
	std::string expression = "-.e+1";
	Vector<lexem*> lx;
	ASSERT_ANY_THROW(lx = parsingLexem(expression));
}

TEST(arithmetic, cant_calculate_const2)
{
	std::string expression = "-3.e-";
	Vector<lexem*> lx;
	ASSERT_ANY_THROW(lx = parsingLexem(expression));
}

TEST(arithmetic, cant_calculate_const3)
{
	std::string expression = "-3.e+";
	Vector<lexem*> lx;
	ASSERT_ANY_THROW(lx = parsingLexem(expression));
}

TEST(arithmetic, cant_calculate_const4)
{
	std::string expression = "..2";
	Vector<lexem*> lx;
	ASSERT_ANY_THROW(lx = parsingLexem(expression));
}

TEST(arithmetic, cant_calculate_const5)
{
	std::string expression = ".e4";
	Vector<lexem*> lx;
	ASSERT_ANY_THROW(lx = parsingLexem(expression));
}

TEST(arithmetic, cant_calculate_const6)
{
	std::string expression = "-.e4";
	Vector<lexem*> lx;
	ASSERT_ANY_THROW(lx = parsingLexem(expression));
}

TEST(arithmetic, cant_calculate_const7)
{
	std::string expression = "-3.e++4";
	Vector<lexem*> lx;
	ASSERT_ANY_THROW(lx = parsingLexem(expression));
}

TEST(arithmetic, cant_calculate_const8)
{
	std::string expression = "-3.e--4";
	Vector<lexem*> lx;
	ASSERT_ANY_THROW(lx = parsingLexem(expression));
}

TEST(arithmetic, cant_calculate_const9)
{
	std::string expression = "-3.e-+4";
	Vector<lexem*> lx;
	ASSERT_ANY_THROW(lx = parsingLexem(expression));
}

TEST(arithmetic, cant_calculate_const10)
{
	std::string expression = "-3.e-1.3";
	Vector<lexem*> lx;
	ASSERT_ANY_THROW(lx = parsingLexem(expression));
}

TEST(arithmetic, cant_calculate_const11)
{
	std::string expression = "-3.e1.3";
	Vector<lexem*> lx;
	ASSERT_ANY_THROW(lx = parsingLexem(expression));
}

TEST(arithmetic, cant_calculate_const12)
{
	std::string expression = "-3e.1.3";
	Vector<lexem*> lx;
	ASSERT_ANY_THROW(lx = parsingLexem(expression));
}

TEST(arithmetic, cant_calculate_const13)
{
	std::string expression = "-3e.1e.3";
	Vector<lexem*> lx;
	ASSERT_ANY_THROW(lx = parsingLexem(expression));
}

TEST(arithmetic, cant_calculate_const14)
{
	std::string expression = "-3ee-1";
	Vector<lexem*> lx;
	ASSERT_ANY_THROW(lx = parsingLexem(expression));
}

TEST(arithmetic, cant_calculate_const15)
{
	std::string expression = "-3ee+1";
	Vector<lexem*> lx;
	ASSERT_ANY_THROW(lx = parsingLexem(expression));
}

TEST(arithmetic, cant_calculate_const16)
{
	std::string expression = "-3e.e+1";
	Vector<lexem*> lx;
	ASSERT_ANY_THROW(lx = parsingLexem(expression));
}

TEST(arithmetic, cant_calculate_const17)
{
	std::string expression = "-3.ee+1";
	Vector<lexem*> lx;
	ASSERT_ANY_THROW(lx = parsingLexem(expression));
}

TEST(arithmetic, can_calculate_easer_arithmetic1)
{
	std::string expression = "1*2";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - 2 < eps);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, can_calculate_easer_arithmetic2)
{
	std::string expression = "1/2";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - 0.5 < eps);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, can_calculate_easer_arithmetic3)
{
	std::string expression = "1-2";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - -1 < eps);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, can_calculate_easer_arithmetic4)
{
	std::string expression = "-1-2";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - -3 < eps);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, can_calculate_easer_arithmetic5)
{
	std::string expression = "-(-1)";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - 1 < eps);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, can_calculate_easer_arithmetic6)
{
	std::string expression = "sin(1)";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - sin(1) < eps);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, can_calculate_easer_arithmetic7)
{
	std::string expression = "cos(1)";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - sin(1) < eps);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, can_calculate_easer_arithmetic8)
{
	std::string expression = "sqrt(5)";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - sqrt(5) < eps);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, can_calculate_easer_arithmetic9)
{
	std::string expression = "log2(5)";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - log2(5) < eps);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, can_calculate_easer_arithmetic10)
{
	std::string expression = "ln(5)";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - log(5) < eps);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, cant_calculate_easer_arithmetic1)
{
	std::string expression = "ln(5";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_ANY_THROW(postfixLx = toPostfix(lx));
	deleteLx(lx);
}

TEST(arithmetic, cant_calculate_easer_arithmetic2)
{
	std::string expression = "ln5";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_ANY_THROW(postfixLx = toPostfix(lx));
	deleteLx(lx);
}

TEST(arithmetic, cant_calculate_easer_arithmetic3)
{
	std::string expression = "5ln";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_ANY_THROW(postfixLx = toPostfix(lx));
	deleteLx(lx);
}

TEST(arithmetic, cant_calculate_easer_arithmetic4)
{
	std::string expression = "5ln";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_ANY_THROW(postfixLx = toPostfix(lx));
	deleteLx(lx);
}

TEST(arithmetic, cant_calculate_easer_arithmetic5)
{
	std::string expression = "5ln5";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_ANY_THROW(postfixLx = toPostfix(lx));
	deleteLx(lx);
}

TEST(arithmetic, cant_calculate_easer_arithmetic6)
{
	std::string expression = "(1-2)(3+2)";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_ANY_THROW(postfixLx = toPostfix(lx));
	deleteLx(lx);
}

TEST(arithmetic, cant_calculate_easer_arithmetic7)
{
	std::string expression = "(1-2)*(3+2";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_ANY_THROW(postfixLx = toPostfix(lx));
	deleteLx(lx);
}

TEST(arithmetic, cant_calculate_easer_arithmetic8)
{
	std::string expression = "(1-2)*3+2)";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_ANY_THROW(postfixLx = toPostfix(lx));
	deleteLx(lx);
}

TEST(arithmetic, cant_calculate_easer_arithmetic9)
{
	std::string expression = "ertygd";
	Vector<lexem*> lx;
	ASSERT_ANY_THROW(lx = parsingLexem(expression));
}

TEST(arithmetic, cant_calculate_easer_arithmetic10)
{
	std::string expression = "sin()4";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_ANY_THROW(postfixLx = toPostfix(lx));
	deleteLx(lx);
}

TEST(arithmetic, cant_calculate_easer_arithmetic11)
{
	std::string expression = "+";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_ANY_THROW(res = calcArithmetic(postfixLx));
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, cant_calculate_easer_arithmetic12)
{
	std::string expression = "()+4";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_ANY_THROW(postfixLx = toPostfix(lx));
	deleteLx(lx);
}

TEST(arithmetic, cant_calculate_easer_arithmetic13)
{
	std::string expression = "4*+4";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_ANY_THROW(postfixLx = toPostfix(lx));
	deleteLx(lx);
}

TEST(arithmetic, cant_calculate_easer_arithmetic14)
{
	std::string expression = "4*/4";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_ANY_THROW(postfixLx = toPostfix(lx));
	deleteLx(lx);
}

TEST(arithmetic, cant_calculate_easer_arithmetic15)
{
	std::string expression = "(4*)4";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_ANY_THROW(postfixLx = toPostfix(lx));
	deleteLx(lx);
}

TEST(arithmetic, cant_calculate_easer_arithmetic16)
{
	std::string expression = "(4*)-4";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_ANY_THROW(postfixLx = toPostfix(lx));
	deleteLx(lx);
}

TEST(arithmetic, cant_calculate_easer_arithmetic17)
{
	std::string expression = "()()(())(1+2)";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_ANY_THROW(postfixLx = toPostfix(lx));
	deleteLx(lx);
}

TEST(arithmetic, cant_calculate_easer_arithmetic18)
{
	std::string expression = "3(3+6)";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_ANY_THROW(postfixLx = toPostfix(lx));
	deleteLx(lx);
}

TEST(arithmetic, cant_calculate_easer_arithmetic19)
{
	std::string expression = "(3+6)ln(7)";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_ANY_THROW(postfixLx = toPostfix(lx));
	deleteLx(lx);
}

TEST(arithmetic, cant_calculate_easer_arithmetic20)
{
	std::string expression = "ln(7+)";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_ANY_THROW(postfixLx = toPostfix(lx));
	deleteLx(lx);
}

TEST(arithmetic, cant_calculate_easer_arithmetic21)
{
	std::string expression = "ln(+)";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_ANY_THROW(postfixLx = toPostfix(lx));
	deleteLx(lx);
}

TEST(arithmetic, cant_calculate_easer_arithmetic22)
{
	std::string expression = "ln(+4)";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_ANY_THROW(postfixLx = toPostfix(lx));
	deleteLx(lx);
}

TEST(arithmetic, cant_calculate_easer_arithmetic23)
{
	std::string expression = "ln(4)/(-)";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_ANY_THROW(postfixLx = toPostfix(lx));
	deleteLx(lx);
}

double eps2 = 1e-5;

TEST(arithmetic, can_calculate_difficult_arithmetic1)
{
	std::string expression = "ln(-ln(sin(2)))";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - -2.353 < eps);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, can_calculate_difficult_arithmetic2)
{
	std::string expression = "sin(sqrt(4 * 1e3)) / cos(6 * (6 - sqrt(sin(2))))";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - 0.95714 < eps2);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, can_calculate_difficult_arithmetic3)
{
	std::string expression = "(4*log2(1024) - 6) * sin(1/1e-1) - ln(4) + cos(4) * cos(9)";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - -18.89772 < eps2);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, can_calculate_difficult_arithmetic4)
{
	std::string expression = "-(-(-(-(-6))))*sqrt(-ln(1e-1))";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - -9.10456 < eps2);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, can_calculate_difficult_arithmetic5)
{
	std::string expression = "-.5*1E+3-.1";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - -500.1 < eps);
	deleteLx(lx);
	deleteLx(postfixLx);
}

TEST(arithmetic, can_calculate_difficult_arithmetic_on_varible)
{
	std::string expression = "(4*log2(x*x) - 6) * sin(x13/1e-1) - ln(x21) + cos(x21) * cos(9)";
	Vector<lexem*> lx, postfixLx;
	ASSERT_NO_THROW(lx = parsingLexem(expression));
	Vector<std::string> varNames(3);
	varNames[0] = "x";
	varNames[1] = "x13";
	varNames[2] = "x21";
	Vector<double> varValue(3);
	varValue[0] = 32;
	varValue[1] = 1;
	varValue[2] = 4;
	for (int i = 0; i < varNames.length(); i++)
	{
		for (int j = 0; j < lx.length(); j++)
		{
			if (lx[j]->what() == -1 && (dynamic_cast<varible*>(lx[j]))->getName() == varNames[i])
			{
				(dynamic_cast<varible*>(lx[j]))->initValue(varValue[i]);
			}
		}
	}
	ASSERT_NO_THROW(postfixLx = toPostfix(lx));
	double res;
	ASSERT_NO_THROW(res = calcArithmetic(postfixLx));
	EXPECT_EQ(true, res - -18.89772 < eps2);
	deleteLx(lx);
	deleteLx(postfixLx);
}