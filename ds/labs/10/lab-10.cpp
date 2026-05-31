#include "utilities.h"

struct Node {
  int data;
  Node *next;

  Node(int d) : data(d), next(nullptr) {}
};

// -----------------------------------------------------

double pow(double, int);
void reverseString(string &, int, int);
bool isPalindrome(string &, int, int);
int gcd(int, int);
int lcm(int, int);
int totalNoOfWaysToReachNthStaircase(int);
void printList(Node *);
int reverseInt(int n, int rev = 0);
void decimalToBinary(int);

const int N = 4;
bool ratInMaze(int maze[N][N], int r, int c, int pathGrid[N][N]);

// -----------------------------------------------------

int main() {
  int choice;

  do {
    cout << "====== MENU ======\n";
    cout << "1. Power (pow)\n";
    cout << "2. Reverse String\n";
    cout << "3. Palindrome Check\n";
    cout << "4. GCD\n";
    cout << "5. LCM\n";
    cout << "6. Print List\n";
    cout << "7. Reverse Integer\n";
    cout << "8. Decimal to Binary\n";
    cout << "9. Rat in a Maze (Backtracking)\n";
    cout << "0. Exit\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {

    case 1: {
      double x;
      int y;
      cout << "Enter base and exponent: ";
      cin >> x >> y;
      cout << "Result: " << pow(x, y) << endl;
      break;
    }

    case 2: {
      string str;
      cout << "Enter string: ";
      cin >> str;
      reverseString(str, 0, str.length() - 1);
      cout << "Reversed: " << str << endl;
      break;
    }

    case 3: {
      string str;
      cout << "Enter string: ";
      cin >> str;

      if (isPalindrome(str, 0, str.length() - 1))
        cout << "Palindrome\n";
      else
        cout << "Not a Palindrome\n";
      break;
    }

    case 4: {
      int a, b;
      cout << "Enter two numbers: ";
      cin >> a >> b;
      cout << "GCD: " << gcd(a, b) << endl;
      break;
    }

    case 5: {
      int a, b;
      cout << "Enter two numbers: ";
      cin >> a >> b;
      cout << "LCM: " << lcm(a, b) << endl;
      break;
    }

    case 6: {
      int *arr = new int[5];
      cout << "Enter 5 numbers: ";
      for (int i = 0; i < 5; i++) {
        cin >> arr[i];
      }

      Node *head = new Node(arr[0]);
      Node *curr = head;

      for (int i = 1; i < 5; i++) {
        curr->next = new Node(arr[i]);
        curr = curr->next;
      }
      delete[] arr;
      arr = nullptr;

      printList(head);
      cout << endl;
      break;
    }
    case 7: {
      int n;
      cout << "Enter integer: ";
      cin >> n;
      cout << "Reversed: " << reverseInt(n) << endl;
      break;
    }

    case 8: {
      int n;
      cout << "Enter number: ";
      cin >> n;
      cout << "Binary: ";
      decimalToBinary(n);
      cout << endl;
      break;
    }

    case 9: {
      int maze[N][N] = {{1, 0, 0, 0}, {1, 1, 0, 1}, {0, 1, 0, 0}, {1, 1, 1, 1}};

      int pathGrid[N][N] = {
          {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

      cout << "Initial Maze Map:\n";
      for (int r = 0; r < N; r++) {
        cout << "  ";
        for (int c = 0; c < N; c++) {
          cout << (maze[r][c] == 1 ? ". " : "# ");
        }
        cout << endl;
      }

      cout << "\nFinding path using backtracking...\n";
      if (ratInMaze(maze, 0, 0, pathGrid)) {
        cout << ">> Clear Path Discovered:\n\n";

        for (int r = 0; r < N; r++) {
          cout << "  ";
          for (int c = 0; c < N; c++) {
            if (pathGrid[r][c] == 1) {
              if (r == N - 1 && c == N - 1)
                cout << "* ";
              else if (c + 1 < N && pathGrid[r][c + 1] == 1)
                cout << "→ ";
              else if (r + 1 < N && pathGrid[r + 1][c] == 1)
                cout << "↓ ";
              else
                cout << "R ";
            } else {
              cout << "  ";
            }
          }
          cout << endl;
        }
      } else {
        cout << "No escape path exists for this maze.\n";
      }
      cout << endl;
      break;
    }

    case 0:
      cout << "Exiting program...\n";
      break;

    default:
      cout << "Invalid choice!\n";
    }

  } while (choice != 0);

  return 0;
}

double pow(double x, int y) {
  // base case
  if (y == 0)
    return 1;

  if (y > 0)
    return x * pow(x, y - 1);
  return (1 / x) * pow(x, y + 1);
}

void reverseString(string &str, int start, int end) {
  // base case
  if (start >= end)
    return;

  swap(str[start], str[end]);
  reverseString(str, start + 1, end - 1);
}

bool isPalindrome(string &str, int start, int end) {
  // base case
  if (start >= end)
    return true;

  if (str[start] != str[end])
    return false;

  return isPalindrome(str, start + 1, end - 1);
}

// gcd formula = gcd(a, b) = gcd(b, a % b)
int gcd(int a, int b) {
  // base case
  if (b == 0)
    return a;

  return gcd(b, a % b);
}

// lcm formula = (a ∗ b) / GCD(a, b)
int lcm(int j, int k) { return (j * k) / gcd(j, k); }

int totalNoOfWaysToReachNthStaircase(int n) {
  if (n == 0 || n == 1)
    return 1; // base case
  return totalNoOfWaysToReachNthStaircase(n - 1) +
         totalNoOfWaysToReachNthStaircase(n - 2);
}

void printList(Node *head) {
  // base case
  if (head == nullptr)
    return;

  cout << head->data << " ";
  printList(head->next);
}

int reverseInt(int n, int rev) {
  // base case
  if (n == 0)
    return rev;

  return reverseInt(n / 10, rev * 10 + (n % 10));
}

void decimalToBinary(int n) {
  // base case
  if (n == 0)
    return;

  decimalToBinary(n / 2);
  cout << n % 2;
}

bool ratInMaze(int maze[N][N], int r, int c, int pathGrid[N][N]) {
  // 1. boundary & wall validation
  if (r < 0 || r >= N || c < 0 || c >= N || maze[r][c] == 0) {
    return false;
  }

  // 2. destination check (goal reached)
  if (r == N - 1 && c == N - 1) {
    pathGrid[r][c] = 1;
    return true;
  }

  // 3. tentatively mark this cell as part of the path
  pathGrid[r][c] = 1;

  // 4. try moving Right
  if (ratInMaze(maze, r, c + 1, pathGrid)) {
    return true;
  }

  // 5. try moving Down
  if (ratInMaze(maze, r + 1, c, pathGrid)) {
    return true;
  }

  // 6. backtrack: unmark this cell if neither choice worked
  pathGrid[r][c] = 0;
  return false;
}