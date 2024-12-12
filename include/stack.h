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
#include <vector.h>

template<typename T>	//�� �� ������ �������
class TDynamicStack {
	
	int top;
public:
	TDynamicStack(size_t _memSize = 1) : top(-1) {};
	size_t size() const { return top + 1; }
	bool isEmpty() const { return top == -1; }
	void Push(const T& val) {mem.push_back(val); top++;}
	void Pop() { mem.pop_back(); top--; }
	T Top() { return mem[top]; }
	void clear() { mem.clear(); top = -1; }vector<T> mem;
};
