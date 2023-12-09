// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

#pragma once
#include<iostream>

using namespace std;

template <class T>
class TStack
{
private:
	T* pMem;
	int ind = -1;
	size_t size;
public:
	TStack()
	{
		size = 5;
		pMem = new T[size];
	}

	void push(T elem) //добавить элемент к стэк
	{
		if (++ind == size)
		{
			T* tmp = new T[size * 2];
			for (size_t i = 0; i < size; i++)
				tmp[i] = pMem[i];
			delete[] pMem;
			pMem = tmp;
			size *= 2;
		}
		pMem[ind] = elem;
	}

	T pop() //извлечь элемент из стэка
	{
		if (isEmpty())
			throw invalid_argument("Sorry, stack is empty");
		return pMem[ind--];
	}

	T top() //возврат верхнего элемента в стэка (peek)
	{
		if (isEmpty())
			throw invalid_argument("Sorry, stack is empty");
		return pMem[ind];
	}

	bool isEmpty() //проверка на пустоту стэка
	{
		return ind == -1;
	}

	size_t GetSize()
	{
		return ind + 1;
	}

	void clear() //очистить элемент
	{
		ind = -1;
	}

	~TStack()
	{
		delete[] pMem;
	}
};