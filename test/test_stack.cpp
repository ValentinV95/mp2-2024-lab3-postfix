// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(Stack, can_create_Stack_with_positive_length)
{
	ASSERT_NO_THROW(Stack<int> v);
}

TEST(Stack, can_create_copied_Stack)
{
	Stack<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push(i);
	}
	ASSERT_NO_THROW(Stack<int> v1(v));
}

TEST(Stack, copied_Stack_is_equal_to_source_one)
{
	Stack<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push(i);
	}
	Stack<int> v2 = v;
	EXPECT_EQ(v.length(), v2.length());
	while (!v.empty())
	{
		EXPECT_EQ(v.top(), v2.top());
		v.pop();
		v2.pop();
	}
	EXPECT_EQ(v.length(), v2.length());
}

TEST(Stack, copied_Stack_has_its_own_memory)
{
	Stack<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push(i);
	}
	Stack<int> v2 = v;
	v2.top() = 100;
	EXPECT_NE(v.top(), v2.top());
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

TEST(Stack, can_assign_Stack_to_itself)
{
	Stack<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push(i);
	}
	Stack<int> v2 = v;
	v = v;
	EXPECT_EQ(v.length(), v2.length());
	while (!v.empty())
	{
		EXPECT_EQ(v.top(), v2.top());
		v.pop();
		v2.pop();
	}
	EXPECT_EQ(v.length(), v2.length());
}

TEST(Stack, can_assign_Stacks_of_equal_size)
{
	Stack<int> v, v2;
	for (int i = 0; i < 10; i++)
	{
		v.push(i);
	}
	ASSERT_NO_THROW(v = v2);
}

TEST(Stack, assign_operator_change_Stack_size)
{
	Stack<int> v, v2;
	for (int i = 0; i < 5; i++)
	{
		v.push(i);
	}
	for (int i = 0; i < 10; i++)
	{
		v.push(i);
	}
	v = v2;
	EXPECT_EQ(v.length(), v2.length());
}

TEST(Stack, can_assign_Stacks_of_different_size)
{
	Stack<int> v, v2;
	for (int i = 0; i < 5; i++)
	{
		v.push(i);
	}
	for (int i = 0; i < 10; i++)
	{
		v.push(i);
	}
	ASSERT_NO_THROW(v = v2);
}

TEST(Stack, can_push)
{
	Stack<int> v;
	for (int i = 0; i < 100; i++)
	{
		ASSERT_NO_THROW(v.push(i));
	}
	EXPECT_EQ(100, v.length());
}

TEST(Stack, can_pop)
{
	Stack<int> v;
	for (int i = 0; i < 100; i++)
	{
		v.push(i);
	}
	ASSERT_NO_THROW(v.pop());
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
	EXPECT_EQ(0, v.length());
}