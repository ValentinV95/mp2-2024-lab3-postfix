// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

template <class T>
class TStack
{
public:
	TStack() : sz(0), cap(256) { data = new T[cap](); }
	TStack(const TStack& s) : sz(s.sz), cap(s.cap)
	{
		data = new T[cap];
		std::copy(s.data, s.data + cap, data);
	}

	TStack(TStack&& s) noexcept
	{
		sz = 0;
		cap = 0;
		data = nullptr;
		swap(*this, s);
	}

	~TStack()
	{
		sz = 0;
		cap = 0;
		delete[] data;
	}

	TStack& operator=(const TStack& s)
	{
		if (this == &s)
			return *this;
		TStack tmp(s);
		swap(*this, tmp);
		return *this;
	}

	TStack& operator=(TStack&& s) noexcept
	{
		TStack tmp(s);
		swap(*this, s);
		return *this;
	}

	friend void swap(TStack& lhs, TStack& rhs) noexcept
	{
		std::swap(lhs.sz, rhs.sz);
		std::swap(lhs.cap, rhs.cap);
		std::swap(lhs.data, rhs.data);
	}

	void push(const T& value)
	{
		if (sz == cap) resize();
		data[sz++] = value;
	}

	void push(T&& value)
	{
		if (sz == cap) resize();
		data[sz++] = std::move(value);
	}

	void pop()
	{
		if (!isEmpty()) { sz--; }
		else throw std::runtime_error("Trying to pop from empty stack");
	}

	void clear() { while (!isEmpty()) pop(); }

	T& top() 
	{ 
		if (sz == 0) throw std::runtime_error("Trying to get element from empty stack");
		return data[sz-1];
	}

	const T& top() const
	{
		if (sz == 0) throw std::runtime_error("Trying to get element from empty stack");
		return data[sz-1];
	}

	bool isEmpty() noexcept { return sz == 0; }
	size_t size() noexcept { return sz; }

private:
	T* data;
	size_t sz;
	size_t cap;

	void resize()
	{
		T* tmp = new T[cap * 2];
		std::copy(data, data + sz, tmp);
		cap *= 2;
		delete[] data;
		data = tmp;
	}
};