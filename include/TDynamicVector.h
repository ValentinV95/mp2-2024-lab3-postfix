#pragma once
#ifndef TDynamicVector_H
#define TDynamicVector_H

#include <stdexcept> // ��� ����������
//#include <iostream>
//using namespace std;

template <typename T>
class TDynamicVector
{
private:
    size_t sz;  // ������ �������
    size_t capacity;  // ����������� �������
    T* pMem;  // ��������� �� ������������ ������

public:
    TDynamicVector(size_t size = 1) : sz(0), capacity(size)
    {
        if (capacity == 0)
            throw std::out_of_range("Vector size must be greater than zero");
        pMem = new T[capacity];
    }

    //����������� �����������
    TDynamicVector(const TDynamicVector& other) : sz(other.sz), capacity(other.capacity), pMem(new T[other.capacity]) {
        for (size_t i = 0; i < sz; ++i) {
            pMem[i] = other.pMem[i];
        }
    }

    //�������� ������������
    TDynamicVector& operator=(const TDynamicVector& other) {
        if (this != &other) {//�������� ��� ���������������� 
            delete[] pMem;
            sz = other.sz;
            capacity = other.capacity;
            pMem = new T[capacity]; //�������� ����� ������

            for (size_t i = 0; i < sz; ++i) {
                pMem[i] = other.pMem[i];
            }
        }
        return *this;
    }

    ~TDynamicVector()
    {
        delete[] pMem;
    }

    // ��������, ���� �� ������
    bool empty() const
    {
        return sz == 0;
    }

    // ��������� �������
    size_t size() const
    {
        return sz;
    }

    // ���������� �������� � ����� �������
    void push_back(const T& value)
    {
        if (sz == capacity)
        {
            // ��������� ����������� ������� ��� ������������
            capacity *= 2;
            T* newMem = new T[capacity];
            for (size_t i = 0; i < sz; ++i)
                newMem[i] = pMem[i];
            delete[] pMem;
            pMem = newMem;
        }
        pMem[sz++] = value;
    }

    // ������ � �������� �� �������
    T& operator[](size_t index)
    {
        if (index >= sz)
            throw std::out_of_range("Index out of range");
        return pMem[index];
    }

    const T& operator[](size_t index) const
    {
        if (index >= sz)
            throw std::out_of_range("Index out of range");
        return pMem[index];
    }

    // �������� �������� � ����� �������
    void pop_back()
    {
        if (empty())
            throw std::out_of_range("Vector is empty");
        --sz;
    }

    // ��������� �������� �� ��������� �������
    T& back()
    {
        if (empty())
            throw std::out_of_range("Vector is empty");
        return pMem[sz - 1];
    }

    const T& back() const
    {
        if (empty())
            throw std::out_of_range("Vector is empty");
        return pMem[sz - 1];
    }

    //������ ��� range-based for
    T* begin() {
        return pMem; //��������� �� 1�� �������
    }

    const T* begin() const {
        return pMem;
    }

    T* end() {
        return pMem + sz; //��������� �� ������� �� ���������
    }

    const T* end() const {
        return pMem + sz;
    }
};

#endif