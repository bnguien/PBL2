#include <iostream>
#include <string>
#include <cctype>
#include "Person.h"
using namespace std;

bool Person::setName (string name) {
     for (int i = 0; i < name.length(); i++) {
          if (!isalpha(name[i]) || name[i] != ' ') {
               cout << "\nInvalid value! Name must have only letters!" << endl;
               return false; // Nhap ten khong hop le
          } 
     }

     this->name = name;
     return true; //Nhap ten hop le
}

string Person::getName () {
     return name;
}

bool Person::setCCCD (string CCCD) {
     if (CCCD.length() != 12) {
          cout << "\nInvalid value! CCCD must have exactly 12 digits!" << endl;
          return false; //CCCD khong du 12
     }
     for (int i = 0; i < CCCD.length(); i++) {
          if (!isdigit(CCCD[i])) {
               cout << "\nInvalid value! CCCD must have only digits!" << endl;
               return false; //CCCD co ki tu khong phai la so
          }
     }

     this->CCCD = CCCD;
     return true; //Nhap CCCD hop le
}

string Person::getCCCD () {
     return CCCD;
}

bool Person::setPhone (string phone) {
     if (phone.length() != 10) {
          cout << "\nInvalid value! Phone must have exactly 10 digits!" << endl;
          return false;
     }
     if (phone[0] != '0') {
          cout << "\nInvalid value! First number must be 0!" << endl;
          return false;
     }
     for (int i = 1; i < phone.length(); i++) {
          if (!isdigit(phone[i])) {
               cout << "\nInvalid value! Phone must have only digits!" << endl;
               return false;
          }
     }

     this->phone = phone;
     return true;
}

string Person::getPhone () {
     return phone;
}

void Person::setAdd (string add) {
     this->add = add;
}

string Person::getAdd () {
     return add;
}

void Person::setAge (int age) {
     this->age = age;
}

int Person::getAge () {
     return age;
}