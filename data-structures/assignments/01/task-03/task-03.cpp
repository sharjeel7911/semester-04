#include "stack/stack.h"

#define stackCap 5

int main() {
    MyStack<char>* roll = new MyStack<char>(stackCap);

    cout << "Pushing 'L'\n"; roll->push('L'); roll->display();
    cout << "----------------------" << endl;
    cout << "Pushing '1'\n"; roll->push('1'); roll->display();
    cout << "----------------------" << endl;
    cout << "Pushing 'F'\n"; roll->push('F'); roll->display();
    cout << "----------------------" << endl;
    cout << "Pushing '2'\n"; roll->push('2'); roll->display();
    cout << "----------------------" << endl;
    cout << "Pushing '4'\n"; roll->push('4'); roll->display();

    cout << "----------------------" << endl;
    cout << "Pushing 'x' will result in stack overflow error.\n" << endl;
    roll->push('x'); roll->display();
    cout << "----------------------\n" << endl;

    //--------------------------------------------------------------------

    cout << "Popping '4'\n"; roll->pop(); roll->display();
    cout << "----------------------" << endl;
    cout << "Popping '2'\n"; roll->pop(); roll->display();
    cout << "----------------------" << endl;
    cout << "Popping 'F'\n"; roll->pop(); roll->display();
    cout << "----------------------" << endl;
    cout << "Popping '1'\n"; roll->pop(); roll->display();
    cout << "----------------------" << endl;
    cout << "Popping 'L'\n"; roll->pop(); roll->display();

    cout << "----------------------" << endl;
    cout << "Popping will result in stack underflow error.\n" << endl;
    roll->pop(); roll->display();
    cout << "----------------------\n" << endl;

    //--------------------------------------------------------------------

    delete roll;
    return 0;
}
