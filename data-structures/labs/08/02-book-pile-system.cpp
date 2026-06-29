#include <iostream>
using namespace std;

//-------------------------------------------------------

// ===== STACK CLASS =====

template <class T>
class MyStack {
public:
    T* st;
    int topPtr;
    int maxSize;

    MyStack(int size) : maxSize(size), topPtr(0) { st = new T[size]; }
    ~MyStack() { delete[] st; }

    MyStack(const MyStack& other) {
        maxSize = other.maxSize;
        topPtr = other.topPtr;
        st = new T[maxSize];

        for (int i = 0; i < topPtr; i++) {
            st[i] = other.st[i];
        }
    }

    bool isFull() { return topPtr == maxSize; }
    bool isEmpty() { return topPtr == 0; }

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
        for (int i = topPtr - 1; i >= 0; i--) {
            cout << (topPtr - i) << ". " << st[i] << endl;
        }
    }
};

//-------------------------------------------------------

// ===== BOOK =====

struct Book {
    int bookId;
    string bookName;

    Book() : bookId(0), bookName("") {};
    Book(int i, string n) : bookId(i), bookName(n) {};
};

ostream& operator<<(ostream& out, const Book b) {
    out << "Book id: " << b.bookId << " Book name: " << b.bookName << endl;
    return out;
}

//-------------------------------------------------------

// ===== BOOKSYSTEM CLASS =====

template <class T>
class BookSystem {
private:
    MyStack<Book> st;
public:
    BookSystem(int sz) : st(sz) {}
    void pushBook(T val) {
        st.push(val);
    }

    T popBook() {
        T rem = st.pop();
        return rem;
    }

    T peekBook() {

        return st.top();
    }

    void displayBooks() {
        cout << "Books display\n";
        st.display();
    }

    int search(int id) {
        MyStack<Book> temp = st;
        int pos = 0;

        while (!temp.isEmpty()) {
            Book b = temp.pop();
            if (b.bookId == id) {
                return pos;
            }
            pos++;
        }
        return -1;
    }

    int countBooks() {
        MyStack<Book> temp = st;
        int count = 0;

        while (!temp.isEmpty()) {
            temp.pop();
            count++;
        }

        return count;
    }

    void reverseStack() {
        MyStack<Book> temp = st;
        MyStack<Book> reversed(100);

        while (!temp.isEmpty()) {
            reversed.push(temp.pop());
        }

        cout << "Reversed Stack:\n";
        reversed.display();
    }

    Book findTopMostEvenID() {
        MyStack<Book> temp = st;

        while (!temp.isEmpty()) {
            Book b = temp.pop();
            if (b.bookId % 2 == 0) {
                return b;
            }
        }
        cout << "No even ID found\n";
        return Book();
    }
};

int main() {
    BookSystem<Book> bs(100);

    Book b1(1, "ali");
    Book b2(2, "bao ji");
    Book b3(3, "ahmad");
    Book b4(4, "zues");

    bs.pushBook(b1);
    bs.pushBook(b2);
    bs.pushBook(b3);
    bs.pushBook(b4);

    bs.displayBooks();

    cout << "\nReversed stack" << endl;
    bs.reverseStack();

    cout << "\nTotal books: " << bs.countBooks() << endl;
    return 0;
}
