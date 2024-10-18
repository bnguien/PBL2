#ifndef PERSON_H
#define PERSON_H
#include "Date.h"
#include <string>
#include <iostream> 

using namespace std; 
class Person {
private:
     string fullName;
     string CCCD;
     string phone;
     string add;
     string gender;
     Date DOB;
public:
     Person () {}
     Person (const Person &P):fullName(P.fullName), CCCD(P.CCCD), phone(P.phone), add(P.add), gender(P.gender), DOB(P.DOB){}
     Person (string fullName, string CCCD, string phone, string add,string gender, Date DOB) {
          this->fullName = fullName;
          this->CCCD = CCCD;
          this->phone = phone;
          this->add = add;
          this->gender=gender;
          this->DOB = DOB;
     }

     bool setFullName (const string& fullName);
     string getFullName () const;
     bool setCCCD (const string& CCCD);
     string getCCCD () const;
     bool setPhone (const string& phone);
     string getPhone () const;
     void setAdd (const string& add);
     string getAdd () const;
     void setGender (const string& gender);
     string getGender() const;
     bool setDOB (const Date& DOB);
     Date getDOB () const;

     void splitName (const string &fullName, string &name);
     void toLowerCase (string &str);
     void standardizeName ();
     static vector<Person> readFilePerson(const string& fileName);
     static void displayPerson(const vector<Person>& people);
     ~ Person() {}
};

#endif