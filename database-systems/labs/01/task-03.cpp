#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

void deptSearch(ifstream& read, int deptNo);
int main() {
    ifstream read("employee.csv");

    if (!read.is_open()) {
        cout << "File open error\n";
        return 0;
    }
    cout << "Which department?" << endl;
    int deptNo;
    cin >> deptNo;
    deptSearch(read, deptNo);
    read.close();
    return 0;
}

void deptSearch(ifstream& read, int deptNo) {
    string header, empId, empName, joinDate, deptId, contact, salary, marital;

    getline(read, header);
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Join Date" << setw(7) << "Dept" << setw(15) << "Contact" << setw(10) << "Salary" << setw(10) << "Status" << endl;

    while (getline(read, empId, ',')) {
        getline(read, empName, ','), getline(read, joinDate, ','), getline(read, deptId, ','), getline(read, contact, ','), getline(read, salary, ','), getline(read, marital);

        if (stoi(deptId) == deptNo) cout << setw(10) << empId << setw(20) << empName << setw(15) << joinDate << setw(7) << deptId << setw(15) << contact << setw(10) << salary << setw(10) << marital << endl;

    }
}
