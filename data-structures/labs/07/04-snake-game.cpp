#include <iostream>
using namespace std;

struct Node {
    int x, y;
    Node* next;

    Node(int xVal, int yVal) : x(xVal), y(yVal), next(nullptr) {}
};

class Snake {
private:
    Node* head;
    Node* tail;
public:
    Snake() : head(nullptr), tail(nullptr) {}

    void printSnake() {
        Node* temp = head;
        cout << "Snake: ";

        while (temp != nullptr) {
            cout << "(" << temp->x << "," << temp->y << ") ";
            temp = temp->next;
        }
        cout << endl;
    }

    bool collisionCheck(int x, int y) {
        Node* temp = head;

        while (temp != nullptr) {
            if (temp->x == x && temp->y == y) {
                return true;
            }
            temp = temp->next;
        }

        return false;
    }

    void addHead(int x, int y) {
        Node* newNode = new Node(x, y);

        if (!head) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head = newNode;
        }
    }

    void removeTail() {
        if (!head) return;

        if (head == tail) {
            delete head;
            head = tail = nullptr;
            return;
        }

        Node* temp = head;

        while (temp->next != tail) {
            temp = temp->next;
        }

        delete tail;
        tail = temp;
        tail->next = nullptr;
    }

    void move(int x, int y, bool foodEaten) {

        if (collisionCheck(x, y)) {
            cout << "Collision detected at (" << x << "," << y << ") \nGAME OVER\n";
            return;
        }

        addHead(x, y);

        if (!foodEaten) {
            removeTail();
        }

        cout << "Moved to (" << x << "," << y << ")" << (foodEaten ? " [Grew]" : "") << endl;
        printSnake();
    }
};

int main() {
    Snake snake;

    snake.addHead(2, 2);
    snake.addHead(2, 1);
    snake.addHead(2, 0);

    cout << "Initial State:\n";
    snake.printSnake();

    cout << "\n--- Game Start ---\n";

    // Move 1 (normal move)
    snake.move(2, 3, false);

    // Move 2 (eat food -> grow)
    snake.move(2, 4, true);

    // Move 3 (normal move)
    snake.move(3, 4, false);

    // Move 4 (normal move)
    snake.move(3, 3, false);

    // Move 5 (self collision case)
    snake.move(2, 3, false);

    return 0;
}