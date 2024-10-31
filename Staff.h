#ifndef STAFF_H
#define STAFF_H

#include "Person.h"
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
         : Person(fullName, CCCD, phone, add, gender, DOB), ID(ID), position(position), salary(salary) {}

     void setID(const string &ID);
     string getID() const;
     bool setPosition(const string &position);
     string getPosition() const;
     void setSalary(const string &salary);
     string getSalary() const;

     bool operator ==(const Staff& staff) const; 
     static vector<Staff> readFileStaff(const string &fileName);
     static string generateStaffID(const vector<Staff> &staffs, const string &position);
     void displayStaff(const vector<Staff> &staffs);

     void updateStaffFile(const vector<Staff> &staffs, const string &fileName);
     void addNewStaff(Staff &newStaff);
     void removeStaff(Staff &staffToRemove);
     void removeStaffByCCCD(const string &CCCDToRemove);
     
     void updateCustomerFile(const vector<Staff> &staffs, const string &fileName);
     void addNewCustomer(Customer &newCus);
     void removeCustomer(Customer &CusToRemove);
     void removeCustomerByCCCD(const string &CCCDToRemove);

     bool changeRoomStatus(const string &roomID); //true: doi thanh cong, false: gap loi

     void updateServiceFile(const vector<Service> &services, const string &fileName);
     void addNewService(Service &newService);
     void removeService(const string ID);
     ~Staff() {}
};


#endif