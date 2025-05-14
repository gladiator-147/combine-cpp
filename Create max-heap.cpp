#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Student {
    int roll;
    string name;
    float grade;

    // For max-heap, compare using grade
    bool operator<(const Student& other) const {
        return grade < other.grade;
    }
};

// Display student details
void displayStudent(const Student& s) {
    cout << "Roll: " << s.roll << ", Name: " << s.name << ", Grade: " << s.grade << endl;
}

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    vector<Student> students;

    cout << "Enter student details:\n";
    for (int i = 0; i < n; ++i) {
        Student s;
        cout << "Student " << i + 1 << " Roll No: ";
        cin >> s.roll;
        cout << "Name: ";
        cin >> s.name;
        cout << "Grade: ";
        cin >> s.grade;
        students.push_back(s);
    }

    // a) Create Max-Heap
    make_heap(students.begin(), students.end());  // Max-heap based on grade
    cout << "\nTopper (next student for internship):\n";
    displayStudent(students.front());  // Root of the heap is topper

    // b) Sort students in ascending order of grades
    sort(students.begin(), students.end(), [](Student a, Student b) {
        return a.grade < b.grade;
    });

    cout << "\nStudents sorted in ascending order of grades:\n";
    for (const auto& s : students) {
        displayStudent(s);
    }

    return 0;
}
