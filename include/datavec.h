// ��������������� �����, ������� �� ���� ������ ������ � ������� �����
#pragma once
#include <stdexcept>
#include <algorithm>
using namespace std;

template <typename T>
class Vec
{
private:
	T* pMem;
	size_t cap, sz;
	static size_t const Vec_Max_Capacity{ (1ull << 32) / sizeof(T) - 1 };
	//static const default_capacity
public:
	Vec(size_t const& capacity = 64) : cap(capacity), sz(0)
	{
		if (cap == 0)
			throw length_error("Vector capacity should be greater than zero");
		if (cap > Vec_Max_Capacity)
			throw overflow_error("Too many elements");
		pMem = new T[cap]();
	};

	Vec(Vec<T> const& v) : cap(v.cap), sz(v.sz)
	{
		pMem = new T[cap]();
		copy(v.pMem, v.pMem + sz, pMem);
	};

	/*Vec(Vec<T>&& v) : cap(64), sz(0), pMem(nullptr) noexcept
	{
		swap(*this, v);
	};
		friend void swap(Vec<T>& lhs, Vec<T>& rhs) noexcept
	{
		swap(lhs.sz, rhs.sz);
		swap(lhs.cap, rhs.cap);
		swap(lhs.pMem, rhs.pMem);
		return;
	};*/

	~Vec()
	{
		delete[] pMem;
		pMem = nullptr;
	};


	T* GetData() noexcept
	{
		return pMem;
	};

	size_t GetSize() noexcept
	{
		return sz;
	};

	void SetSize(size_t _sz)	//������ ��� ������
	{
		if (_sz > cap)
			throw("Can not set size because it's biggen than current capacity");
		sz = _sz;
	};

	size_t GetCapacity() noexcept
	{
		return cap;
	};

	/*Vec<T>& operator = (Vec<T> const& v)
	{
		if (this != &v)
		{
			if (cap != v.cap)
			{
				T* tmp = new T[v.cap];
				sz = v.sz;
				cap = v.cap;
				delete[] pMem;
				pMem = tmp;
			}
			copy(v.pMem, v.pMem + sz, pMem);
		}
		return *this;
	};

	Vec<T>& operator = (Vec<T>&& v) noexcept
	{
		swap(*this, v);
		return *this;
	};*/

	bool operator==(const Vec<T>& v) const	// ������ ��� ������
	{
		return (cap == v.cap && sz == v.sz && equal(pMem, pMem + sz, v.pMem));
	};

	bool operator!=(const Vec<T>& v) const	// ������ ��� ������
	{
		return !(*this == v);
	};

	T& operator [](size_t ind) noexcept		// ������ ��� ������
	{
		return pMem[ind];
	}

	bool Is_Full() noexcept
	{
		return (sz == cap);
	};

	bool Is_Empty() noexcept
	{
		return (sz == 0);
	};

	void push_back(T const& val)
	{
		if (this->Is_Full())
		{
			if (cap == Vec_Max_Capacity)
				throw overflow_error("Eventually ran out of memory");
			size_t neu_cap = cap * 3 / 2;
			if (neu_cap > Vec_Max_Capacity)
				neu_cap = Vec_Max_Capacity;
			T* tmp = new T[neu_cap]();
			copy(pMem, pMem + sz, tmp);
			swap(tmp, pMem);
			delete[] tmp;
			cap = neu_cap;
		}
		pMem[sz++] = val;
		return;
	};

	T Top()
	{
		if (Is_Empty())
			throw underflow_error("Trying to take element from empty vector");
		return pMem[sz - 1];
	};

	void pop_back() noexcept
	{
		sz--;
		return;
	};

	void clear()
	{
		T* tmp = new T[64]();
		swap(pMem, tmp);
		delete[] tmp;
		sz = 0;
		cap = 64;
		return;
	};
};