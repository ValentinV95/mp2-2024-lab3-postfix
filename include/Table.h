#pragma once
#include "Node.h"

class Table {
private:
	Node* mem;
	int size, count;
	double search(std::string key) {
		for (int i = 0; i < count; i++) {
			if (mem[i].getName() == key) return i;
		}
		return -1;
	}
public:
	Table(int _size = 0) {
		size = _size;
		count = 0;
		mem = new Node[size];
		for (int i = 0; i < size; i++) {
			mem[i] = Node();
		}
	}
	Table(const Table& tmp) {
		size = tmp.size;
		count = tmp.count;
		mem = new Node[size];
		for (int i = 0; i < size; i++) {
			mem[i] = tmp.mem[i];
		}
	}
	Table& operator=(const Table& tmp) {
		if (size != tmp.size) {
			if (size != 0) {
				delete[]mem;
			}
			size = tmp.size;
		}
		count = tmp.count;
		mem = new Node[size];
		for (int i = 0; i < size; i++) {
			mem[i] = tmp.mem[i];
		}
		return *this;
	}
	~Table() {
		delete[] mem;
	}
	double searchInfo(std::string key) {
		int l = -1;
		int i = 0;
		while ((l == -1) && (i <= count)) {
			if (key == mem[i].getName()) {
				l = i;
			}
			i++;
		}
		if (l > -1) {
			return mem[l].getValue();
		}
		return l;
	}
	void add(Node tmp) {
		int l = search(tmp.getName());
		if (l == -1) {
			mem[count++] = tmp;
		}
		else {
			mem[l].setValue(tmp.getValue());
		}
	}
	bool empty() {
		if (count == 0) {
			return 1; //True
		}
		return 0; //False
	}
	bool full() {
		if (count == size) {
			return 1; //True
		}
		return 0; //False
	}
	Node operator[](int k) {
		Node res;
		if ((k <= count) && (k > -1)) {
			return  mem[k];
		}
		return res;
	}
	void del(std::string key) {
		int l = search(key);
		if (l > -1) {
			mem[l] = mem[--count];
		}
	}
	void setVar(int n, double k) {
		if (n >= size) return;
		mem[n].setValue(k);
	}
	void add(std::string key, double value){
		Node tmp(key, value);
		add(tmp);
	}
	int getCount() {
		return count;
	}
};