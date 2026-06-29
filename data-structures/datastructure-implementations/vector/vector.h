#include <iostream>
using namespace std;

template <class T>
class MyVector {
private:
    T* vec;
    int sz;
    int cap;

    void resize() {
        cap *= 2;
        T* newVec = new T[cap];
        for (int i = 0; i < sz; i++) newVec[i] = vec[i];
        delete[] vec;
        vec = newVec;
    }

public:
    MyVector(int capacity = 1) : cap(capacity), sz(0) { vec = new T[capacity]; }
    ~MyVector() { delete[] vec; }

    bool empty() { return sz == 0; }
    bool full() { return sz == cap; }
    void clear() { sz = 0; }
    int size() { return sz; }
    int capacity() { return cap; }

    T& operator[](int index) { return vec[index]; }

    T pop_back() {
        if (empty()) { cout << "Vector is empty\n"; return T(); }
        return vec[--sz];
    }

    void push_back(T val) {
        if (full()) resize();
        vec[sz++] = val;
    }

    void display() {
        cout << "Size: " << size() << "\nCapacity: " << capacity() << endl;
        if (empty()) { cout << "Vector is empty\n"; return; }
        for (int i = 0; i < sz; i++) cout << i << ". " << vec[i] << endl;
    }
};