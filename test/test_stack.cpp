// тесты для стека

#include "Stack.h"
#include <gtest.h>


class StackTest : public ::testing::Test {
protected:
    Stack<int> stack;

    void SetUp() override {
    }
};

TEST_F(StackTest, TestPushAndTop) {
    stack.push(10);
    EXPECT_EQ(stack.top(), 10);
    stack.push(20);
    EXPECT_EQ(stack.top(), 20);
}

TEST_F(StackTest, TestPop) {
    stack.push(30);
    stack.push(40);
    EXPECT_EQ(stack.pop(), 40);
    EXPECT_EQ(stack.top(), 30);
}

TEST_F(StackTest, TestIsEmpty) {
    EXPECT_TRUE(stack.is_empty());
    stack.push(50);
    EXPECT_FALSE(stack.is_empty());
}

TEST_F(StackTest, TestIsFull) {
    Stack<int> fullStack(1);
    fullStack.push(60);
    EXPECT_TRUE(fullStack.is_full());
}

TEST_F(StackTest, TestGetCount) {
    EXPECT_EQ(stack.Getcount(), 0);
    stack.push(70);
    EXPECT_EQ(stack.Getcount(), 1);
    stack.pop();
    EXPECT_EQ(stack.Getcount(), 0);
}
