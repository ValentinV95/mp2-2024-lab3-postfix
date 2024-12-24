// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(stack, pop)
{
	TStack<int> s;
	s.push(3);
	s.push(2);
	ASSERT_NO_THROW(s.pop());
	ASSERT_EQ(s.top(), 3);
}
TEST(stack, cant_Pop_from_empty)
{
	TStack<int> s;
	ASSERT_ANY_THROW(s.pop());
}
TEST(stack, right_isEmpty_for_not_empty)
{
	TStack<int> s;
	s.push(3);
	s.push(2);
	ASSERT_NO_THROW(s.isEmpty());
	ASSERT_EQ(s.isEmpty(), false);
}
TEST(stack, right_isEmpty_for_empty)
{
	TStack<int> s;
	ASSERT_NO_THROW(s.isEmpty());
	ASSERT_EQ(s.isEmpty(), true);
}
TEST(stack, pop_delete_elements)
{
	TStack<int> s;
	s.push(3); s.push(2);
	ASSERT_EQ(s.pop(), 2);
	ASSERT_EQ(s.pop(), 3);
}