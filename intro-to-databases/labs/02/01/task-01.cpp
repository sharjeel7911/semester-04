#include <iostream>
#include <fstream>
using namespace std;

int main() {
    cout << "Enter registration no\n";
    string reg;
    getline(cin, reg);

    ifstream read("data.csv");
    if (!read.is_open()) {
        cout << "File failed to open\n";
        return 0;
    }
    string regNo, name, prog, contact; float gpa;

    while (getline(read, regNo, ',')) {
        getline(read, name, ','), getline(read, prog, ',');
        read >> gpa;
        read.ignore(1, ',');
        getline(read, contact);
        if (regNo == reg) {
            cout << "Registration No: " << regNo << endl;
            cout << "Name: " << name << endl;
            cout << "Program: " << prog << endl;
            cout << "Gpa: " << gpa << endl;
            cout << "Contact: " << contact << endl;
            break;
        }
    }
    read.close();
    return 0;
}
