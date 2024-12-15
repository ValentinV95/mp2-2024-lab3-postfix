#include <algorithm>
#pragma once

template <typename T>
class myVector {
private:
    T* data;
    size_t capacity;
    const size_t k;
protected:
    size_t sizevar;
public:
    myVector(size_t sizevar = 0, const T& v = T()) : k(2), capacity(1) {
        if (sizevar > 0) { 
            capacity = sizevar;
        }
        data = new T[capacity];
        std::fill(data, data + capacity, v);
        this->sizevar = sizevar;
    }
    myVector(const myVector& vec) : k(2) {
        data = new T[vec.capacity]();
        capacity = vec.capacity;
        sizevar = vec.sizevar;
        std::copy(vec.data, vec.data + sizevar, data);
    }
    myVector(myVector&& vec) : k(2) {
        data = nullptr;
        std::swap(data, vec.data);
        capacity = vec.capacity;
        sizevar = vec.sizevar;
    }
    ~myVector() {
        delete[] data;
    }
    myVector& operator=(const myVector& vec) {
        if (this == &vec) return *this;
        if (capacity < vec.sizevar) {
            T* t = new T[vec.capacity]();
            delete[] data;
            data = t;
        }
        capacity = vec.capacity;
        sizevar = vec.sizevar;
        std::copy(vec.data, vec.data + vec.sizevar, data);
        return *this;
    }
    myVector& operator=(myVector&& vec) {
        delete[] data;
        data = nullptr;
        capacity = vec.capacity;
        sizevar = vec.sizevar;
        std::swap(data, vec.data);
        return *this;
    }
    const size_t size() const {
        return sizevar;
    }
    const T& operator[](size_t i) const {
//        if (i >= sizevar) throw std::out_of_range("OUT OF RANGE"); //
        return data[i];
    } 
    T& operator[](size_t i) {
//        if (i >= sizevar) throw std::out_of_range("OUT OF RANGE"); //
        return data[i];
    }
    void push_back(const T& v) {
        if (sizevar >= capacity) {
            T* t = new T[capacity * k];
            std::copy(data, data + capacity, t);
            delete[] data;
            data = t;
            capacity *= k;
        }
        data[sizevar++] = v;
    }
    void resize(size_t n) {
        if (n > capacity) {
            T* t = new T[n]();
            std::copy(data, data + capacity, t);
            capacity = n;
            delete[] data;
            data = t;
        }
        sizevar = n;
    }
};