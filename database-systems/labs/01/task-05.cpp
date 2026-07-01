#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int main() {
    ifstream read("employee.csv");
 
    if (!read.is_open()) {
        cout << "File open error\n";
        return 0;
    }
    string* empId = new string[15];
    string* empName = new string[15];
    string* joining = new string[15];
    string* deptId = new string[15];
    string* contact = new string[15];
    string* salary = new string[15];
    string* marital = new string[15];

    string header;
    getline(read, header);

    int i = 0;
    while (getline(read, empId[i], ',')) {
        getline(read, empName[i], ','), getline(read, joining[i], ','), getline(read, deptId[i], ','), getline(read, contact[i], ','), getline(read, salary[i], ','), getline(read, marital[i]);
        i++;
    }

    //---------------------------------------------------------
    int maxSal = stoi(salary[0]), minSal = stoi(salary[0]);
    int x = 0;
    for (int k = 1; k < i; k++) {
        if (stoi(salary[k]) > maxSal) {
            maxSal = stoi(salary[k]);
            x = k;
        }
    }

    cout << empName[x] << " has highest salary with: " << maxSal << endl;

    x = 0;
    for (int k = 1; k < i; k++) {
        if (stoi(salary[k]) < minSal) {
            minSal = stoi(salary[k]);
            x = k;
        }
    }

    cout << empName[x] << " has lowest salary with: " << minSal << endl;
    //---------------------------------------------------------

    int num = 0;
    for (int k = 0; k < i; k++) {
        string m = "Married";
        if (marital[k] == m) num++;
    }
    cout << "Total married employees: " << num << endl;

    num = 0;
    for (int k = 0; k < i; k++) {
        string m = "Single";
        if (marital[k] == m) num++;
    }
    cout << "Total single employees: " << num << endl;
    //---------------------------------------------------------

    float avg = 0;
    for (int k = 0; k < i; k++) {
        avg += stoi(salary[k]);
    }
    avg = avg / i;
    cout << "Average salary: " << avg << endl;
    delete[] empId, delete[] empName, delete[] joining, delete[] deptId, delete[] contact, delete[] salary, delete[] marital;
    read.close();
    return 0;
}
