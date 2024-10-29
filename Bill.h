#ifndef BILL_H
#define BILL_H

#include "Function.h"
#include "Vector.h"
#include "Room.h"
#include "Service.h"
#include "Date.h"

using namespace std;

class Bill 
{
protected:
    Customer customer;          
    string BillID;          
    string paymentStatus;       
    string paymentMethod;     
    vector<string> roomIDs;    
    vector<string> services;     
    Date checkinDate;     
    Date checkoutDate;        
    double totalPrice;      

public:
    Bill();
   Bill::Bill(const Customer& cust, const vector<string>& roomIDs, const Date& checkout)
    : customer(cust), roomIDs(roomIDs), checkinDate(cust.getArrivalDate()), checkoutDate(checkout), totalPrice(0.0) 
{
    BillID = createID(customer);
}

    virtual int convert(const string& input);
    string createID(const Customer& customer);
    void calculateTotalPrice(const vector<Customer> &customers,const vector<Room> &rooms, const vector<Service> &services) ;
    void setPaymentMethod(const string& method);
    virtual void displayBill() const;

    virtual ~Bill() {}
};

#endif
