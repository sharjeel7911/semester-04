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



// ===================================================

// ========== LINKED LIST USING HEAD & TAIL ==========

// ===================================================

template <class T>
class MySinglyLinkedList {
public:
    Node<T>* head;
    Node<T>* tail;

    // constructor
    MySinglyLinkedList() : head(nullptr), tail(nullptr) {}

    // destructor
    ~MySinglyLinkedList() { while (!isEmpty()) deleteFromHead(); }

    // checks if linked list is empty
    bool isEmpty() { return head == nullptr && tail == nullptr; }

    // search for a value if present in linked list
    bool search(T val) {
        if (isEmpty()) { cout << "Linked list is empty." << endl; return false; }
        else {
            Node<T>* tempPtr = head;
            while (tempPtr != nullptr) {
                if (tempPtr->data == val) return true;
                tempPtr = tempPtr->next;
            }
        }
        return false;
    }

    // display linked list
    void display() {
        if (isEmpty()) { cout << "Linked list is empty." << endl; return; }

        Node<T>* tempPtr = head;
        int k = 0;
        while (tempPtr != nullptr) {
            cout << k++ << ". " << tempPtr->data << endl;
            tempPtr = tempPtr->next;
        }
    }

    // -----------------------------------------------------------------------------

    // insert values at head
    void insertAtHead(T val) {
        Node<T>* newNode = new Node<T>(val);

        // empty linked list 
        if (isEmpty()) {
            head = tail = newNode;
        }

        // non - empty linked list
        else {
            newNode->next = head;
            head = newNode;
        }
    }

    // insert values at tail
    void insertAtTail(T val) {
        Node<T>* newNode = new Node<T>(val);

        // empty linked list 
        if (isEmpty()) {
            head = tail = newNode;
        }

        // non - empty linked list
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // insert at specific position
    void insertAtPosition(T val, int index) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return; }
        if (isEmpty() && index != 0) { cout << "List is empty. Can only insert at position 0." << endl; return; }

        Node<T>* newNode = new Node<T>(val);

        if (index == 0) {
            // case I : empty list
            if (isEmpty()) {
                head = tail = newNode;
            }
            // case I : non - empty list
            else {
                newNode->next = head;
                head = newNode;
            }
            cout << "Value inserted at position " << index << endl;
            return;
        }

        // case III : insert elsewhere -> traverse to (position - 1)
        Node<T>* tempPtr = head;
        // tempPtr is a pointer, so it can only store an address -> it points to memories
        // tempPtr points to a box0 which is also pointed by head. tempPtr -> [data | address to next box1]
        // { tempPtr->next = box0->next = [box1 address] } and { tempPtr->data = box0->data }
        // [temp = tempPtr->next] goes to addrees which is stored in the box0 and starts pointing to that address [box1 address]
        // hence now tempPtr is pointing to next box which is box1
        for (int i = 0; i < index - 1 && tempPtr != nullptr; i++) {
            // if box0 → box1 → box2 → box3 → null, and we want to insert at end to create box4 [index = 4]-> loop will run upto 2 [i < index - 1 -> {4 - 1 = 3} -> less than 3 is 2] and [tempPtr->next] of box2 will point to box3 which is last box in current list before insertion
            tempPtr = tempPtr->next;
        }

        // bounds check -> ensure we didn't go past the end
        if (tempPtr == nullptr) {
            cout << "Index out of bounds." << endl;
            delete newNode;
            return;
        }

        // link the new node
        //              [tempPtr]
        //                |
        // box0 → box1 → box2 → box3 → null
        // assume we insert at position 3 -> tempPtr points to box2 -> [tempPtr->next] points to box3
        newNode->next = tempPtr->next; // newNode starts pointing towards [tempPtr->next] which is box3 -> newNode is connected with right side of list  
        tempPtr->next = newNode; // { tempPtr->next = box->next } -> [box->next] starts pointing to newNode -> newNode connects to previous node, the left side
        // box0 → box1 → box2 → newNode → box3 → null

        // update tail if inserted at end
        if (newNode->next == nullptr) {
            tail = newNode;
        }
        cout << "Value inserted at position " << index << endl;
    }

    // insert in sorted order
    void insertSorted(T val) {
        Node<T>* newNode = new Node<T>(val);

        // case I: empty list
        if (isEmpty()) {
            head = tail = newNode;
            cout << "Value " << val << " inserted at position 0." << endl; return;
        }

        // case II: insert at head (val is smaller than head)
        if (val < head->data) {
            newNode->next = head;
            head = newNode;
            cout << "Value " << val << " inserted at head." << endl; return;
        }

        // case III: traverse to find correct position
        Node<T>* tempPtr = head;
        while (tempPtr->next != nullptr && tempPtr->next->data < val) {
            tempPtr = tempPtr->next;
        }

        // insert between tempPtr and tempPtr->next
        // if Node A = 6, B = 10, C = 15 and new Val = 12
        // tempPtr = tempPtr->next will point to Node C. remember it is the next of NODE B that contains an address of NODE C
        // newNode->next = tempPtr->next; {newNode->next which was nullptr before now starts pointing to Node C}
        newNode->next = tempPtr->next;
        // tempPtr->next is the next of NODE B which holds the adress for NODE C
        // now NODE B next will hold the address of NODE newNode hence newNode is inserted between NODE B and NODE C
        tempPtr->next = newNode;

        // update tail if inserted at end
        if (newNode->next == nullptr) {
            tail = newNode;
        }
        cout << "Value " << val << " inserted in sorted order." << endl;
    }

    // update a value present in the node
    void updateNode(int index, T newVal) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return; }
        if (isEmpty()) { cout << "Linked list is empty." << endl; return; }

        // traverse to the node at index
        Node<T>* tempPtr = head;
        for (int i = 0; i < index && tempPtr != nullptr; i++) {
            tempPtr = tempPtr->next;
        }

        // bounds check: ensure index is valid
        if (tempPtr == nullptr) { cout << "Index out of bounds." << endl; return; }

        // update the value
        T oldVal = tempPtr->data;
        tempPtr->data = newVal;
        cout << "Node at index " << index << " updated from " << oldVal << " to " << newVal << endl;
    }

    //------------------------------------------------------------------------------------------------

    // delete values from head
    T deleteFromHead() {
        if (isEmpty()) { cout << "Linked list is empty" << endl; return T(); }

        // if linked list has only one node
        else if (head == tail) {
            T returningVal = head->data; // or  tail->data;

            delete head; // or  tail;
            head = tail = nullptr;

            return returningVal;
        }

        else {
            T returningVal = head->data;

            Node<T>* tempPtr = head;
            head = head->next;

            delete tempPtr;
            tempPtr = nullptr;

            return returningVal;
        }
    }

    // delete values from tail
    T deleteFromTail() {
        if (isEmpty()) { cout << "Linked list is empty" << endl; return T(); }

        // if linked list has only one node
        if (head == tail) {
            T returningVal = tail->data; // or  head->data;

            delete  tail; // or  head;
            head = tail = nullptr;

            return returningVal;
        }

        else {
            T returningVal = tail->data;

            Node<T>* tempPtr = head;

            while (tempPtr->next != tail) {
                tempPtr = tempPtr->next;
            }

            delete  tail;
            tail = tempPtr;
            tail->next = nullptr; // or tempPtr = nullptr; [same pointer] 

            return returningVal;
        }
    }

    // delete from a specific position
    T deleteFromPosition(int index) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return T(); }
        if (isEmpty()) { cout << "List is empty." << endl; return T(); }

        if (index == 0) {
            T returningVal = head->data;
            Node<T>* tempPtr = head;
            head = head->next;

            // if list becomes empty, update tail
            if (head == nullptr) tail = nullptr;

            delete tempPtr;
            return returningVal;
        }

        // delete from elsewhere: traverse to index - 1
        Node<T>* tempPtr = head;
        for (int i = 0; i < index - 1 && tempPtr != nullptr; i++) {
            tempPtr = tempPtr->next;
        }

        // bounds check
        if (tempPtr == nullptr || tempPtr->next == nullptr) {
            cout << "Index out of bounds." << endl;
            return T();
        }

        // get the node to delete
        Node<T>* nodeToDelete = tempPtr->next;
        T returningVal = nodeToDelete->data;

        // unlink and delete
        tempPtr->next = nodeToDelete->next;

        // update tail if we deleted the last node
        if (nodeToDelete == tail) {
            tail = tempPtr;
        }

        delete nodeToDelete;
        return returningVal;
    }

    // delete the the first value of given parameter present in linked list 
    void deleteValue(T val) {
        if (isEmpty()) { cout << "Linked list is empty." << endl; return; }

        // case I: delete from head
        if (head->data == val) {
            Node<T>* tempPtr = head;
            head = head->next;

            // if list becomes empty after deletion
            if (head == nullptr) {
                tail = nullptr;
            }

            delete tempPtr;
            cout << "Value " << val << " deleted from list." << endl;
            return;
        }

        // case II: delete from middle or tail
        Node<T>* tempPtr = head;
        while (tempPtr->next != nullptr) {
            if (tempPtr->next->data == val) {  // tempPtr->next->data: [if tempPtr points to A, then tempPtr->next has adress of B and [tempPtr->next->data] will give data of Node B]
                Node<T>* nodeToDelete = tempPtr->next;
                T deletedVal = nodeToDelete->data;

                // unlink the node
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

        // value not found
        cout << "Value " << val << " not found in list." << endl;
    }
};

//------------------------------------------------------------------------------------------------------------------



// =================================================

// ========== LINKED LIST USING HEAD ONLY ==========

// =================================================

template <class T>
class MySinglyLinkedListHead {
public:
    Node<T>* head;

    // constructor
    MySinglyLinkedListHead() : head(nullptr) {}

    // destructor
    ~MySinglyLinkedListHead() { while (!isEmpty()) deleteFromHead(); }

    // checks if linked list is empty
    bool isEmpty() { return head == nullptr; }

    // search for a value if present in linked list
    bool search(T val) {
        if (isEmpty()) { cout << "Linked list is empty." << endl; return false; }
        else {
            Node<T>* tempPtr = head;
            while (tempPtr != nullptr) {
                if (tempPtr->data == val) return true;
                tempPtr = tempPtr->next;
            }
        }
        return false;
    }

    // display linked list
    void display() {
        if (isEmpty()) { cout << "Linked list is empty." << endl; return; }

        Node<T>* tempPtr = head;
        int k = 0;
        while (tempPtr != nullptr) {
            cout << k++ << ". " << tempPtr->data << endl;
            tempPtr = tempPtr->next;
        }
    }

    // -----------------------------------------------------------------------------

    // insert values at head
    void insertAtHead(T val) {
        Node<T>* newNode = new Node<T>(val);

        if (isEmpty()) {
            head = newNode;
        }
        else {
            newNode->next = head;
            head = newNode;
        }
    }

    // insert values at tail (traverse required)
    void insertAtTail(T val) {
        Node<T>* newNode = new Node<T>(val);

        if (isEmpty()) {
            head = newNode;
        }
        else {
            Node<T>* tempPtr = head;
            while (tempPtr->next != nullptr) {
                tempPtr = tempPtr->next;
            }
            tempPtr->next = newNode;
        }
    }

    // insert at specific position
    void insertAtPosition(T val, int index) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return; }
        if (isEmpty() && index != 0) { cout << "List is empty. Can only insert at position 0." << endl; return; }

        Node<T>* newNode = new Node<T>(val);

        if (index == 0) {
            if (isEmpty()) {
                head = newNode;
            }
            else {
                newNode->next = head;
                head = newNode;
            }
            cout << "Value inserted at position " << index << endl;
            return;
        }

        Node<T>* tempPtr = head;
        for (int i = 0; i < index - 1 && tempPtr != nullptr; i++) {
            tempPtr = tempPtr->next;
        }

        if (tempPtr == nullptr) {
            cout << "Index out of bounds." << endl;
            delete newNode;
            return;
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
            head = newNode;
            cout << "Value " << val << " inserted at position 0." << endl;
            return;
        }

        // case II: insert at head
        if (val < head->data) {
            newNode->next = head;
            head = newNode;
            cout << "Value " << val << " inserted at head." << endl;
            return;
        }

        // case III: traverse to find correct position
        Node<T>* tempPtr = head;
        while (tempPtr->next != nullptr && tempPtr->next->data < val) {
            tempPtr = tempPtr->next;
        }

        newNode->next = tempPtr->next;
        tempPtr->next = newNode;
        cout << "Value " << val << " inserted in sorted order." << endl;
    }

    // update a value present in the node
    void updateNode(int index, T newVal) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return; }
        if (isEmpty()) { cout << "Linked list is empty." << endl; return; }

        Node<T>* tempPtr = head;
        for (int i = 0; i < index && tempPtr != nullptr; i++) {
            tempPtr = tempPtr->next;
        }

        if (tempPtr == nullptr) { cout << "Index out of bounds." << endl; return; }

        T oldVal = tempPtr->data;
        tempPtr->data = newVal;
        cout << "Node at index " << index << " updated from " << oldVal << " to " << newVal << endl;
    }

    // -----------------------------------------------------------------------------

    // delete values from head
    T deleteFromHead() {
        if (isEmpty()) { cout << "Linked list is empty" << endl; return T(); }

        T returningVal = head->data;
        Node<T>* tempPtr = head;
        head = head->next;

        delete tempPtr;
        return returningVal;
    }

    // delete values from tail (traverse required)
    T deleteFromTail() {
        if (isEmpty()) { cout << "Linked list is empty" << endl; return T(); }

        if (head->next == nullptr) {
            T returningVal = head->data;
            delete head;
            head = nullptr;
            return returningVal;
        }

        Node<T>* tempPtr = head;
        while (tempPtr->next->next != nullptr) {
            tempPtr = tempPtr->next;
        }

        T returningVal = tempPtr->next->data;
        delete tempPtr->next;
        tempPtr->next = nullptr;
        return returningVal;
    }

    // delete from a specific position
    T deleteFromPosition(int index) {
        if (index < 0) { cout << "Index cannot be negative." << endl; return T(); }
        if (isEmpty()) { cout << "List is empty." << endl; return T(); }

        if (index == 0) {
            T returningVal = head->data;
            Node<T>* tempPtr = head;
            head = head->next;
            delete tempPtr;
            return returningVal;
        }

        Node<T>* tempPtr = head;
        for (int i = 0; i < index - 1 && tempPtr != nullptr; i++) {
            tempPtr = tempPtr->next;
        }

        if (tempPtr == nullptr || tempPtr->next == nullptr) {
            cout << "Index out of bounds." << endl;
            return T();
        }

        Node<T>* nodeToDelete = tempPtr->next;
        T returningVal = nodeToDelete->data;
        tempPtr->next = nodeToDelete->next;
        delete nodeToDelete;
        return returningVal;
    }

    // delete the first value of given parameter present in linked list
    void deleteValue(T val) {
        if (isEmpty()) { cout << "Linked list is empty." << endl; return; }

        // case I: delete from head
        if (head->data == val) {
            Node<T>* tempPtr = head;
            head = head->next;
            delete tempPtr;
            cout << "Value " << val << " deleted from list." << endl;
            return;
        }

        // case II: delete from middle or tail
        Node<T>* tempPtr = head;
        while (tempPtr->next != nullptr) {
            if (tempPtr->next->data == val) {
                Node<T>* nodeToDelete = tempPtr->next;
                T deletedVal = nodeToDelete->data;
                tempPtr->next = nodeToDelete->next;
                delete nodeToDelete;
                cout << "Value " << deletedVal << " deleted from list." << endl;
                return;
            }
            tempPtr = tempPtr->next;
        }
        cout << "Value " << val << " not found in list." << endl;
    }
};
