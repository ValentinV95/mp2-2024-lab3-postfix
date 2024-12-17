// объявление функций и классов для вычисления арифметических выражений
// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память


#ifndef Stack_H
#define Stack_H

#include "TDynamicVector.h"  // Подключаем вектор

template <typename T>
class TStack
{
private:
    TDynamicVector<T> vec;  // Стек будет использовать вектор

public:
    // Конструктор по умолчанию
    TStack() {}

    // Вставка элемента в стек
    void push(const T& value)
    {
        vec.push_back(value);  // Добавляем элемент в вектор
    }

    // Извлечение элемента из стека
    void pop()
    {
        if (isEmpty())
            throw std::out_of_range("Stack is empty");
        vec.pop_back();  // Удаляем последний элемент из вектора
    }

    // Просмотр верхнего элемента стека (без удаления)
    T& top()
    {
        if (isEmpty())
            throw std::out_of_range("Stack is empty");
        return vec.back();  // Возвращаем последний элемент
    }

    const T& top() const
    {
        if (isEmpty())
            throw std::out_of_range("Stack is empty");
        return vec.back();  // Возвращаем последний элемент
    }

    // Проверка на пустоту
    bool isEmpty() const
    {
        return vec.empty();  // Проверяем, пуст ли вектор
    }

    // Получение количества элементов в стеке
    size_t size() const
    {
        return vec.size();  // Размер вектора = количество элементов в стеке
    }

    // Очистка стека
    void clear()
    {
        while (!isEmpty())
        {
            pop();  // Удаляем все элементы
        }
    }
};

#endif