// тесты для стека

#include <gtest.h>
#include "stack.h"

TEST(TStack, creates)
{
	EXPECT_NO_THROW(TStack<int> T);
	EXPECT_NO_THROW(TStack<long long int> T);
	EXPECT_NO_THROW(TStack<double> T);
	EXPECT_NO_THROW(TStack<float> T);
	EXPECT_NO_THROW(TStack<char> T);
	EXPECT_NO_THROW(TStack<std::string> T);
}

TEST(TStack, can_push)
{
	TStack<int> T;
	for (int i = 0; i < 100; i++)
		EXPECT_NO_THROW(T.push(i));
}

TEST(TStack, quantElems_returns_correct_value)
{
	TStack<int> T;
	for (int i = 0; i < 100; i++)
		T.push(i);
	EXPECT_EQ(100, T.quantElems());
}

TEST(TStack, can_pop)
{
	TStack<int> T;
	T.push(2);
	EXPECT_NO_THROW(T.pop());
}

TEST(TStack, pops_correctly)
{
	TStack<int> T;
	for (int i = 0; i < 100; i++)
		T.push(i);
	for (int i = 99; i >= 0; i--)
		EXPECT_EQ(i, T.pop());
}

TEST(TStack, isEmpty_is_correct)
{
	TStack<int> T;
	EXPECT_EQ(true, T.isEmpty());
	for (int i = 0; i < 100; i++)
		T.push(i);
	EXPECT_EQ(false, T.isEmpty());
	for (int i = 0; i < 100; i++)
		T.pop();
	EXPECT_EQ(true, T.isEmpty());
}

TEST(TStack, throws_when_try_pop_from_empty_stack)
{
	TStack<int> T;
	for (int i = 0; i < 100; i++)
		T.push(i);
	EXPECT_ANY_THROW(
		for (int i = 0; i < 200; i++)
			T.pop();
	);
}

TEST(TStack, can_top)
{
	TStack<int> T;
	T.push(2);
	EXPECT_NO_THROW(T.top());
}

TEST(TStack, throws_when_try_top_from_empty_stack)
{
	TStack<int> T;
		T.push(1);
		T.pop();
	EXPECT_ANY_THROW(T.top());
}

TEST(TStack, top_is_correct)
{
	TStack<int> T;
		T.push(2);
		T.top() = 3;
		EXPECT_EQ(3, T.pop());
}

TEST(TStack, can_clear)
{
	TStack<int> T;
	for (int i = 0; i < 100; i++)
		T.push(i);
	EXPECT_NO_THROW(T.clear());
}

TEST(TStack, clear_is_correct)
{
	TStack<int> T;
	for (int i = 0; i < 100; i++)
		T.push(i);
	T.clear();
	EXPECT_EQ(true, T.isEmpty());
}
