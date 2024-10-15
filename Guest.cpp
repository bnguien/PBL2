#include "Guest.h"
#include<iostream>
using namespace std;

void Guest::display() const {
    Person::display(); // Hiển thị thông tin từ lớp cha
    cout << "Guest ID: " << ID << endl;
    cout << "Status: " << status << endl;
    cout << "Room IDs: ";
    for (const auto &room : roomID) {
        cout << room << " ";
    }
    cout << endl;
    cout << "Arrival Date: ";
    arrivalDate.display(); // Hiển thị ngày đến
}
Guest::~Guest() {}
