// тесты для стека

#include "Stack.h"
#include <gtest.h>


TEST(StackTest, TestPushAndTop) {
    Stack <int> stack;
    
    stack.push(10);
    EXPECT_EQ(stack.top(), 10);
    stack.push(20);
    EXPECT_EQ(stack.top(), 20);
}

TEST(StackTest, TestPop) {
    
    Stack <int> stack;
    
    stack.push(30);
    stack.push(40);
    EXPECT_EQ(stack.pop(), 40);
    EXPECT_EQ(stack.top(), 30);
}

TEST(StackTest, TestIsEmpty) {
    
    Stack <int> stack;
    
    EXPECT_TRUE(stack.is_empty());
    stack.push(50);
    EXPECT_FALSE(stack.is_empty());
}

TEST(StackTest, TestIsFull) {
    Stack<int> fullStack(1);
    fullStack.push(60);
    EXPECT_TRUE(fullStack.is_full());
}

TEST(StackTest, TestGetCount) {
    Stack <int> stack;
    
    EXPECT_EQ(stack.Getcount(), 0);
    stack.push(70);
    EXPECT_EQ(stack.Getcount(), 1);
    stack.pop();
    EXPECT_EQ(stack.Getcount(), 0);
}
