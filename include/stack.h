#pragma once
#include <iostream>
using namespace std;

template <class T>
class Stack
{
private:
	T* data;          // Указатель на массив элементов стека
	size_t capacity;  // Общая ёмкость стека
	size_t size;      // Текущее количество элементов в стеке
public:
	Stack()
	{
		data = new T[10];
		capacity = 10;
		size = 0;
	}
	bool isEmpty()
	{
		return size == 0;
	}
	T pop()
	{
		if (isEmpty())
			throw invalid_argument("Stack is empty");
		else
			return data[--size];
	}
	T top()
	{
		if (isEmpty())
			throw invalid_argument("Stack is empty");
		else
			return data[size - 1];
	}
	void push(T elem)
	{
		if (size == capacity)
		{
			T* tmp = new T[size * 2]();
			for (size_t i = 0; i < size; i++)
			{
				tmp[i] = data[i];
			}
			capacity = 2 * size;
			delete[] data;
			data = tmp;
		}
		data[size++] = elem;
	}
	size_t getSize()
	{
		return size;
	}
	void clear()
	{
		if (capacity > 10)
		{
			T* tmp = new T[10];
			delete[] data;
			data = tmp;
			capacity = 10;

		}
		size = 0;
	}
	~Stack()
	{
		delete[] data;
		data = nullptr;
		size = 0;
		capacity = 0;
	}
};
