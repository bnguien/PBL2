#include <iostream>
#include <string>
#include <cctype>
#include<vector>
#include<sstream>
#include<fstream>
#include "Room.h"
using namespace std;

void Room::setID (const string &ID) {
     this->ID = ID;
}
string Room::getID () const {
     return ID;
}

bool Room::setType (const string &type) {
     if (type == "Single" || type == "Double" || type == "Suite" || type == "Standard" || type == "Delux") {
          this->type = type;
          return 1; //Nhap dung loai phong
     }
     else return 0; //Nhap sai loai phong, can nhap lai
}
string Room::getType () const {
     return type;
}

void Room::setPrice (const string &price) {
     this->price = price;
}
string Room::getPrice () const {
     return price;
}

bool Room::setStatus (const string &status) {
     if (status == "Unavailable" || status == "Available") {
          this->status = status;
          return 1; //thiet lap trang thai thanh cong
     }
     else return 0; //sai dinh dang trang thai, can nhap lai
}
string Room::getStatus () const {
     return status;
}

bool Room::checkAvailable ()
{
     if (this->status == "Available")
          return true;
     else if (this->status == "Unavailable")
          return false;
     else 
     {
          cout << "\nInvalid information!" << endl;
          return false;
     }
}

vector<Room> readFileRoom(const string& fileName) {
    ifstream file(fileName);
    vector<Room> rooms;
    string line;

    if (!file.is_open()) {
        cout << "Cannot open file!" << endl;
        return rooms;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string ID, type, price, status;
        
        getline(ss, ID, '|');
        getline(ss, type, '|');
        getline(ss, price, '|');
        getline(ss, status, '|');

        Room R(ID, type, price, status);
        rooms.push_back(R);
    }

    file.close();
    return rooms;
}
void printRoom(const vector<Room>& rooms) {
    for (const auto& room : rooms) {
        cout << "ID: " << room.getID() << endl;
        cout << "Type: " << room.getType() << endl;
        cout << "Price(VND/night): " << room.getPrice() << endl;
        cout << "Status: " << room.getStatus() << endl;
        cout << "-----------------------------" << endl;
    }
}