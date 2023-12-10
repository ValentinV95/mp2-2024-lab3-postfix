// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack)
{
	ASSERT_NO_THROW(TStack<int> s);
}

TEST(TStack, can_copy_stack)
{
	TStack<int> s;
	ASSERT_NO_THROW(TStack<int> s1(s));
}

TEST(TStack, copied_class_has_own_memory)
{
	TStack<int> s;
	s.push(42);

	TStack<int> s1(s);
	EXPECT_FALSE(&s1.top() == &s.top());
}

TEST(TStack, can_do_self_assignment)
{
	TStack<int> s;
	ASSERT_NO_THROW(s = s);
}

TEST(TStack, can_assign_stack)
{
	TStack<int> s, s1;
	ASSERT_NO_THROW(s1 = s);
}

TEST(TStack, assigned_stack_has_own_memory)
{
	TStack<int> s, s1;
	s.push(343156);
	s1 = s;
	EXPECT_FALSE(&s1.top() == &s.top());
}

TEST(TStack, assignment_changes_size)
{
	TStack<int> s, s1;
	s.push(38238);
	s1 = s;
	EXPECT_EQ(1, s1.size());
}

TEST(TStack, can_push_element)
{
	TStack<int> s;

	for(int i = 0; i < 300; i++)
		ASSERT_NO_THROW(s.push(i));

	ASSERT_NO_THROW(s.push(42));
}

TEST(TStack, can_pop_element)
{
	TStack<int> s;
	s.push(42);
	ASSERT_NO_THROW(s.pop());
}

TEST(TStack, can_get_top_element)
{
	TStack<int> s;
	s.push(2);
	ASSERT_NO_THROW(s.top());
}

TEST(TStack, top_element_changes_on_push)
{
	TStack<int> s;
	s.push(42);
	s.push(44);
	EXPECT_EQ(44, s.top());
}

TEST(TStack, top_element_changes_on_pop)
{
	TStack<int> s;
	s.push(83434);
	s.push(42);
	s.pop();
	EXPECT_EQ(83434, s.top());
}

TEST(TStack, cant_get_top_from_empty_stack)
{
	TStack<int> s;
	ASSERT_ANY_THROW(s.top());
}

TEST(TStack, stack_size_returns_zero_on_empty_stack)
{
	TStack<int> s;
	ASSERT_EQ(0, s.size());
}

TEST(TStack, stack_size_increases_on_push)
{
	TStack<int> s;
	s.push(42);
	ASSERT_EQ(1, s.size());
}

TEST(TStack, stack_size_decreases_on_pop)
{
	TStack<int> s;
	s.push(42);
	s.push(42);
	s.pop();
	ASSERT_EQ(1, s.size());
}

TEST(TStack, isempty_returns_true_on_empty_stack)
{
	TStack<int> s;
	ASSERT_TRUE(s.isEmpty());
}

TEST(TStack, isempty_returns_false_where_there_are_elements_in_stack)
{
	TStack<int> s;
	s.push(42);
	ASSERT_FALSE(s.isEmpty());
}