#include <iostream>
#include <string>
#include <cctype>
#include "Person.h"
using namespace std;

bool Person::setFullName (const string& fullName) {
     for (int i = 0; i < fullName.length(); i++) {
          if (!isalpha(fullName[i]) || fullName[i] != ' ') {
               cout << "\nInvalid value! Full name must have only letters!" << endl;
               return false; // Nhap ten khong hop le
          } 
     }

     this->fullName = fullName;
     return true; //Nhap ten hop le
}

string Person::getFullName () {
     return fullName;
}

bool Person::setCCCD (const string& CCCD) {
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

bool Person::setPhone (const string& phone) {
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

void Person::setAdd (const string& add) {
     this->add = add;
}

string Person::getAdd () {
     return add;
}

bool Person::setAge (int age) {
     if (age < 16) {
          cout << "\nThis service is not suitable for individuals under 16 years of age." << endl;
          return false; //Yeu cau nguoi dung tren 16 tuoi
     }

     this->age = age;
}

int Person::getAge () {
     return age;
}