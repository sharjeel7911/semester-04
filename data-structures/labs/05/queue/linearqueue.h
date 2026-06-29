#include <iostream>
using namespace std;

// ===== LINEAR QUEUE USING ARRAY =====

template <class T>
class MyLinearQueue {
private:
    T* qu;
    int currSize;
    int maxSize;
public:
    MyLinearQueue(int size) : currSize(0), maxSize(size) { qu = new T[size]; }
    ~MyLinearQueue() { delete[] qu; }

    bool isFull() { return currSize == maxSize; }
    bool isEmpty() { return currSize == 0; }

    T peek() {
        if (isEmpty()) { cout << "Queue is empty\n"; return T(); }
        return qu[0];
    }

    void enqueue(T val) {
        if (isFull()) { cout << "Queue is full\n"; return; }
        qu[currSize++] = val;
    }

    T dequeue() {
        if (isEmpty()) { cout << "Queue is empty\n"; return T(); }

        T removedVal = qu[0];
        for (int i = 0; i < currSize - 1; i++) qu[i] = qu[i + 1];

        currSize--;
        return removedVal;
    }

    void display() {
        cout << "Current Size: " << currSize << "\nMax Size: " << maxSize << endl;
        if (isEmpty()) { cout << "Queue is empty\n"; return; }
        for (int i = 0; i < currSize; i++) cout << i << ". " << qu[i] << endl;
    }
};

// ---------------------------------------------------------------------------------------

// ===== LINEAR QUEUE USING LINKED LIST =====

template <class T>
class Node {
public:
    T data;
    Node* next;

    Node() : data(T()), next(nullptr) {}
    Node(T val) : data(val), next(nullptr) {}
};

template <class T>
class MyLinearQueueLL {
private:
    Node<T>* front;
    Node<T>* rear;
public:
    MyLinearQueueLL() { front = rear = nullptr; }
    ~MyLinearQueueLL() { while (!isEmpty()) dequeue(); }

    bool isEmpty() { return front == nullptr; }

    T peek() {
        if (isEmpty()) { cout << "Queue is empty\n"; return T(); }
        return front->data;
    }

    void enqueue(T val) {
        Node<T>* newNode = new Node<T>(val);

        if (rear == nullptr) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    T dequeue() {
        if (isEmpty()) { cout << "Queue is empty\n"; return T(); }

        Node<T>* temp = front;

        T val = front->data;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp;
        return val;
    }

    void display() {
        if (isEmpty()) { cout << "Queue is empty\n"; return; }

        Node<T>* temp = front;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};