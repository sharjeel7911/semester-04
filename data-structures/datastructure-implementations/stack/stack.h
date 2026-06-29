#include <iostream>
using namespace std;

// ===== STACK USING ARRAY =====

template <class T>
class MyStack {
private:
    T* st;
    int topPtr;
    int maxSize;
public:
    MyStack(int size) : maxSize(size), topPtr(0) { st = new T[size]; }
    ~MyStack() { delete[] st; }

    bool isFull() { return topPtr == maxSize; }
    bool isEmpty() { return topPtr == 0; }
    int size() { return topPtr; }

    T top() {
        if (isEmpty()) { cout << "Stack is empty\n"; return T(); }
        return st[topPtr - 1];
    }

    void push(T val) {
        if (isFull()) { cout << "Stack overflow\n"; return; }
        st[topPtr++] = val;
    }

    T pop() {
        if (isEmpty()) { cout << "Stack underflow\n"; return T(); }
        return st[--topPtr];
    }

    void display() {
        cout << "Current Size: " << topPtr << "\nMax Size: " << maxSize << endl;
        if (isEmpty()) { cout << "Stack is empty\n"; return; }
        for (int i = topPtr - 1; i >= 0; i--) cout << (topPtr - i) << ". " << st[i] << endl;
    }
};

// ---------------------------------------------------------------------------------------

// ===== STACK USING LINKED LIST =====

template <class T>
class Node {
public:
    T data;
    Node* next;

    Node() : data(T()), next(nullptr) {}
    Node(T val) : data(val), next(nullptr) {}
};

template <class T>
class MyStackLL {
private:
    Node<T>* topNode;
public:
    MyStackLL() : topNode(nullptr) {}
    ~MyStackLL() { while (!isEmpty()) pop(); }

    bool isEmpty() { return topNode == nullptr; }

    T top() {
        if (isEmpty()) { cout << "Queue is empty\n"; return T(); }
        return topNode->data;
    }

    void push(T val) {
        Node<T>* newNode = new Node<T>(val);
        newNode->next = topNode;
        topNode = newNode;
    }

    T pop() {
        if (isEmpty()) { cout << "Queue is empty\n"; return T(); }

        Node<T>* temp = topNode;
        T val = topNode->data;
        topNode = topNode->next;

        delete temp;
        return val;
    }

    void display() {
        if (isEmpty()) { cout << "Queue is empty\n"; return; }

        Node<T>* temp = topNode;
        int pos = 1;
        while (temp != nullptr) {
            cout << pos++ << ". " << temp->data << endl;
            temp = temp->next;
        }
    }
};