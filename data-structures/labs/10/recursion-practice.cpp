#include <iostream>
#include <vector>
#include <string>

using namespace std;

// --- global constants ---
const int MAZE_SIZE = 4;

// --- data structures ---
struct Node {
    int data;
    Node* next;
    Node(int d) : data(d), next(nullptr) {}
};

// --- recursive function declarations ---
int evaluateSeries(int n);
int sumUptoN(int n);
int getNoOfDigits(int n);
int getSumOfDigits(int n);
void decimalToBinary(int n);
void print1ToN(int n);
void printNTo1(int n);
int factorial(int n);
int fibonacci(int n);
int fibonacciSum(int a, int b, int n);
void reverseArray(vector<int> &vec, int left, int right);
bool isPalindrome(const string &str, int left, int right);
int evaluatePower(int base, int exp, int result = 1);
int countOccurrences(int array[], int target, int currentCount, int index, int size);
int binarySearchRecursive(int array[], int target, int left, int right);
void pyramidPattern(int n, int currentX, int originalX, bool ascending = true);
void printListRecursive(Node* head);
bool ratInMaze(int maze[MAZE_SIZE][MAZE_SIZE], int r, int c, int pathGrid[MAZE_SIZE][MAZE_SIZE]);

// --- application entry driver ---
int main() {
    int choice;

    do {
        cout << "\n================= UTILITY RECURSION MENU =================\n";
        cout << "1.  Evaluate Nth custom series node\n";
        cout << "2.  Sum of numbers from 1 to N\n";
        cout << "3.  Count number of digits in an integer\n";
        cout << "4.  Sum of digits in an integer\n";
        cout << "5.  Convert decimal to binary representation\n";
        cout << "6.  Print numbers sequence (1 to N & N to 1)\n";
        cout << "7.  Calculate factorial of N\n";
        cout << "8.  Evaluate Nth fibonacci & custom sum sequence\n";
        cout << "9.  Reverse elements of a vector\n";
        cout << "10. Check if string reads as a palindrome\n";
        cout << "11. Calculate base raised to power exponent\n";
        cout << "12. Count occurrences of element in data array\n";
        cout << "13. Execute recursive binary search algorithm\n";
        cout << "14. Draw geometric counting pyramid pattern\n";
        cout << "15. Generate dynamic single linked list and print\n";
        cout << "16. Run rat in a maze pathfinding solver\n";
        cout << "0.  Exit program\n";
        cout << "==========================================================\n";
        cout << "Enter your selection index: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int n;
                cout << "enter position term for custom series sequence: ";
                cin >> n;
                if (n <= 0) cout << "error: value must be greater than zero.\n";
                else cout << "value at sequence index " << n << " is: " << evaluateSeries(n) << endl;
                break;
            }
            case 2: {
                int n;
                cout << "enter ceiling target integer N: ";
                cin >> n;
                cout << "sum from 1 up to " << n << " is: " << sumUptoN(n) << endl;
                break;
            }
            case 3: {
                int n;
                cout << "enter any target integer value: ";
                cin >> n;
                cout << "total number of digits present: " << getNoOfDigits(n) << endl;
                break;
            }
            case 4: {
                int n;
                cout << "enter target integer sequence: ";
                cin >> n;
                cout << "sum of component digits evaluates to: " << getSumOfDigits(n) << endl;
                break;
            }
            case 5: {
                int n;
                cout << "enter base 10 positive decimal value: ";
                cin >> n;
                cout << "binary representation bitstream: ";
                if (n == 0) cout << "0";
                else decimalToBinary(n);
                cout << endl;
                break;
            }
            case 6: {
                int n;
                cout << "enter ceiling index constraint N: ";
                cin >> n;
                cout << "ascending sequence tracking forward: ";
                print1ToN(n);
                cout << "\ndescending sequence tracking backward: ";
                printNTo1(n);
                cout << endl;
                break;
            }
            case 7: {
                int n;
                cout << "enter non-negative factorial target number: ";
                cin >> n;
                if (n < 0) cout << "invalid configuration: input cannot be negative.\n";
                else cout << "factorial outcome evaluates to: " << factorial(n) << endl;
                break;
            }
            case 8: {
                int n;
                cout << "enter sequence position reference N: ";
                cin >> n;
                cout << "calculated position node element value: " << fibonacci(n) << endl;
                cout << "full computed sequence stream path: ";
                for (int i = 0; i <= n; i++) cout << fibonacci(i) << " ";
                cout << "\naggregated summation total for path sequence: " << fibonacciSum(0, 1, n + 1) - 1 << endl;
                break;
            }
            case 9: {
                vector<int> data = {10, 20, 30, 40, 50};
                cout << "original raw collection layout: ";
                for (int v : data) cout << v << " ";
                reverseArray(data, 0, data.size() - 1);
                cout << "\nmodified configuration post recursive swap operation: ";
                for (int v : data) cout << v << " ";
                cout << endl;
                break;
            }
            case 10: {
                string inputStr;
                cout << "enter single continuous string array for check: ";
                cin >> inputStr;
                if (isPalindrome(inputStr, 0, inputStr.length() - 1)) cout << "result confirmed: true palindrome.\n";
                else cout << "result confirmed: sequence is non-palindromic.\n";
                break;
            }
            case 11: {
                int base, exp;
                cout << "enter base value and target exponent power sequence: ";
                cin >> base >> exp;
                if (exp < 0) cout << "error: utility implementation optimized for positive indices.\n";
                else cout << "evaluation product outcome: " << evaluatePower(base, exp) << endl;
                break;
            }
            case 12: {
                int referenceData[] = {1, 4, 2, 7, 4, 9, 4, 3};
                int targetElement, totalSize = 8;
                cout << "array sample pool values: 1 4 2 7 4 9 4 3\nenter search key element: ";
                cin >> targetElement;
                cout << "total calculated instances in collection: " << countOccurrences(referenceData, targetElement, 0, 0, totalSize) << endl;
                break;
            }
            case 13: {
                int sortedData[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
                int targetKey, elementsCount = 10;
                cout << "sorted pool data: 2 5 8 12 16 23 38 56 72 91\nenter value to locate via binary algorithm: ";
                cin >> targetKey;
                int locationIndex = binarySearchRecursive(sortedData, targetKey, 0, elementsCount - 1);
                if (locationIndex != -1) cout << "match identified at storage container slot position: " << locationIndex << endl;
                else cout << "requested key missing from internal sorted collection indexes.\n";
                break;
            }
            case 14: {
                int startingVal, variationOffset;
                cout << "enter seed root base value (N): ";
                cin >> startingVal;
                cout << "enter upper ceiling step iteration increment threshold (X): ";
                cin >> variationOffset;
                cout << "--- rendering geometric layout output sequence ---\n";
                pyramidPattern(startingVal, 0, variationOffset, true);
                break;
            }
            case 15: {
                int dataInputs[5];
                cout << "enter 5 integers sequentially to convert into list form: ";
                for (int i = 0; i < 5; i++) cin >> dataInputs[i];
                Node* listHead = new Node(dataInputs[0]);
                Node* currentPointer = listHead;
                for (int i = 1; i < 5; i++) {
                    currentPointer->next = new Node(dataInputs[i]);
                    currentPointer = currentPointer->next;
                }
                cout << "verifying linear node storage layout via recursive display: ";
                printListRecursive(listHead);
                cout << endl;
                while (listHead != nullptr) {
                    Node* operationalTemp = listHead->next;
                    delete listHead;
                    listHead = operationalTemp;
                }
                break;
            }
            case 16: {
                int localMazeGrid[MAZE_SIZE][MAZE_SIZE] = {
                    {1, 0, 0, 0},
                    {1, 1, 0, 1},
                    {0, 1, 0, 0},
                    {1, 1, 1, 1}
                };
                int functionalPathTrackingGrid[MAZE_SIZE][MAZE_SIZE] = {0};
                cout << "initiating operational pathfinding engine configuration matrix...\n";
                if (ratInMaze(localMazeGrid, 0, 0, functionalPathTrackingGrid)) {
                    cout << "solution matrix located:\n";
                    for (int r = 0; r < MAZE_SIZE; r++) {
                        for (int c = 0; c < MAZE_SIZE; c++) {
                            cout << functionalPathTrackingGrid[r][c] << " ";
                        }
                        cout << endl;
                    }
                } else {
                    cout << "no path identified connecting to escape objective.\n";
                }
                break;
            }
            case 0:
                cout << "shutting down modules. execution terminated smoothly.\n";
                break;
            default:
                cout << "invalid index selection mapping. reference valid operations list.\n";
        }
    } while (choice != 0);

    return 0;
}

// --- recursive function logic block definitions ---

// custom linear recurrence mapping three base nodes
int evaluateSeries(int n) {
    if (n == 1) return 1; // custom base case node 1
    if (n == 2) return 0; // custom base case node 2
    if (n == 3) return 7; // custom base case node 3
    return evaluateSeries(n - 1) + evaluateSeries(n - 2) + evaluateSeries(n - 3);
}

// continuous integer range accumulator function
int sumUptoN(int n) {
    if (n <= 0) return 0; // functional floor boundary termination
    return n + sumUptoN(n - 1);
}

// identifies baseline character width magnitude counts of tracking variables
int getNoOfDigits(int n) {
    if (n < 0) n = -n; // absolute value transformation context rule
    if (n == 0) return 0; // structural boundary floor baseline
    return 1 + getNoOfDigits(n / 10);
}

// splits unit parameters to isolate totals
int getSumOfDigits(int n) {
    if (n < 0) n = -n; // safe parsing formatting rule
    if (n == 0) return 0; // base case exit flag
    return (n % 10) + getSumOfDigits(n / 10);
}

// strips decimal integer value strings into binary bit array indicators
void decimalToBinary(int n) {
    if (n == 0) return; // calculation floor boundary limit
    decimalToBinary(n / 2);
    cout << n % 2; // print execution streams post unwind process
}

// loops sequential increments utilizing the program execution call stack
void print1ToN(int n) {
    if (n <= 0) return; // base step exit anchor
    print1ToN(n - 1);
    cout << n << " ";
}

// outputs descending variable sequences
void printNTo1(int n) {
    if (n <= 0) return; // base step exit anchor
    cout << n << " ";
    printNTo1(n - 1);
}

// processes standard sequential value chain factor multiplication
int factorial(int n) {
    if (n == 0 || n == 1) return 1; // base definition boundary locks
    return n * factorial(n - 1);
}

// standard implementation evaluating index positions
int fibonacci(int n) {
    if (n <= 0) return 0; // safety index floor zero check
    if (n == 1) return 1; // standard index point reference value 1
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// tail recursive algorithm accumulator mapping structural trends
int fibonacciSum(int a, int b, int n) {
    if (n == 0) return a; // sequence loop constraint flag
    return fibonacciSum(b, a + b, n - 1);
}

// double index parameter step switcher mechanism
void reverseArray(vector<int> &vec, int left, int right) {
    if (left >= right) return; // collision cross reference check
    int swapHolder = vec[left];
    vec[left] = vec[right];
    vec[right] = swapHolder;
    reverseArray(vec, left + 1, right - 1);
}

// symmetric mirrored balance parser
bool isPalindrome(const string &str, int left, int right) {
    if (left >= right) return true; // match checks completed successfully
    if (str[left] != str[right]) return false; // mismatch exception handling exit point
    return isPalindrome(str, left + 1, right - 1);
}

// standard recursive exponential multiplication utility
int evaluatePower(int base, int exp, int result) {
    if (exp == 0) return result; // zero index evaluation override logic
    return evaluatePower(base, exp - 1, result * base);
}

// loops target array sequence tracking matching value signatures
int countOccurrences(int array[], int target, int currentCount, int index, int size) {
    if (index == size) return currentCount; // operational pool completely parsed
    if (array[index] == target) currentCount++; // trace point verification matches criteria
    return countOccurrences(array, target, currentCount, index + 1, size);
}

// standard binary midpoint tracking lookup strategy
int binarySearchRecursive(int array[], int target, int left, int right) {
    if (left > right) return -1; // collection data range search completed without identifying matches
    int calculatedMidpoint = left + (right - left) / 2;
    if (array[calculatedMidpoint] == target) return calculatedMidpoint; // match confirmed
    if (array[calculatedMidpoint] > target) {
        return binarySearchRecursive(array, target, left, calculatedMidpoint - 1); // target lower range block shift
    }
    return binarySearchRecursive(array, target, calculatedMidpoint + 1, right); // target upper range block shift
}

// custom visual structural array sequence tracking print configuration
void pyramidPattern(int n, int currentX, int originalX, bool ascending) {
    // prints component items starting from baseline N up to position offset limit
    for (int i = 0; i <= currentX; i++) {
        cout << (n + i) << " ";
    }
    cout << endl;

    if (ascending) {
        if (currentX < originalX) {
            pyramidPattern(n, currentX + 1, originalX, true); // drill up path sequence step
        } else {
            pyramidPattern(n, currentX - 1, originalX, false); // pivot downward processing trace phase
        }
    } else {
        if (currentX >= 0) {
            pyramidPattern(n, currentX - 1, originalX, false); // continue descending loop sequence tracking
        }
    }
}

// single linked data collection print engine
void printListRecursive(Node* head) {
    if (head == nullptr) return; // dynamic address link list sequence completion point
    cout << head->data << " ";
    printListRecursive(head->next);
}

// classic matrix backtracking routing application step tracker
bool ratInMaze(int maze[MAZE_SIZE][MAZE_SIZE], int r, int c, int pathGrid[MAZE_SIZE][MAZE_SIZE]) {
    // grid edge and obstacle block validation criteria mapping rules
    if (r < 0 || r >= MAZE_SIZE || c < 0 || c >= MAZE_SIZE || maze[r][c] == 0) {
        return false;
    }
    // matching destination objective tracking coordinate coordinates confirmed
    if (r == MAZE_SIZE - 1 && c == MAZE_SIZE - 1) {
        pathGrid[r][c] = 1;
        return true;
    }

    pathGrid[r][c] = 1; // execute tentative route map trace selection step

    if (ratInMaze(maze, r, c + 1, pathGrid)) return true; // explore horizontal path options rightward
    if (ratInMaze(maze, r + 1, c, pathGrid)) return true; // explore vertical path options downward

    pathGrid[r][c] = 0; // backtrack protocol triggered: erase step configuration footprints
    return false;
}
