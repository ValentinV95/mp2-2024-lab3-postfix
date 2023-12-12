// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"
TEST(Arithmeticexpr, can_create_element) {
	ASSERT_NO_THROW(ArithmeticExpr el("1+1"));
}
TEST(Arithmeticexpr, can_get_infix) {
	ArithmeticExpr el("1+1");
	EXPECT_EQ(el.GetInfix(), "1+1");
}
TEST(Arithmeticexpr, can_do_PreStringIsCorrect) {
	ASSERT_NO_THROW(StringIsAlmostCorrect("5+6*x7"));
}
TEST(Arithmeticexpr, PreStringIsCorrect_ret_corect_value_if_string_is_correct) {
	EXPECT_EQ(StringIsAlmostCorrect("5+6*x7"),-128);
}
TEST(Arithmeticexpr, PreStringIsCorrect_ret_incorrect_value_if_string_isnt_correct) {
	EXPECT_NE(StringIsAlmostCorrect("5+6x7-."), -128);
}
TEST(Arithmeticexpr, can_Parse) {
	ArithmeticExpr el("1+1");
	ASSERT_NO_THROW(el.Parse());
}
TEST(Arithmeticexpr, Parse_is_correct) {
	string s = "1+1";
	ArithmeticExpr el(s);
	el.Parse();
	vector<string> tmp = el.GetLexems();
	for (int i = 0; i < s.length(); i++) {
		EXPECT_EQ(string(1,s[i]), tmp[i]);
	}
}

TEST(Arithmeticexpr, cant_Parse_when_string_is_not_correct) {
	ArithmeticExpr el("1#1");
	ASSERT_ANY_THROW(el.Parse());
}
TEST(Arithmeticexpr, can_do_IsNumberOrVar_with_number) {
	ArithmeticExpr el("1+1");
	ASSERT_NO_THROW(el.strNumberOrVar("3.7e-67+8"));
}
TEST(Arithmeticexpr, can_do_IsNumberOrVar_with_var) {
	ArithmeticExpr el("1+1");
	ASSERT_NO_THROW(el.strNumberOrVar("x67+8"));
}
TEST(Arithmeticexpr, IsNumberOrVar_with_number_is_correct) {
	ArithmeticExpr el("1+1");
	string tmp = el.strNumberOrVar("3.7e-67+8");
	EXPECT_EQ("3.7e-67", tmp);
}
TEST(Arithmeticexpr, IsNumberOrVar_with_var_is_corect) {
	ArithmeticExpr el("1+1");
	string tmp = el.strNumberOrVar("x67+8");
	EXPECT_EQ(tmp, "x67");
}
TEST(Arithmeticexpr, cant_do_IsNumberOrVar_when_number_isnt_corect) {
	ArithmeticExpr el("1+1");
	ASSERT_ANY_THROW(el.strNumberOrVar("7.7.7+8"));
}
TEST(Arithmeticexpr, do_IsNumberOrVar_when_there_is_not_number_or_var) {
	ArithmeticExpr el("1+1");
	EXPECT_EQ("",el.strNumberOrVar("+7-x2"));
}
TEST(Arithmeticexpr, can_do_Is_Func) {
	ArithmeticExpr el("1+1");
	ASSERT_NO_THROW(el.strFunc("sin(6)+x0"));
}
TEST(Arithmeticexpr, Is_Func_is_correct) {
	ArithmeticExpr el("1+1");
	string t = el.strFunc("sin(6)+x0");
	EXPECT_EQ(t, "sin");
}
TEST(Arithmeticexpr, can_do_ToPostfix) {
	ArithmeticExpr el("1+1");
	ASSERT_NO_THROW(el.ToPostfix());
}
TEST(Arithmeticexpr, can_get_postfix) {
	ArithmeticExpr el("1+1");
	el.ToPostfix();
	ASSERT_NO_THROW(el.GetPostfix());
}
TEST(Arithmeticexpr, postfix_is_correct) {
	ArithmeticExpr el("1+1");
	el.ToPostfix();
	EXPECT_EQ(el.GetPostfix(), "11+");
}
TEST(Arithmeticexpr, can_calculate) {
	ArithmeticExpr el("6*x8-4/0.2e+1");
	map<string, double> val = { {"x8",5} };
	el.ToPostfix();
	ASSERT_NO_THROW(el.Calculate(val));
}
TEST(Arithmeticexpr, calculate_is_correct) {
	ArithmeticExpr el("-6*x8-4/0.2e+1+(-sin(sin(0+0)))");
	map<string, double> val = { {"x8",5} };
	el.ToPostfix();
	double res = el.Calculate(val);
	cout << res;
	EXPECT_EQ(res, -32);
}
TEST(Arithmeticexpr, can_translate_from_string_to_number) {
	ArithmeticExpr el("1+1");
	ASSERT_NO_THROW(el.Translate("1.0e-12"));
}
TEST(Arithmeticexpr, cant_translate_from_string_to_number_if_string_is_not_correct) {
	ArithmeticExpr el("1+1");
	ASSERT_ANY_THROW(el.Translate("1.0ee-12"));
}
TEST(Arithmeticexpr, translate_from_string_to_number_is_correct) {
	ArithmeticExpr el("1+1");
	EXPECT_EQ(6284,el.Translate("62.84e+2"));
}