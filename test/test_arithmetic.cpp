#include <gtest.h>
#include "arithmetic.h"
#include <iostream>
#include <fstream>
#include <string>

static double eps = 1e-20;

TEST(calculator, can_create_calculator_0) {
	ASSERT_NO_THROW(calculator calc("1-2"));
}

TEST(calculator, correctly_converted_0)
{
	calculator calc("1-2");
	myVector<lexem*> v;
	v.push_back(new constant{ "1", 0 });
	v.push_back(new operation{ "-", 1 });
	v.push_back(new constant{ "2", 2 });

	for (int i = 0; i < v.size(); ++i) {
		EXPECT_EQ(v[i]->getSym(), calc.getData()[i]->getSym());
		EXPECT_EQ(v[i]->getPos(), calc.getData()[i]->getPos());
	}
	for (int i = 0; i < v.size(); ++i) {
		delete[] v[i];
	}

	std::ostream out(nullptr);
	std::istringstream sl("");
	std::istream in(sl.rdbuf());
	calc.askForVariablesValues(in, out);
	EXPECT_EQ(true, abs(calc.calculate() - -1.0) < eps);
}

TEST(calculator, correctly_calculated_0)
{
	calculator calc("1-2");

	std::ostream out(nullptr);
	std::istringstream sl("");
	std::istream in(sl.rdbuf());
	calc.askForVariablesValues(in, out);
	EXPECT_EQ(true, abs(calc.calculate() - -1.0) < eps);
}

TEST(calculator, can_create_calculator_1) 
{
	ASSERT_NO_THROW(calculator calc("1+2"));
}

TEST(calculator, correctly_converted_1)
{
	calculator calc("1+2");
	myVector<lexem*> v;
	v.push_back(new constant{ "1", 0 });
	v.push_back(new operation{ "+", 1 });
	v.push_back(new constant{ "2", 2 });

	for (int i = 0; i < v.size(); ++i) {
		EXPECT_EQ(v[i]->getSym(), calc.getData()[i]->getSym());
		EXPECT_EQ(v[i]->getPos(), calc.getData()[i]->getPos());
	}
	for (int i = 0; i < v.size(); ++i) {
		delete[] v[i];
	}
}

TEST(calculator, can_create_calcuator_2)
{
	ASSERT_NO_THROW(calculator calc("---1"));
}

TEST(calculator, correctly_converted_2)
{
	calculator calc("---1");
	myVector<lexem*> v;
	v.push_back(new operation{ "~", 0 });
	v.push_back(new operation{ "~", 1 });
	v.push_back(new operation{ "~", 2 });
	v.push_back(new constant{ "1", 3 });

	for (int i = 0; i < v.size(); ++i) {
		EXPECT_EQ(v[i]->getSym(), calc.getData()[i]->getSym());
		EXPECT_EQ(v[i]->getPos(), calc.getData()[i]->getPos());
	}
	for (int i = 0; i < v.size(); ++i) {
		delete[] v[i];
	}
}

TEST(calculator, calculation_throwed_exception_2) //r
{
	calculator calc("---1");
	myVector<lexem*> v;

	std::ostream out(nullptr);
	std::istringstream sl("");
	std::istream in(sl.rdbuf());
	calc.askForVariablesValues(in, out);
	ASSERT_ANY_THROW(calc.calculate());
}

TEST(calculator, can_create_calculator_3)
{
	ASSERT_NO_THROW(calculator calc("111"));
}

TEST(calculator, correctly_converted_3)
{
	calculator calc("111");
	myVector<lexem*> v;
	v.push_back(new constant{ "111", 0 });

	for (int i = 0; i < v.size(); ++i) {
		EXPECT_EQ(v[i]->getSym(), calc.getData()[i]->getSym());
		EXPECT_EQ(v[i]->getPos(), calc.getData()[i]->getPos());
	}
	for (int i = 0; i < v.size(); ++i) {
		delete[] v[i];
	}
}

TEST(calculator, correctly_calculated_3)
{
	calculator calc("111");

	std::ostream out(nullptr);
	std::istringstream sl("");
	std::istream in(sl.rdbuf());
	calc.askForVariablesValues(in, out);
	EXPECT_EQ(true, abs(calc.calculate() - 111.0) < eps);
}

TEST(calculator, can_create_calculator_4) 
{
	ASSERT_NO_THROW(calculator calc("2+-1"));
}

TEST(calculator, correctly_converted_4)
{
	calculator calc("2+-1");
	myVector<lexem*> v;
	v.push_back(new constant{ "2", 0 });
	v.push_back(new operation{ "+", 1 });
	v.push_back(new operation{ "~", 2 });
	v.push_back(new constant{ "1", 3 });

	for (int i = 0; i < v.size(); ++i) {
		EXPECT_EQ(v[i]->getSym(), calc.getData()[i]->getSym());
		EXPECT_EQ(v[i]->getPos(), calc.getData()[i]->getPos());
	}
	for (int i = 0; i < v.size(); ++i) {
		delete[] v[i];
	}
}

TEST(calculator, can_create_calculator_5)
{
	ASSERT_NO_THROW(calculator calc("4*(1+2)"));
}

TEST(calculator, correctly_converted_5)
{
	calculator calc("4*(1+2)");
	myVector<lexem*> v;
	v.push_back(new constant{ "4", 0 });
	v.push_back(new operation{ "*", 1 });
	v.push_back(new operation{ "(", 2 });
	v.push_back(new constant{ "1", 3 });
	v.push_back(new operation{ "+", 4 });
	v.push_back(new constant{ "2", 5 });
	v.push_back(new operation{ ")", 6 });

	for (int i = 0; i < v.size(); ++i) {
		EXPECT_EQ(v[i]->getSym(), calc.getData()[i]->getSym());
		EXPECT_EQ(v[i]->getPos(), calc.getData()[i]->getPos());
	}
	for (int i = 0; i < v.size(); ++i) {
		delete[] v[i];
	}
}

TEST(calculator, can_create_calculator_6)
{
	ASSERT_NO_THROW(calculator calc("(1.42e-1+.4e+1)/(77e-2-sin(1))"));
}

TEST(calculator, correctly_converted_6) 
{
	calculator calc("(1.42e-1+.4e+1)/(77e-2-sin(1))");
	myVector<lexem*> v;
	v.push_back(new operation{ "(", 0 });
	v.push_back(new constant{ "1.42e-1", 1 });
	v.push_back(new operation{ "+", 8 });
	v.push_back(new constant{ ".4e+1", 9 });
	v.push_back(new operation{ ")", 14 });
	v.push_back(new operation{ "/", 15 });
	v.push_back(new operation{ "(", 16 });
	v.push_back(new constant{ "77e-2", 17 });
	v.push_back(new operation{ "-", 22 });
	v.push_back(new operation{ "sin", 23 });
	v.push_back(new operation{ "(", 26 });
	v.push_back(new constant{ "1", 27 });
	v.push_back(new operation{ ")", 28 });
	v.push_back(new operation{ ")", 29 });

	for (int i = 0; i < v.size(); ++i) {
		EXPECT_EQ(v[i]->getSym(), calc.getData()[i]->getSym());
		EXPECT_EQ(v[i]->getPos(), calc.getData()[i]->getPos());
	}
	for (int i = 0; i < v.size(); ++i) {
		delete[] v[i];
	}
}

TEST(calculator, can_create_calculator_7)
{
	ASSERT_NO_THROW(calculator calc("(1.42E-1+.4E+1)/(77E-2-sin(1))"));
}

TEST(calculator, correctly_converted_and_calculated_7)
{
	calculator calc("(1.42E-1+.4E+1)/(77E-2-sin(1))");
	myVector<lexem*> v;
	v.push_back(new operation{ "(", 0 });
	v.push_back(new constant{ "1.42E-1", 1 });
	v.push_back(new operation{ "+", 8 });
	v.push_back(new constant{ ".4E+1", 9 });
	v.push_back(new operation{ ")", 14 });
	v.push_back(new operation{ "/", 15 });
	v.push_back(new operation{ "(", 16 });
	v.push_back(new constant{ "77E-2", 17 });
	v.push_back(new operation{ "-", 22 });
	v.push_back(new operation{ "sin", 23 });
	v.push_back(new operation{ "(", 26 });
	v.push_back(new constant{ "1", 27 });
	v.push_back(new operation{ ")", 28 });
	v.push_back(new operation{ ")", 29 });

	for (int i = 0; i < v.size(); ++i) {
		EXPECT_EQ(v[i]->getSym(), calc.getData()[i]->getSym());
		EXPECT_EQ(v[i]->getPos(), calc.getData()[i]->getPos());
	}
	for (int i = 0; i < v.size(); ++i) {
		delete[] v[i];
	}
}

TEST(calculator, can_create_calculator_8)
{
	ASSERT_NO_THROW(calculator calc("4 * ( 1 + 2 )"));
}

TEST(calculator, correctly_converted_8)
{
	calculator calc("4 * ( 1 + 2 ) ");
	myVector<lexem*> v;
	v.push_back(new constant{ "4", 0 });
	v.push_back(new operation{ "*", 2 });
	v.push_back(new operation{ "(", 4 });
	v.push_back(new constant{ "1", 6 });
	v.push_back(new operation{ "+", 8 });
	v.push_back(new constant{ "2", 10 });
	v.push_back(new operation{ ")", 12 });

	for (int i = 0; i < v.size(); ++i) {
		EXPECT_EQ(v[i]->getSym(), calc.getData()[i]->getSym());
		EXPECT_EQ(v[i]->getPos(), calc.getData()[i]->getPos());
	}
	for (int i = 0; i < v.size(); ++i) {
		delete[] v[i];
	}
}

TEST(calculator, can_create_calculator_with_variables_0)
{
	ASSERT_NO_THROW(calculator calc("(x+y)/(xy-sin(yx))"));
}

TEST(calculator, correctly_converted_with_variables_0)
{
	calculator calc("(x+y)/(xy-sin(yx))");
	myVector<lexem*> v;
	v.push_back(new operation{ "(", 0 });
	v.push_back(new variable{ "x", 1 });
	v.push_back(new operation{ "+", 2 });
	v.push_back(new variable{ "y", 3 });
	v.push_back(new operation{ ")", 4 });
	v.push_back(new operation{ "/", 5 });
	v.push_back(new operation{ "(", 6 });
	v.push_back(new variable{ "xy", 7 });
	v.push_back(new operation{ "-", 9 });
	v.push_back(new operation{ "sin", 10 });
	v.push_back(new operation{ "(", 13 });
	v.push_back(new variable{ "yx", 14 });
	v.push_back(new operation{ ")", 16 });
	v.push_back(new operation{ ")", 17 });

	for (int i = 0; i < v.size(); ++i) {
		EXPECT_EQ(v[i]->getSym(), calc.getData()[i]->getSym());
		EXPECT_EQ(v[i]->getPos(), calc.getData()[i]->getPos());
	}
	for (int i = 0; i < v.size(); ++i) {
		delete[] v[i];
	}
}

TEST(calculator, correctly_calculated_with_one_value_of_variables_0)
{
	calculator calc("(x+y)/(xy-sin(yx))");

	std::ostream out(nullptr);
	std::istringstream sl("1.42e-1\n.4e+1\n77e-2\n1\n");
	std::istream in1(sl.rdbuf());
	calc.askForVariablesValues(in1, out);
	EXPECT_EQ(true, abs(calc.calculate() - -57.95358789490711615144) < eps);
}

TEST(calculator, correctly_calculated_with_another_value_of_variables_0)
{
	calculator calc("(x+y)/(xy-sin(yx))");

	std::ostream out(nullptr);
	std::istringstream sl("1.42e-1\n.4e+1\n77e-2\n1\n");
	std::istream in1(sl.rdbuf());
	calc.askForVariablesValues(in1, out);
	EXPECT_EQ(true, abs(calc.calculate() - -57.95358789490711615144) < eps);

	sl = std::istringstream("1.0\n2.0\n1.0\n0");
	std::istream in2(sl.rdbuf());
	calc.askForVariablesValues(in2, out);
	EXPECT_EQ(true, abs(calc.calculate() - 3.0) < eps);
}

TEST(calculator, can_create_calculator_9) 
{
	ASSERT_NO_THROW(calculator calc("1.5e-1^-.5"));
}

TEST(calculator, correctly_converted_9)
{
	calculator calc("1.5e-1^-.5");
	myVector<lexem*> v;
	v.push_back(new constant{ "1.5e-1", 0 });
	v.push_back(new operation{ "^", 6 });
	v.push_back(new operation{ "~", 7 });
	v.push_back(new constant{ ".5", 8 });

	for (int i = 0; i < v.size(); ++i) {
		EXPECT_EQ(v[i]->getSym(), calc.getData()[i]->getSym());
		EXPECT_EQ(v[i]->getPos(), calc.getData()[i]->getPos());
	}
	for (int i = 0; i < v.size(); ++i) {
		delete[] v[i];
	}
}

TEST(calculator, can_create_calculator_with_variables_1)
{
	ASSERT_NO_THROW(calculator calc("var"));
}

TEST(calculator, correctly_converted_and_calculated_with_variables_1)
{
	calculator calc("var");
	myVector<lexem*> v;
	v.push_back(new variable{ "var", 0 });

	for (int i = 0; i < v.size(); ++i) {
		EXPECT_EQ(v[i]->getSym(), calc.getData()[i]->getSym());
		EXPECT_EQ(v[i]->getPos(), calc.getData()[i]->getPos());
	}
	for (int i = 0; i < v.size(); ++i) {
		delete[] v[i];
	}
}

TEST(calculator, correctly_calculated_for_one_values_of_variable_1)
{
	calculator calc("var");

	std::ostream out(nullptr);
	std::istringstream sl("-1.0\n");
	std::istream in1(sl.rdbuf());
	calc.askForVariablesValues(in1, out);
	EXPECT_EQ(true, abs(calc.calculate() - -1.0) < eps);
}

TEST(calculator, correctly_calculated_for_another_values_of_variable_1)
{
	calculator calc("var");

	std::ostream out(nullptr);
	std::istringstream sl("-1.0\n");
	std::istream in1(sl.rdbuf());
	calc.askForVariablesValues(in1, out);
	EXPECT_EQ(true, abs(calc.calculate() - -1.0) < eps);

	sl = std::istringstream("993\n");
	std::istream in2(sl.rdbuf());
	calc.askForVariablesValues(in2, out);
	EXPECT_EQ(true, abs(calc.calculate() - 993.0) < eps);
}

TEST(calculator, can_create_calculator_12)
{
	ASSERT_NO_THROW(calculator calc("1+2)"));
}

TEST(calculator, correctly_converted_12)
{
	calculator calc("1+2)");
	myVector<lexem*> v;
	v.push_back(new constant{ "1", 0 });
	v.push_back(new operation{ "+", 1 });
	v.push_back(new constant{ "2", 2 });
	v.push_back(new operation{ ")", 3 });

	for (int i = 0; i < v.size(); ++i) {
		EXPECT_EQ(v[i]->getSym(), calc.getData()[i]->getSym());
		EXPECT_EQ(v[i]->getPos(), calc.getData()[i]->getPos());
	}
	for (int i = 0; i < v.size(); ++i) {
		delete[] v[i];
	}
}

TEST(calculator, throwed_exception_with_brackets_0)
{
	calculator calc("1+2)");

	std::ostream out(nullptr);
	std::istringstream sl("");
	std::istream in1(sl.rdbuf());
	calc.askForVariablesValues(in1, out);

	ASSERT_ANY_THROW(calc.calculate());
}

TEST(calculator, exception_is_correct_0)
{
	calculator calc("1+2)");

	std::ostream out(nullptr);
	std::istringstream sl("");
	std::istream in1(sl.rdbuf());
	calc.askForVariablesValues(in1, out);

	try {
		calc.calculate();
	}
	catch (std::exception& e) {
		EXPECT_EQ("3ENo opening bracket for this bracket", std::string(e.what()));
	}
}

TEST(calculator, can_create_calculator_13)
{
	ASSERT_NO_THROW(calculator calc("  1  +  2  ) "));
}

TEST(calculator, correctly_converted_13)
{
	calculator calc("  1  +  2  ) ");
	myVector<lexem*> v;
	v.push_back(new constant{ "1", 2 });
	v.push_back(new operation{ "+", 5 });
	v.push_back(new constant{ "2", 8 });
	v.push_back(new operation{ ")", 11 });

	for (int i = 0; i < v.size(); ++i) {
		EXPECT_EQ(v[i]->getSym(), calc.getData()[i]->getSym());
		EXPECT_EQ(v[i]->getPos(), calc.getData()[i]->getPos());
	}
	for (int i = 0; i < v.size(); ++i) {
		delete[] v[i];
	}
}

TEST(calculator, throwed_exception_with_brackets_1)
{
	calculator calc("  1  +  2  ) ");

	std::ostream out(nullptr);
	std::istringstream sl("");
	std::istream in1(sl.rdbuf());
	calc.askForVariablesValues(in1, out);

	ASSERT_ANY_THROW(calc.calculate());
}

TEST(calculator, exception_is_correct_1)
{
	calculator calc("  1  +  2  ) ");

	std::ostream out(nullptr);
	std::istringstream sl("");
	std::istream in1(sl.rdbuf());
	calc.askForVariablesValues(in1, out);

	try {
		calc.calculate();
	}
	catch (std::exception& e) {
		EXPECT_EQ("11ENo opening bracket for this bracket", std::string(e.what()));
	}
}

TEST(calculator, throwed_exception_0)
{
	ASSERT_ANY_THROW(calculator calc("(1.42e-1+..4e+1)/(77e-2-sin(1))"));
}

TEST(calculator, throwed_exception_is_correct_0)
{
	try {
		calculator calc("(1.42e-1+..4e+1)/(77e-2-sin(1))");
	}
	catch (std::exception& e) {
		EXPECT_EQ("5L10EMissing operator, code: 11", std::string(e.what()));
	}
}

TEST(calculator, throwed_exception_1)
{
	ASSERT_ANY_THROW(calculator calc("1ee-1"));
}

TEST(calculator, throwed_exception_is_correct_1)
{
	try {
		calculator calc("1ee-1");
	}
	catch (std::exception& e) {
		EXPECT_EQ("1L2EMissing operator, code: 11", std::string(e.what()));
	}
}

TEST(calculator, throwed_exception_2)
{
	ASSERT_ANY_THROW(calculator calc("(1+var)(1-var)"));
}

TEST(calculator, throwed_exception_is_correct_2)
{
	try {
		calculator calc("(1+var)(1-var)");
	}
	catch (std::exception& e) {
		EXPECT_EQ("1L7EMissing operator, code: 3", std::string(e.what()));
	}
}

TEST(calculator, throwed_exception_3)
{
	ASSERT_ANY_THROW(calculator calc("(1+2)*(3+)"));
}

TEST(calculator, throwed_exception_is_correct_3)
{
	try {
		calculator calc("(1+2)*(3+)");
	}
	catch (std::exception& e) {
		EXPECT_EQ("1L8EMissing operand, code: 2", std::string(e.what()));
	}
}

TEST(calculator, throwed_exception_4)
{
	ASSERT_ANY_THROW(calculator calc("(1+2)*(3log)"));
}

TEST(calculator, throwed_exception_is_correct_4)
{
	try {
		calculator calc("(1+2)*(3log)");
	}
	catch (std::exception& e) {
		EXPECT_EQ("3L8EInvalid unary operator syntax, code: 5", std::string(e.what()));
	}
}

TEST(calculator, throwed_exception_5)
{
	ASSERT_ANY_THROW(calculator calc("(1 + var) (1 - var)"));
}

TEST(calculator, throwed_exception_is_correct_5)
{
	try {
		calculator calc("(1 + var) (1 - var)");
	}
	catch (std::exception& e) {
		EXPECT_EQ("1L10EMissing operator, code: 3", std::string(e.what()));
	}
}

TEST(calculator, throwed_exception_6)
{
	ASSERT_ANY_THROW(calculator calc(")(2 * 3) * 4"));
}

TEST(calculator, throwed_exception_is_correct_6)
{
	try {
		calculator calc(")(2 * 3) * 4");
	}
	catch (std::exception& e) {
		EXPECT_EQ("1L0ENo closing bracket for this bracket, code: 0", std::string(e.what()));
	}
}

TEST(calculator, throwed_exception_7)
{
	ASSERT_ANY_THROW(calculator calc("(2 * 3 () ) * 4"));
}

TEST(calculator, throwed_exception_is_correct_7)
{
	try {
		calculator calc("(2 * 3 () ) * 4");
	}
	catch (std::exception& e) {
		EXPECT_EQ("1L5EMissing operator, code: 4", std::string(e.what()));
	}
}

TEST(calculator, throwed_exception_9)
{
	ASSERT_ANY_THROW(calculator calc("2*sin1 + log"));
}

TEST(calculator, throwed_exception_is_correct_9)
{
	try {
		calculator calc("2*sin1 + log");
	}
	catch (std::exception& e) {
		EXPECT_EQ("3L9ENo operands for this operator, code: 6", std::string(e.what()));
	}
}

TEST(calculator, throwed_exception_10)
{
	ASSERT_ANY_THROW(calculator calc("+ 1"));
}

TEST(calculator, throwed_exception_is_correct_10)
{
	try {
		calculator calc("+ 1");
	}
	catch (std::exception& e) {
		EXPECT_EQ("1L0ENo operands for this operator, code: 7", std::string(e.what()));
	}
}

TEST(calculator, throwed_exception_12)
{
	ASSERT_ANY_THROW(calculator calc("48 + v1 ++ v2 * 12"));
}

TEST(calculator, throwed_exception_is_correct_12)
{
	try {
		calculator calc("48 + v1 ++ v2 * 12");
	}
	catch (std::exception& e) {
		EXPECT_EQ("1L9ETwo or more operators in a row, code: 8", std::string(e.what()));
	}
}

TEST(calculator, throwed_exception_14)
{
	ASSERT_ANY_THROW(calculator calc("12 * (1 + 2)var"));
}

TEST(calculator, throwed_exception_is_correct_14)
{
	try {
		calculator calc("12 * (1 + 2)var");
	}
	catch (std::exception& e) {
		EXPECT_EQ("3L12EMissing operator, code: 10", std::string(e.what()));
	}
}

TEST(calculator, throwed_exception_15)
{
	ASSERT_ANY_THROW(calculator calc("(2 * 3 + () ) * 4"));
}

TEST(calculator, throwed_exception_is_correct_15)
{
	try {
		calculator calc("(2 * 3 + () ) * 4");
	}
	catch (std::exception& e) {
		EXPECT_EQ("1L10EMissing operand, code: 1", std::string(e.what()));
	}
}

TEST(calculator, throwed_exception_16)
{
	ASSERT_ANY_THROW(calculator calc("x + ( + 1)"));
}

TEST(calculator, throwed_exception_is_correct_16)
{
	try {
		calculator calc("x + ( + 1)");
	}
	catch (std::exception& e) {
		EXPECT_EQ("1L6ENo operands for this operator, code: 9", std::string(e.what()));
	}
}