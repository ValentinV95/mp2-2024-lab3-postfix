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
#include "datavec.h"

template <typename T>
class MyStack
{
protected:
	Vec<T> data{};
public:
	MyStack() = default;
	MyStack(MyStack const& stack_) = delete;
	~MyStack() = default;

	bool Is_Empty()
	{
		return data.Is_Empty();
	};

	bool Is_Full()
	{
		return data.Is_Full();
	};

	size_t GetSize()
	{
		return data.GetSize();
	};

	Vec<T>* GetData()
	{
		return &data;
	};

	void push(T const& val)
	{
		data.push_back(val);
		return;
	};

	T const& Top()
	{
		return data.Top();
	};

	void Pop()
	{
		data.pop_back();
		return;
	};

	void clear()
	{
		data.clear();
		return;
	};
};