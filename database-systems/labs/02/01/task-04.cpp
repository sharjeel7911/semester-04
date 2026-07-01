#include <iostream>
#include <fstream>
using namespace std;

int main() {
    string reg;
    cout << "Enter Registration Number to Delete: ";
    getline(cin, reg);

    ifstream read("data.csv");
    ofstream temp("temp.csv");

    if (!read.is_open() || !temp.is_open()) {
        cout << "File failed to open\n";
        return 0;
    }

    string regNo, name, prog, contact;
    float gpa;

    bool found = false;

    while (getline(read, regNo, ',')) {

        getline(read, name, ',');
        getline(read, prog, ',');
        read >> gpa;
        read.ignore(1, ',');
        getline(read, contact);

        if (regNo != reg) temp << regNo << "," << name << "," << prog << "," << gpa << "," << contact << "\n";
        else found = true;
    }

    read.close();
    temp.close();

    remove("data.csv");
    rename("temp.csv", "data.csv");

    if (found) cout << "\nRecord deleted successfully!\n";
    else cout << "\nStudent not found!\n";
    return 0;
}