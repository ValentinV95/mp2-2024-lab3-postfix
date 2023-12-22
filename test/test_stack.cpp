// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack)
{
	ASSERT_NO_THROW(TStack<int> stack);
}

TEST(TStack, can_push_element_in_stack) {
	TStack<int> stack;
	ASSERT_NO_THROW(stack.push(123));
}

TEST(TStack, can_pop_element_from_stack) {
	TStack<int> stack;
	stack.push(123);
	EXPECT_EQ(123, stack.pop());
}

TEST(TStack, isEmpty_is_correct) {
	TStack<int> stack;
	EXPECT_EQ(true, stack.isEmpty());
}

TEST(TStack, top_is_correct) {
	TStack<int> stack;
	stack.push(123);
	EXPECT_EQ(123, stack.top());
}

TEST(TStack, can_top) {
	TStack<int> stack;
	stack.push(123);
	ASSERT_NO_THROW(stack.top());
}

TEST(TStack, pop_delete_element_on_the_top_of_stack)
{
	TStack<int> stack;
	stack.push(123);
	stack.push(45);
	stack.pop();
	EXPECT_EQ(123, stack.pop());
}

TEST(TStack, throws_when_do_top_when_stack_is_empty) {
	TStack<int> stack;
	ASSERT_ANY_THROW(stack.top());
}

TEST(TStack, can_pop) {
	TStack<int> stack;
	stack.push(123);
	ASSERT_NO_THROW(stack.pop());
}

TEST(TStack, throws_when_element_pop_from_empty_stack)
{
	TStack<int> stack;
	stack.push(123);
	stack.pop();
	ASSERT_ANY_THROW(stack.pop());
}

TEST(TStack, stack_size_)
{
	TStack<int> stack;
	stack.push(123);
	ASSERT_EQ(1, stack.get_size());
}
