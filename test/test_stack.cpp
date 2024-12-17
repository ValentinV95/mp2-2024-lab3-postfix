// тесты для стека



#include "stack.h"
#include <gtest.h>
#include <stdexcept>  // Для исключений

// Тестируем стандартные операции стека
TEST(StackTest, TestPushAndPop)
{
    TStack<int> stack;

    // Проверка пустоты стека
    EXPECT_TRUE(stack.isEmpty());
    EXPECT_EQ(stack.size(), 0);

    // Добавляем элемент в стек
    stack.push(1);
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_EQ(stack.size(), 1);

    // Проверка верхнего элемента
    EXPECT_EQ(stack.top(), 1);

    // Извлекаем элемент
    stack.pop();
    EXPECT_TRUE(stack.isEmpty());
    EXPECT_EQ(stack.size(), 0);
}

// Тест на извлечение из пустого стека
TEST(StackTest, TestPopFromEmptyStack)
{
    TStack<int> stack;

    // Проверка на пустой стек при попытке извлечь элемент
    EXPECT_THROW(stack.pop(), std::out_of_range);
}

// Тест на получение верхнего элемента из пустого стека
TEST(StackTest, TestTopFromEmptyStack)
{
    TStack<int> stack;

    // Проверка на пустой стек при попытке получить верхний элемент
    EXPECT_THROW(stack.top(), std::out_of_range);
}

// Тест на несколько операций push
TEST(StackTest, TestMultiplePush)
{
    TStack<int> stack;

    // Добавляем несколько элементов в стек
    stack.push(1);
    stack.push(2);
    stack.push(3);

    // Проверка верхнего элемента
    EXPECT_EQ(stack.top(), 3);
    EXPECT_EQ(stack.size(), 3);

    // Извлекаем элементы и проверяем
    stack.pop();
    EXPECT_EQ(stack.top(), 2);
    stack.pop();
    EXPECT_EQ(stack.top(), 1);
    stack.pop();

    // Стек должен быть пустым
    EXPECT_TRUE(stack.isEmpty());
}

// Тест на очистку стека
TEST(StackTest, TestClear)
{
    TStack<int> stack;

    // Добавляем элементы
    stack.push(1);
    stack.push(2);
    stack.push(3);

    // Очищаем стек
    stack.clear();

    // Проверяем, что стек пуст
    EXPECT_TRUE(stack.isEmpty());
    EXPECT_EQ(stack.size(), 0);
}