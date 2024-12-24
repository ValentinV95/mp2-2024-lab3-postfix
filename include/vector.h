#pragma once
#include <initializer_list>
#include <iostream>

template<typename T>
class vector {
private:
	
public:
	T* pMem;
	size_t sz, cp;

	vector(std::initializer_list<T> list) {
		sz = list.size();
		cp = sz + 1;
		pMem = new T[cp];
		size_t p = 0;
		for (auto& el : list) {
			pMem[p++] = el;
		}
	}
	vector() {
		cp = 1;
		sz = 0;
		pMem = new T[cp]();
	}
	vector(size_t _sz) {
		sz = _sz;
		cp = sz + 1;
		pMem = new T[cp]();
	}
	vector(size_t _sz, const T& val_) {
		sz = _sz;
		cp = sz + 1;
		pMem = new T[cp];
		std::fill(pMem, pMem + cp, val_);
	}
	vector(const vector<T>& v) {
		sz = v.sz;
		cp = v.cp;
		pMem = new T[cp];
		std::copy(v.pMem, v.pMem + cp, pMem);
	}
	vector(vector<T>&& v) : pMem(nullptr), sz(0), cp(1) {
		pMem = v.pMem;
		cp = v.cp;
		sz = v.sz;
		v.pMem = nullptr;
		v.cp = v.sz = 0;
	}
	~vector() {
		delete[] pMem;
		cp = sz = 0;
		pMem = nullptr;
	}

	vector& operator=(const vector& v) {
		if (&v == this) { return *this; }
		if (sz != v.sz) {
			sz = v.sz;
			cp = v.cp;
			T* p = new T[cp];
			delete[] pMem;
			pMem = p;
		}
		std::copy(v.pMem, v.pMem + sz, pMem);
		return *this;
	}

	vector& operator=(vector&& v) {
		if (this != &v)
		{
			delete[] pMem;
			pMem = nullptr;
			cp = sz = 0;
		}
		pMem = v.pMem;
		cp = v.cp;
		sz = v.sz;
		v.pMem = nullptr;
		v.cp = v.sz = 0;
		return *this;
	}

	size_t size() { return sz; }
	size_t size() const { return sz; }
	size_t capacity() { return cp; }
	size_t capacity() const { return cp; }

	const T& operator[](size_t ind) const {
		return pMem[ind];
	}
	T& operator[](size_t ind) {
		return pMem[ind];
	}

	void push_back(const T& val) {
		if (sz >= cp) {
			T* tmpMem = new T[cp * 2]();
			std::copy(pMem, pMem + cp, tmpMem);
			delete[] pMem;
			pMem = tmpMem;
			cp *= 2;
		}
		pMem[sz++] = val;
	}

	void pop_back() {
		if (sz == 0)throw std::out_of_range("Cant pop element from empty vector");
		sz--;
	}
};