#include <iostream>
#include <fstream>
using namespace std;

int main() {
    string regNo, firstName, secondName, program; float gpa; string contactNo;
    cout << "Enter registration number\n";
    getline(cin, regNo);
    cout << "Enter first name\n";
    getline(cin, firstName);
    cout << "Enter second name\n";
    getline(cin, secondName);
    cout << "Enter degree\n";
    getline(cin, program);
    cout << "Enter gpa\n";
    cin >> gpa;
    cout << "Enter contact number\n";
    getline(cin, contactNo);

    ofstream write("student-info.csv", ios::app);
    if (!write.is_open()) {
        cout << "Can't open file\n";
        return 1;
    }

    write << regNo << "," << firstName << "," << secondName << "," << program << "," << gpa << "," << contactNo << "\n";
    cout << "Date saved\n";
    write.close();
    return 0;
}