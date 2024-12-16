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
class TDynamicStack {
	
	int top;
public:
	TDynamicStack(size_t _memSize=0) : top(-1), mem(_memSize) {  };
	size_t size() const { return top + 1; }
	bool isEmpty() const { return top == -1; }
	void Push(const T& val) {mem.push_back(val); top++;}
	void Pop() { mem.pop_back(); top--; }
	T Top() { return mem[top]; }
	void clear() { mem.clear(); top = -1; }
private:
	vector<T> mem;
};
