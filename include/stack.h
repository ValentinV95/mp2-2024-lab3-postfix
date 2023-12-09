// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память
#include <iostream>

template <class T> 
class TStack {
	T* mas;
	size_t count;
	size_t size;
	bool isFull() {
		return count == size;
	}
	void resize() {
		size *= 2;
		T* tmp = new T[size];
		std::copy(mas, mas + size, tmp);
		delete[] mas;
		mas = tmp;
	}
public:
	TStack() {
		mas = new T[10];
		count = 0;
		size = 10;
	}
	~TStack() {
		delete[] mas;
		mas = nullptr;
	}
	bool isEmpty() noexcept {
		return count == 0;
	}
	void push_back(const T& val) {
		if (isFull()) resize();
		mas[count++] = val;
	}
	size_t GetCount() noexcept {
		return count;
	}
	T& show_back() {
		if (!isEmpty())return mas[count];
		throw std::out_of_range("There are no elements in this Stack");
	}
	T pop_back() {
		if (!isEmpty()) return mas[count--];
		throw std::out_of_range("There are no elements in this Stack");
	}
	void clear() {
		this->~TStack();
		this->TStack();
	}
};