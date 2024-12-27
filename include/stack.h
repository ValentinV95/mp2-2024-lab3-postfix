#pragma once


template <typename T>
class Stack {
private:
	T* mem;
	int size, count;
public:
	Stack(int _size = 20) {
		size = _size;
		count = 0;
		mem = new T[size];
		for (int i = 0; i < size; i++) {
			mem[i] = T();
		}
	}
	Stack(const Stack& tmp) {
		size = tmp.size;
		count = tmp.count;
		mem = new T[size];
		for (int i = 0; i < size; i++) {
			mem[i] = tmp.mem[i];
		}
	}
	~Stack() {
		delete[]mem;
	}
	Stack& operator =(Stack<T> tmp) {
		if (size != tmp.size) {
			if (size != 0) {
				delete[]mem;
			}
			size = tmp.size;
			mem = new T[size];

		}
		count = tmp.count;
		for (int i = 0; i < size; i++) {
			mem[i] = tmp.mem[i];
		}
		return *this;
	}
	void push(T val) {
		if (count < size) {
			mem[count++] = val;
		}
	}
	T top() {
		if (count > 0) {
			return mem[count - 1];
		}
		else {
			T res(0);
			return res;
		}
	}
	T pop() {
		if (count > 0) {
			return mem[--count];
		}
		else {
			T res(0);
			return res;
		}
	}
	int is_full() {
		if (count == size) {
			return 1; 
		}
		else {
			return 0; 
		}
	}
	int is_empty() {
		if (count == 0) {
			return 1; 
		}
		else {
			return 0; 
		}
	}
	int Getcount() {
		return count;
	}
};