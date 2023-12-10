// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack)
{
	ASSERT_NO_THROW(TStack<int> s);
}
TEST(TStack, can_do_Is_Empty)
{
	TStack<int> s;
	ASSERT_NO_THROW(s.isEmpty());
}
TEST(TStack, Is_Empty_is_correct)
{
	TStack<int> s;
	EXPECT_EQ(true, s.isEmpty());
}
TEST(TStack, can_do_top)
{
	TStack<int> s;
	int a = 3;
	s.push(a);
	ASSERT_NO_THROW(s.top());
}
TEST(TStack, cant_do_top_when_stack_is_empty) 
{
	TStack<int> s;
	ASSERT_ANY_THROW(s.top());
}
TEST(TStack, top_is_correct) 
{
	TStack<int> s;
	int a = 3;
	s.push(a);
	EXPECT_EQ(3, s.top());
}
TEST(TStack, can_do_pop) 
{
	TStack<int> s;
	int a = 3;
	s.push(a);
	ASSERT_NO_THROW(s.pop());
}
TEST(TStack, cant_do_pop_when_stack_is_empty) 
{
	TStack<int> s;
	ASSERT_ANY_THROW(s.pop());
}
TEST(TStack, pop_is_correct) 
{
	TStack<int> s;
	int a = 3;
	s.push(a);
	EXPECT_EQ(3, s.pop());
}
TEST(TStack, get_size_is_correct) 
{
	TStack<int> s;
	int a = 3;
	s.push(a);
	EXPECT_EQ(1, s.get_size());
}
TEST(stack, can_resize) 
{
	TStack<int> s;
	for (int i = 0; i <= 5; i++) 
	{
		ASSERT_NO_THROW(s.push(i));
	}
}
TEST(TStack, can_clear) 
{
	TStack<int> s;
	ASSERT_NO_THROW(s.clear());
}
TEST(TStack, clear_is_correct)
{
	TStack<int> s;
	int a = 3;
	s.push(a);
	s.clear();
	EXPECT_EQ(s.top(), 0);
}