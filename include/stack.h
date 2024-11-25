#include "myvector.h"
#pragma once

template <typename T>
class myStack : protected myVector<T> {
private:
    using myVector::sizevar;
public:
    using myVector::size;
    myStack(size_t size = 0) : myVector(size) {}
    myStack(const myStack& st) : myVector(&dynamic_cast<myVector*>(&st)) {} // https://habr.com/ru/articles/64369/
    myStack(myStack&& st) : myVector(st) {}
    myStack& operator=(const myStack& st) {
        this->myVector::operator=(st);
        return *this;
    }
    myStack& operator=(myStack&& st) {
        this->myVector::operator=(st);
        return *this;
    }
    bool isEmpty() const { return sizevar == 0; }
    void push(const T& v) {
        this->myVector::push_back(v);
    }
    const T& pop() {
        return this->myVector::operator[](--this->myVector::sizevar);
    }
    T& top() {
        return this->myVector::operator[](this->myVector::sizevar - 1);
    }
    void clear() {
        this->myVector::resize(0);
    }
};