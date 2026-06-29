#include "queue/linearqueue.h"

int main() {
    Queue<int>* qu = new MyLinearQueue<int>(4);

    cout << "Linear queue\n\n";
    qu->enqueue(55);
    qu->enqueue(44);
    qu->enqueue(-99);
    qu->enqueue(1);

    // will give error
    qu->enqueue(0); cout << endl;

    qu->display();

    qu->dequeue();
    cout << "\nAfter removing front element\n";
    qu->display();

    qu->enqueue(103);
    cout << endl;
    cout << "\nAfter adding one more element\n";
    qu->display();

    qu->dequeue();
    qu->dequeue();
    qu->dequeue();
    qu->dequeue();

    // will give error
    qu->dequeue();

    cout << "\nQueue Display\n";
    qu->display();
    delete qu;
    return 0;
}
