#include "stack/stack.h"

int main() {
    MyStack<string>* table = new MyStack<string>(4);
    table->push("One hundrad years of solitude");
    table->push("My name is red");
    table->push("Aag ka darya");
    table->push("Udass naslen");
    cout << "Displaying Stack" << endl;
    table->display();

    // stack overflow
    cout << endl;
    table->push("War and peace");
    cout << endl;

    table->pop();
    table->pop();
    table->pop();
    table->pop();
    cout << "Displaying Stack" << endl;
    table->display();

    // stack underflow
    cout << endl;
    table->pop();

    delete table;
    return 0;
}
