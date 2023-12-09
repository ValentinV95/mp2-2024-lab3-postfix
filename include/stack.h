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
class stack {
private:
    T* data;
    size_t size, capacity;
public:
    stack() {
        data = new T[10];
        capacity = 10;
        size = 0;
    }
    bool isEmpty() {
        return size == 0;
    }
    T top() {
        if (isEmpty()) throw std::out_of_range("stack is empty");
        else return data[size-1];
    }
    T pop() {
        if (isEmpty()) throw std::out_of_range("stack is empty");
        else {
            T tmp = data[size-1];
            data[size - 1] = {};
            size--;
            return tmp;
        }
    }
    void push(T& el) {
        if (size == capacity) resize();
        data[size++] = el;
    }
    
    void resize() {
        T* tmp = new T[size];
        std::memcpy(tmp, data, this->size * sizeof(T));
        delete[] data;
        data = new T[size*2];
        for (int i = 0; i < size; i++) {
            data[i] = tmp[i];
        }
        capacity = size*2;
    }
    size_t get_size() {
        return size;
    }
    void clear() {
        for (int i = 0; i < size; i++) {
            data[i] = {};
        }
    }
    ~stack() {
        delete[] data;
        size = 0;
        capacity = 0;
    }
};