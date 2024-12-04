// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(myStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(myStack<int> v(5));
}

TEST(myStack, can_create_stack_with_zero_length)
{
	ASSERT_NO_THROW(myStack<int> v());
	ASSERT_NO_THROW(myStack<int> v(0));
}

TEST(myStack, can_create_copied_stack)
{
	myStack<int> st;
	st.push(0);
	st.push(1);
	st.push(2);

	ASSERT_NO_THROW(myStack<int> v(st));
}

TEST(myStack, copied_stack_is_equal_to_source_one)
{
	myStack<int> st;
	st.push(0);
	st.push(1);
	st.push(2);
	myStack<int> st2 = st;

	while (!st2.isEmpty() || !st.isEmpty()) {
		EXPECT_EQ(st2.pop(), st.pop());
	}
}

TEST(myStack, copied_stack_has_its_own_memory)
{
	myStack<int> st;
	st.push(0);
	st.push(1);
	st.push(2);
	myStack<int> st2 = st;
	st2.top() = 1;

	EXPECT_NE(st2.top(), st.top());
}

TEST(myStack, returns_empty_if_is_empty)
{
	myStack<int> st;
	st.push(1);
	EXPECT_EQ(false, st.isEmpty());

	st.pop();
	EXPECT_EQ(true, st.isEmpty());
}

TEST(myStack, can_assign_stack_to_itself) 
{
	myStack<int> st;
	st.push(0);
	st.push(1);
	st.push(2);

	myStack<int> st2 = st;
	st = st;
	while (!st2.isEmpty() || !st.isEmpty()) {
		EXPECT_EQ(st2.pop(), st.pop());
	}
}

TEST(myStack, can_assign_stacks)
{
	myStack<int> st;
	st.push(0);
	st.push(1);
	st.push(2);

	myStack<int> st2;
	st2 = st;
	while (!st2.isEmpty() || !st.isEmpty()) {
		EXPECT_EQ(st2.pop(), st.pop());
	}
}

TEST(myStack, assign_changes_emptinesss)
{
	myStack<int> st;
	st.push(0);
	st.push(1);
	st.push(2);

	myStack<int> st2;
	EXPECT_EQ(true, st2.isEmpty());
	st2 = st;
	EXPECT_EQ(false, st2.isEmpty());
}

TEST(myStack, can_clear_stack)
{
	myStack<int> st;
	st.push(0);
	st.push(1);
	st.push(2);
	EXPECT_EQ(false, st.isEmpty());
	st.clear();
	EXPECT_EQ(true, st.isEmpty());
}

TEST(myStack, can_set_and_get_top) {
	myStack<int> st;
	st.push(0);
	st.push(1);
	st.push(2);

	EXPECT_EQ(2, st.top());
	st.top() = 3;
	EXPECT_EQ(3, st.top());
}

TEST(myStack, can_push_and_pop_element) {
	myStack<int> st;
	st.push(0);
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	st.push(5);

	int it = 6;
	while (!st.isEmpty()) {
		EXPECT_EQ(--it, st.pop());
	}
}
