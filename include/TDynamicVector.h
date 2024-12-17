#pragma once
#ifndef TDynamicVector_H
#define TDynamicVector_H

#include <stdexcept> // Для исключений
//#include <iostream>
//using namespace std;

template <typename T>
class TDynamicVector
{
private:
    size_t sz;  // Размер вектора
    size_t capacity;  // Вместимость вектора
    T* pMem;  // Указатель на динамическую память

public:
    TDynamicVector(size_t size = 1) : sz(0), capacity(size)
    {
        if (capacity == 0)
            throw std::out_of_range("Vector size must be greater than zero");
        pMem = new T[capacity];
    }

    //конструктор копирования
    TDynamicVector(const TDynamicVector& other) : sz(other.sz), capacity(other.capacity), pMem(new T[other.capacity]) {
        for (size_t i = 0; i < sz; ++i) {
            pMem[i] = other.pMem[i];
        }
    }

    //оператор присваивания
    TDynamicVector& operator=(const TDynamicVector& other) {
        if (this != &other) {//проверка наа самоприсваивание 
            delete[] pMem;
            sz = other.sz;
            capacity = other.capacity;
            pMem = new T[capacity]; //выделяем новую память

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

    // Проверка, пуст ли вектор
    bool empty() const
    {
        return sz == 0;
    }

    // Получение размера
    size_t size() const
    {
        return sz;
    }

    // Добавление элемента в конец вектора
    void push_back(const T& value)
    {
        if (sz == capacity)
        {
            // Удваиваем вместимость вектора при переполнении
            capacity *= 2;
            T* newMem = new T[capacity];
            for (size_t i = 0; i < sz; ++i)
                newMem[i] = pMem[i];
            delete[] pMem;
            pMem = newMem;
        }
        pMem[sz++] = value;
    }

    // Доступ к элементу по индексу
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

    // Удаление элемента с конца вектора
    void pop_back()
    {
        if (empty())
            throw std::out_of_range("Vector is empty");
        --sz;
    }

    // Получение элемента на последней позиции
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

    //методы для range-based for
    T* begin() {
        return pMem; //указатель на 1ый элемент
    }

    const T* begin() const {
        return pMem;
    }

    T* end() {
        return pMem + sz; //указатель на элемент за последним
    }

    const T* end() const {
        return pMem + sz;
    }
};

#endif