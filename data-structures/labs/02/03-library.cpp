#include <iostream>
#include <string>
using namespace std;

template <class T>
class Media {
public:
    virtual void display() = 0;
};

//-------------------------------------------------------------------------------------------------

template <class T>
class Book : public Media<Book<T>> {
private:
    T title;
    T author;
    int pages;
public:
    Book();
    Book(T t, T a, int p);

    T getTitle();
    int getPages();
    void display();
};

template <class T>
Book<T>::Book() { title = "", author = "", pages = 0; }

template <class T>
Book<T>::Book(T t, T a, int p) { title = t, author = a, pages = p; }

template <typename T>
T Book<T>::getTitle() { return title; }

template <typename T>
int Book<T>::getPages() { return pages; }

template <typename T>
void Book<T>::display() { cout << "Book: " << title << ", Author: " << author << ", Pages: " << pages << endl; }

//-------------------------------------------------------------------------------------------------

template <class T>
class Newspaper : public Media<Newspaper<T>> {
private:
    T name;
    T date;
    T edition;
public:
    Newspaper();
    Newspaper(T n, T d, T e);

    T getName();
    T getEdition();
    void display();
};

template <class T>
Newspaper<T>::Newspaper() { name = "", date = "", edition = ""; }

template <class T>
Newspaper<T>::Newspaper(T n, T d, T e) { name = n, date = d, edition = e; }

template <typename T>
T Newspaper<T>::getName() { return name; }

template <typename T>
T Newspaper<T>::getEdition() { return edition; }

template <typename T>
void Newspaper<T>::display() { cout << "Newspaper: " << name << ", Date: " << date << ", Edition: " << edition << endl; }

//-------------------------------------------------------------------------------------------------

template <class B, class N>
class Library {
private:
    B books[100];
    N newspapers[100];

    int bookCount;
    int newspaperCount;
public:
    Library();

    void addBook(B b);
    void addNewspaper(N n);

    void sortBooksByPages();
    void sortNewspapersByEdition();

    void displayCollection();

    B* searchBookByTitle(string title);
    N* searchNewspaperByName(string name);
};

template <class B, class N>
Library<B, N>::Library() {
    bookCount = 0;
    newspaperCount = 0;
}

template <typename B, typename N>
void Library<B, N>::addBook(B b) { books[bookCount++] = b; }

template <typename B, typename N>
void Library<B, N>::addNewspaper(N n) { newspapers[newspaperCount++] = n; }


template <typename B, typename N>
void Library<B, N>::sortBooksByPages() {
    for (int i = 0; i < bookCount - 1; i++) {
        for (int j = 0; j < bookCount - i - 1; j++) {
            if (books[j].getPages() > books[j + 1].getPages()) {
                B temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
}

template <typename B, typename N>
void Library<B, N>::sortNewspapersByEdition() {
    for (int i = 0; i < newspaperCount - 1; i++) {
        for (int j = 0; j < newspaperCount - i - 1; j++) {
            if (newspapers[j].getEdition() > newspapers[j + 1].getEdition()) {
                N temp = newspapers[j];
                newspapers[j] = newspapers[j + 1];
                newspapers[j + 1] = temp;
            }
        }
    }
}

template <typename B, typename N>
void Library<B, N>::displayCollection() {
    cout << "\nBooks:\n";
    for (int i = 0; i < bookCount; i++) books[i].display();

    cout << "\nNewspapers:\n";
    for (int i = 0; i < newspaperCount; i++) newspapers[i].display();
}

template <typename B, typename N>
B* Library<B, N>::searchBookByTitle(string title) {
    int index = linearSearchBook(books, bookCount, title);

    if (index != -1)
        return &books[index];

    return nullptr;
}

template <typename B, typename N>
N* Library<B, N>::searchNewspaperByName(string name) {
    int index = linearSearchNewspaper(newspapers, newspaperCount, name);

    if (index != -1)
        return &newspapers[index];

    return nullptr;
}

//-------------------------------------------------------------------------------------------------

template <class T>
int linearSearchBook(T arr[], int size, string key) {
    for (int i = 0; i < size; i++) {
        if (arr[i].getTitle() == key)
            return i;
    }
    return -1;
}

template <class T>
int linearSearchNewspaper(T arr[], int size, string key) {
    for (int i = 0; i < size; i++) {
        if (arr[i].getName() == key)
            return i;
    }
    return -1;
}

//-------------------------------------------------------------------------------------------------

template <typename T>
int binarySearch(T* arr, int size, T key) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

//-------------------------------------------------------------------------------------------------

int main() {

    Book<string> book1("The Catcher in the Rye", "J.D. Salinger", 277);
    Book<string> book2("To Kill a Mockingbird", "Harper Lee", 324);

    Newspaper<string> newspaper1("Washington Post", "2024-10-13", "ZEdition");
    Newspaper<string> newspaper2("The Times", "2024-10-12", "AEdition");

    Library<Book<string>, Newspaper<string>> library;

    library.addBook(book1);
    library.addBook(book2);
    library.addNewspaper(newspaper1);
    library.addNewspaper(newspaper2);

    cout << "Before Sorting:\n";
    library.displayCollection();

    library.sortBooksByPages();
    library.sortNewspapersByEdition();

    cout << "\nAfter Sorting:\n";
    library.displayCollection();

    Book<string>* foundBook =
        library.searchBookByTitle("The Catcher in the Rye");

    if (foundBook) {
        cout << "\nFound Book:\n";
        foundBook->display();
    } else {
        cout << "\nBook not found.\n";
    }

    Newspaper<string>* foundNewspaper =
        library.searchNewspaperByName("The Times");

    if (foundNewspaper) {
        cout << "\nFound Newspaper:\n";
        foundNewspaper->display();
    } else {
        cout << "\nNewspaper not found.\n";
    }

    return 0;
}
