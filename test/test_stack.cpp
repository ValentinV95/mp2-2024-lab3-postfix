#include "stack.h"
#include <gtest.h>

TEST(MyStack, can_create_stack)
{
	ASSERT_NO_THROW(MyStack<double> stk);
}

TEST(MyStack, can_get_size)
{
	MyStack<int> stk;
	stk.GetData()->SetSize(6);
	ASSERT_NO_THROW(stk.GetSize());
	EXPECT_EQ(6, stk.GetSize());
}

TEST(MyStack, can_determine_if_its_empty_or_full)
{
	MyStack<int> stk;
	stk.GetData()->SetSize(0);
	EXPECT_EQ(false, stk.Is_Full());
	EXPECT_EQ(true, stk.Is_Empty());
	stk.GetData()->SetSize(32);
	EXPECT_EQ(false, stk.Is_Full());
	EXPECT_EQ(false, stk.Is_Empty());
	stk.GetData()->SetSize(64);
	EXPECT_EQ(true, stk.Is_Full());
	EXPECT_EQ(false, stk.Is_Empty());
}

TEST(MyStack, can_push_value)
{
	MyStack<double> stk;
	ASSERT_NO_THROW(stk.Push(5.0));
}

TEST(MyStack, size_is_increased_after_push)
{
	MyStack<double> stk;
	stk.Push(5.0);
	EXPECT_EQ(1, stk.GetSize());
}


TEST(MyStack, pushes_correct_value)
{
	MyStack<double> stk;
	stk.Push(5.0);
	EXPECT_DOUBLE_EQ(5.0, stk.GetData()->Top());
}


TEST(MyStack, can_take_top_value)
{
	MyStack<double> stk;
	double f;
	stk.Push(5.0);
	ASSERT_NO_THROW(f = stk.Top());
	EXPECT_DOUBLE_EQ(5.0, f);
}

TEST(MyStack, taking_value_from_empty_stack_throws)
{
	MyStack<double> stk;
	double f;
	ASSERT_ANY_THROW(f = stk.Top());
}

TEST(MyStack, can_pop_value)
{
	MyStack<double> stk;
	stk.Push(5.0);
	stk.Push(6.0);
	ASSERT_NO_THROW(stk.Pop());
}

TEST(MyStack, decrease_size_after_pop)
{
	MyStack<double> stk;
	stk.Push(5.0);
	stk.Push(6.0);
	stk.Pop();
	EXPECT_EQ(1, stk.GetSize());
}

TEST(MyStack, can_clear_itself)
{
	MyStack<size_t> stk;
	for (size_t i = 0; i < 10; i++)
	{
		stk.Push(i);
	}
	ASSERT_NO_THROW(stk.clear());
	EXPECT_EQ(0, stk.GetSize());
}