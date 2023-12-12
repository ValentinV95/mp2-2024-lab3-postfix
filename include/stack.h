// ���������� � ���������� ���������� �����
// ���� ������������ ��������: 
// - ������� ��������, 
// - ���������� ��������, 
// - �������� �������� �������� (��� ��������)
// - �������� �� �������, 
// - ��������� ���������� ��������� � �����
// - ������� �����
// ��� ������� � ������ ���� ������ �������������� ������

#ifndef __STACK_H__
#define __STACK_H__

#include <iostream>

template<typename T>
class TStack
{
private:
	T* data;
	size_t size;
	int index;
public:
	TStack()
	{
		data = new T[100];
		index = -1;
		size = 100;
	}
	TStack(size_t n)
	{
		size = n;
		data = new T[size];
		index = -1;
	}
	TStack(const TStack& a)
	{
		size = a.size;
		head = a.head;
		data = new T[szie];
		for (size_t i = 0; i < size; i++)
		{
			data[i] = a.data[i];
		}
	}
	~TStack()
	{
		data = nullptr;
	}
	bool isEmpty()
	{
		return index == -1;
	}
	bool isFull()
	{
		return index == size - 1;
	}
	void push(T a)
	{
		if (isFull())
		{
			T* s = new T[size * 2];
			for (int i = 0; i < size; i++)
				s[i] = data[i];
			delete[]data;
			size = size * 2;
			data = s;
		}
		data[index + 1] = a;
		index++;
	}
	T pop()
	{
		if (!isEmpty())
		{
			return data[index--];
		}
		else
		{
			throw "Stack is empty";
		}
	}
	void clear()
	{
		delete[] data;
		index = -1;
	}
	int Getsize()
	{
		return size;
	}
	T peek()
	{
		if (!isEmpty())
		{
			return data[index];
		}
		else
		{
			throw "Is Empty stack";
		}
	}
};

#endif
