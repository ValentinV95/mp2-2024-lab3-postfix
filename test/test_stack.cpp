// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(TDynamicStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicStack<int> s(5));
}

TEST(TDynamicStack, can_create_stack_without_length)
{
	ASSERT_NO_THROW(TDynamicStack<int> s());
}

TEST(TDynamicStack, cant_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicStack<int> s(-5));
}

TEST(TDynamicStack, can_create_stack_with_null_length)
{
	ASSERT_ANY_THROW(TDynamicStack<int> s(0));
}

TEST(TDynamicStack, correct_see_empty_1)
{
	TDynamicStack<int> s(5);
	ASSERT_NO_THROW(s.isEmpty());
}

TEST(TDynamicStack, correct_see_empty_2)
{
	TDynamicStack<int> s(5);
	s.push(7);
	s.pop();
	ASSERT_NO_THROW(s.isEmpty());
}

TEST(TDynamicStack, can_push_element)
{
	TDynamicStack<int> s(5);
	ASSERT_NO_THROW(s.push(7));
}

TEST(TDynamicStack, can_push_and_resize_memory)
{
	TDynamicStack<int> s(1);
	s.push(7);
	ASSERT_NO_THROW(s.push(5));
}

TEST(TDynamicStack, can_pop_element)
{
	TDynamicStack<int> s(5);
	s.push(7);
	ASSERT_NO_THROW(s.pop());
}

TEST(TDynamicStack, cant_pop_empty_stack)
{
	TDynamicStack<int> s(5);
	ASSERT_ANY_THROW(s.pop());
}

TEST(TDynamicStack, dont_delete_top_element)
{
	TDynamicStack<int> s(5);
	s.push(7);
	s.top();
	EXPECT_EQ(0, s.isEmpty());
	EXPECT_EQ(7, s.pop());
}

TEST(TDynamicStack, cant_see_top_in_empty_stack)
{
	TDynamicStack<int> s(5);
	ASSERT_ANY_THROW(s.top());
}

TEST(TDynamicStack, can_clear_stack)
{
	TDynamicStack<int> s(5);
	s.push(7);
	s.push(5);
	s.clear();
	EXPECT_EQ(1,s.isEmpty());
}

TEST(TDynamicStack, can_get_size)
{
	TDynamicStack<int> s(5);
	s.push(7);
	s.push(5);
	EXPECT_EQ(2, s.size());
}