
#include "stack.h"
#include <gtest.h>

TEST(TStack, CanCreateStack)
{
	ASSERT_NO_THROW(TStack<int> stack);
}

TEST(TStack, CanPushElementInStack) 
{
	TStack<int> stack;
	ASSERT_NO_THROW(stack.push(123));
}

TEST(TStack, CanPopElementFromStack) 
{
	TStack<int> stack;
	stack.push(123);
	EXPECT_EQ(123, stack.pop());
}

TEST(TStack, IsEmptyIsCorrect) 
{
	TStack<int> stack;
	EXPECT_TRUE(stack.isEmpty());
}

TEST(TStack, TopIsCorrect) 
{
	TStack<int> stack;
	stack.push(123);
	EXPECT_EQ(123, stack.top());
}

TEST(TStack, CanCallTop) 
{
	TStack<int> stack;
	stack.push(123);
	ASSERT_NO_THROW(stack.top());
}

TEST(TStack, PopDeletesElementOnTheTopOfStack)
{
	TStack<int> stack;
	stack.push(123);
	stack.push(45);
	stack.pop();
	EXPECT_EQ(123, stack.pop());
}

TEST(TStack, ThrowsWhenDoTopWhenStackIsEmpty) 
{
	TStack<int> stack;
	ASSERT_ANY_THROW(stack.top());
}

TEST(TStack, CanCallPop) 
{
	TStack<int> stack;
	stack.push(123);
	ASSERT_NO_THROW(stack.pop());
}

TEST(TStack, ThrowsWhenPopFromEmptyStack)
{
	TStack<int> stack;
	stack.push(123);
	stack.pop();
	ASSERT_ANY_THROW(stack.pop());
}

TEST(TStack, StackSizeIsCorrect)
{
	TStack<int> stack;
	stack.push(1);
  	stack.push(2);
  	stack.push(3);
	ASSERT_EQ(3, stack.get_size());
}

TEST(TStack, PopReducesStackSize)
{
	TStack<int> stack;
	stack.push(123);
	stack.push(123);
	stack.push(123);
	stack.pop();
	ASSERT_EQ(2, stack.get_size());
}
