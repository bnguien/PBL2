#ifndef INVOICE_H
#define INVOICE_H

#include "Function.h"
#include "Vector.h"
#include "Room.h"
#include "Service.h"
#include "Date.h"

using namespace std;

class Invoice 
{
private:
    Customer customer;          
    string invoiceID;          
    string paymentStatus;       
    string paymentMethod;     
    vector<string> roomIDs;    
    vector<string> services;     
    Date checkinDate;     
    Date checkoutDate;        
    double totalPrice;      

public:
    Invoice() : totalPrice(0.0) {}
    Invoice(const Customer& cust, const vector<string>& roomIDs, const Date& checkin, const Date& checkout)
        : customer(cust), roomIDs(roomIDs), checkinDate(checkin), checkoutDate(checkout), totalPrice(0.0)
    {
        invoiceID = createID(customer);
    }
    string createID(const Customer& customer);
    void calculateTotalPrice(const string& roomFile, const string& serviceFile);
    void setPaymentMethod(const string& method);
    void displayInvoice() const;
    ~Invoice() {}
};

#endif
