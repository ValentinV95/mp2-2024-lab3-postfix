// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

#pragma once

#include "Vector.h"

template<class T>
class Stack : protected Vector<T>
{
public:
    Stack() { }
    Stack(const Stack& s) = delete;
    ~Stack() { }
    using Vector<T>::length;
    using Vector<T>::operator=;
    using Vector<T>::clear;
    void push(const T& item)
    {
        Vector<T>::push_back(item);
        return;
    }
    T& top() const noexcept
    {
        return Vector<T>::back();
    }
    void pop() noexcept
    {
        Vector<T>::pop_back();
        return;
    }
    bool empty() const noexcept
    {
        return length() == 0;
    }
};