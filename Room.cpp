#include <iostream>
#include <string>
#include <cctype>
#include "Room.h"
using namespace std;

void Room::setID (const string &ID) {
     this->ID = ID;
}
string Room::getID () {
     return ID;
}

bool Room::setType (const string &type) {
     if (type == "Single" || type == "Double" || type == "Suite" || type == "Standard" || type == "Delux") {
          this->type = type;
          return 1; //Nhap dung loai phong
     }
     else return 0; //Nhap sai loai phong, can nhap lai
}
string Room::getType () {
     return type;
}

void Room::setPrice (const string &price) {
     this->price = price;
}
string Room::getPrice () {
     return price;
}

bool Room::setStatus (const string &status) {
     if (status == "booked" || status == "unbooked") {
          this->status = status;
          return 1; //thiet lap trang thai thanh cong
     }
     else return 0; //sai dinh dang trang thai, can nhap lai
}
string Room::getStatus () {
     return status;
}