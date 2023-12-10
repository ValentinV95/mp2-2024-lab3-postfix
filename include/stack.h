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
class TStack {
private:
    T* data;
    size_t size;
    size_t capacity;
public:
    TStack() 
    {
        data = new T[10];
        capacity = 10;
        size = 0;
    }
    bool isEmpty() {
        return size == 0;
    }
    T top() {
        if (isEmpty())
        {
            throw std::out_of_range("stack is empty");
        }
        else
        {
            return data[--size];
        }
    }
    T pop() {
        if (isEmpty())
        {
            throw std::out_of_range("stack is empty");
        }
        else 
        {
            T mas = data[--size];
            data[size - 1] = {};
            size--;
            return mas;
        }
    }
    void push(T a) {
        if (size == capacity)
        {
            resize();
        }
        data[size++] = a;
    }
    void resize() 
    {
        T* mas = new T[size];
        std::memcpy(mas, data, this->size * sizeof(T));
        delete[] data;
        data = new T[size * 2];
        for (int i = 0; i < size; i++) 
        {
            data[i] = mas[i];
        }
        capacity = size * 2;
    }
    size_t get_size() 
    {
        return size;
    }
    void clear() 
    {
        for (int i = 0; i < size; i++) 
        {
            data[i] = {};
        }
    }
    ~TStack() 
    {
        delete[] data;
        size = 0;
        capacity = 0;
    }
};