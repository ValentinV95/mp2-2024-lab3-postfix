
// ����� ��� �����



#include "stack.h"
#include <gtest.h>
#include <stdexcept>  // ��� ����������

// ��������� ����������� �������� �����
TEST(StackTest, TestPushAndPop)
{
    TStack<int> stack;

    // �������� ������� �����
    EXPECT_TRUE(stack.isEmpty());
    EXPECT_EQ(stack.size(), 0);

    // ��������� ������� � ����
    stack.push(1);
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_EQ(stack.size(), 1);

    // �������� �������� ��������
    EXPECT_EQ(stack.top(), 1);

    // ��������� �������
    stack.pop();
    EXPECT_TRUE(stack.isEmpty());
    EXPECT_EQ(stack.size(), 0);
}

// ���� �� ���������� �� ������� �����
TEST(StackTest, TestPopFromEmptyStack)
{
    TStack<int> stack;

    // �������� �� ������ ���� ��� ������� ������� �������
    EXPECT_THROW(stack.pop(), std::out_of_range);
}

// ���� �� ��������� �������� �������� �� ������� �����
TEST(StackTest, TestTopFromEmptyStack)
{
    TStack<int> stack;

    // �������� �� ������ ���� ��� ������� �������� ������� �������
    EXPECT_THROW(stack.top(), std::out_of_range);
}

// ���� �� ��������� �������� push
TEST(StackTest, TestMultiplePush)
{
    TStack<int> stack;

    // ��������� ��������� ��������� � ����
    stack.push(1);
    stack.push(2);
    stack.push(3);

    // �������� �������� ��������
    EXPECT_EQ(stack.top(), 3);
    EXPECT_EQ(stack.size(), 3);

    // ��������� �������� � ���������
    stack.pop();
    EXPECT_EQ(stack.top(), 2);
    stack.pop();
    EXPECT_EQ(stack.top(), 1);
    stack.pop();

    // ���� ������ ���� ������
    EXPECT_TRUE(stack.isEmpty());
}

// ���� �� ������� �����
TEST(StackTest, TestClear)
{
    TStack<int> stack;

    // ��������� ��������
    stack.push(1);
    stack.push(2);
    stack.push(3);

    // ������� ����
    stack.clear();

    // ���������, ��� ���� ����
    EXPECT_TRUE(stack.isEmpty());
    EXPECT_EQ(stack.size(), 0);
}
