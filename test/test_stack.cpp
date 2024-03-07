#include "stack.h"
#include <gtest.h>

TEST(DStack, can_create_stack){
    ASSERT_NO_THROW(DStack<double> s);
}

TEST(DStack, can_push_elem){
    double a = 1.5;
    DStack<double> s;
    ASSERT_NO_THROW(s.push(a));
}

TEST(DStack, can_resize_memory){
    DStack<int> s;
    for (int i = 0; i< 10; i++){
        s.push(i);
    }
    ASSERT_NO_THROW(s.push(12));
}

TEST(DStack, can_pop_elem_check_elem){
    DStack<int> s;
    int a = 15;
    s.push(2);
    s.push(3);
    s.push(a);
    EXPECT_EQ(15, s.pop());
}

TEST(DStack, cant_pop_empty_stack){
    DStack<int> s;
    ASSERT_ANY_THROW(s.pop());
}

TEST(DStack, correctly_return_curr_elem){
    DStack<int> s;
    int a = 15;
    s.push(2);
    s.push(a);
    EXPECT_EQ(15, s.current());
}

TEST(DStack, dont_change_size_after_get_curr){
    DStack<int> s;
    int a = 15;
    int v;
    s.push(2);
    s.push(a);
    v = s.current();
    EXPECT_EQ(2, s.Size());
}

TEST(DStack, cant_return_curr_elem_from_empty_stack){
    DStack<int> s;
    ASSERT_ANY_THROW(s.current());
}

TEST(DStack, correctly_check_isEmpty){
    DStack<int> s;
    EXPECT_EQ(1, s.isEmpty());
}

TEST(DStack, correctly_return_size){
    DStack<int> s;
    int sz = 5;
    for (int i = 0; i< sz;i++){
        s.push(i);
    }
    EXPECT_EQ(sz, s.Size());
}

TEST(DStack, can_pop_elem_change_size){
    DStack<int> s;
    int a = 15;
    s.push(2);
    s.push(a);
    s.pop();
    EXPECT_EQ(1, s.Size());
}

TEST(DStack, can_eraise_stack){
    DStack<int> s;
    int sz = 5;
    for (int i = 0; i< sz;i++){
        s.push(i);
    }
    s.del();
    EXPECT_EQ(0, s.Size());
}
