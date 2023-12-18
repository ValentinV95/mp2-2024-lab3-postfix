// тесты для стека

#include "stack.h"
#include <gtest.h>
TEST(TStack, can_create_stack)
{
	ASSERT_NO_THROW(TStack<int> s);
}

TEST(TStack, isEmpty_is_correct) {
	TStack<int> st;
	EXPECT_EQ(true, st.isEmpty());
}

TEST(TStack, can_do_push_back) {
	TStack<int> st;
	ASSERT_NO_THROW(st.push_back(5));
}

TEST(TStack, can_do_top) {
	TStack<int> st;
	st.push_back(10);
	ASSERT_NO_THROW(st.top());
}

TEST(TStack, throws_when_do_top_when_stack_is_empty) {
	TStack<int> st;
	ASSERT_ANY_THROW(st.top());
}

TEST(TStack, top_is_correct) {
	TStack<int> st;
	st.push_back(7);
	EXPECT_EQ(7, st.top());
}

TEST(TStack, can_do_pop_back) {
	TStack<int> st;
	st.push_back(11);
	ASSERT_NO_THROW(st.pop_back());
}

TEST(TStack, throws_when_do_pop_back_when_stack_is_empty) {
	TStack<int> st;
	ASSERT_ANY_THROW(st.pop_back());
}

TEST(TStack, pop_back_is_correct) {
	TStack<int> st;
	st.push_back(9);
	EXPECT_EQ(9, st.pop_back());
}

TEST(TStack, count_of_empty_stack_is_equal_to_zero) {
	TStack<int> st;
	EXPECT_EQ(0, st.GetCount());
}

TEST(TStack, GetCount_is_correct) {
	TStack<int> st;
	st.push_back(0);
	EXPECT_EQ(1, st.GetCount());
}

TEST(TStack, push_back_increases_count_by_1) {
	TStack<int> st1, st2;
	st2.push_back(0);
	EXPECT_EQ(st1.GetCount() + 1, st2.GetCount());
}

TEST(TStack, pop_back_decreases_count_by_1) {
	TStack<int> st1, st2;
	st1.push_back(2);
	st2.push_back(3);
	st1.push_back(5);
	st2.push_back(7);
	st1.pop_back();
	EXPECT_EQ(st1.GetCount() + 1, st2.GetCount());
}

TEST(TStack, can_clear) {
	TStack<int> st;
	ASSERT_NO_THROW(st.clear());
}
 
TEST(TStack, clear_is_correct) {
	TStack<int> st;
	st.push_back(5);
	st.clear();
	EXPECT_EQ(true,st.isEmpty());
}