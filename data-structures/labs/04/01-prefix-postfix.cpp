#include "stack/stack.h"

bool isOperand(char);
bool isOperator(char);
int precedence(char);
char* infixToPostfix(char*, int);
char* infixToPrefix(char*, int);
bool isOperator(string);
int calculateValue(int, int, string);
int evaluateReversePolishNotation(string*, int);

int main() {
    //char arr[] = { '(', '(', '(', 'A', '+', 'B', ')', '*', '(', 'C', '-', 'E', ')', ')', '/', '(', 'F', '+', 'G', ')', ')' };
    //char arr[] = { '(', '(', 'A', '+', 'B', ')', '*', '(', 'C', '-', 'D', ')', ')', '\0' };
    //char arr[] = { '(','a','+','b','+','c' ,')' };
    //char arr[] = { '(', 'A', '+', 'B', '*', 'C', ')' };
    //char arr[] = { '(', 'A', '+', 'B', '*', 'C', '-', 'D', '/', 'E', ')' };
    //char arr[] = { 'A', '+', 'B', '*', 'C', '-', 'D' };

    char arr[] = { 'A', '+', 'B', '*', '(', 'C', '^', 'D', '-', 'E', ')', '^', '(', 'F', '+', 'G', '*', 'H', ')', '-', 'I' };
    int size = sizeof(arr) / sizeof(char);
    char* postfix = infixToPostfix(arr, size);

    cout << "Original: ";
    for (int i = 0; i < size; i++) { cout << arr[i] << " "; } cout << endl;

    cout << "Postfix: ";
    for (int i = 0; postfix[i] != '\0'; i++) { cout << postfix[i] << " "; } cout << endl;
    cout << endl;
    delete[] postfix;

    //-----------------------------------------------------------------------------------------------

    //char array[] = { '(', '(', '(', 'A', '+', 'B', ')', '*', '(', 'C', '-', 'E', ')', ')', '/', '(', 'F', '+', 'G', ')', ')' };
    //char array[] = { '(', '(', 'A', '+', 'B', ')', '*', '(', 'C', '-', 'D', ')', ')', '\0' };
    //char array[] = { '(','a','+','b','+','c' ,')' };
    //char array[] = { '(', 'A', '+', 'B', '*', 'C', ')' };

    char array[] = { 'A', '+', 'B', '*', '(', 'C', '^', 'D', '-', 'E', ')', '^', '(', 'F', '+', 'G', '*', 'H', ')', '-', 'I' };
    size = sizeof(arr) / sizeof(char);
    char* prefix = infixToPrefix(array, size);

    cout << "Original: ";
    for (int i = 0; i < size; i++) { cout << array[i] << " "; } cout << endl;

    cout << "Prefix:  ";
    for (int i = 0; prefix[i] != '\0'; i++) { cout << prefix[i] << " "; } cout << endl;
    cout << endl;
    delete[] prefix;

    //-----------------------------------------------------------------------------------------------

    //string tokens[] = { "4","13","5","/","+" };
    //string tokens[] = { "10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+" };
    //string tokens[] = { "5", "1", "2", "+", "4", "*", "+", "3", "-" }; // = 14;           
    string tokens[] = { "/" };
    cout << "Evaluation of Reverse Polish Notation: " << evaluateReversePolishNotation(tokens, sizeof(tokens) / sizeof(string));
    cout << endl;
    return 0;
}

bool isOperand(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }

bool isOperator(char c) { return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^'; }

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '^') return 3;
    return 0;
}

char* infixToPostfix(char* arr, int size) {
    MyStack<char> st(30);
    char* result = new char[size + 1];

    int k = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] == '(') { st.push(arr[i]); }
        else if (isOperand(arr[i])) { result[k++] = arr[i]; }

        else if (isOperator(arr[i])) {
            while (!st.isEmpty() && st.top() != '(' && (precedence(st.top()) >= precedence(arr[i]) && arr[i] != '^'))) {
                result[k++] = st.top();
                st.pop();
            }
            st.push(arr[i]);
        }

        else if (arr[i] == ')') {
            while (!st.isEmpty() && st.top() != '(') {
                result[k++] = st.top();
                st.pop();
            }
            if (!st.isEmpty()) st.pop(); // pop '('
        }
    }

    // pop any remaining operators in stack {NOT IMPORTANT cause stack will be discarded when function returns}
    while (!st.isEmpty()) { result[k++] = st.top(); st.pop(); }

    result[k] = '\0';
    return result;
}

char* infixToPrefix(char* arr, int size) {
    // reverse and swap brackets
    char* reversed = new char[size + 1];
    for (int i = 0; i < size; i++) {
        char ch = arr[size - 1 - i];

        if (ch == '(')      reversed[i] = ')';
        else if (ch == ')') reversed[i] = '(';
        else                reversed[i] = ch;
    }
    reversed[size] = '\0';

    // run postfix on reversed array
    MyStack<char> st(30);
    char* temp = new char[size + 1];
    int k = 0;

    for (int i = 0; i < size; i++) {
        if (reversed[i] == '(') { st.push(reversed[i]); }
        else if (isOperand(reversed[i])) { temp[k++] = reversed[i]; }

        else if (isOperator(reversed[i])) {
            while (!st.isEmpty() && st.top() != '(' && (precedence(st.top()) > precedence(reversed[i]))) {
                // important: >= converts to > which will handle both left and right assosiative
                temp[k++] = st.top();
                st.pop();
            }
            st.push(reversed[i]);
        }

        else if (reversed[i] == ')') {
            while (!st.isEmpty() && st.top() != '(') {
                temp[k++] = st.top();
                st.pop();
            }
            if (!st.isEmpty()) st.pop(); // pop '('
        }
    }

    // pop any remaining operators in stack {NOT IMPORTANT cause stack will be discarded when function returns}
    while (!st.isEmpty()) { temp[k++] = st.top(); st.pop(); }

    temp[k] = '\0';

    // reverse the result
    char* result = new char[k + 1];
    for (int i = 0; i < k; i++) { result[i] = temp[k - 1 - i]; }
    result[k] = '\0';

    delete[] reversed;
    delete[] temp;
    return result;
}

bool isOperator(string s) { return s == "+" || s == "-" || s == "*" || s == "/" || s == "%"; }

int calculateValue(int a, int b, string s) {
    if (s == "+") return a + b;
    else if (s == "-") return a - b;
    else if (s == "*") return a * b;
    else if (s == "%") return a % b;
    else if (s == "/") {
        if (b == 0) {
            cout << "Error: Division by zero\n";
            exit(1);
        }
        return a / b;
    }
    return -1;
}

int evaluateReversePolishNotation(string* tokens, int size) {
    MyStack<int> st(30);
    int result = 0;
    for (int i = 0; i < size; i++) {
        if (isOperator(tokens[i])) {
            if (st.size() < 2) {
                cout << "Error: Not enough operands\n";
                exit(1);
            }
            int b = st.pop();
            int a = st.pop();
            st.push(calculateValue(a, b, tokens[i]));
        }
        else {
            st.push(stoi(tokens[i]));
        }
    }
    return st.top();
}
