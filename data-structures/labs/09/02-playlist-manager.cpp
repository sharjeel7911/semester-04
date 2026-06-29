#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct SongNode {
    int songID;
    string songName;
    float duration;

    SongNode* prev;
    SongNode* next;

    SongNode(int id, string name, float d) : songID(id), songName(name), duration(d), prev(nullptr), next(nullptr) {}
};

class Playlist {
private:
    SongNode* head;
    SongNode* tail;
    SongNode* curr;

public:
    Playlist() : head(nullptr), tail(nullptr), curr(nullptr) {}

    // add song at end
    void addSong(int id, string name, float duration) {
        SongNode* newNode = new SongNode(id, name, duration);

        if (!head) {
            head = tail = curr = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // delete song by name
    void deleteSong(string name) {
        if (!head) {
            cout << "Playlist is empty.\n";
            return;
        }

        SongNode* temp = head;

        while (temp && temp->songName != name) {
            temp = temp->next;
        }

        if (!temp) {
            cout << "Song not found.\n";
            return;
        }

        // adjust curr pointer if needed
        if (curr == temp) {
            curr = temp->next ? temp->next : temp->prev;
        }

        // only node
        if (temp == head && temp == tail) {
            head = tail = nullptr;
        }
        // head node
        else if (temp == head) {
            head = head->next;
            head->prev = nullptr;
        }
        // tail node
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
        cout << "Song deleted successfully.\n";
    }

    // play next song
    void playNext() {
        if (!curr) {
            cout << "No song playing.\n";
            return;
        }

        if (curr->next) {
            curr = curr->next;
            cout << "Now Playing: " << curr->songName << endl;
        }
        else {
            cout << "Already at last song.\n";
        }
    }

    // play previous song
    void playPrevious() {
        if (!curr) {
            cout << "No song playing.\n";
            return;
        }

        if (curr->prev) {
            curr = curr->prev;
            cout << "Now Playing: " << curr->songName << endl;
        }
        else {
            cout << "Already at first song.\n";
        }
    }

    // reverse playlist 
    void reversePlaylist() {
        if (!head) return;

        SongNode* temp = nullptr;
        SongNode* node = head;

        while (node) {
            temp = node->prev;
            node->prev = node->next;
            node->next = temp;
            node = node->prev;
        }

        temp = head;
        head = tail;
        tail = temp;

        curr = head;

        cout << "Playlist reversed successfully.\n";
    }

    // display playlist
    void display() {
        if (!head) {
            cout << "Playlist is empty.\n";
            return;
        }
        cout << left << setw(5) << "ID" << setw(25) << "Name" << setw(10) << "Duration" << endl;

        SongNode* temp = head;
        while (temp) {
            cout << left << setw(5) << temp->songID << setw(25) << temp->songName << setw(10) << temp->duration << endl;
            temp = temp->next;
        }
    }

    // start playback from first song 
    void start() {
        curr = head;
        cout << "Now Playing: " << curr->songName << endl;
    }
};

int main() {

    Playlist p;

    p.addSong(1, "Believer", 3.2);
    p.addSong(2, "Faded", 3.5);
    p.addSong(3, "Senorita", 3.1);
    p.addSong(4, "Perfect", 4.0);

    p.display();

    cout << "\n--- Start Playback ---\n";
    p.start();

    p.playNext();
    p.playNext();
    p.playPrevious();

    cout << "\n--- Delete Song ---\n";
    p.deleteSong("Faded");
    p.display();

    cout << "\n--- Reverse Playlist ---\n";
    p.reversePlaylist();
    p.display();

    cout << "\n--- Playback After Shuffle ---\n";
    p.playNext();

    return 0;
}