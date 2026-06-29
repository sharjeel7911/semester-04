#include <iostream>
using namespace std;

struct Vehicle {
    int id;
    string type;

    Vehicle() : id(0), type("") {}
    Vehicle(int i, string t) : id(i), type(t) {}
};

#define SIZE 5
class TrafficQueue {
private:
    Vehicle queue[SIZE];
    int front;
    int rear;
    int count;

public:
    TrafficQueue() :front(0), rear(-1), count(0) {}
    bool isFull() { return count == SIZE; }
    bool isEmpty() { return count == 0; }

    void enqueueNormal(Vehicle v) {
        if (isFull()) {
            cout << "Queue Full\n";
            return;
        }

        rear = (rear + 1) % SIZE;
        queue[rear] = v;
        count++;
        cout << "Normal vehicle added\n";
    }

    void enqueueEmergency(Vehicle v) {
        if (isFull()) {
            cout << "Queue Full\n";
            return;
        }

        front = (front - 1 + SIZE) % SIZE;
        queue[front] = v;
        count++;
        cout << "Emergency vehicle added with priority\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "No vehicles to pass\n";
            return;
        }

        Vehicle removed = queue[front];
        front = (front + 1) % SIZE;
        count--;
        cout << "Vehicle passed: " << removed.id << " (" << removed.type << ")\n";
    }

    void displayQueue() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }

        cout << "\nTraffic Queue:\n";

        for (int i = 0; i < count; i++) {
            int index = (front + i) % SIZE;
            cout << queue[index].id << " - " << queue[index].type << endl;
        }
    }

    void systemStatus() {
        cout << "\n--- SYSTEM STATUS ---\n";
        cout << "Total Vehicles: " << count << endl;
        cout << "Emergency Vehicles: " << countEmergency() << endl;
        cout << "Normal Vehicles: " << countNormal() << endl;
    }

    int countEmergency() {
        int c = 0;
        for (int i = 0; i < count; i++) {
            int index = (front + i) % SIZE;
            if (queue[index].type == "Emergency")
                c++;
        }
        return c;
    }

    int countNormal() {
        int c = 0;
        for (int i = 0; i < count; i++) {
            int index = (front + i) % SIZE;
            if (queue[index].type == "Normal")
                c++;
        }
        return c;
    }
};

class System {
private:
    TrafficQueue tq;
public:
    void addNormal(Vehicle v) { tq.enqueueNormal(v); }
    void addEmergency(Vehicle v) { tq.enqueueEmergency(v); }
    void passVehicle() { tq.dequeue(); }
    void show() { tq.displayQueue(); }
    void status() { tq.systemStatus(); }
};


int main() {
    System s;

    Vehicle v1(1, "Normal");
    Vehicle v2(2, "Emergency");
    Vehicle v3(3, "Normal");
    Vehicle v4(4, "Emergency");
    Vehicle v5(5, "Normal");

    s.addNormal(v1);
    s.addEmergency(v2);
    s.addNormal(v3);
    s.addEmergency(v4);
    s.addNormal(v5);

    s.show();

    cout << "\n--- Passing Vehicles ---\n";
    s.passVehicle();
    s.passVehicle();

    s.show();

    s.status();
    return 0;
}