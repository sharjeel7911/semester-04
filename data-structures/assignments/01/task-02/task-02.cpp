#include <iostream>
using namespace std;

void printArray(int arr[], int size);

int main() {
    cout << "Enter your first name: ";
    string name;
    getline(cin, name);

    int arrSize = name.size();
    int* nameArr = new int[arrSize];

    cout << "Task 0: Initial array" << endl;
    for (int i = 0; i < name.size(); i++) nameArr[i] = name[i];
    printArray(nameArr, arrSize);

    //------------------------------------------------------------------------------

    // task - 01: insert the ASCII value of your last name's first letter at position 2

    cout << "\nEnter your second name: ";
    getline(cin, name);

    nameArr[1] = name[0];

    cout << "\nTask 01: Last name first letter's ASCII at position 2 (index 1) in array" << endl;
    printArray(nameArr, arrSize);

    //------------------------------------------------------------------------------

    // task - 02: delete the element at position 3

    int* tempArr = new int[arrSize - 1];
    int k = 0;
    for (int i = 0; i < arrSize; i++) {
        if (i != 2) tempArr[k++] = nameArr[i];
    }

    arrSize--;

    delete[] nameArr;
    nameArr = tempArr;
    tempArr = nullptr;

    cout << "\nTask 02: Deleted value at position 3 (index 2)" << endl;
    cout << "New size of array: " << arrSize << endl;
    printArray(nameArr, arrSize);

    //------------------------------------------------------------------------------

    // task - 03: replace the last element with 100

    nameArr[arrSize - 1] = 100;

    cout << "\nTask 03: Changed last element to 100" << endl;
    printArray(nameArr, arrSize);

    //------------------------------------------------------------------------------
    cout << endl;
    delete[] nameArr;
    return 0;
}

void printArray(int arr[], int size) {
    cout << "Ascii: ";
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;
    cout << "Char: ";
    for (int i = 0; i < size; i++) cout << (char)arr[i];
    cout << endl;
}