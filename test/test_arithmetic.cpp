#include <gtest.h>
#include "arithmetic.h"
#include <iostream>
#include <fstream>
#include <string>

TEST(calculator, correctly_converted_into_vector_of_lexems_0)
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

	double eps = 1e-25;
	std::ostream out(nullptr);
	std::istringstream sl("");
	std::istream in(sl.rdbuf());
	calc.askForVariablesValues(in, out);
	EXPECT_EQ(true, abs(calc.calculate() - -1.0) < eps);
}

TEST(calculator, correctly_converted_into_vector_of_lexems_1)
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

	double eps = 1e-25;
	std::ostream out(nullptr);
	std::istringstream sl("");
	std::istream in(sl.rdbuf());
	calc.askForVariablesValues(in, out);
	EXPECT_EQ(true, abs(calc.calculate() - 3.0) < eps);
}

TEST(calculator, correctly_converted_into_vector_of_lexems_2)
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

	std::ostream out(nullptr);
	std::istringstream sl("");
	std::istream in(sl.rdbuf());
	calc.askForVariablesValues(in, out);
	ASSERT_ANY_THROW(calc.calculate());
}

TEST(calculator, correctly_converted_into_vector_of_lexems_3)
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

	double eps = 1e-23;
	std::ostream out(nullptr);
	std::istringstream sl("");
	std::istream in(sl.rdbuf());
	calc.askForVariablesValues(in, out);
	EXPECT_EQ(true, abs(calc.calculate() - 111.0) < eps);
}

TEST(calculator, correctly_converted_into_vector_of_lexems_4)
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

	double eps = 1e-25;
	std::ostream out(nullptr);
	std::istringstream sl("");
	std::istream in(sl.rdbuf());
	calc.askForVariablesValues(in, out);
	EXPECT_EQ(true, abs(calc.calculate() - 1.0) < eps);
}

TEST(calculator, correctly_converted_into_vector_of_lexems_5)
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

	double eps = 1e-25;
	std::ostream out(nullptr);
	std::istringstream sl("");
	std::istream in(sl.rdbuf());
	calc.askForVariablesValues(in, out);
	EXPECT_EQ(true, abs(calc.calculate() - 12.0) < eps);
}

TEST(calculator, correctly_converted_into_vector_of_lexems_6)
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

	double eps = 1e-04;
	std::ostream out(nullptr);
	std::istringstream sl("");
	std::istream in(sl.rdbuf());
	calc.askForVariablesValues(in, out);
	EXPECT_EQ(true, abs(calc.calculate() - -57.9536) < eps);
}

TEST(calculator, correctly_converted_into_vector_of_lexems_7)
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

	double eps = 1e-04;
	std::ostream out(nullptr);
	std::istringstream sl("");
	std::istream in(sl.rdbuf());
	calc.askForVariablesValues(in, out);
	EXPECT_EQ(true, abs(calc.calculate() - -57.9536) < eps);
}

TEST(calculator, correctly_converted_into_vector_of_lexems_8)
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

	double eps = 1e-04;
	std::ostream out(nullptr);
	std::istringstream sl("1.42e-1\n.4e+1\n77e-2\n1\n");
	std::istream in(sl.rdbuf());
	calc.askForVariablesValues(in, out);
	EXPECT_EQ(true, abs(calc.calculate() - -57.9536) < eps);
}

TEST(calculator, correctly_converted_into_vector_of_lexems_9)
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

	double eps = 1e-05;
	std::ostream out(nullptr);
	std::istringstream sl("");
	std::istream in(sl.rdbuf());
	calc.askForVariablesValues(in, out);
	EXPECT_EQ(true, abs(calc.calculate() - 2.58199) < eps);
}

TEST(calculator, correctly_converted_into_vector_of_lexems_10)
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

	double eps = 1e-25;
	std::ostream out(nullptr);
	std::istringstream sl("-1.0\n");
	std::istream in(sl.rdbuf());
	calc.askForVariablesValues(in, out);
	EXPECT_EQ(true, abs(calc.calculate() - -1.0) < eps);
}

TEST(calculator, correctly_converted_into_vector_of_lexems_11)
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

	double eps = 1e-25;
	std::ostream out(nullptr);
	std::istringstream sl("-1.0\n-1.0\n");
	std::istream in(sl.rdbuf());
	calc.askForVariablesValues(in, out);
	EXPECT_EQ(true, abs(calc.calculate() - -1.0) < eps);
}

TEST(calculator, correctly_converted_into_vector_of_lexems_12)
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

	ASSERT_ANY_THROW(calc.calculate());
}

TEST(calculator, correctly_converted_into_vector_of_lexems_13)
{
	ASSERT_ANY_THROW(calculator calc("(1.42e-1+..4e+1)/(77e-2-sin(1))"));
	/*
	myVector<lexem*> v;
	v.push_back(new operation{ "(", 0 });
	v.push_back(new constant{ "1.42e-1", 1 });
	v.push_back(new operation{ "+", 8 });
	v.push_back(new variable{ ".", 9 });
	v.push_back(new constant{ ".4e+1", 10 });
	v.push_back(new operation{ ")", 15 });
	v.push_back(new operation{ "/", 16 });
	v.push_back(new operation{ "(", 17 });
	v.push_back(new constant{ "77e-2", 18 });
	v.push_back(new operation{ "-", 23 });
	v.push_back(new operation{ "sin", 24 });
	v.push_back(new operation{ "(", 27 });
	v.push_back(new constant{ "1", 28 });
	v.push_back(new operation{ ")", 29 });
	v.push_back(new operation{ ")", 30 });

	for (int i = 0; i < v.size(); ++i) {
		EXPECT_EQ(v[i]->getSym(), calc.getData()[i]->getSym());
		EXPECT_EQ(v[i]->getPos(), calc.getData()[i]->getPos());
	}
	for (int i = 0; i < v.size(); ++i) {
		delete[] v[i];
	}
	*/
}

TEST(calculator, correctly_converted_into_vector_of_lexems_14)
{
	ASSERT_ANY_THROW(calculator calc("1ee-1"));
	/*
	myVector<lexem*> v;
	v.push_back(new constant{ "1e", 0 });
	v.push_back(new variable{ "e", 2 });
	v.push_back(new operation{ "-", 3 });
	v.push_back(new constant{ "1", 4 });

	for (int i = 0; i < v.size(); ++i) {
		EXPECT_EQ(v[i]->getSym(), calc.getData()[i]->getSym());
		EXPECT_EQ(v[i]->getPos(), calc.getData()[i]->getPos());
	}
	for (int i = 0; i < v.size(); ++i) {
		delete[] v[i];
	}
	*/
}

TEST(calculator, correctly_converted_into_vector_of_lexems_15)
{
	ASSERT_ANY_THROW(calculator calc("(1+var)(1-var)"));
}

TEST(calculator, correctly_converted_into_vector_of_lexems_16)
{
	ASSERT_ANY_THROW(calculator calc("(1+2)*(3+)"));
}

TEST(calculator, correctly_converted_into_vector_of_lexems_17)
{
	ASSERT_ANY_THROW(calculator calc("(1+2)*(3log)"));
}