#include <iostream>
using namespace std;

struct PlayerNode {
    int playerID;
    int score;
    PlayerNode* next;

    PlayerNode(int id, int s) : playerID(id), score(s), next(nullptr) {}
};

class Game {
private:
    PlayerNode* tail;
public:
    Game() : tail(nullptr) {}

    // add player (circular insert)
    void addPlayer(int id, int score) {
        PlayerNode* newPlayer = new PlayerNode(id, score);

        if (!tail) {
            tail = newPlayer;
            tail->next = tail; // circular link
            return;
        }

        PlayerNode* temp = tail;

        // go to last node
        while (temp->next != tail) {
            temp = temp->next;
        }

        temp->next = newPlayer;
        newPlayer->next = tail;
    }

    // remove player
    void removePlayer(int id) {
        if (!tail) {
            cout << "No players in game.\n";
            return;
        }

        PlayerNode* temp = tail;
        PlayerNode* prev = nullptr;

        // single node case
        if (tail->next == tail && tail->playerID == id) {
            delete tail;
            tail = nullptr;
            cout << "Player removed. Game ended.\n";
            return;
        }

        // find node
        do {
            if (temp->playerID == id) break;
            prev = temp;
            temp = temp->next;
        }
        while (temp != tail);

        if (temp->playerID != id) {
            cout << "Player not found.\n";
            return;
        }

        // if deleting tail node, move tail forward
        if (temp == tail) {
            PlayerNode* last = tail;
            while (last->next != tail) {
                last = last->next;
            }

            tail = tail->next;
            last->next = tail;
        }
        else {
            prev->next = temp->next;
        }

        delete temp;
        cout << "Player removed successfully.\n";
    }

    // move to next player
    void nextTurn() {
        if (!tail) {
            cout << "No players.\n";
            return;
        }

        tail = tail->next;
        cout << "Next Turn -> Player " << tail->playerID << endl;
    }

    // skip player 
    void skipPlayer() {
        if (!tail) return;

        cout << "Skipping Player " << tail->next->playerID << endl;
        tail = tail->next->next;

        cout << "Now Turn -> Player " << tail->playerID << endl;
    }

    // check winner 
    void checkWinner() {
        if (!tail) {
            cout << "No players.\n";
            return;
        }

        if (tail->next == tail) {
            cout << "Winner is Player " << tail->playerID
                << " with score " << tail->score << endl;
        }
        else {
            cout << "Game still running.\n";
        }
    }

    // display players
    void display() {
        if (!tail) {
            cout << "No players.\n";
            return;
        }

        PlayerNode* temp = tail;

        cout << "Players in Game:\n";

        do {
            cout << "PlayerID: " << temp->playerID << " | Score: " << temp->score << endl;
            temp = temp->next;
        }
        while (temp != tail);
    }
};

int main() {

    Game g;

    g.addPlayer(1, 10);
    g.addPlayer(2, 20);
    g.addPlayer(3, 30);
    g.addPlayer(4, 40);

    g.display();

    cout << "\n--- Turns ---\n";
    g.nextTurn();
    g.nextTurn();

    cout << "\n--- Skip Player ---\n";
    g.skipPlayer();

    cout << "\n--- Remove Player ---\n";
    g.removePlayer(2);
    g.display();

    cout << "\n--- Winner Check ---\n";
    g.checkWinner();

    return 0;
}