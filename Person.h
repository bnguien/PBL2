#ifndef PERSON_H
#define PERSON_H

class Person {
private:
     string fullName;
     string CCCD;
     string phone;
     string add;
     int age;
public:
     Person () {}
     Person (string fullName, string CCCD, string phone, string add, int age) {
          this->fullName = fullName;
          this->CCCD = CCCD;
          this->phone = phone;
          this->add = add;
          this->age = age;
     }

     bool setFullName (const string& fullName);
     string getFullName ();
     bool setCCCD (const string& CCCD);
     string getCCCD ();
     bool setPhone (const string& phone);
     string getPhone ();
     void setAdd (const string& add);
     string getAdd ();
     bool setAge (int age);
     int getAge ();

     void splitName (const string &fullName, string &name);
     void toLowerCase (string &str);
};

#endif