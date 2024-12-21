// ���������� ������� � ������� ��� ���������� �������������� ���������
// ���������� � ���������� ���������� �����
// ���� ������������ ��������: 
// - ������� ��������, 
// - ���������� ��������, 
// - �������� �������� �������� (��� ��������)
// - �������� �� �������, 
// - ��������� ���������� ��������� � �����
// - ������� �����
// ��� ������� � ������ ���� ������ �������������� ������


#ifndef TStack_H
#define TStack_H

#include "TDynamicVector.h"  // ���������� ������

template <typename T>
class TStack
{
private:
    TDynamicVector<T> vec;  // ���� ����� ������������ ������

public:
    // ����������� �� ���������
    TStack() {}

    // ������� �������� � ����
    void push(const T& value)
    {
        vec.push_back(value);  // ��������� ������� � ������
    }

    // ���������� �������� �� �����
    void pop()
    {
        if (isEmpty())
            throw std::out_of_range("Stack is empty");
        vec.pop_back();  // ������� ��������� ������� �� �������
    }

    // �������� �������� �������� ����� (��� ��������)
    T& top()
    {
        if (isEmpty())
            throw std::out_of_range("Stack is empty");
        return vec.back();  // ���������� ��������� �������
    }

    const T& top() const
    {
        if (isEmpty())
            throw std::out_of_range("Stack is empty");
        return vec.back();  // ���������� ��������� �������
    }

    // �������� �� �������
    bool isEmpty() const
    {
        return vec.empty();  // ���������, ���� �� ������
    }

    // ��������� ���������� ��������� � �����
    size_t size() const
    {
        return vec.size();  // ������ ������� = ���������� ��������� � �����
    }

    // ������� �����
    void clear()
    {
        while (!isEmpty())
        {
            pop();  // ������� ��� ��������
        }
    }
};

#endif