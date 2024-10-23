#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "Person.h"
#include "Date.h"
#include "Service.h"
#include "Room.h"
#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Customer : public Person
{
    private: 
        vector<string> roomIDs; //Danh sách ID phòng
        vector<string> serviceIDs; //Danh sách dịch vụ
        Date arrivalDate; //Ngày đến
        bool checkedOut;   
    public:
        Customer(): Person() {} // Default constructor
        Customer(const Customer &g) : Person(g), roomIDs(g.roomIDs), 
                                      arrivalDate(g.arrivalDate), checkedOut(g.checkedOut) {}
         Customer(const Person& person, const vector<string>& roomIDs, const Date& arrivalDate) 
        : Person(person), roomIDs(roomIDs), arrivalDate(arrivalDate), checkedOut(false) {}
        
        void displayCustomer(const vector<Customer>& customers, const vector<Service>& services);
        void setArrivalDate(const Date& arrivalDate);
        Date getArrivalDate () const;
        vector<string> getRoomIDs() const;
        void setRoomIDs(const vector<string>& roomIDs);
        bool getCheckedOut() const;
        void setCheckedOut(bool status);
        
        static vector<Customer> readFileCustomer(const string& fileName);
        void bookedRoom();
        void bookServices();
        void checkInfor(const string& inputUserName, const vector<Customer>& customers, const vector<Service>& services);
        void checkout(const string& inputUserName, const vector<Customer>& customers);
        ~Customer();
};
#endif
