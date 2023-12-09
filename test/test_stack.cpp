// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack)
{
    ASSERT_NO_THROW(TStack<int> stack);
}

TEST(TStack, can_get_stack_size)
{
    TStack<int> st;
    ASSERT_NO_THROW(st.GetSize());
}

TEST(TStack, empty_stack_is_null)
{
    TStack<int> st;
    EXPECT_EQ(0, st.GetSize());
}

TEST(TStack, stack_have_correct_size)
{
    TStack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    EXPECT_EQ(3, st.GetSize());
}

TEST(TStack, can_return_top_element_when_stack_isnt_empty)
{
    TStack<int> st;
    st.push(1);
    st.push(2);
    ASSERT_NO_THROW(st.top());
}

TEST(TStack, correct_return_top_element_when_stack_isnt_empty)
{
    TStack<int> st;
    st.push(1);
    st.push(2);
    EXPECT_EQ(2, st.top());
}

TEST(TStack, cant_return_top_element_if_stack_is_empty)
{
    TStack<int> st;
    ASSERT_ANY_THROW(st.top());
}

TEST(TStack, can_do_pop_when_stack_isnt_empty)
{
    TStack<int> st;
    st.push(1);
    ASSERT_NO_THROW(st.pop());
}

TEST(TStack, can_correct_do_pop_when_stack_isnt_empty)
{
    TStack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    EXPECT_EQ(3, st.pop());
}

TEST(TStack, cant_do_pop_when_stack_is_empty)
{
    TStack<int> st;
    ASSERT_ANY_THROW(st.pop());
}


TEST(TStack, top_cant_change_stack_size)
{
    TStack<int> st;
    st.push(1);
    st.push(2);
    st.top();
    EXPECT_EQ(2, st.GetSize());
}

TEST(TStack, pop_can_change_stack_size)
{
    TStack<int> st;
    st.push(1);
    st.push(2);
    st.pop();
    EXPECT_EQ(1, st.GetSize());
}

TEST(TStack, can_clean_stack)
{
    TStack<int> st;

    ASSERT_NO_THROW(st.clear());
}

TEST(TStack, can_correct_clean_stack)
{
    TStack<int> st;
    st.push(1);
    st.push(2);
    st.clear();
    EXPECT_EQ(0, st.GetSize());
}