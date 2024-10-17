#ifndef STAFF_H
#define STAFF_H
#include "Person.h"
#include "Date.h"

class Staff : public Person 
{
     private:
          string ID, position, salary;
     public:
          Staff ();
          Staff (const Staff &s);
          Staff (string name, string CCCD, string gender, string phone, string add, Date DOB,
          string ID, string position, string salary);
};

#endif