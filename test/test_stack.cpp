// тесты дл€ стека

#include "stack.h"
#include <gtest.h>

TEST(StackTest, PushAndTop) {
    Stack<int> stack;
    stack.push(1);
    EXPECT_EQ(stack.top(), 1);
    stack.push(2);
    EXPECT_EQ(stack.top(), 2);
}

TEST(StackTest, Pop) {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.pop();
    EXPECT_EQ(stack.top(), 1);
}

TEST(StackTest, IsEmpty) {
    Stack<int> stack;
    EXPECT_TRUE(stack.isEmpty());
    stack.push(1);
    EXPECT_FALSE(stack.isEmpty());
}

TEST(StackTest, Size) {
    Stack<int> stack;
    EXPECT_EQ(stack.size(), 0);
    stack.push(1);
    EXPECT_EQ(stack.size(), 1);
    stack.push(2);
    EXPECT_EQ(stack.size(), 2);
    stack.pop();
    EXPECT_EQ(stack.size(), 1);
}

TEST(StackTest, Clear) {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.clear();
    EXPECT_TRUE(stack.isEmpty());
}

TEST(StackTest, TopOnEmptyStack) {
    Stack<int> stack;
    EXPECT_THROW(stack.top(), std::out_of_range);
}

TEST(StackTest, PopOnEmptyStack) {
    Stack<int> stack;
    EXPECT_ANY_THROW(stack.pop());
}

TEST(StackTest, MultiplePush) {
    Stack<int> stack;
    for (int i = 0; i < 100; ++i) {
        stack.push(i);
    }
    EXPECT_EQ(stack.size(), 100);
}

TEST(StackTest, MultiplePop) {
    Stack<int> stack;
    for (int i = 0; i < 100; ++i) {
        stack.push(i);
    }
    for (int i = 99; i >= 0; --i) {
        EXPECT_EQ(stack.top(), i);
        stack.pop();
    }
    EXPECT_TRUE(stack.isEmpty());
}

TEST(StackTest, PushNull) {
    Stack<int*> stack;
    int a = 5;
    stack.push(&a);
    EXPECT_EQ(stack.top(), &a);
}

TEST(StackTest, ClearAfterPush) {
    Stack<int> stack;
    stack.push(1);
    stack.clear();
    EXPECT_TRUE(stack.isEmpty());
}

TEST(StackTest, SizeAfterClear) {
    Stack<int> stack;
    stack.push(1);
    stack.clear();
    EXPECT_EQ(stack.size(), 0);
}

TEST(StackTest, PushAndPopOrder) {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    EXPECT_EQ(stack.top(), 3);
    stack.pop();
    EXPECT_EQ(stack.top(), 2);
    stack.pop();
    EXPECT_EQ(stack.top(), 1);
}

TEST(StackTest, LargeNumberOfElements) {
    Stack<int> stack;
    for (int i = 0; i < 10000; ++i) {
        stack.push(i);
    }
    EXPECT_EQ(stack.size(), 10000);
    for (int i = 9999; i >= 0; --i) {
        EXPECT_EQ(stack.top(), i);
        stack.pop();
    }
}

TEST(StackTest, CheckMemoryReallocation) {
    Stack<int> stack;
    for (int i = 0; i < 1000; ++i) {
        stack.push(i);
    }
    EXPECT_EQ(stack.size(), 1000);
}

TEST(StackTest, ClearMultipleTimes) {
    Stack<int> stack;
    stack.push(1);
    stack.clear();
    stack.clear(); // ƒолжно работать без ошибок
    EXPECT_TRUE(stack.isEmpty());
}

TEST(StackTest, PushAfterClear) {
    Stack<int> stack;
    stack.push(1);
    stack.clear();
    stack.push(2);
    EXPECT_EQ(stack.top(), 2);
}

TEST(StackTest, PopUntilEmpty) {
    Stack<int> stack;
    for (int i = 0; i < 10; ++i) {
        stack.push(i);
    }
    while (!stack.isEmpty()) {
        stack.pop();
    }
    EXPECT_TRUE(stack.isEmpty());
}

TEST(StackTest, SizeAfterMultiplePushesAndPops) {
    Stack<int> stack;
    for (int i = 0; i < 50; ++i) {
        stack.push(i);
    }
    for (int i = 0; i < 25; ++i) {
        stack.pop();
    }
    EXPECT_EQ(stack.size(), 25);
}