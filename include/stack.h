// ���������� � ���������� ���������� �����
// ���� ������������ ��������: 
// - ������� ��������, 
// - ���������� ��������, 
// - �������� �������� �������� (��� ��������)
// - �������� �� �������, 
// - ��������� ���������� ��������� � �����
// - ������� �����
// ��� ������� � ������ ���� ������ �������������� ������

#include "myvector.h"

template <typename T>
class myStack : protected myVector<T> {
private:
    using myVector::size;
public:
    myStack(size_t size = 0) : myVector(size) {}
    myStack(const myStack& st) : myVector(st.myVector) {}
    myStack& operator=(const myStack& st) {
        data = st.data;
        size = st.size;
    }
    bool isEmpty() { return size == 0; }
    void push(const T& v) {
        data.push_back(v);
    }
    const T& pop() {
        return data[--size];
    }
};