#pragma once
#include <initializer_list>
#include <iostream>

template<typename T>
class Iterator_ : public std::iterator<std::input_iterator_tag, T>
{
private:
	T* ptr;
public:
	Iterator_(T* ptr) : ptr(ptr) {};
	Iterator_(const Iterator_& iter) : ptr(iter.ptr) {};

	bool operator!=(const Iterator_& it2) const { return ptr != it2.ptr; };
	bool operator==(const Iterator_& it2) const { return ptr == it2.ptr; };
	typename Iterator_::reference operator*() const { return *ptr; };
	Iterator_& operator++() { ptr++; return *this; };

};

template<typename T>
class vector {
private:
	T* pMem;
	size_t sz, cp;
public:
	//<---------------iterators-------------->	//I use only for construction like "for(auto& el : ^vector^)"
	Iterator_<T> begin() { return Iterator_<T>(pMem); }
	Iterator_<T> end() { return Iterator_<T>(pMem+sz); }
	Iterator_<const T> begin()const { return Iterator_(pMem); }
	Iterator_<const T> end()const { return Iterator_(pMem + sz); }
	//<-------------end iterators------------>

	//<-------------constructors------------>
	vector(std::initializer_list<T> list_) {
		sz = list_.size();
		cp = sz;
		pMem = new T[cp];
		size_t p = 0;
		for (auto& el : list_) {
			pMem[p++] = el;
		}
	}
	vector() {
		cp = 4;
		sz = 0;
		pMem = new T[cp]();
	}
	vector(size_t _sz) {
		if (_sz < 0) throw std::out_of_range("cant set size lower 0");
		cp = _sz;
		sz = cp;
		pMem = new T[cp]();
	}
	vector(size_t _sz, const T& val_) {
		sz = _sz;
		cp = sz;
		pMem = new T[cp];
		std::fill(pMem, pMem + cp, val_);
	}
	vector(const vector<T>& v) {
		sz = v.sz;
		cp = v.cp;
		pMem = new T[cp];
		std::copy(v.pMem, v.pMem + cp, pMem);
	}
	vector(vector<T>&& v) : pMem(nullptr), sz(0),pc(0) {
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
	//<------end constructors block--------->
	
	//<------assign.. operators------------->
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
	//<-------assign.. operators end-------->

	//<---------info methods---------------->
	size_t size() { return sz; }
	size_t capacity() { return cp; }
	//<-------info methods end-------------->


	//<data or size changing/access methods->
		//access-->>
	const T& operator[](size_t ind) const {
		return pMem[ind];
	}
	T& operator[](size_t ind) {
		return pMem[ind];
	}
	const T& at(size_t ind) const {
		if (ind >= sz || ind < 0) throw std::out_of_range("index out of range\n");
		return pMem[ind];
	}
	T& at(size_t ind) {
		if (ind >= sz || ind < 0) throw std::out_of_range("index out of range\n");
		return pMem[ind];
	}
		//end access--<<
		
		//touch data/size-->>
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
		if (sz == 0)throw std::out_of_range("out of range - cant pop element from empty vector");
		sz--;
	}
	void resize(size_t sz_) {
		if (sz_ < 0) throw std::out_of_range("Cannot set size lower than 0");

		if (sz_ <= cp) {
			if (sz_ < sz) {
				for (size_t i = sz; i > sz_; i--) {
					pMem[i - 1].~T();
				}
			}
			sz = sz_;
		}
		else {
			size_t new_cp = sz_;
			T* tmpMem = new T[new_cp];
			try {
				std::move(pMem, pMem + sz, tmpMem);
				for (size_t i = sz; i < sz_; i++) new (tmpMem + i) T();
				delete[] pMem;
				pMem = tmpMem;
				cp = new_cp;
				sz = sz_;
			}
			catch (...) {
				delete[] tmpMem;
				throw;
			}
		}
	}
	void clear() { resize(0); }
		//touch data/size end<
	//<data or size changing/access methods end->
};