// объявление и реализация шаблонного стека
// стек поддерживает операции:
// - вставка элемента,
// - извлечение элемента,
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту,
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память
#include <iostream>
using namespace std;

template <typename T>
class DStack {
private:
    size_t size;
    size_t capacity;
    T* data;
public:
    DStack() {
        size = 0;
        capacity = 10;
        data = new T [capacity];
    }

    ~DStack() {
        size = 0;
        delete[]data;
        capacity = 0;
    }

    bool isFull(){
        return (size == capacity);
    }

    int isEmpty() {
        return (size == 0);
    }

    void resize(){
        capacity*=2;
        T* tmp = new T[capacity];
        memcpy(tmp, data, (this->size)*sizeof(T));
        delete[] data;
        data = tmp;
    }

    void push(T elem) {
        if (isFull()) {
            resize();
        }
        data[size++] = elem;
    }

    T pop() {
        if (!isEmpty()) {
            return(data[--size]);
        }
        else throw logic_error("Stack is empty");
    }

    T current(){
        if (!isEmpty()) {
            return data[size-1];
        }
        else throw logic_error("Stack is empty");
    }

    size_t Size(){
        return(size);
    }

    void del(){
        size = 0;
    }
};