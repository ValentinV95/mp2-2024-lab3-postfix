// ���������� � ���������� ���������� �����
// ���� ������������ ��������: 
// - ������� ��������, 
// - ���������� ��������, 
// - �������� �������� �������� (��� ��������)
// - �������� �� �������, 
// - ��������� ���������� ��������� � �����
// - ������� �����
// ��� ������� � ������ ���� ������ �������������� ������

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