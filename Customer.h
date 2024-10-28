#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Person.h"
#include "Room.h"
#include "Service.h"
#include "Login.h"
#include "Staff.h"
#include "Vector.h"
#include "Date.h"
#include "Function.h"

using namespace std;

class Customer : public Person
{
private:
    vector<string> roomIDs;    
    vector<string> serviceIDs; 
    Date arrivalDate;  
    bool checkedOut; 
    string currentFullName;//lưu tên khách hàng đã đăng nhập
public:
    Customer() : Person(), checkedOut(false) {} 
    Customer(const Customer &g) 
        : Person(g), roomIDs(g.roomIDs), 
          serviceIDs(g.serviceIDs), arrivalDate(g.arrivalDate), 
          checkedOut(g.checkedOut) {}
    Customer(const Person &person, const vector<string> &roomIDs, const Date &arrivalDate)
        : Person(person), roomIDs(roomIDs), arrivalDate(arrivalDate), checkedOut(false) {}

    void displayCustomer(const vector<Customer> &customers, const vector<Service> &services);
    void setArrivalDate(const Date &arrivalDate);
    Date getArrivalDate() const;
    vector<string> getRoomIDs() const;
    void setRoomIDs(const vector<string> &roomIDs);
    bool getCheckedOut() const;
    void setCheckedOut(bool status);

    static vector<Customer> readFileCustomer(const string &fileName);
    void bookedRoom();
    void bookServices(const string &inputUserName);
    void addServicesToCustomerFile(const string &inputUserName, const vector<Service> &services);
    void checkInfor(const string &inputUserName, const vector<Customer> &customers, const vector<Service> &services);
    void checkout(const string &inputUserName, const vector<Customer> &customers);

    ~Customer();
};

#endif
