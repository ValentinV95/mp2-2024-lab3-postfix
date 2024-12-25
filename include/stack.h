#pragma once
#include "vector.h"

template <typename T>
class Stack: protected Vector<T> {

public:
    using Vector<T>::getsize;
    Stack(){}

    // ������� ��������
    void push(const T& v) {
        return Vector<T>::push_back(v);
    }

    // ���������� ��������
    void pop() {
        Vector<T>::pop_back();
    }

    // �������� �������� ��������
    T& top() const {
        return Vector<T>::back();
    }

    // �������� �� �������
    bool isEmpty() const {
        return getsize() == 0;
    }

    // ��������� ���������� ��������� � �����
    size_t size() const {
        return getsize();
    }

    // ������� �����
    void clear() {
        return Vector<T>::clear();
    }
};