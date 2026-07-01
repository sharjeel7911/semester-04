#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream write("data.csv", ios::app);

    if (!write.is_open()) {
        cout << "File failed to open\n";
        return 0;
    }

    string regNo, name, prog, contact;
    float gpa;

    cout << "Enter Registration No: ";
    getline(cin, regNo);

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Program: ";
    getline(cin, prog);

    cout << "Enter GPA: ";
    cin >> gpa;
    cin.ignore();

    cout << "Enter Contact: ";
    getline(cin, contact);

    write << regNo << "," << name << "," << prog << "," << gpa << "," << contact << "\n";

    cout << "\nStudent record added successfully!\n";
    write.close();
    return 0;
}