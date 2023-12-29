#pragma once
#include <iostream>
using namespace std;

template<typename T>
class Stack
{
	T* data;
	size_t capacity;
	int size=-1;
public:
	Stack()
	{
		data = new T[10];
		capacity = 10;
	}
	Stack(size_t n)
	{
		capacity = n;
		data = new T[capacity];
		size = -1;
	}
	~Stack()
	{
		delete[] data;
		data = nullptr;
	}
	bool isEmpty()
	{
		return size == 0;
	}
	T top()
	{
		if (isEmpty())
			throw invalid_argument("Stack is empty");
		else
			return data[size - 1];
	}
	T pop()
	{
		if (isEmpty())
			throw invalid_argument("Stack is empty");
		else
			return data[--size];
	}
	void push(const T& elem)
	{
		if (++size == capacity)
		{
			T* tmp = new T[capacity * 2];
			for (size_t i = 0; i < capacity; i++)
			{
				tmp[i] = data[i];
			}
			delete[] data;
			data = tmp;
			capacity = 2 * capacity;
		}
		data[size] = elem;
	}
	size_t getSize()
	{
		return size;
	}
	void clear()
	{
		size = -1;
	}
};

