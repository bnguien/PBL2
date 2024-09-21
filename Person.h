#ifndef PERSON_H
#define PERSON_H
#include <string>
#include <iostream> 

using namespace std; 
class Person {
private:
     string fullName;
     string CCCD;
     string phone;
     string add;
     int age;
public:
     Person () {}
     Person (const Person &P) {
          this->fullName = P.fullName;
          this->CCCD = P.CCCD;
          this->phone = P.phone;
          this->add = P.add;
          this->age = P.age;
     }
     Person (string fullName, string CCCD, string phone, string add, int age) {
          this->fullName = fullName;
          this->CCCD = CCCD;
          this->phone = phone;
          this->add = add;
          this->age = age;
     }

     bool setFullName (const string& fullName);
     string getFullName () const;
     bool setCCCD (const string& CCCD);
     string getCCCD () const;
     bool setPhone (const string& phone);
     string getPhone () const;
     void setAdd (const string& add);
     string getAdd () const;
     bool setAge (int age);
     int getAge () const;

     void splitName (const string &fullName, string &name);
     void toLowerCase (string &str);
     void standardizeName ();

     ~ Person() {}
};

#endif