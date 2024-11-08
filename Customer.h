#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Staff.h"
class Date;
class Room;
class Service;
class Login;
class Bill;

using namespace std;

class Customer : public Person
{
private:
    vector<string> roomIDs;
    vector<string> serviceIDs;
    vector<string> serviceNames;
    vector<Bill> bills;
    Date arrivalDate;
    string currentFullName; // lưu tên khách hàng đã đăng nhập
public:
    Customer() : Person(),
                 serviceIDs{"None"},
                 serviceNames{"None"} {}
    Customer(const Customer &g)
        : Person(g),
          roomIDs(g.roomIDs),
          serviceIDs(g.serviceIDs),
          serviceNames(g.serviceNames),
          arrivalDate(g.arrivalDate) {}
    Customer(const Person &person,
             const vector<string> &roomIDs,
             const Date &arrivalDate,
             const vector<string> &serviceIDs,
             const vector<string> &serviceNames)
        : Person(person),
          roomIDs(roomIDs),
          arrivalDate(arrivalDate),
          serviceIDs(serviceIDs),
          serviceNames(serviceNames) {}

    void addBill(const Bill &bill) {
        bills.push_back(bill);
    }

    const vector<Bill>& getBills() const {
        return bills;
    }
    void displayCustomer(const vector<Customer> &customers, const vector<Service> &services);
    void setArrivalDate(const Date &arrivalDate);
    Date getArrivalDate() const;
    vector<string> getRoomIDs() const;
    vector<string> getServiceIDs() const;
    void setServiceIDs(const vector<string>& ids);
    vector<string> getServiceNames() const;
    void setServiceNames(const vector<string>& names);
    void setRoomIDs(const vector<string> &roomIDs);

    bool operator == (const Customer &customer) const;

    static bool saveCustomerToFile(const Customer &customer, const string &fileName);
    static vector<Customer> readFileCustomer(const string &fileName);
    void bookedRoom();
    void bookServices(const string &inputUserName, const string &inputPassword);
    void addServicesToCustomerFile(const string &inputUserName, const string &inputPassword, const vector<Service> &services, const vector<string> &serviceIDs);
    void checkInfor(const string &inputUserName, const string &inputPassword,const vector<Customer> &customers,const vector<Service> &services);
    void updateCustomerInfo(const string &inputUserName, const string &inputPassword, vector<Customer> &customers, const string &fileName) ;
    ~Customer();
};

#endif
