#include <iostream>
using namespace std;

template <class T>
struct Node {
    T data;
    Node<T>* next;

    // constructor
    Node() : data(T()), next(nullptr) {}
    Node(T val) : data(val), next(nullptr) {}
};

//------------------------------------------------------------------------------------------------------------------


// =====================================================

// ===== CIRCULAR LINKED LIST USING HEAD & TAIL =====

// =====================================================

template <class T>
class SinglyCircularLinkedList {
public:
    Node<T>* head;
    Node<T>* tail;

    // constructor
    SinglyCircularLinkedList() : head(nullptr), tail(nullptr) {}

    // destructor
    ~SinglyCircularLinkedList() { while (!isEmpty()) deleteFromHead(); }

    // checks if circular linked list is empty
    bool isEmpty() { return head == nullptr && tail == nullptr; }

    // search for a value if present in circular linked list
    bool search(T val) {
        if (isEmpty()) { cout << "Circular linked list is empty." << endl; return false; }

        Node<T>* tempPtr = head;
        do {
            if (tempPtr->data == val) return true;
            tempPtr = tempPtr->next;
        }
        while (tempPtr != head);
        return false;
    }

    // display circular linked list
    void display() {
        if (isEmpty()) { cout << "Circular linked list is empty." << endl; return; }

        Node<T>* tempPtr = head;
        int k = 0;
        do {
            cout << k++ << ". " << tempPtr->data << endl;
            tempPtr = tempPtr->next;
        }
        while (tempPtr != head);
    }

    // get size of circular linked list
    int getSize() {
        if (isEmpty()) return 0;

        Node<T>* tempPtr = head;
        int count = 0;
        do {
            count++;
            tempPtr = tempPtr->next;
        }
        while (tempPtr != head);

        return count;
    }

    // insert values at head
    void insertAtHead(T val) {
        Node<T>* newNode = new Node<T>(val);

        // empty list
        if (isEmpty()) {
            head = tail = newNode;
            newNode->next = head;  // point to itself in circular manner
        }
        // non-empty list
        else {
            newNode->next = head;
            head = newNode;
            tail->next = head;  // maintain circularity
        }
    }

    // insert values at tail
    void insertAtTail(T val) {
        Node<T>* newNode = new Node<T>(val);

        // empty list
        if (isEmpty()) {
            head = tail = newNode;
            newNode->next = head;
        }
        // non-empty list
        else {
            tail->next = newNode;
            newNode->next = head;  // maintain circularity
            tail = newNode;
        }
    }

    // insert at specific position
    void insertAtPosition(T val, int index) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return; }

        int size = getSize();
        if (isEmpty() && index != 0) { cout << "List is empty. Can only insert at position 0." << endl; return; }
        if (index > size) { cout << "Index out of bounds." << endl; return; }

        Node<T>* newNode = new Node<T>(val);

        // insert at head
        if (index == 0) {
            if (isEmpty()) {
                head = tail = newNode;
                newNode->next = head;
            }
            else {
                newNode->next = head;
                head = newNode;
                tail->next = head;
            }
            cout << "Value inserted at position " << index << endl;
            return;
        }

        // insert at tail
        if (index == size) {
            tail->next = newNode;
            newNode->next = head;
            tail = newNode;
            cout << "Value inserted at position " << index << endl;
            return;
        }

        // insert in middle
        Node<T>* tempPtr = head;
        for (int i = 0; i < index - 1; i++) {
            tempPtr = tempPtr->next;
        }

        newNode->next = tempPtr->next;
        tempPtr->next = newNode;
        cout << "Value inserted at position " << index << endl;
    }

    // insert in sorted order
    void insertSorted(T val) {
        Node<T>* newNode = new Node<T>(val);

        // case I: empty list
        if (isEmpty()) {
            head = tail = newNode;
            newNode->next = head;
            cout << "Value " << val << " inserted at position 0." << endl;
            return;
        }

        // case II: insert at head (val is smaller than head)
        if (val < head->data) {
            newNode->next = head;
            head = newNode;
            tail->next = head;  // maintain circularity
            cout << "Value " << val << " inserted at head." << endl;
            return;
        }

        // case III: traverse to find correct position
        Node<T>* tempPtr = head;
        while (tempPtr->next != head && tempPtr->next->data < val) {
            tempPtr = tempPtr->next;
        }

        // insert between tempPtr and tempPtr->next
        newNode->next = tempPtr->next;
        tempPtr->next = newNode;

        // update tail if inserted at end
        if (newNode->next == head) {
            tail = newNode;
        }
        cout << "Value " << val << " inserted in sorted order." << endl;
    }

    // update a value present in the node
    void updateNode(int index, T newVal) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return; }
        if (isEmpty()) { cout << "Circular linked list is empty." << endl; return; }

        int size = getSize();
        if (index >= size) { cout << "Index out of bounds." << endl; return; }

        // traverse to the node at index
        Node<T>* tempPtr = head;
        for (int i = 0; i < index; i++) {
            tempPtr = tempPtr->next;
        }

        // update the value
        T oldVal = tempPtr->data;
        tempPtr->data = newVal;
        cout << "Node at index " << index << " updated from " << oldVal << " to " << newVal << endl;
    }

    // delete values from head
    T deleteFromHead() {
        if (isEmpty()) { cout << "Circular linked list is empty" << endl; return T(); }

        T returningVal = head->data;

        // if list has only one node
        if (head == tail) {
            delete head;
            head = tail = nullptr;
            return returningVal;
        }

        // more than one node
        Node<T>* tempPtr = head;
        head = head->next;
        tail->next = head;  // maintain circularity
        delete tempPtr;

        return returningVal;
    }

    // delete values from tail
    T deleteFromTail() {
        if (isEmpty()) { cout << "Circular linked list is empty" << endl; return T(); }

        T returningVal = tail->data;

        // if list has only one node
        if (head == tail) {
            delete tail;
            head = tail = nullptr;
            return returningVal;
        }

        // more than one node
        Node<T>* tempPtr = head;
        while (tempPtr->next != tail) {
            tempPtr = tempPtr->next;
        }

        delete tail;
        tail = tempPtr;
        tail->next = head;  // maintain circularity

        return returningVal;
    }

    // delete from a specific position
    T deleteFromPosition(int index) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return T(); }
        if (isEmpty()) { cout << "List is empty." << endl; return T(); }

        int size = getSize();
        if (index >= size) { cout << "Index out of bounds." << endl; return T(); }

        // delete from head
        if (index == 0) {
            return deleteFromHead();
        }

        // delete from elsewhere
        Node<T>* tempPtr = head;
        for (int i = 0; i < index - 1; i++) {
            tempPtr = tempPtr->next;
        }

        Node<T>* nodeToDelete = tempPtr->next;
        T returningVal = nodeToDelete->data;

        tempPtr->next = nodeToDelete->next;

        // update tail if we deleted the last node
        if (nodeToDelete == tail) {
            tail = tempPtr;
        }

        delete nodeToDelete;
        return returningVal;
    }

    // delete the first value of given parameter present in circular linked list
    void deleteValue(T val) {
        if (isEmpty()) { cout << "Circular linked list is empty." << endl; return; }

        // case I: delete from head
        if (head->data == val) {
            T deletedVal = head->data;
            deleteFromHead();
            cout << "Value " << deletedVal << " deleted from list." << endl;
            return;
        }

        // case II: delete from middle or tail
        Node<T>* tempPtr = head;
        do {
            if (tempPtr->next->data == val) {
                Node<T>* nodeToDelete = tempPtr->next;
                T deletedVal = nodeToDelete->data;

                tempPtr->next = nodeToDelete->next;

                // if we deleted the tail, update tail pointer
                if (nodeToDelete == tail) {
                    tail = tempPtr;
                }

                delete nodeToDelete;
                cout << "Value " << deletedVal << " deleted from list." << endl;
                return;
            }
            tempPtr = tempPtr->next;
        }
        while (tempPtr != head);

        // value not found
        cout << "Value " << val << " not found in list." << endl;
    }
};

//------------------------------------------------------------------------------------------------------------------

// =================================================

// ===== CIRCULAR LINKED LIST USING TAIL ONLY =====

// =================================================

template <class T>
class SinglyCircularLinkedListTailOnly {
public:
    Node<T>* tail;

    // constructor
    SinglyCircularLinkedListTailOnly() : tail(nullptr) {}

    // destructor
    ~SinglyCircularLinkedListTailOnly() { while (!isEmpty()) deleteFromHead(); }

    // checks if circular linked list is empty
    bool isEmpty() { return tail == nullptr; }

    // get head (tail->next points to head in circular list)
    Node<T>* getHead() {
        if (isEmpty()) return nullptr;
        return tail->next;
    }

    // search for a value if present in circular linked list
    bool search(T val) {
        if (isEmpty()) { cout << "Circular linked list is empty." << endl; return false; }

        Node<T>* head = getHead();
        Node<T>* tempPtr = head;
        do {
            if (tempPtr->data == val) return true;
            tempPtr = tempPtr->next;
        }
        while (tempPtr != head);

        return false;
    }

    // display circular linked list
    void display() {
        if (isEmpty()) { cout << "Circular linked list is empty." << endl; return; }

        Node<T>* head = getHead();
        Node<T>* tempPtr = head;
        int k = 0;
        do {
            cout << k++ << ". " << tempPtr->data << endl;
            tempPtr = tempPtr->next;
        }
        while (tempPtr != head);
    }

    // get size of circular linked list
    int getSize() {
        if (isEmpty()) return 0;

        Node<T>* head = getHead();
        Node<T>* tempPtr = head;
        int count = 0;
        do {
            count++;
            tempPtr = tempPtr->next;
        }
        while (tempPtr != head);

        return count;
    }

    // insert values at head
    void insertAtHead(T val) {
        Node<T>* newNode = new Node<T>(val);

        // empty list
        if (isEmpty()) {
            tail = newNode;
            newNode->next = tail;  // point to itself
        }
        // non-empty list
        else {
            newNode->next = tail->next;  // new node points to current head
            tail->next = newNode;  // tail's next becomes new node (new head)
        }
    }

    // insert values at tail (most efficient operation with tail-only)
    void insertAtTail(T val) {
        Node<T>* newNode = new Node<T>(val);

        // empty list
        if (isEmpty()) {
            tail = newNode;
            newNode->next = tail;  // point to itself
        }
        // non-empty list
        else {
            newNode->next = tail->next;  // new node points to head
            tail->next = newNode;  // old tail points to new node
            tail = newNode;  // update tail
        }
    }

    // insert at specific position
    void insertAtPosition(T val, int index) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return; }

        int size = getSize();
        if (isEmpty() && index != 0) { cout << "List is empty. Can only insert at position 0." << endl; return; }
        if (index > size) { cout << "Index out of bounds." << endl; return; }

        Node<T>* newNode = new Node<T>(val);

        // insert at head
        if (index == 0) {
            if (isEmpty()) {
                tail = newNode;
                newNode->next = tail;
            }
            else {
                newNode->next = tail->next;
                tail->next = newNode;
            }
            cout << "Value inserted at position " << index << endl;
            return;
        }

        // insert at tail
        if (index == size) {
            newNode->next = tail->next;
            tail->next = newNode;
            tail = newNode;
            cout << "Value inserted at position " << index << endl;
            return;
        }

        // insert in middle
        Node<T>* head = getHead();
        Node<T>* tempPtr = head;
        for (int i = 0; i < index - 1; i++) {
            tempPtr = tempPtr->next;
        }

        newNode->next = tempPtr->next;
        tempPtr->next = newNode;
        cout << "Value inserted at position " << index << endl;
    }

    // insert in sorted order
    void insertSorted(T val) {
        Node<T>* newNode = new Node<T>(val);

        // case I: empty list
        if (isEmpty()) {
            tail = newNode;
            newNode->next = tail;
            cout << "Value " << val << " inserted at position 0." << endl;
            return;
        }

        Node<T>* head = getHead();

        // case II: insert at head (val is smaller than head)
        if (val < head->data) {
            newNode->next = head;
            tail->next = newNode;  // new node becomes head
            cout << "Value " << val << " inserted at head." << endl;
            return;
        }

        // case III: traverse to find correct position
        Node<T>* tempPtr = head;
        while (tempPtr->next != head && tempPtr->next->data < val) {
            tempPtr = tempPtr->next;
        }

        // insert between tempPtr and tempPtr->next
        newNode->next = tempPtr->next;
        tempPtr->next = newNode;

        // update tail if inserted at end
        if (newNode->next == head) {
            tail = newNode;
        }
        cout << "Value " << val << " inserted in sorted order." << endl;
    }

    // update a value present in the node
    void updateNode(int index, T newVal) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return; }
        if (isEmpty()) { cout << "Circular linked list is empty." << endl; return; }

        int size = getSize();
        if (index >= size) { cout << "Index out of bounds." << endl; return; }

        Node<T>* head = getHead();
        Node<T>* tempPtr = head;
        for (int i = 0; i < index; i++) {
            tempPtr = tempPtr->next;
        }

        T oldVal = tempPtr->data;
        tempPtr->data = newVal;
        cout << "Node at index " << index << " updated from " << oldVal << " to " << newVal << endl;
    }

    // delete values from head
    T deleteFromHead() {
        if (isEmpty()) { cout << "Circular linked list is empty" << endl; return T(); }

        Node<T>* head = getHead();
        T returningVal = head->data;

        // if list has only one node
        if (head == tail) {
            delete head;
            tail = nullptr;
            return returningVal;
        }

        // more than one node
        tail->next = head->next;  // tail now points to new head
        delete head;

        return returningVal;
    }

    // delete values from tail
    T deleteFromTail() {
        if (isEmpty()) { cout << "Circular linked list is empty" << endl; return T(); }

        T returningVal = tail->data;

        // if list has only one node
        if (tail->next == tail) {
            delete tail;
            tail = nullptr;
            return returningVal;
        }

        // more than one node: traverse to find node before tail
        Node<T>* head = getHead();
        Node<T>* tempPtr = head;
        while (tempPtr->next != tail) {
            tempPtr = tempPtr->next;
        }

        delete tail;
        tail = tempPtr;
        tail->next = head;  // maintain circularity

        return returningVal;
    }

    // delete from a specific position
    T deleteFromPosition(int index) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return T(); }
        if (isEmpty()) { cout << "List is empty." << endl; return T(); }

        int size = getSize();
        if (index >= size) { cout << "Index out of bounds." << endl; return T(); }

        // delete from head
        if (index == 0) {
            return deleteFromHead();
        }

        Node<T>* head = getHead();
        Node<T>* tempPtr = head;
        for (int i = 0; i < index - 1; i++) {
            tempPtr = tempPtr->next;
        }

        Node<T>* nodeToDelete = tempPtr->next;
        T returningVal = nodeToDelete->data;

        tempPtr->next = nodeToDelete->next;

        // update tail if we deleted the last node
        if (nodeToDelete == tail) {
            tail = tempPtr;
        }

        delete nodeToDelete;
        return returningVal;
    }

    // delete the first value of given parameter
    void deleteValue(T val) {
        if (isEmpty()) { cout << "Circular linked list is empty." << endl; return; }

        Node<T>* head = getHead();

        // case I: delete from head
        if (head->data == val) {
            T deletedVal = head->data;
            deleteFromHead();
            cout << "Value " << deletedVal << " deleted from list." << endl;
            return;
        }

        // case II: delete from middle or tail
        Node<T>* tempPtr = head;
        do {
            if (tempPtr->next->data == val) {
                Node<T>* nodeToDelete = tempPtr->next;
                T deletedVal = nodeToDelete->data;

                tempPtr->next = nodeToDelete->next;

                if (nodeToDelete == tail) {
                    tail = tempPtr;
                }

                delete nodeToDelete;
                cout << "Value " << deletedVal << " deleted from list." << endl;
                return;
            }
            tempPtr = tempPtr->next;
        }
        while (tempPtr != head);

        cout << "Value " << val << " not found in list." << endl;
    }
};

//------------------------------------------------------------------------------------------------------------------
