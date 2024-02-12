#pragma once
using namespace std;

template<class T>
class TStack
{
    T* pMem; // массив
    int Msize; // размер стека
    int Capacity; // вместимость стека
    void resize()
    {
        T* tmp = new T[Msize * 2];
        for (int i = 0; i < Msize; i++) {
            tmp[i] = pMem[i];
        }
        delete[] pMem;
        pMem = tmp;
        Capacity = Msize * 2;
    }
    int CurrInd; // индекс вершины
public:
    TStack(int _Msize = 15) // конструктор
    {
        if (_Msize < 1) throw ("Wrong size!\n");
        Msize = _Msize;
        pMem = new T[Msize];
        CurrInd = -1;
    }
    TStack(const TStack& s) // конструктор копирования
    {
        Msize = s.Msize;
        pMem = new T[Msize];
        CurrInd = s.CurrInd;
        for (int i = 0; i <= CurrInd; i++)
            pMem[i] = s.pMem[i];
    }
    ~TStack() { delete[] pMem; }
    bool IsEmpty() const // проверка на пустоту
    {
        if (CurrInd < 0)
            return true;
        else
            return false;
    }
    bool IsFull() const // проверка на полный стек
    {
        if (CurrInd == Msize - 1)
            return true;
        else
            return false;
    }
    T Top() // - просмотр верхнего элемента (без удаления)
    {
        if (CurrInd == -1)
            throw "Empty";
        return pMem[CurrInd];

    }
    T Pop() //удаление элемента с вершины стека
    {
        if (CurrInd == -1)
            throw "Empty";
        CurrInd--;
        return pMem[CurrInd + 1];
    }
    int size() //  получение количества элементов в стеке
    {
        if (CurrInd == -1)
            throw "Empty";
        return CurrInd + 1;
    }
    void Push(const T& val) //  вставка элемента
    {
        if (CurrInd == Msize - 1) {
            resize();
        }
    }
    void Clear() // - очистка стека
    {
        CurrInd = -1;
        delete[] pMem;
    }

    friend istream& operator>>(istream& istr, TStack& s)
    {
        for (int i = 0; i < s.Msize; i++)
            istr >> s.pMem[i];
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TStack& s)
    {
        if (s.CurrInd == -1) {
            ostr << "Stack Is Empty" << endl;
        }
        else {
            for (int i = 0; i < s.CurrInd; i++)
                ostr << s.pMem[i] << ' ';
            ostr << endl;
        }
        return ostr;
    }
};
