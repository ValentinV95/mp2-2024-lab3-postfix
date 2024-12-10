#include "stack.h"
#include <gtest.h>

myStack<int> foo() {
	myStack<int> st;
	st.push(1);
	st.push(2);
	st.push(3);
	return st;
}

TEST(myStack, can_create_stack_with_no_operands)
{
	ASSERT_NO_THROW(myStack<int> v());
}


TEST(myStack, can_create_copied_stack)
{
	myStack<int> st;
	st.push(0);
	st.push(1);
	st.push(2);

	ASSERT_NO_THROW(myStack<int> v(st));
}

TEST(myStack, can_create_moved_stack)
{
	ASSERT_NO_THROW(myStack<int> v(foo()));
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

TEST(myStack, moved_stack_is_equal_to_source_one)
{
	myStack<int> st;
	st.push(1);
	st.push(2);
	st.push(3);
	myStack<int> st2 = foo();

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

TEST(myStack, can_assign_stack_to_itself)
{
	myStack<int> st;
	st.push(0);
	st.push(1);
	st.push(2);

	ASSERT_NO_THROW(st = st);
}

TEST(myStack, assign_stack_to_itself_is_correct)
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
	ASSERT_NO_THROW(st2 = st);
}

TEST(myStack, assign_stacks_is_correct)
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

TEST(myStack, can_assign_move_stacks)
{
	myStack<int> st;
	st.push(1);
	st.push(2);
	st.push(3);

	myStack<int> st2;
	ASSERT_NO_THROW(st2 = foo());
}

TEST(myStack, assign_move_stacks_is_correct)
{
	myStack<int> st;
	st.push(1);
	st.push(2);
	st.push(3);

	myStack<int> st2;
	st2 = foo();
	while (!st2.isEmpty() || !st.isEmpty()) {
		EXPECT_EQ(st2.pop(), st.pop());
	}
}

TEST(myStack, zero_length_stack_is_empty) {
	myStack<int> st;
	EXPECT_EQ(true, st.isEmpty());
}

TEST(myStack, assign_changes_emptiness)
{
	myStack<int> st;
	st.push(0);
	st.push(1);
	st.push(2);

	myStack<int> st2;
	st2 = st;
	EXPECT_EQ(false, st2.isEmpty());
}

TEST(myStack, isEmpty_returns_true)
{
	myStack<int> st;
	st.push(0);
	st.pop();
	EXPECT_EQ(true, st.isEmpty());
}

TEST(myStack, clear_is_correct)
{
	myStack<int> st;
	st.push(0);
	st.push(1);
	st.push(2);
	st.clear();
	EXPECT_EQ(true, st.isEmpty());
}


TEST(myStack, isEmpty_returns_false_if_its_false)
{
	myStack<int> st;
	st.push(0);
	st.push(1);
	st.push(2);
	EXPECT_EQ(false, st.isEmpty());
}

TEST(myStack, can_get_top) {
	myStack<int> st;
	st.push(0);
	st.push(1);
	st.push(2);

	EXPECT_EQ(2, st.top());
}

TEST(myStack, can_set_top) {
	myStack<int> st;
	st.push(0);
	st.push(1);
	st.push(2);
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
