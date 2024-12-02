#ifndef STAFF_H
#define STAFF_H

#include "Person.h"
#include "Graphics.h"
class Customer;
class Room;
class Service;

class Staff : public Person
{
private:
     string ID, position, salary;

public:
     Staff() {}
     Staff(const Staff &s) : Person(s), ID(s.ID), position(s.position), salary(s.salary) {}
     Staff(string fullName, string CCCD, string phone, string add, string gender, Date DOB, string ID, string position, string salary)
         : Person(fullName, CCCD, phone, add, gender, DOB), ID(ID), salary(salary)
     {
          if (position == "Manager" || position == "Receptionist" 
           || position == "Housekeeping" || position == "Laundry" || position == "Server")
          {
               this->position = position;
          }
          else
          {
               changeConsoleColor(12);
               cout << "The entered position '" << position << "' is not available in our hotel!" << endl;
               cout << "Valide position are: Manager, Receptionist, Housekeeping, Laundry, Server." << endl;
          }
     }

     void setID(const string &ID);
     string getID() const;
     bool setPosition(const string &position);
     string getPosition() const;
     void setSalary(const string &salary);
     string getSalary() const;

     static string formatSalary (const string &salary);
     static void showList (const vector<Staff> staffs);

     bool operator==(const Staff &staff) const;
     static vector<Staff> readFileStaff(const string &fileName);
     static string generateStaffID(const vector<Staff> &staffs, const string &position);
     void displayStaff();
     bool findCustomerByAttribute(const Staff &staff, const string &attributeName, const string &attributeValue);
     bool hasAccess(const Staff &staff) const ;

     void updateStaffFile(const vector<Staff> &staffs, const string &fileName);
     bool addNewStaff(Staff &newStaff);
     bool updateStaff(vector<Staff> &staffs, const int &index);
     bool removeStaff(Staff &staffToRemove);
     bool removeStaffByCCCD(const string &CCCDToRemove);

     int cusExists(const vector<Customer> &customers, const Customer &newCus);
     bool writeRemainingCus(const vector<Customer> &remainingCustomers, const string &fileName);
     bool addNewCustomer(Staff &staff);
     bool updateCustomer (Staff &staff, const string &fileName, vector<Customer> &customers);
     bool removeCustomerByCCCD(const Staff &staff,const string &CCCDToRemove);

     bool findCustomerByCCCD(const Staff &staff, const string &CCCD);
     bool findCustomerByFirstName(const Staff &staff,const string &firstName);
     bool findCustomerByLastName(const Staff &staff,const string &lastName);
     bool findCustomerByLetter(const Staff &staff,const char &letter);

     bool changeRoomStatus(const string &roomID);
     bool changeServicePrice(const string &serID, const string &price);

     static void displayCustomer (const vector<Customer> customers);

     ~Staff() {}
};

#endif