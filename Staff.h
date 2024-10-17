#ifndef STAFF_H
#define STAFF_H
#include "Person.h"
#include <iostream>
using namespace std;

class Staff : public Person
{
private:
     string ID, position, salary;
public:
     Staff ();
     Staff (const Staff &s) : Person (s), ID(s.ID), position(s.position), salary (s.salary) {}
     Staff (string fullName, string CCCD, string phone, string add, string gender, Date DOB, string ID, string position, string salary) 
                                        : Person (fullName, CCCD, phone, add, gender, DOB), ID (ID), position(position), salary (salary) {}

     void setID (string ID);
     string getID () const;
     bool setPosition (string position);
     string getPosition () const;
     void setSalary (string salary);
     string getSalary () const;

     ~ Staff () {}
};

#endif