#ifndef STAFF_H
#define STAFF_H
#include "Person.h"

class Staff : public Person
{
private:
     string ID, position, salary;
public:
     Staff () {}
     Staff (const Staff &s) : Person (s), ID(s.ID), position(s.position), salary (s.salary) {}
     Staff (string fullName, string CCCD, string phone, string add, string gender, Date DOB, string ID, string position, string salary) 
                                        : Person (fullName, CCCD, phone, add, gender, DOB), ID (ID), position(position), salary (salary) {}

     void setID (const string& ID);
     string getID () const;
     bool setPosition (const string& position);
     string getPosition () const;
     void setSalary (const string& salary);
     string getSalary () const;

     static vector<Staff> readFileStaff (const string &fileName);
     void displayStaff (const vector<Staff>& staffs);

     ~ Staff () {}
};

#endif