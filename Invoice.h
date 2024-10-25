#ifndef INVOICE_H
#define INVOICE_H

#include "Date.h"
#include "Customer.h"
#include "Vector.h"
#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
using namespace std;

class Invoice 
{
    private:
        Customer customer;
        string InvoiceID;
        string PayMentStt, PayMentMethod;
        vector<string> roomIDs; 
        vector<string> services;
        Date checkinDate, checkoutDate;
        double totalPrice;
    public:
        Invoice(){};
        Invoice(const Customer& cust, const vector<string>& roomIDs, const Date& checkin)
        : customer(cust), roomIDs(roomIDs), checkinDate(checkin), totalPrice(0.0) 
    {
        checkoutDate = checkoutDate.getCurrentDate();
    }
        string createID(const Customer& customer);
        void calculateTotalPrice(const string& roomFile, const string& serviceFile);
        void setPaymentMethod(const string& method);
        void printInvoice();
        ~Invoice();
        
};
#endif