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
     Staff (string );
};

#endif