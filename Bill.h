#ifndef BILL_H
#define BILL_H

#include "Service.h"
#include "Room.h"
class Date;

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
    Date checkoutDate;
    long double totalPrice;

public:
    Bill() : totalPrice(0.0), paymentStatus("Unpaid"), paymentMethod("Cash")
    {
        BillID = "";
    }

    Bill(const Customer &cust, const vector<string> &roomIDs, const Date &checkout)
        : customer(cust), roomIDs(roomIDs),  checkoutDate(checkout), totalPrice(0.0)
    {
        BillID = createID(customer);
    }
    Date getCheckoutDate() const;
    void setCheckoutDate(const Date &date);
    virtual int convert(const string &input);
    static string createID(const Customer &customer);
    void calculateTotalPrice(const Customer &customer, const vector<Room> &rooms, const vector<Service> &services, Date checkoutDate);
    std::string formatCurrency(int amount);
    void setPaymentMethod(const string &method);
    /*virtual void displayBill() const;*/

    Date inputCheckoutDate(const Date &checkInDate);
    void checkBillInfo(const string& inputUserName, const string& inputPassword, const vector<Customer>& customers, const vector<Room>& rooms, const vector<Service>& services);
    ~Bill();
};

#endif
