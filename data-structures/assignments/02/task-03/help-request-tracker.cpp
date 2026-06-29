#include "../linkedlist/singlylinkedlist.h"
#include <string>

struct Request {
    int requestID;
    string studentName;
    string issueType;
    string status;
};

// ===== REQUEST TRACKER CLASS =====

class RequestTracker {
private:
    MySinglyLinkedList<Request> list;
    int nextRequestID;
public:
    // constructor
    RequestTracker() {
        nextRequestID = 506;
    }

    // add normal request (insert at end)
    void addRequest(const string& name, const string& issue) {
        Request r;
        r.requestID = nextRequestID++;
        r.studentName = name;
        r.issueType = issue;
        r.status = "Pending";

        list.insertAtTail(r);
        cout << "Request Added: ID " << r.requestID << endl;
    }

    // insert urgent request (at head)
    void addUrgentRequest(const string& name, const string& issue) {
        Request r;
        r.requestID = nextRequestID++;
        r.studentName = name;
        r.issueType = issue;
        r.status = "Urgent";

        list.insertAtHead(r);

        cout << "URGENT Request Added: ID " << r.requestID << endl;
    }

    // delete request by ID
    void deleteRequest(int id) {
        if (list.isEmpty()) { cout << "No requests to delete.\n"; return; }

        Node<Request>* temp = list.head;

        // if head matches
        if (temp->data.requestID == id) {
            list.deleteFromHead();
            cout << "Request " << id << " deleted.\n";
            return;
        }

        // traverse
        while (temp->next != nullptr) {
            if (temp->next->data.requestID == id) {
                Request deleted = temp->next->data;
                list.deleteValue(deleted);
                cout << "Request " << id << " deleted.\n";
                return;
            }
            temp = temp->next;
        }

        cout << "Request ID not found.\n";
    }

    // search request by ID
    void searchRequest(int id) {
        Node<Request>* temp = list.head;

        while (temp != nullptr) {
            if (temp->data.requestID == id) {
                cout << "\nFound Request:\n";
                cout << "ID: " << temp->data.requestID << " | Name: " << temp->data.studentName << " | Issue: " << temp->data.issueType << " | Status: " << temp->data.status << endl;
                return;
            }
            temp = temp->next;
        }

        cout << "Request not found.\n";
    }

    // display all requests
    void displayAll() {
        if (list.isEmpty()) {
            cout << "No requests available.\n";
            return;
        }

        cout << "\n--- All Requests ---\n";

        Node<Request>* temp = list.head;
        int i = 0;

        while (temp != nullptr) {
            cout << i++ << ". " << "ID: " << temp->data.requestID << " | Name: " << temp->data.studentName << " | Issue: " << temp->data.issueType << " | Status: " << temp->data.status << endl;
            temp = temp->next;
        }
    }

    // count requests
    void countRequests() {
        int count = 0;
        Node<Request>* temp = list.head;

        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }

        cout << "Total Requests: " << count << endl;
    }

    // update status
    void updateStatus(int id, string newStatus) {
        Node<Request>* temp = list.head;

        while (temp != nullptr) {
            if (temp->data.requestID == id) {
                temp->data.status = newStatus;
                cout << "Status updated for ID " << id << endl;
                return;
            }
            temp = temp->next;
        }

        cout << "Request not found.\n";
    }
};

bool operator==(const Request& a, const Request& b) {
    return a.requestID == b.requestID;
}

ostream& operator<<(ostream& os, const Request& r) {
    os << "ID: " << r.requestID << ", Name: " << r.studentName << ", Issue: " << r.issueType << ", Status: " << r.status;
    return os;
}

int main() {
    RequestTracker rt;

    // 5 sample records 
    rt.addRequest("Ali", "Library Card Issue");
    rt.addRequest("Sara", "Course Registration Error");
    rt.addRequest("Usman", "WiFi Connectivity Issue");
    rt.addRequest("Ayesha", "Fee Voucher Problem");
    rt.addRequest("Hassan", "Hostel Electricity Issue");

    // urgent requests
    rt.addUrgentRequest("Bilal", "Exam Roll Number Issue");

    rt.displayAll();

    rt.updateStatus(508, "Resolved");

    cout << "\nAfter Update:\n";
    rt.displayAll();
    return 0;
}
