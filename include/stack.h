#pragma once
#include "vector.h"

template <typename T>
class Stack: protected Vector<T> {

public:
    using Vector<T>::getsize;
    Stack(){}

    void push(const T& v) {
        return Vector<T>::push_back(v);
    }

    void pop() {
        if (Vector<T>::isEmpty()) {
            throw std::out_of_range("Error in Stack::pop: out of range at position: " + std::to_string(Vector<T>::getsize()));
        }
        Vector<T>::pop_back();
    }

    T& top() const {
        if (Vector<T>::isEmpty()) {
            throw std::out_of_range("Error in Stack::top: out of range at position: " + std::to_string(Vector<T>::getsize()));
        }
        return Vector<T>::back();
    }

    bool isEmpty() const {
        return getsize() == 0;
    }

    size_t size() const {
        return getsize();
    }

    void clear() {
        return Vector<T>::clear();
    }
};