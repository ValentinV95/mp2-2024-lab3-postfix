// тесты для стека
#include "stack.h"
#include <gtest.h>

TEST(stack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicStack<int> s(5));
}
TEST(stack, cant_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicStack<int> s(-5));
}
TEST(stack, can_push)
{
	TDynamicStack<int> s;

	ASSERT_NO_THROW(s.Push(229));
}
TEST(stack, can_get_right_size)
{
	TDynamicStack<int> s;
	s.Push(3);
	s.Push(2);
	ASSERT_NO_THROW(s.size());
	ASSERT_EQ(s.size(),2);
}
TEST(stack, can_top)
{
	TDynamicStack<int> s;
	s.Push(3);
	s.Push(2);
	ASSERT_NO_THROW(s.Top());
	ASSERT_EQ(s.Top(), 2);
}
TEST(stack, can_Pop)
{
	TDynamicStack<int> s;
	s.Push(3);
	s.Push(2);
	ASSERT_NO_THROW(s.Pop());
	ASSERT_EQ(s.Top(), 3);
}
TEST(stack, cant_Pop_from_empty)
{
	TDynamicStack<int> s;
	ASSERT_ANY_THROW(s.Pop());
}
TEST(stack, right_isEmpty_for_not_empty)
{
	TDynamicStack<int> s;
	s.Push(3);
	s.Push(2);
	ASSERT_NO_THROW(s.isEmpty());
	ASSERT_EQ(s.isEmpty(), false);
}
TEST(stack, right_isEmpty_for_empty)
{
	TDynamicStack<int> s;
	ASSERT_NO_THROW(s.isEmpty());
	ASSERT_EQ(s.isEmpty(), true);
}
TEST(stack, can_clear)
{
	TDynamicStack<int> s;
	ASSERT_NO_THROW(s.clear());
}
TEST(stack, clear_change_to_empty)
{
	TDynamicStack<int> s;
	s.clear();
	ASSERT_EQ(s.isEmpty(),true);
}
