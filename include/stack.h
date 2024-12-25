#pragma once
#include "vector.h"

template <typename T>
class Stack: protected Vector<T> {

public:
    using Vector<T>::getsize;
    Stack(){}

    // Вставка элемента
    void push(const T& v) {
        return Vector<T>::push_back(v);
    }

    // Извлечение элемента
    void pop() {
        Vector<T>::pop_back();
    }

    // Просмотр верхнего элемента
    T& top() const {
        return Vector<T>::back();
    }

    // Проверка на пустоту
    bool isEmpty() const {
        return getsize() == 0;
    }

    // Получение количества элементов в стеке
    size_t size() const {
        return getsize();
    }

    // Очистка стека
    void clear() {
        return Vector<T>::clear();
    }
};