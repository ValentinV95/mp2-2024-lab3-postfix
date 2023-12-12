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

	TStack(size_t n)
	{
		if (n < 0)
			throw invalid_argument("Incorrent size stack");
		size = n;
		pMem = new T[size];
		ind = -1;
	}

	void push(T elem)
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

	T pop()
	{
		if (isEmpty())
			throw invalid_argument("Sorry, stack is empty");
		return pMem[ind--];
	}

	T top()
	{
		if (isEmpty())
			throw invalid_argument("Sorry, stack is empty");
		return pMem[ind];
	}

	bool isEmpty() const noexcept
	{
		return ind == -1;
	}

	size_t GetSize() const noexcept
	{
		return ind + 1;
	}

	void clear()
	{
		ind = -1;
	}

	~TStack()
	{
		delete[] pMem;
	}
};
