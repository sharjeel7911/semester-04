#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::swap;

inline void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    cout << "\033[2J\033[1;1H";
#endif
}

inline void pauseScreen() {
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}