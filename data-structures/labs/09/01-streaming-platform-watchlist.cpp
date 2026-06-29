#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct MovieNode {
    int movieID;
    string movieName;
    float rating;

    MovieNode* prev;
    MovieNode* next;

    MovieNode(int id, string name, float r) : movieID(id), movieName(name), rating(r), prev(nullptr), next(nullptr) {}
};

class Watchlist {
private:
    MovieNode* head;
    MovieNode* tail;
    MovieNode* curr;

public:
    Watchlist() : head(nullptr), tail(nullptr), curr(nullptr) {}

    // add movie at end
    void addMovie(int id, string name, float rating) {
        MovieNode* newNode = new MovieNode(id, name, rating);

        if (!head) {
            head = tail = curr = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // remove movie by name
    void removeMovie(string name) {
        if (!head) {
            cout << "Watchlist is empty.\n";
            return;
        }

        MovieNode* temp = head;

        while (temp && temp->movieName != name) {
            temp = temp->next;
        }

        if (!temp) {
            cout << "Movie not found.\n";
            return;
        }

        if (curr == temp) {
            curr = temp->next ? temp->next : temp->prev;
        }

        // case: only node
        if (temp == head && temp == tail) {
            head = tail = nullptr;
        }
        // case: head node
        else if (temp == head) {
            head = head->next;
            head->prev = nullptr;
        }
        // case: tail node
        else if (temp == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        // middle node
        else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        delete temp;
        cout << "Movie removed successfully.\n";
    }

    // play next movie
    void playNext() {
        if (!curr) {
            cout << "No movie playing.\n";
            return;
        }

        if (curr->next) {
            curr = curr->next;
            cout << "Now Playing: " << curr->movieName << endl;
        }
        else {
            cout << "Already at last movie.\n";
        }
    }

    // play previous movie
    void playPrevious() {
        if (!curr) {
            cout << "No movie playing.\n";
            return;
        }

        if (curr->prev) {
            curr = curr->prev;
            cout << "Now Playing: " << curr->movieName << endl;
        }
        else {
            cout << "Already at first movie.\n";
        }
    }

    // reverse watchlist 
    void reverseWatchlist() {
        if (!head) return;

        MovieNode* temp = nullptr;
        MovieNode* curr = head;

        while (curr) {
            temp = curr->prev;
            curr->prev = curr->next;
            curr->next = temp;
            curr = curr->prev;
        }

        // swap head and tail
        temp = head;
        head = tail;
        tail = temp;

        curr = head;

        cout << "Watchlist reversed successfully.\n";
    }

    // display watchlist
    void display() {
        if (!head) {
            cout << "Watchlist is empty.\n";
            return;
        }

        cout << left << setw(5) << "ID" << setw(25) << "Name" << setw(10) << "Rating" << endl;

        cout << "------------------------------------------\n";

        MovieNode* temp = head;
        while (temp) {
            cout << left << setw(5) << temp->movieID << setw(25) << temp->movieName << setw(10) << temp->rating << endl;
            temp = temp->next;
        }
    }

    // highest rated movie
    void highestRated() {
        if (!head) {
            cout << "Watchlist is empty.\n";
            return;
        }

        MovieNode* temp = head;
        MovieNode* best = head;

        while (temp) {
            if (temp->rating > best->rating) {
                best = temp;
            }
            temp = temp->next;
        }

        cout << "\nHighest Rated Movie:\n";
        cout << best->movieID << " - " << best->movieName << " - " << best->rating << endl;
    }

    // start movie watching from beginning
    void start() {
        curr = head;
        cout << "Now Playing: " << curr->movieName << endl;
    }
};

int main() {

    Watchlist w;

    w.addMovie(1, "Inception", 8.8);
    w.addMovie(2, "Interstellar", 8.6);
    w.addMovie(3, "Avatar", 7.9);
    w.addMovie(4, "The Dark Knight", 9.0);

    w.display();

    cout << "\n--- Navigation ---\n";
    w.start();
    w.playNext();
    w.playNext();
    w.playNext();
    w.playNext();
    w.playPrevious();

    cout << "\n--- Remove Movie ---\n";
    w.removeMovie("Avatar");
    w.display();

    cout << "\n--- Reverse Watchlist ---\n";
    w.reverseWatchlist();
    w.display();

    cout << "\n--- Highest Rated ---\n";
    w.highestRated();

    return 0;
}