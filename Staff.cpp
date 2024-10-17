#include "Staff.h"
#include "windows.h"
#include <unordered_set>

void changeConsoleColor(int colorCode)
{
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(hConsole, colorCode);
}

void Staff::setID (string ID)
{
     this->ID = ID;
}
string Staff::getID () const
{
     return this->ID;
}

bool Staff::setPosition (string position)
{
     static const unordered_set<string> validPositions = {"Manager", "Receptionist", "Housekeeping", "Laundry", "Server"};
     if (validPositions.find (position) != validPositions.end())
     {
          this->position = position;
          return true;
     }
     else
     {
          changeConsoleColor (12);
          cout << "The entered position '" << position << "' is not available in our hotel!" << endl;
          return true;
     }
} 
string Staff::getPosition () const
{
     return this->position;
}

void Staff::setSalary (string salary)
{
     this->salary = salary;
}
string Staff::getSalary () const
{
     return this->salary;
}