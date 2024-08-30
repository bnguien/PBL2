#ifndef PERSON_H
#define PERSON_H

class Person {
private:
     string name;
     string CCCD;
     string phone;
     string add;
     int age;
public:
     Person () {}
     Person (string name, string CCCD, string phone, string add, int age) {
          this->name = name;
          this->CCCD = CCCD;
          this->phone = phone;
          this->add = add;
          this->age = age;
     }
     bool setName (string name);
     string getName ();
     bool setCCCD (string CCCD);
     string getCCCD ();
     bool setPhone (string phone);
     string getPhone ();
     void setAdd (string add);
     string getAdd ();
     void setAge (int age);
     int getAge ();
};
#endif