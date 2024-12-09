#include "RPN.h"
#include <gtest.h>
#include <string>

static double eps = 1e-20;

TEST(RPN, fill_operations)
{
	operation::fillOperations();
}

TEST(RPN, can_create_rpn_0)
{
	myVector<lexem*> infix;
	infix.push_back(new constant{ "1", 0 });
	infix.push_back(new operation{ "-", 1 });
	infix.push_back(new constant{ "2", 2 });
	ASSERT_NO_THROW(RPN rpn(infix));
	for (int i = 0; i < infix.size(); ++i) delete[] infix[i];
}

TEST(RPN, correct_convertation_from_infix_to_postfix_0)
{
	myVector<lexem*> infix;
	infix.push_back(new constant{ "1", 0 });
	infix.push_back(new operation{ "-", 1 });
	infix.push_back(new constant{ "2", 2 });
	RPN rpn(infix);

	myVector<lexem*> postfix;
	postfix.push_back(infix[0]);
	postfix.push_back(infix[2]);
	postfix.push_back(infix[1]);

	for (int i = 0; i < rpn.getPostfix().size(); ++i) {
		EXPECT_EQ(postfix[i], rpn.getPostfix()[i]);
		EXPECT_EQ(postfix[i], rpn.getPostfix()[i]);
	}

	for (int i = 0; i < infix.size(); ++i) delete[] infix[i];
}

TEST(RPN, correct_calculated_0)
{
	myVector<lexem*> infix;
	infix.push_back(new constant{ "1", 0 });
	infix.push_back(new operation{ "-", 1 });
	infix.push_back(new constant{ "2", 2 });
	RPN rpn(infix);

	for (size_t i = 0; i < infix.size(); ++i) {
		if (infix[i]->isOperation()) continue;
		dynamic_cast<operand*>(infix[i])->fillValue();
	}

	EXPECT_EQ(true, abs(rpn.calculate() - -1.0) < eps);

	for (int i = 0; i < infix.size(); ++i) delete[] infix[i];
}

TEST(RPN, can_create_rpn_1)
{
	myVector<lexem*> infix;
	infix.push_back(new constant{ "2", 0 });
	infix.push_back(new operation{ "+", 1 });
	infix.push_back(new operation{ "~", 2 });
	infix.push_back(new constant{ "1", 3 });
	ASSERT_NO_THROW(RPN rpn(infix));

	for (int i = 0; i < infix.size(); ++i) delete[] infix[i];
}

TEST(RPN, correct_convertation_from_infix_to_postfix_1)
{
	myVector<lexem*> infix;
	infix.push_back(new constant{ "2", 0 });
	infix.push_back(new operation{ "+", 1 });
	infix.push_back(new operation{ "~", 2 });
	infix.push_back(new constant{ "1", 3 });
	RPN rpn(infix);

	myVector<lexem*> postfix;
	postfix.push_back(infix[0]);
	postfix.push_back(infix[3]);
	postfix.push_back(infix[2]);
	postfix.push_back(infix[1]);

	for (int i = 0; i < rpn.getPostfix().size(); ++i) {
		EXPECT_EQ(postfix[i], rpn.getPostfix()[i]);
		EXPECT_EQ(postfix[i], rpn.getPostfix()[i]);
	}

	for (int i = 0; i < infix.size(); ++i) delete[] infix[i];
}

TEST(RPN, correct_calculation_1)
{
	myVector<lexem*> infix;
	infix.push_back(new constant{ "2", 0 });
	infix.push_back(new operation{ "+", 1 });
	infix.push_back(new operation{ "~", 2 });
	infix.push_back(new constant{ "1", 3 });
	RPN rpn(infix);

	for (size_t i = 0; i < infix.size(); ++i) {
		if (infix[i]->isOperation()) continue;
		dynamic_cast<operand*>(infix[i])->fillValue();
	}

	EXPECT_EQ(true, abs(rpn.calculate() - 1.0) < eps);

	for (int i = 0; i < infix.size(); ++i) {
		delete[] infix[i];
	}
}

TEST(RPN, can_create_rpn_2)
{
	myVector<lexem*> infix;
	infix.push_back(new constant{ "4", 0 });
	infix.push_back(new operation{ "*", 1 });
	infix.push_back(new operation{ "(", 2 });
	infix.push_back(new constant{ "1", 3 });
	infix.push_back(new operation{ "+", 4 });
	infix.push_back(new constant{ "2", 5 });
	infix.push_back(new operation{ ")", 6 });
	ASSERT_NO_THROW(RPN rpn(infix));

	for (int i = 0; i < infix.size(); ++i) delete[] infix[i];
}

TEST(RPN, correct_convertation_from_infix_to_postfix_2)
{
	myVector<lexem*> infix;
	infix.push_back(new constant{ "4", 0 });
	infix.push_back(new operation{ "*", 1 });
	infix.push_back(new operation{ "(", 2 });
	infix.push_back(new constant{ "1", 3 });
	infix.push_back(new operation{ "+", 4 });
	infix.push_back(new constant{ "2", 5 });
	infix.push_back(new operation{ ")", 6 });
	RPN rpn(infix);

	myVector<lexem*> postfix;
	postfix.push_back(infix[0]);
	postfix.push_back(infix[3]);
	postfix.push_back(infix[5]);
	postfix.push_back(infix[4]);
	postfix.push_back(infix[1]);

	for (int i = 0; i < rpn.getPostfix().size(); ++i) {
		EXPECT_EQ(postfix[i], rpn.getPostfix()[i]);
		EXPECT_EQ(postfix[i], rpn.getPostfix()[i]);
	}

	for (int i = 0; i < infix.size(); ++i) delete[] infix[i];
}

TEST(RPN, correct_calculations_2)
{
	myVector<lexem*> infix;
	infix.push_back(new constant{ "4", 0 });
	infix.push_back(new operation{ "*", 1 });
	infix.push_back(new operation{ "(", 2 });
	infix.push_back(new constant{ "1", 3 });
	infix.push_back(new operation{ "+", 4 });
	infix.push_back(new constant{ "2", 5 });
	infix.push_back(new operation{ ")", 6 });
	RPN rpn(infix);

	for (size_t i = 0; i < infix.size(); ++i) {
		if (infix[i]->isOperation()) continue;
		dynamic_cast<operand*>(infix[i])->fillValue();
	}

	EXPECT_EQ(true, abs(rpn.calculate() - 12.0) < eps);

	for (int i = 0; i < infix.size(); ++i) delete[] infix[i];
}

TEST(RPN, can_create_rpn_3)
{
	myVector<lexem*> infix;
	infix.push_back(new constant{ "4", 0 });
	infix.push_back(new operation{ "*", 1 });
	infix.push_back(new constant{ "7", 2 });
	infix.push_back(new operation{ "-", 3 });
	infix.push_back(new constant{ "2", 4 });
	infix.push_back(new operation{ "*", 5 });
	infix.push_back(new constant{ "6", 6 });
	ASSERT_NO_THROW(RPN rpn(infix));

	for (int i = 0; i < infix.size(); ++i) delete[] infix[i];
}

TEST(RPN, correct_convertation_from_infix_to_postfix_3)
{
	myVector<lexem*> infix;
	infix.push_back(new constant{ "4", 0 });
	infix.push_back(new operation{ "*", 1 });
	infix.push_back(new constant{ "7", 2 });
	infix.push_back(new operation{ "-", 3 });
	infix.push_back(new constant{ "2", 4 });
	infix.push_back(new operation{ "*", 5 });
	infix.push_back(new constant{ "6", 6 });
	RPN rpn(infix);

	myVector<lexem*> postfix;
	postfix.push_back(infix[0]);
	postfix.push_back(infix[2]);
	postfix.push_back(infix[1]);
	postfix.push_back(infix[4]);
	postfix.push_back(infix[6]);
	postfix.push_back(infix[5]);
	postfix.push_back(infix[3]);

	for (int i = 0; i < rpn.getPostfix().size(); ++i) {
		EXPECT_EQ(postfix[i], rpn.getPostfix()[i]);
		EXPECT_EQ(postfix[i], rpn.getPostfix()[i]);
	}

	for (int i = 0; i < infix.size(); ++i) delete[] infix[i];
}

TEST(RPN, correct_calculations_3)
{
	myVector<lexem*> infix;
	infix.push_back(new constant{ "4", 0 });
	infix.push_back(new operation{ "*", 1 });
	infix.push_back(new constant{ "7", 2 });
	infix.push_back(new operation{ "-", 3 });
	infix.push_back(new constant{ "2", 4 });
	infix.push_back(new operation{ "*", 5 });
	infix.push_back(new constant{ "6", 6 });
	RPN rpn(infix);

	for (size_t i = 0; i < infix.size(); ++i) {
		if (infix[i]->isOperation()) continue;
		dynamic_cast<operand*>(infix[i])->fillValue();
	}

	EXPECT_EQ(true, abs(rpn.calculate() - 16.0) < eps);

	for (int i = 0; i < infix.size(); ++i) delete[] infix[i];
}

TEST(RPN, correct_calculations_4)
{
	myVector<lexem*> v;
	v.push_back(new constant{ "1", 0 });
	v.push_back(new operation{ "-", 1 });
	v.push_back(new constant{ "2", 2 });
	RPN rpn(v);

	for (size_t i = 0; i < v.size(); ++i) {
		if (v[i]->isOperation()) continue;
		dynamic_cast<operand*>(v[i])->fillValue();
	}

	EXPECT_EQ(true, abs(rpn.calculate() - -1.0) < eps);
	for (int i = 0; i < v.size(); ++i) delete[] v[i];
}

TEST(RPN, correct_calculations_5)
{
	myVector<lexem*> v;
	v.push_back(new constant{ "1", 0 });
	v.push_back(new operation{ "+", 1 });
	v.push_back(new constant{ "2", 2 });
	RPN rpn(v);

	for (size_t i = 0; i < v.size(); ++i) {
		if (v[i]->isOperation()) continue;
		dynamic_cast<operand*>(v[i])->fillValue();
	}

	EXPECT_EQ(true, abs(rpn.calculate() - 3.0) < eps);
	for (int i = 0; i < v.size(); ++i) delete[] v[i];
}

TEST(RPN, correct_calculations_6)
{
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
	RPN rpn(v);

	for (size_t i = 0; i < v.size(); ++i) {
		if (v[i]->isOperation()) continue;
		dynamic_cast<operand*>(v[i])->fillValue();
	}

	EXPECT_EQ(true, abs(rpn.calculate() - -57.95358789490711615144) < eps);
	for (int i = 0; i < v.size(); ++i) delete[] v[i];
}

TEST(RPN, correct_calculations_7)
{
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
	RPN rpn(v);

	for (size_t i = 0; i < v.size(); ++i) {
		if (v[i]->isOperation()) continue;
		dynamic_cast<operand*>(v[i])->fillValue();
	}

	EXPECT_EQ(true, abs(rpn.calculate() - -57.95358789490711615144) < eps);
	for (int i = 0; i < v.size(); ++i) delete[] v[i];
}

TEST(RPN, correct_calculations_8)
{
	myVector<lexem*> v;
	v.push_back(new constant{ "1.5e-1", 0 });
	v.push_back(new operation{ "^", 6 });
	v.push_back(new operation{ "~", 7 });
	v.push_back(new constant{ ".5", 8 });
	RPN rpn(v);

	for (size_t i = 0; i < v.size(); ++i) {
		if (v[i]->isOperation()) continue;
		dynamic_cast<operand*>(v[i])->fillValue();
	}

	EXPECT_EQ(true, abs(rpn.calculate() - 2.5819888974716112) < eps);
	for (int i = 0; i < v.size(); ++i) delete[] v[i];
}

TEST(RPN, convertation_from_infix_to_postfix_throws_exception_0)
{
	myVector<lexem*> v;
	v.push_back(new constant{ "(", 0 });
	v.push_back(new operation{ "(", 1 });
	v.push_back(new operation{ "(", 2 });
	v.push_back(new constant{ ")", 3 });
	ASSERT_ANY_THROW(RPN rpn(v));

	for (int i = 0; i < v.size(); ++i) delete[] v[i];
}

TEST(RPN, convertation_from_infix_to_postfix_exception_0)
{
	myVector<lexem*> v;
	v.push_back(new operation{ "(", 0 });
	v.push_back(new operation{ "(", 1 });
	v.push_back(new operation{ "(", 2 });
	v.push_back(new operation{ "(", 3 });
	v.push_back(new operation{ ")", 4 });
	try {
		RPN rpn(v);
	}
	catch (std::exception& e) {
		EXPECT_EQ("2ENo closing bracket for this bracket", std::string(e.what()));
	}

	for (int i = 0; i < v.size(); ++i) delete[] v[i];
}


TEST(RPN, convertation_from_infix_to_postfix_throws_exception_1)
{
	myVector<lexem*> v;
	v.push_back(new operation{ "(", 0 });
	v.push_back(new operation{ ")", 1 });
	v.push_back(new operation{ ")", 2 });
	v.push_back(new operation{ ")", 3 });
	ASSERT_ANY_THROW(RPN rpn(v));

	for (int i = 0; i < v.size(); ++i) delete[] v[i];
}

TEST(RPN, convertation_from_infix_to_postfix_exception_1)
{
	myVector<lexem*> v;
	v.push_back(new operation{ "(", 0 });
	v.push_back(new operation{ ")", 1 });
	v.push_back(new operation{ ")", 2 });
	v.push_back(new operation{ ")", 3 });
	try {
		RPN rpn(v);
	}
	catch (std::exception& e) {
		EXPECT_EQ("2ENo opening bracket for this bracket", std::string(e.what()));
	}

	for (int i = 0; i < v.size(); ++i) delete[] v[i];
}


TEST(RPN, convertation_from_infix_to_postfix_throws_exception_2)
{
	myVector<lexem*> v;
	v.push_back(new operation{ "(", 0 });
	v.push_back(new constant{ "1", 1 });
	v.push_back(new operation{ ")", 2 });
	v.push_back(new operation{ ")", 3 });
	ASSERT_ANY_THROW(RPN rpn(v));

	for (int i = 0; i < v.size(); ++i) delete[] v[i];
}

TEST(RPN, convertation_from_infix_to_postfix_exception_2)
{
	myVector<lexem*> v;
	v.push_back(new operation{ "(", 0 });
	v.push_back(new constant{ "1", 1 });
	v.push_back(new operation{ ")", 2 });
	v.push_back(new operation{ ")", 3 });
	try {
		RPN rpn(v);
	}
	catch (std::exception& e) {
		EXPECT_EQ("3ENo opening bracket for this bracket", std::string(e.what()));
	}

	for (int i = 0; i < v.size(); ++i) delete[] v[i];
}

TEST(RPN, wrong_calculation_correctly_converted_with_no_exception_0)
{
	myVector<lexem*> v;
	v.push_back(new operation{ "~", 0 });
	v.push_back(new operation{ "~", 1 });
	v.push_back(new operation{ "~", 2 });
	v.push_back(new constant{ "1", 3 });
	ASSERT_NO_THROW(RPN rpn(v));

	for (int i = 0; i < v.size(); ++i) delete[] v[i];
}

TEST(RPN, wrong_calculation_correctly_converted_0)
{
	myVector<lexem*> v;
	v.push_back(new operation{ "~", 0 });
	v.push_back(new operation{ "~", 1 });
	v.push_back(new operation{ "~", 2 });
	v.push_back(new constant{ "1", 3 });
	RPN rpn(v);

	myVector<lexem*> postfix;
	postfix.push_back(v[0]);
	postfix.push_back(v[1]);
	postfix.push_back(v[3]);
	postfix.push_back(v[2]);

	for (int i = 0; i < rpn.getPostfix().size(); ++i) {
		EXPECT_EQ(postfix[i], rpn.getPostfix()[i]);
		EXPECT_EQ(postfix[i], rpn.getPostfix()[i]);
	}

	for (int i = 0; i < v.size(); ++i) delete[] v[i];
}

TEST(RPN, wrong_calculation_throws_an_exception_0)
{
	myVector<lexem*> v;
	v.push_back(new operation{ "~", 0 });
	v.push_back(new operation{ "~", 1 });
	v.push_back(new operation{ "~", 2 });
	v.push_back(new constant{ "1", 3 });
	RPN rpn(v);

	for (size_t i = 0; i < v.size(); ++i) {
		if (v[i]->isOperation()) continue;
		dynamic_cast<operand*>(v[i])->fillValue();
	}

	ASSERT_ANY_THROW(rpn.calculate());

	for (int i = 0; i < v.size(); ++i) delete[] v[i];
}

TEST(RPN, wrong_calculation_throws_correct_exception_0)
{
	myVector<lexem*> v;
	v.push_back(new operation{ "~", 0 });
	v.push_back(new operation{ "~", 1 });
	v.push_back(new operation{ "~", 2 });
	v.push_back(new constant{ "1", 3 });
	RPN rpn(v);

	for (size_t i = 0; i < v.size(); ++i) {
		if (v[i]->isOperation()) continue;
		dynamic_cast<operand*>(v[i])->fillValue();
	}

	try {
		rpn.calculate();
	}
	catch (std::exception& e) {
		EXPECT_EQ("1L0ENo operand for this operator", std::string(e.what()));
	}

	for (int i = 0; i < v.size(); ++i) delete[] v[i];
}

TEST(RPN, wrong_calculation_correctly_and_throws_no_exception_1)
{
	myVector<lexem*> v;
	v.push_back(new operation{ "(", 0 });
	v.push_back(new constant{ "1", 1 });
	v.push_back(new operation{ "+", 2 });
	v.push_back(new constant{ "2", 3 });
	v.push_back(new operation{ ")", 0 });
	v.push_back(new operation{ "*", 1 });
	v.push_back(new operation{ "(", 2 });
	v.push_back(new constant{ "3", 3 });
	v.push_back(new operation{ "+", 3 });
	v.push_back(new operation{ ")", 3 });
	ASSERT_NO_THROW(RPN rpn(v));

	for (int i = 0; i < v.size(); ++i) delete[] v[i];
}

TEST(RPN, wrong_calculation_correctly_converted_1)
{
	myVector<lexem*> v;
	v.push_back(new operation{ "(", 0 });
	v.push_back(new constant{ "1", 1 });
	v.push_back(new operation{ "+", 2 });
	v.push_back(new constant{ "2", 3 });
	v.push_back(new operation{ ")", 0 });
	v.push_back(new operation{ "*", 1 });
	v.push_back(new operation{ "(", 2 });
	v.push_back(new constant{ "3", 3 });
	v.push_back(new operation{ "+", 3 });
	v.push_back(new operation{ ")", 3 });
	RPN rpn(v);

	myVector<lexem*> postfix;
	postfix.push_back(v[1]);
	postfix.push_back(v[3]);
	postfix.push_back(v[2]);
	postfix.push_back(v[7]);
	postfix.push_back(v[8]);
	postfix.push_back(v[5]);

	for (int i = 0; i < rpn.getPostfix().size(); ++i) {
		EXPECT_EQ(postfix[i], rpn.getPostfix()[i]);
		EXPECT_EQ(postfix[i], rpn.getPostfix()[i]);
	}

	for (int i = 0; i < v.size(); ++i) delete[] v[i];
}

TEST(RPN, wrong_calculation_throws_an_exception_1)
{
	myVector<lexem*> v;
	v.push_back(new operation{ "(", 0 });
	v.push_back(new constant{ "1", 1 });
	v.push_back(new operation{ "+", 2 });
	v.push_back(new constant{ "2", 3 });
	v.push_back(new operation{ ")", 0 });
	v.push_back(new operation{ "*", 1 });
	v.push_back(new operation{ "(", 2 });
	v.push_back(new constant{ "3", 3 });
	v.push_back(new operation{ "+", 3 });
	v.push_back(new operation{ ")", 3 });
	RPN rpn(v);

	for (size_t i = 0; i < v.size(); ++i) {
		if (v[i]->isOperation()) continue;
		dynamic_cast<operand*>(v[i])->fillValue();
	}

	ASSERT_ANY_THROW(rpn.calculate());

	for (int i = 0; i < v.size(); ++i) delete[] v[i];
}