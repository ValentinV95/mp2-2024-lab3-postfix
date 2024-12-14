// тесты для вычисления арифметических выражений
#include <iomanip>
#include <gtest.h>
#include "arithmetic.h"

TEST(TArithmeticExpression, can_create_non_empty_string) {
	ASSERT_NO_THROW(TArithmeticExpression e("1"));
}
TEST(TArithmeticExpression, cant_create_empty_string) {
	ASSERT_ANY_THROW(TArithmeticExpression e(""));
}
TEST(TArithmeticExpression, cant_calculate_before_postfix_method) {
	TArithmeticExpression d("1");
	ASSERT_ANY_THROW(d.simple_calc());
}
TEST(TArithmeticExpression, cant_print_rpn_before_postfix_method) {
	TArithmeticExpression d("1");
	ASSERT_ANY_THROW(d.print_rpn());
}
TEST(TArithmeticExpression, can_print_rpn_after_postfix_method) {
	TArithmeticExpression d("1");
	d.ToPostfix();
	ASSERT_NO_THROW(d.print_rpn());
}
TEST(TArithmeticExpression, can_print_infix_method) {
	TArithmeticExpression d("1+3");
	ASSERT_NO_THROW(d.print_infix());
}
TEST(TArithmeticExpression, _1) {
	TArithmeticExpression d("1+3");
	double res = 0.0;
	ASSERT_NO_THROW(d.ToPostfix());
	ASSERT_NO_THROW(res = d.simple_calc());
	ASSERT_EQ(res, 4.0);
}
TEST(TArithmeticExpression, _2) {
	TArithmeticExpression d("1+-1");
	double res = 0.0;
	ASSERT_NO_THROW(d.ToPostfix());
	ASSERT_NO_THROW(res = d.simple_calc());
	ASSERT_EQ(res, 0.0);
}
TEST(TArithmeticExpression, _3) {
	TArithmeticExpression d("-1+1");
	double res = 0.0;
	ASSERT_NO_THROW(d.ToPostfix());
	ASSERT_NO_THROW(res = d.simple_calc());
	ASSERT_EQ(res, 0.0);
}
TEST(TArithmeticExpression, _4) {
	TArithmeticExpression d("-1+-1");
	double res = 0.0;
	ASSERT_NO_THROW(d.ToPostfix());
	ASSERT_NO_THROW(res = d.simple_calc());
	ASSERT_EQ(res, -2.0);
}
TEST(TArithmeticExpression, _5) {
	TArithmeticExpression d("-(1 + 23*2)");
	double res = 0.0;
	ASSERT_NO_THROW(d.ToPostfix());
	ASSERT_NO_THROW(res = d.simple_calc());
	ASSERT_EQ(res, -47.0);
}
TEST(TArithmeticExpression, _6) {
	TArithmeticExpression d("-(---1 + 23*2)");
	double res = 0.0;
	ASSERT_NO_THROW(d.ToPostfix());
	ASSERT_NO_THROW(res = d.simple_calc());
	ASSERT_EQ(res, -45.0);
}
TEST(TArithmeticExpression, _7) {
	TArithmeticExpression d("1");
	double res = 0.0;
	ASSERT_NO_THROW(d.ToPostfix());
	ASSERT_NO_THROW(res = d.simple_calc());
	ASSERT_EQ(res, 1.0);
}
TEST(TArithmeticExpression, _8) {
	TArithmeticExpression d("-1");
	double res = 0.0;
	ASSERT_NO_THROW(d.ToPostfix());
	ASSERT_NO_THROW(res = d.simple_calc());
	ASSERT_EQ(res, -1.0);
}
TEST(TArithmeticExpression, _9) {
	TArithmeticExpression d("-1.1212344");
	double res = 0.0;
	double ans = -1.1212344;
	ASSERT_NO_THROW(d.ToPostfix());
	ASSERT_NO_THROW(res = d.simple_calc());
	ASSERT_LE(abs(ans-res), std::numeric_limits<double>::epsilon());
}
TEST(TArithmeticExpression, _10) {
	TArithmeticExpression d("-1.21+23.23-12.4*3879.2204-203/12.345");
	double res = 0.0;
	double ans = -48096.756864414748;
	
	ASSERT_NO_THROW(d.ToPostfix());
	ASSERT_NO_THROW(res = d.simple_calc());
	ASSERT_LE(abs(ans - res), std::numeric_limits<double>::epsilon());
}
TEST(TArithmeticExpression, _11) {
	TArithmeticExpression d("1.0e+2+sin(cos(tan(cot(123454))))");
	double res = 0.0;
	double ans = 100.7819623919247361;
	ASSERT_NO_THROW(d.ToPostfix());
	ASSERT_NO_THROW(res = d.simple_calc());
	ASSERT_LE(abs(ans - res), std::numeric_limits<double>::epsilon());
}
TEST(TArithmeticExpression, _12) {
	TArithmeticExpression d("1/-2*2/-4");
	double res = 0.0;
	double ans = 0.25;
	ASSERT_NO_THROW(d.ToPostfix());
	ASSERT_NO_THROW(res = d.simple_calc());
	ASSERT_LE(abs(ans - res), std::numeric_limits<double>::epsilon());
}
TEST(TArithmeticExpression, _13) {
	TArithmeticExpression d("(2.2e-3+-.2e+2)/(228e-2+tan(1))");
	double res = 0.0;
	double ans = -5.211278403260732622;
	ASSERT_NO_THROW(d.ToPostfix());
	ASSERT_NO_THROW(res = d.simple_calc());
	ASSERT_LE(abs(ans - res), std::numeric_limits<double>::epsilon());
}
TEST(TArithmeticExpression, _14) {
	//вольфрам альфа не позволил посчитать ans с большой точностью для такого кол-ва символов(
	//некоторые онлайн калькуляторы дают чуть больше точность чем всплывающий результат в вольфрам альфа, некоторые ломались)
	TArithmeticExpression d("((12.345*(sin(0.785)+2.56)/(cos(1.23)-0.987))-((6.789/(4.321-1.01)+tan(0.5))*3.14159)+(1/(cot(0.2)*7.777)))*((cos(0.9)*123.456)/(sin(1.1)*(tan(0.3)+1/(cot(0.4)))))-((77.777+1/3.0)*((sin(0.5)/(0.888+cos(1.7)))-((10.0/1.111)/(1.2+cot(1.5))))+((1/(tan(0.123)-1/(2*2.5))*1.2)/(1.0/((cos(2.0)+2.1)+0.9))))+((sin(1.5)*(1/(tan(0.1)+3.5)*100.0)+(10.5-cos(0.75))*(1/(cot(1.8)-2.1)))/((10.0/((5.5+tan(1.9))*2.3))+(0.123+(1/10.1)+cot(0.6))))*((1000.5+12.7)/((5.23-0.14)*sin(0.98)))-(((25.5/(1/2.5+tan(0.333)))+(1/(cot(0.444)+1.23)))*(cos(1.22)-12.2))+((1/(1/3.3+sin(0.666))+12/cot(1.3)+2.3)/(123.4*0.1))");
	double res = 0.0;
	double ans = -5594.804539117726;
	ASSERT_NO_THROW(d.ToPostfix());
	ASSERT_NO_THROW(res = d.simple_calc());
	ASSERT_LE(abs(ans - res), 1e-12);
}
TEST(TArithmeticExpression, _15) {
	TArithmeticExpression d("((1.123*(2.345-sin(0.456)/(cos(0.789)+0.1)))/((7.89/(1.01+4.567)+tan(0.234))*12.123)-(1.0/(cot(0.111)+5.55)))+((cos(1.001)*9.876)/(sin(0.222)*((tan(0.333)/1.1)+(1/cot(0.444)))))-(((12.345+(1/2.0))*((sin(0.12)/(0.33+cos(0.77)))-((1/(3.3-cot(0.22)))/1.3)))+((1.23/(tan(0.567)-0.8))+(1.0/((cos(0.65)+1.1)*2.3))))*((10.0/(1.234+tan(1.8)))-(0.345/(1.1+(1/cot(0.9)))))+((sin(0.8)*(1/(2.3+tan(0.1))))+(1.2-cos(0.9))*(1/(cot(1.7)+1.1)))/((10.0/((3.3+tan(1.6))*1.2))+(0.12+1/10.1+cot(0.5)))+((((23.2/(1/2.1+tan(0.222))+(1/(cot(0.333)+1.11))))*(cos(1.3)+13.3))-((1/(1/3.1+sin(0.444))+10/cot(1.2)+2.1)/111.1))*(1001.2/((2.22-0.111)*sin(0.777)))");
	double res = 0.0;
	double ans = 305787.2023910995;
	ASSERT_NO_THROW(d.ToPostfix());
	ASSERT_NO_THROW(res = d.simple_calc());
	ASSERT_LE(abs(ans - res), 1e-12);
}