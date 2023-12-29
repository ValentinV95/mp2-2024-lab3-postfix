// òåñòû äëÿ ñòåêà

#include "stack.h"
#include <gtest.h>
TEST(Stack, can_create_stack)
{
	ASSERT_NO_THROW(Stack<int> stack);
}

TEST(Stack, can_push_element_in_stack) 
{
	Stack<int> stack;
	ASSERT_NO_THROW(stack.push(123));
}

TEST(Stack, can_pop_element_from_stack) 
{
	Stack<int> stack;
	stack.push(123);
	EXPECT_EQ(123, stack.pop());
}

TEST(Stack, isEmpty_is_correct) 
{
	Stack<int> stack;
	EXPECT_EQ(true, stack.isEmpty());
}

TEST(Stack, top_is_correct) 
{
	Stack<int> stack;
	stack.push(123);
	EXPECT_EQ(123, stack.top());
}

TEST(Stack, can_top) 
{
	Stack<int> stack;
	stack.push(123);
	ASSERT_NO_THROW(stack.top());
}

TEST(Stack, pop_delete_element_on_the_top_of_stack)
{
	Stack<int> stack;
	stack.push(123);
	stack.push(45);
	stack.pop();
	EXPECT_EQ(123, stack.pop());
}

TEST(Stack, throws_when_do_top_when_stack_is_empty) 
{
	TStack<int> stack;
	ASSERT_ANY_THROW(stack.top());
}

TEST(Stack, can_pop) 
{
	TStack<int> stack;
	stack.push(123);
	ASSERT_NO_THROW(stack.pop());
}

TEST(Stack, throws_when_element_pop_from_empty_stack)
{
	Stack<int> stack;
	stack.push(123);
	stack.pop();
	ASSERT_ANY_THROW(stack.pop());
}

TEST(Stack, stack_size_is_correct)
{
	Stack<int> stack;
	stack.push(1);
  	stack.push(2);
  	stack.push(3);
	ASSERT_EQ(3, stack.get_size());
}

TEST(Stack, pop_reduces_stack_size)
{
	Stack<int> stack;
	stack.push(123);
	stack.push(123);
	stack.push(123);
	stack.pop();
	ASSERT_EQ(2, stack.get_size());
}
