#include "RPN.h"
#include <gtest.h>

TEST(RPN, correct_convertation_from_infix_to_postfix_0)
{
	operation::fillOperations();
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

	for (size_t i = 0; i < postfix.size(); ++i) {
		if (postfix[i]->isOperation()) continue;
		dynamic_cast<operand*>(postfix[i])->fillValue();
	}

	double eps = 1e-25;
	EXPECT_EQ(true, abs(rpn.calculate() - -1.0) < eps);

	for (int i = 0; i < infix.size(); ++i) {
		delete[] infix[i];
	}
}

TEST(RPN, correct_convertation_from_infix_to_postfix_1)
{
	operation::fillOperations();
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

	for (size_t i = 0; i < postfix.size(); ++i) {
		if (postfix[i]->isOperation()) continue;
		dynamic_cast<operand*>(postfix[i])->fillValue();
	}

	double eps = 1e-25;
	EXPECT_EQ(true, abs(rpn.calculate() - 1.0) < eps);

	for (int i = 0; i < infix.size(); ++i) {
		delete[] infix[i];
	}
}

TEST(RPN, correct_convertation_from_infix_to_postfix_2)
{
	operation::fillOperations();
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

	for (size_t i = 0; i < postfix.size(); ++i) {
		if (postfix[i]->isOperation()) continue;
		dynamic_cast<operand*>(postfix[i])->fillValue();
	}

	double eps = 1e-25;
	EXPECT_EQ(true, abs(rpn.calculate() - 12.0) < eps);

	for (int i = 0; i < infix.size(); ++i) {
		delete[] infix[i];
	}
}

TEST(RPN, correct_convertation_from_infix_to_postfix_3)
{
	operation::fillOperations();
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

	for (size_t i = 0; i < postfix.size(); ++i) {
		if (postfix[i]->isOperation()) continue;
		dynamic_cast<operand*>(postfix[i])->fillValue();
	}

	double eps = 1e-25;
	EXPECT_EQ(true, abs(rpn.calculate() - 16.0) < eps);

	for (int i = 0; i < infix.size(); ++i) {
		delete[] infix[i];
	}
}
