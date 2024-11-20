template <typename T>
class myVector {
private:
    T* data;
    size_t capacity;
    size_t sizevar;
    const size_t k;
public:
    myVector(size_t sizevar = 0, const T& v = T()) : k(2), capacity(1) {
        if (sizevar > 0) { 
            capacity = sizevar;
        }
        data = new T[capacity];
        fill(data, data + capacity, v);
        this->sizevar = sizevar;
    }
    myVector(const myVector& vec) : k(2) {
        data = new T[vec.capacity]();
        capacity = vec.capacity;
        sizevar = vec.sizevar;
        copy(vec.data, vec.data + sizevar, data);
    }
    myVector(myVector&& vec) : k(2) {
        data = nullptr;
        swap(data, vec.data);
        capacity = vec.capacity;
        sizevar = vec.sizevar;
    }
    ~myVector() {
        delete[] data;
    }
    myVector& operator=(const myVector& vec) {
        if (this == &vec) return *this;
        if (capacity < vec.sizevar) {
            T* t = new T[vec.capacity]();
            delete[] data;
            data = t;
        }
        capacity = vec.capacity;
        sizevar = vec.sizevar;
        copy(vec.data, vec.data + vec.sizevar, data);
        return *this;
    }
    myVector& operator=(myVector&& vec) {
        delete[] data;
        data = nullptr;
        capacity = vec.capacity;
        sizevar = vec.sizevar;
        swap(data, vec.data);
        return *this;
    }
    const size_t size() const {
        return sizevar;
    }
    const T& operator[](size_t i) const {
        return data[i];
    } 
    T& operator[](size_t i) {
        return data[i];
    }
    void push_back(const T& v) {
        if (sizevar >= capacity) {
            capacity *= k;
            T* t = new T[capacity]();
            copy(data, data + capacity, t);
            delete[] data;
            data = t;
        }
        data[sizevar++] = v;
    }
    void resize(size_t n) {
        if (n > capacity) {
            capacity = n;
            T* t = new T[capacity]();
            copy(data, data + capacity, t);
            delete[] data;
            data = t;
        }
        if (n < sizevar) fill(data + n, data + sizevar, T());
        sizevar = n;
    }
};