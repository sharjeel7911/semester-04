#include <iostream>
using namespace std;

//-------------------------------------------------------

// ===== ORDER =====

struct Order {
    int orderId;
    string name;
    string item;
    int priority;

    Order() : orderId(0), name(""), item(""), priority(0) {}
    Order(int i) : orderId(i), name(""), item(""), priority(0) {}
    Order(int i, string n, string it, int p) : orderId(i), name(n), item(it), priority(p) {}
};

ostream& operator<<(ostream& out, const Order b) {
    out << "Order id: " << b.orderId << ", Customer name: " << b.name << ", Item: " << b.item << ", Priority: " << b.priority;
    return out;
}

//-------------------------------------------------------

// ===== PRIORITY QUEUE =====

template <class T>
class MyPriorityQueue {
public:

    T* qu;
    int currSize;
    int maxSize;

    MyPriorityQueue(int size) : currSize(0), maxSize(size) { qu = new T[size]; }
    ~MyPriorityQueue() { delete[] qu; }


    bool isFull() { return currSize == maxSize; }
    bool isEmpty() { return currSize == 0; }

    T peek() {
        if (isEmpty()) { cout << "Queue is empty\n"; return T(); }

        int minPriority = qu[0].priority;
        int minIndex = 0;

        for (int i = 1; i < currSize; i++) {
            if (qu[i].priority < minPriority) {
                minPriority = qu[i].priority;
                minIndex = i;
            }
        }
        return qu[minIndex];
    }

    void enqueue(T val) {
        if (isFull()) { cout << "Queue is full\n"; return; }
        qu[currSize++] = val;
    }

    T dequeue() {
        if (isEmpty()) { cout << "Queue is empty\n"; return T(); }

        int minPriority = qu[0].priority;
        int minIndex = 0;

        for (int i = 1; i < currSize; i++) {
            if (qu[i].priority < minPriority) {
                minPriority = qu[i].priority;
                minIndex = i;
            }
        }

        T removedVal = qu[minIndex];
        for (int i = minIndex; i < currSize - 1; i++) {
            qu[i] = qu[i + 1];
        }

        currSize--;
        return removedVal;
    }
    void display() {
        cout << "Current Size: " << currSize << "\nMax Size: " << maxSize << endl;
        for (int i = 0; i < currSize; i++) cout << i << ". " << qu[i] << endl;
    }
};

//-------------------------------------------------------

// ===== LINKED LIST =====

template <class T>
struct Node {
    T data;
    Node<T>* next;
    Node() : data(T()), next(nullptr) {}
    Node(T val) : data(val), next(nullptr) {}
};

template <class T>
class MySinglyLinkedList {
public:
    Node<T>* head;
    Node<T>* tail;

    MySinglyLinkedList() : head(nullptr), tail(nullptr) {}

    bool isEmpty() { return head == nullptr; }

    bool search(int val) {
        if (isEmpty()) { cout << "Linked list is empty." << endl; return false; }
        else {
            Node<T>* tempPtr = head;
            while (tempPtr != nullptr) {
                Order o = tempPtr->data;

                if (o.orderId == val) return true;
                tempPtr = tempPtr->next;
            }
        }
        return false;
    }

    void display() {
        if (isEmpty()) { cout << "Linked list is empty." << endl; return; }

        Node<T>* tempPtr = head;
        int k = 0;
        while (tempPtr != nullptr) {
            cout << k++ << ". " << tempPtr->data << endl;
            tempPtr = tempPtr->next;
        }
    }

    void insertAtTail(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (isEmpty()) head = tail = newNode;


        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void deleteValue(int val) {
        Order o = head->data;

        if (o.orderId == val) {
            Node<T>* temp = head;
            head = head->next;
            if (head == nullptr) tail = nullptr;
            delete temp;
            return;
        }

        Node<T>* tempPtr = head;
        while (tempPtr->next != nullptr) {
            Order oe = tempPtr->next->data;
            if (oe.orderId == val) {
                Node<T>* nodeToDelete = tempPtr->next;
                tempPtr->next = nodeToDelete->next;
                if (nodeToDelete == tail) tail = tempPtr;
                delete nodeToDelete;
                return;
            }
            tempPtr = tempPtr->next;
        }
        cout << "Value " << val << " not found in list." << endl;
    }
};

//-------------------------------------------------------

// ===== FOOD CLASS =====

class Food {
public:
    MySinglyLinkedList<Order> ll;
    MyPriorityQueue<Order> qu;

    Food(int sz) : qu(sz) {}

    void addOrderAtEnd(Order o) {
        ll.insertAtTail(o);
    }

    void deleteOrder(int id) {
        ll.deleteValue(id);
    }

    bool searchOrder(int id) {
        return ll.search(id);
    }


    void displayOrders() {
        ll.display();
    }

//-------------------------------------------------------

    void enqueOrder(Order o) {
        qu.enqueue(o);
    }

    Order dequeOrder() {
        return qu.dequeue();
    }

    void displayQueue() {
        qu.display();
    }

    Order peeking() {
        return qu.peek();
    }
};

//-------------------------------------------------------

// ===== MAIN =====

int main() {

    Food f(100);

    Order o1(1, "Ali", "Pizza", 2);
    Order o2(2, "Sara", "Burger", 1);
    Order o3(3, "Ahmed", "Pasta", 2);
    Order o4(4, "John", "Biryani", 1);

    f.addOrderAtEnd(o1);
    f.addOrderAtEnd(o2);
    f.addOrderAtEnd(o3);
    f.addOrderAtEnd(o4);

    cout << "Linked List Orders:\n";
    f.displayOrders();

    cout << "\nSearch Order 3: " << f.searchOrder(3) << endl;

    f.deleteOrder(3);

    cout << "\nAfter Deletion:\n";
    f.displayOrders();

//-------------------------------------------------------

    cout << "\nQUEUE OPERATIONS\n";

    f.enqueOrder(o1);
    f.enqueOrder(o2);
    f.enqueOrder(o3);
    f.enqueOrder(o4);

    cout << "\nInitial Queue:\n";
    f.displayQueue();

    cout << "\nPeek (Highest Priority Order):\n";
    cout << f.peeking() << endl;

    cout << "\nDequeue Operations (Priority Based):\n";

    cout << "Removed: " << f.dequeOrder() << endl;
    f.displayQueue();

    cout << "\nRemoved: " << f.dequeOrder() << endl;
    f.displayQueue();

    cout << "\nRemoved: " << f.dequeOrder() << endl;
    f.displayQueue();

    cout << "\nRemoved: " << f.dequeOrder() << endl;
    f.displayQueue();

    // Final state
    cout << "\nFinal Queue State:\n";
    f.displayQueue();
    return 0;
}
