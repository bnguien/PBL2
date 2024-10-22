#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctype.h>
#include <sstream>
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

string Person::getFullName () const {
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

string Person::getCCCD () const {
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

string Person::getPhone () const {
     return phone;
}

void Person::setAdd (const string& add) {
     this->add = add;
}

string Person::getAdd () const{
     return add;
}

void Person::setGender (const string& gender){
     this->gender=gender;
}

string Person::getGender () const{
     return gender;
}

bool Person::setDOB(const Date& dob) {
    this->DOB = dob;
    return true;
}

Date Person::getDOB() const {
    return DOB;
}


string Person::standardizeString (const string& input) {
     string res = "";
     stringstream ss (input);
     string token;
     while (ss >> token) {
          res += toupper (token[0]);
          for (size_t i = 1; i < token.length(); i++) {
               res += tolower (token[i]);
          }
          res += " ";
     }
     
     res.erase(res.length() - 1);
     return res;
}
vector<Person> readFilePerson(const string& fileName) {
    ifstream file(fileName);
    vector<Person> people;
    string line;

    if (!file.is_open()) {
        cout << "Cannot open file!" << endl;
        return people;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string fullName, CCCD, phone, add,gender, DOBstr;
        Date DOB;

        getline(ss, fullName, '|');
        getline(ss, CCCD, '|');
        getline(ss, phone, '|');
        getline(ss, add, '|');
        getline(ss, DOBstr, '|');
        DOB = Date(DOBstr);
        getline(ss, gender, '|');

        Person person(fullName, CCCD, phone, add,gender,DOB);
        people.push_back(person);
    }

    file.close();
    return people;
}
void Person::displayPerson(const vector<Person>& people) {
    for (const auto& person : people) {
        cout << "Full Name: " << person.getFullName() << endl;
        cout << "CCCD: " << person.getCCCD() << endl;
        cout << "Phone: " << person.getPhone() << endl;
        cout << "Address: " << person.getAdd() << endl;
        cout << "DOB: ";
        person.getDOB().display();
        cout<<"Gender: "<<person.getGender()<<endl;
        cout << "-----------------------------" << endl;
    }
}