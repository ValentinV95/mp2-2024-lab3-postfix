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

	bool Is_Empty() const
	{
		return data.Is_Empty();
	};

	bool Is_Full() const
	{
		return data.Is_Full();
	};

	size_t GetSize() const
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

	T Top() const
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