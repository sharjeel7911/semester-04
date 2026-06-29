#include <iostream>
using namespace std;

template <class T>
class Course {
public:
    virtual void duration() = 0;
};

//-------------------------------------------------------------------------------------

template <class T>
class OnlineCourse : public Course<T> {
private:
    T weeks;
    T hourPerWeek;
public:
    OnlineCourse(T, T);
    void duration();
    void area();
};

template <class T>
OnlineCourse<T>::OnlineCourse(T weeks, T hourPerWeek) {
    this->weeks = weeks;
    this->hourPerWeek = hourPerWeek;
}

template <typename T>
void OnlineCourse<T>::duration() {
    cout << "Weeks: " << weeks << ", Hours per week: " << hourPerWeek << endl;
}

template <typename T>
void OnlineCourse<T>::area() {
    cout << "This is area function of online." << endl;
}

//-------------------------------------------------------------------------------------

template <class T>
class OfflineCourse : public Course<T> {
private:
    T months;
    T hoursPerDay;
public:
    OfflineCourse(T, T);
    void duration();
    void area();
};

template <class T>
OfflineCourse<T>::OfflineCourse(T months, T hoursPerDay) {
    this->months = months;
    this->hoursPerDay = hoursPerDay;
}

template <typename T>
void OfflineCourse<T>::duration() {
    cout << "Months: " << months << ", Hours per day: " << hoursPerDay << endl;
}

template <typename T>
void OfflineCourse<T>::area() {
    cout << "This is area function of offline." << endl;
}

//-------------------------------------------------------------------------------------

int main() {
    Course<int>* cr1 = new OnlineCourse<int>(3, 40);
    Course<int>* cr2 = new OfflineCourse<int>(4, 8);

    cr1->duration();
    cr2->duration();

    cout << "\n\n";

    OnlineCourse<int>* cr3 = new OnlineCourse<int>(3, 30);
    OfflineCourse<int>* cr4 = new OfflineCourse<int>(3, 9);

    cr3->duration();
    cr4->duration();

    cout << "\n\n";

    cr3->area();
    cr4->area();

    delete cr1, delete cr2, delete cr3, delete cr4;
    return 0;
}
