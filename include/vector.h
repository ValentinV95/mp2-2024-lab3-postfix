#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
class Vector {
private:
    T* data;
    size_t capacity;
    size_t size;

public:
    Vector(size_t sz = 0, const T& v = T()) : size(sz)
    {
        if (size != 0) {
            capacity = sz;
        }
        else {
            capacity = 1;
        }
        data = new T[capacity];
        std::fill(data, data + size, v);
    }
    Vector(Vector&& v) : data(nullptr), size(0), capacity(1)
    {
        data = v.data;
        capacity = v.capacity;
        size = v.size;
        v.data = nullptr;
        v.capacity = 0;
        v.size = 0;
    }
    Vector(const Vector& v) : capacity(v.capacity), size(v.size)
    {
        data = new T[capacity];
        std::copy(v.data, v.data + v.size, data);
    }
    ~Vector()
    {
        capacity = 0;
        size = 0;
        delete[] data;
    }
    Vector& operator=(const Vector& v)
    {
        if (this == &v) {
            return *this;
        }
        if (capacity < v.capacity)
        {
            T* newData = new T[v.capacity];
            delete[] data;
            data = newData;
            capacity = v.capacity;
        }
        std::copy(v.data, v.data + v.capacity, data);
        size = v.size;
        return *this;
    }
    Vector& operator=(Vector&& v)
    {
        delete[] data;
        data = nullptr;
        capacity = v.capacity;
        size = v.size;
        std::swap(data, v.data);
        v.capacity = 0;
        v.size = 0;
        return *this;
    }

    bool operator==(const Vector& v) const {
        if (size != v.size) {
            return false; 
        }
        for (size_t i = 0; i < size; ++i) {
            if (data[i] != v.data[i]) {
                return false;
            }
        }
        return true; 
    }

    bool operator!=(const Vector& v) const {
        return !(*this == v);
    }

    bool isEmpty() const {
        return size == 0;
    }

    const size_t getsize() const {
        return size;
    }
    const size_t getcapacity() const {
        return capacity;
    }
    const T& operator[](size_t index) const {
        return data[index];
    }
    T& operator[](size_t index) {
        return data[index];
    }
    void resize_pushback() {
        capacity *= 2;
        T* newData = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }
    void push_back(const T& v) {
        if (size == capacity) {
            resize_pushback();
        }
        data[size++] = v;
    }
    const T& at(size_t index) const {
        if (index >= size || index < 0) {
            throw std::out_of_range("Index out of range at position " + std::to_string(index));
        }
        return data[index];
    }
    void pop_back() {
        if (size == 0) {
            throw std::out_of_range("out of range");
        }
        size--;
    }
    void resize(size_t sz) {
        if (sz > capacity) {
            T* newData = new T[sz]();
            std::copy(data, data + size, newData);
            capacity = sz;
            delete[] data;
            data = newData;
        }
        size = sz;
    }
    void clear() { 
        resize(0); 
    }
    T& back() const { 
        if (!size) {
            throw std::out_of_range("out of range");
        }
        return data[size - 1];
    }
    T& front() const{
        if (!size) {
            throw std::out_of_range("out of range");
        }
        return data[0];
    }
};