#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "Person.h"
#include "Date.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Customer : public Person
{
private:
    vector<string> roomIDs; // Danh sách ID phòng
    Date arrivalDate;       // Ngày đến
public:
    Customer() : Person() {} // Default constructor
    Customer(const Customer &g) : Person(g)
    {
        this->roomIDs = g.roomIDs;
        this->arrivalDate = g.arrivalDate;
    }
    Customer(const Person &person, const vector<string> &roomIDs, const Date &arrivalDate)
        : Person(person), roomIDs(roomIDs), arrivalDate(arrivalDate) {}

    void displayCustomer(const vector<Customer> &customers);
    void setArrivalDate(const Date &arrivalDate);
    Date getArrivalDate() const;
    vector<string> getRoomIDs() const;
    
    void setRoomIDs(const vector<string> &roomIDs);
    void bookedRoom();
    void bookServices ();
    ~Customer();
};
#endif
