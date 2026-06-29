#include <iostream>
using namespace std;

template <class T>
class Stack {
private:
    T* st;
    int topPtr;
    int maxSize;

public:
    Stack() {
        maxSize = 5;
        topPtr = 0;
        st = new T[maxSize];
    }

    ~Stack() { delete[] st; }
    bool isFull() { return topPtr == maxSize; }
    bool isEmpty() { return topPtr == 0; }

    void push(T val) {
        if (isFull()) {
            cout << "Stack overflow\n";
            return;
        }
        st[topPtr++] = val;
    }

    T pop() {
        if (isEmpty()) {
            cout << "Stack underflow\n";
            return T();
        }
        return st[--topPtr];
    }

    void display() {
        if (isEmpty()) {
            cout << "Stack is empty\n";
            return;
        }

        for (int i = topPtr - 1; i >= 0; i--) {
            cout << (topPtr - i) << ". " << st[i] << endl;
        }
    }
};

template <class T>
class Queue {
private:
    T* qu;
    int currSize;
    int maxSize;

public:
    Queue() {
        maxSize = 5;
        currSize = 0;
        qu = new T[maxSize];
    }

    ~Queue() { delete[] qu; }
    bool isFull() { return currSize == maxSize; }
    bool isEmpty() { return currSize == 0; }

    void enqueue(T val) {
        if (isFull()) {
            cout << "Queue is full\n";
            return;
        }
        qu[currSize++] = val;
    }

    T dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return T();
        }

        T removed = qu[0];

        for (int i = 0; i < currSize - 1; i++) {
            qu[i] = qu[i + 1];
        }

        currSize--;
        return removed;
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }

        for (int i = 0; i < currSize; i++) {
            cout << i << ". " << qu[i] << endl;
        }
    }
};

class FoodDelivery {
public:
    Stack<int> st;
    Queue<int> qu;

    void placeOrder(int orderId) {
        if (qu.isFull()) { cout << "Queue Full\n"; return; }
        qu.enqueue(orderId);
        cout << "Order added to queue" << endl;
    }

    void deliverOrder() {
        if (qu.isEmpty()) { cout << "No orders to deliver\n"; return; }
        int order = qu.dequeue();
        st.push(order);
        cout << order << " delivered" << endl;
    }

    void undoLastDelivery() {
        if (st.isEmpty()) { cout << "No delivery to undo\n"; return; }
        int order = st.pop();
        qu.enqueue(order);
        cout << "Last delivery cancelled" << endl;
    }
};

int main() {
    FoodDelivery f;

    do {

        cout << "1. Add New Order \n2. Deliver Order \n3. Undo Last Delivery \n4. Display Pending Orders (Queue) \n5. Display Delivered Orders (Stack) \n6. Exit " << endl;

        int ch;
        cin >> ch;

        if (ch == 1) {
            cout << "Enter id" << endl;
            int id;
            cin >> id;
            f.placeOrder(id);
        }
        else if (ch == 2) { f.deliverOrder(); }
        else if (ch == 3) { f.undoLastDelivery(); }
        else if (ch == 4) { f.qu.display(); }
        else if (ch == 5) { f.st.display(); }
        else if (ch == 6) { cout << "Exiting...\n"; break; }
    }
    while (1);

    return 0;
}
