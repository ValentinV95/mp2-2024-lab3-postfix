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
#include "vector.h"

template<typename T>
class TStack {
	int num;
	vector<T> mem;
public:
	TStack(size_t memSize = 0) {
		num = -1;
		mem = memSize;
	};
	size_t size() const 
	{ 
		return num + 1; 
	}
	bool isEmpty() const { return num == -1; }
	void push(const T& val) 
	{ 
		mem.push_back(val); 
		num++; 
	}
	T pop() {
		T val = mem[num];
		mem.pop_back();
		num--;
		return val;
	}
	T top() { 
		return mem[num]; 
	}
};