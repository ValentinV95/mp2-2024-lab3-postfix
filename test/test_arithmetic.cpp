// тесты для вычисления арифметических выражений
#define _USE_MATH_DEFINES
#include <gtest.h>
#include "arithmetic.h"

TEST(TPostfix, can_create_easy_postfix)
{
	string inp("1+2");
	EXPECT_NO_THROW(TPostfix Sol(inp));
}

TEST(TPostfix, can_correctly_count_easy_postfix)
{
	string inp("1+2");
	TPostfix Sol(inp);
	EXPECT_EQ(3, Sol.count());
}

TEST(TPostfix, throws_when_operation_input_is_incorrect)
{
	string inp = "1+/2";
	EXPECT_ANY_THROW(TPostfix Sol(inp); Sol.count());
	inp = "1-/2";
	EXPECT_ANY_THROW(TPostfix Sol(inp); Sol.count());
	inp = "1+*2";
	EXPECT_ANY_THROW(TPostfix Sol(inp); Sol.count());
	inp = "*12";
	EXPECT_ANY_THROW(TPostfix Sol(inp); Sol.count());
	inp = "/1+2";
	EXPECT_ANY_THROW(TPostfix Sol(inp); Sol.count());
	inp = "1-+2";
	EXPECT_ANY_THROW(TPostfix Sol(inp); Sol.count());
	inp = "+1-2";
	EXPECT_ANY_THROW(TPostfix Sol(inp); Sol.count());
	inp = "+-12";
	EXPECT_ANY_THROW(TPostfix Sol(inp); Sol.count());
	inp = "12+";
	EXPECT_ANY_THROW(TPostfix Sol(inp); Sol.count());
	inp = "1-";
	EXPECT_ANY_THROW(TPostfix Sol(inp); Sol.count());
	inp = "1*";
	EXPECT_ANY_THROW(TPostfix Sol(inp); Sol.count());
	inp = "1/";
	EXPECT_ANY_THROW(TPostfix Sol(inp); Sol.count());
}

TEST(TPostfix, throws_when_function_input_is_incorrect)
{
	string inp = "tg0";
	EXPECT_ANY_THROW(TPostfix Sol(inp); Sol.count());
	inp = "log1";
	EXPECT_ANY_THROW(TPostfix Sol(inp); Sol.count());
	inp = "cos";
	EXPECT_ANY_THROW(TPostfix Sol(inp); Sol.count());
	inp = "sin";
	EXPECT_ANY_THROW(TPostfix Sol(inp); Sol.count());
	inp = "tan";
	EXPECT_ANY_THROW(TPostfix Sol(inp); Sol.count());
}

TEST(TPostfix, throws_when_numerage_input_is_incorrect)
{
	string inp = ".e-1";
	EXPECT_ANY_THROW(TPostfix Sol(inp); Sol.count());
	inp = "1.0e-";
	EXPECT_ANY_THROW(TPostfix Sol(inp); Sol.count());
	inp = "1.0e+";
	EXPECT_ANY_THROW(TPostfix Sol(inp); Sol.count());
	inp = "1.0e*4";
	EXPECT_ANY_THROW(TPostfix Sol(inp); Sol.count());
}

TEST(TPostfix, throws_when_brackets_input_is_incorrect)
{
	string inp = "(1+2";
	EXPECT_ANY_THROW(TPostfix Sol(inp); Sol.count());
	inp = "1+2)";
	EXPECT_ANY_THROW(TPostfix Sol(inp); Sol.count());
	inp = "((1+2)";
	EXPECT_ANY_THROW(TPostfix Sol(inp); Sol.count());
	inp = "1+()+2";
	EXPECT_ANY_THROW(TPostfix Sol(inp); Sol.count());
	inp = "(1+(2)))";
}

TEST(TPostfix, can_input_numerage)
{
	string inp("1.0e+3");
	TPostfix Sol(inp);
	EXPECT_EQ(1000, Sol.count());
	inp = "0.2e-2";
	TPostfix Sol1(inp);
	EXPECT_EQ(0.002, Sol1.count());
	inp = "0,005";
	TPostfix Sol2(inp);
	EXPECT_EQ(0.005, Sol2.count());
	inp = "15";
	TPostfix Sol3(inp);
	EXPECT_EQ(15, Sol3.count());
	inp = ",2e+2";
	TPostfix Sol4(inp);
	EXPECT_EQ(20, Sol4.count());
}

TEST(TPostfix, can_count_easy_main_operations_with_brackets_unary_minus_and_extra_spaces)
{
	string inp("2 + -3");
	TPostfix Sol(inp);
	EXPECT_EQ(-1, Sol.count());
	inp = "-(--(2*2))/3";
	TPostfix Sol1(inp);
	EXPECT_EQ (((-1)*4 / (double)3), Sol1.count());
	inp = "2-- --- 5";
	TPostfix Sol2(inp);
	EXPECT_EQ(-3, Sol2.count());
	inp = "5 + (27 / 3) ";
	TPostfix Sol3(inp);
	EXPECT_EQ(14, Sol3.count());
	inp = "(4--1) * - 2";
	TPostfix Sol4(inp);
	EXPECT_EQ(-10, Sol4.count());
	inp = "1*2+cos0";
	TPostfix Sol5(inp);
	EXPECT_EQ(3, Sol5.count());
}

TEST(TPostfix, can_count_with_function)
{
	string inp("cos(2)");
	TPostfix Sol(inp);
	EXPECT_EQ(cos(2), Sol.count());
	inp = "sin(0)*2+15/5/cos(0)";
	TPostfix Sol1(inp);
	EXPECT_EQ(3, Sol1.count());
	inp = "--tan2";
	TPostfix Sol2(inp);
	EXPECT_EQ(tan(2), Sol2.count());
	inp = "ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(ln(exp(1))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))";
	TPostfix Sol3(inp);
	EXPECT_EQ(1, Sol3.count());
}

TEST(TPostfix, can_count_with_variables)
{
	string inp("x0+x1+x20+x3+x42+x5+x6+x7+x80+x9+x10+x11+x124+x163+x14+x105+x16+x177+x18+x159+x202+x1054+x22");
	TPostfix Sol(inp);
	double arr[23] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 };
	Sol.input_variables(arr, 23);
	EXPECT_EQ(276, Sol.count());
	for (int i = 0; i < 23; i++)
		arr[i] = 0;
	Sol.input_variables(arr, 23);
	EXPECT_EQ(0, Sol.count());
	for (int i = 0; i < 23; i++)
		arr[i] = i;
	Sol.input_variables(arr, 23);
	EXPECT_EQ(253, Sol.count());
	inp = "sin(x53)";
	TPostfix Sol2(inp);
	for (int i = 0; i <= 3; i++)
	{
		double* p = new double(M_PI * i);
		Sol2.input_variables(p, 1);
		EXPECT_LE(abs(Sol2.count()), 1e-7);
	}
	inp = "cos(x35)";
	TPostfix Sol3(inp);
	for (int i = 0; i <= 3; i++)
	{
		double* p = new double(M_PI * i);
		Sol3.input_variables(p, 1);
		EXPECT_LE(abs(Sol3.count()-pow((-1),i)), 1e-7);
	}
}

TEST(TPostfix, can_count_long_or_difficult_expressions)
{
	string inp("(2+204*3-56)+54-8/7-(56*(312-35))");
	TPostfix Sol(inp);
	EXPECT_LE(abs(-14901.1428571 - Sol.count()), 1e-7);
	inp = "(2+204*3-56)+54-8/7-(56*(312-35*cos(3.14)))";
	TPostfix Sol1(inp);
	EXPECT_LE(abs( -18821.1403713 - Sol1.count()), 1e-7);
	inp = "2+-(3*cos(0))";
	TPostfix Sol2(inp);
	EXPECT_EQ(-1, Sol2.count());
	inp = "1/2*3";
	TPostfix Sol3(inp);
	EXPECT_EQ(1.5, Sol3.count());
	inp = "1/3*2";
	TPostfix Sol4(inp);
	EXPECT_TRUE(abs(0.66666666666 - Sol4.count())<1e-7);
	inp = "1-2+2*1";
	TPostfix Sol5(inp);
	EXPECT_EQ(1, Sol5.count());
	inp = "1*2-2+1";
	TPostfix Sol6(inp);
	EXPECT_EQ(1, Sol6.count());
	inp = "1+2*2-1";
	TPostfix Sol7(inp);
	EXPECT_EQ(4, Sol7.count());
	inp = "1-2--3";
	TPostfix Sol8(inp);
	EXPECT_EQ(2, Sol8.count());
}