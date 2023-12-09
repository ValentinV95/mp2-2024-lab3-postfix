// тесты для стека

#include "stack.h"
#include <gtest.h>
TEST(TStack, can_create_stack)
{
	ASSERT_NO_THROW(TStack<int> s);
}
TEST(TStack, isEmpty_is_correct) {
	TStack<int> s;
	EXPECT_EQ(true, s.isEmpty());
}
TEST(TStack, can_do_push_back) {
	TStack<int> s;
	ASSERT_NO_THROW(s.push_back())
}
TEST(TStack, can_do_show_back) {
	TStack<int> s;
	s.push_back(5);
	ASSERT_NO_THROW(s.show_back());
}
TEST(TStack, cant_do_show_back_when_stack_is_empty) {
	TStack<int> s;
	ASSERT_ANY_THROW(s.show_back());
}
TEST(TStack, show_back_is_correct) {
	TStack<int> s;
	s.push_back(5);
	EXPECT_EQ(5, s.show_back());
}
TEST(TStack, can_do_pop_back) {
	TStack<int> s;
	s.push_back(5);
	ASSERT_NO_THROW(s.pop_back());
}
TEST(TStack, cant_do_pop_back_when_stack_is_empty) {
	TStack<int> s;
	ASSERT_ANY_THROW(s.pop_back());
}
TEST(TStack, pop_back_is_correct) {
	TStack<int> s;
	s.push_back(5);
	EXPECT_EQ(5, s.pop_back());
}
TEST(TStack, GetCount_is_correct) {
	TStack<int> s;
	s.push_back(5);
	EXPECT_EQ(1, s.get_size());
}
TEST(TStack, can_clear) {
	TStack<int> s;
	ASSERT_NO_THROW(s.clear());
}
TEST(TStack, clear_is_correct) {
	TStack<int> s;
	s.push_back(5);
	s.clear();
	EXPECT_EQ(true,s.isEmpty());
}