// тесты для стека
#include "stack.h"
#include <gtest.h>

TEST(Stack, can_create_Stack)
{
	ASSERT_NO_THROW(Stack<int> v);
}

TEST(Stack, can_push)
{
	Stack<int> v;
	for (int i = 0; i < 100; i++)
	{
		ASSERT_NO_THROW(v.push(i));
	}
}

TEST(Stack, can_get_size)
{
	Stack<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push(i);
	}
	EXPECT_EQ(10, v.length());
}

TEST(Stack, can_set_and_get_element)
{
	Stack<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push(i);
	}
	v.top() = 4;
	EXPECT_EQ(4, v.top());
}

TEST(Stack, check_pushed_items)
{
	Stack<int> v;
	for (int i = 0; i < 100; i++)
	{
		v.push(i);
	}
	for (int i = 99; i >= 0; i--)
	{
		int item = v.top();
		v.pop();
		EXPECT_EQ(i, item);
	}
}

TEST(Stack, can_pop)
{
	Stack<int> v;
	for (int i = 0; i < 100; i++)
	{
		v.push(i);
	}
	v.pop();
	EXPECT_EQ(99, v.length());
}

TEST(Stack, can_clear)
{
	Stack<int> v;
	for (int i = 0; i < 100; i++)
	{
		v.push(i);
	}
	ASSERT_NO_THROW(v.clear());
}

TEST(Stack, check_length_after_clear)
{
	Stack<int> v;
	for (int i = 0; i < 100; i++)
	{
		v.push(i);
	}
	v.clear();
	EXPECT_EQ(0, v.length());
}