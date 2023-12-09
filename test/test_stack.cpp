// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(stack, can_create_stack)
{
	ASSERT_NO_THROW(stack<int> s);
}
TEST(stack, can_do_Is_Empty) {
	stack<int> s;
	ASSERT_NO_THROW(s.isEmpty());
}
TEST(stack, Is_Empty_is_correct) {
	stack<int> s;
	EXPECT_EQ(true, s.isEmpty());
}
TEST(stack, can_do_top) {
	stack<int> s;
	int a = 5;
	s.push(a);
	ASSERT_NO_THROW(s.top());
}
TEST(stack, cant_do_top_when_stack_is_empty) {
	stack<int> s;
	ASSERT_ANY_THROW(s.top());
}
TEST(stack, top_is_correct) {
	stack<int> s;
	int a = 5;
	s.push(a);
	EXPECT_EQ(5, s.top());
}
TEST(stack, can_do_pop) {
	stack<int> s;
	int a = 5;
	s.push(a);
	ASSERT_NO_THROW(s.pop());
}
TEST(stack, cant_do_pop_when_stack_is_empty) {
	stack<int> s;
	ASSERT_ANY_THROW(s.pop());
}
TEST(stack, pop_is_correct) {
	stack<int> s;
	int a = 5;
	s.push(a);
	EXPECT_EQ(5, s.pop());
}

TEST(stack, get_size_is_correct) {
	stack<int> s;
	int a = 5;
	s.push(a);
	EXPECT_EQ(1, s.get_size());
}
TEST(stack, can_resize) {
	stack<int> s;
	for (int i = 0; i <= 10; i++) {
		ASSERT_NO_THROW(s.push(i));
	}
}
TEST(stack, can_clear) {
	stack<int> s;
	ASSERT_NO_THROW(s.clear());
}
TEST(stack, clear_is_correct) {
	stack<int> s;
	int a = 5;
	s.push(a);
	s.clear();
	EXPECT_EQ(s.top(), 0);
}