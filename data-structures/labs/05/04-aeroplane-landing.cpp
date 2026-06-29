#include "../queue/priorityqueue.h"
#include <string>

// task-04 + task-05 + task-06 (all together)

// ==================== Flight struct ====================

struct Flight {
    string flightID;
    int priority;  // 3 = emergency, 2 = passenger, 1 = cargo
    int arrivalSequence;  // for fifo within same priority

    // constructor
    Flight() : flightID(""), priority(0), arrivalSequence(0) {}
    Flight(string id, int p, int seq) : flightID(id), priority(p), arrivalSequence(seq) {}

    bool operator<(const Flight&) const;
    friend ostream& operator<<(ostream&, const Flight&);
};

// overload < operator for priority queue (higher priority = higher value)
bool Flight::operator<(const Flight& obj) const {
    if (this->priority != obj.priority) {
        return this->priority < obj.priority;
    }
    // if same priority, use fifo (lower arrival sequence = higher priority)
    return this->arrivalSequence > obj.arrivalSequence;
}

// overload << for display
ostream& operator<<(ostream& out, const Flight& fl) {
    out << fl.flightID;
    return out;
}

// ==================== Runaway scheduling syastem ====================

struct RunwayScheduler {
    MyPriorityQueue<Flight> scheduler;
    int arrivalCounter;

    // constructor
    RunwayScheduler(int maxFlights = 50) : scheduler(maxFlights), arrivalCounter(0) {}

    void enqueue(string flightType, string flightID);
    Flight dequeue();
    void display();
    friend string getFlightType(const Flight& f);
};

void RunwayScheduler::enqueue(string flightType, string flightID) {
    int priority = 0;
    string typeLabel;

    if (flightType == "E") {
        priority = 3;  // Emergency: HIGHEST priority 
        typeLabel = "Emergency";
    }
    else if (flightType == "P") {
        priority = 2;  // Passenger: MEDIUM priority
        typeLabel = "Passenger";
    }
    else if (flightType == "C") {
        priority = 1;  // Cargo: LOWEST priority
        typeLabel = "Cargo";
    }
    else {
        cout << "Invalid flight type!\n";
        return;
    }

    Flight flight(flightID, priority, arrivalCounter++);
    scheduler.enqueue(flight);

    cout << "[ARRIVAL " << arrivalCounter << "]: " << typeLabel << " flight " << flightID << " queued for landing\n";
}

Flight RunwayScheduler::dequeue() {
    if (scheduler.isEmpty()) {
        cout << "ERROR: No flights waiting to land!\n"; return Flight();
    }

    Flight flight = scheduler.dequeue();
    cout << "LANDING Flight " << flight.flightID << " is now landing\n";
    return flight;
}

void RunwayScheduler::display() {
    cout << "\n========== CURRENT RUNWAY QUEUE ==========\n";
    scheduler.display();
    cout << "========================================\n\n";
}

// helper to get flight type string
string getFlightType(const Flight& fl) {
    if (fl.priority == 3) return "Emergency";
    if (fl.priority == 2) return "Passenger";
    return "Cargo";
}

// ==================== MAIN ====================
int main() {
    RunwayScheduler scheduler(50);

    // sequence: Passenger(P1), Cargo(C1), Emergency(E1), Passenger(P2), Cargo(C2), Emergency(E2)
    scheduler.enqueue("P", "P1");
    scheduler.enqueue("C", "C1");
    scheduler.enqueue("E", "E1");
    scheduler.enqueue("P", "P2");
    scheduler.enqueue("C", "C2");
    scheduler.enqueue("E", "E2");

    scheduler.display();

    int landingSequence = 1;
    while (!scheduler.scheduler.isEmpty()) {
        cout << "Landing Slot " << landingSequence << ": ";
        scheduler.dequeue();
        landingSequence++;
        scheduler.display();
    }
    return 0;
}
