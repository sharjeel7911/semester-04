#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int main() {
    string header;
    string regNo, firstName, secondName, program; float gpa; string contactNo;
    ifstream read("student-info.csv");
    if (!read.is_open()) {
        cout << "Can't open file\n";
        return 1;
    }
    getline(read, header, '\n');
    cout << "Students with gpa higher or equal to 3.5\n";
    cout << left << setw(20) << "Name" << "Gpa\n";
    while (getline(read, regNo, ',')) {
        getline(read, firstName, ',');
        getline(read, secondName, ',');
        getline(read, program, ',');
        read >> gpa;
        read.ignore(20);
        string name = firstName + " " + secondName;
        if (gpa >= 3.5) cout << setw(20) << name << setw(4) << gpa << endl;
    }
    read.close();
    return 0;
}