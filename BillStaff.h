#include "Bill.h"
#include "Login.h"

class BillStaff : public Bill
{
private:
    vector<Bill *> bills;

public:
    BillStaff() : Bill() {}

    void addBill(Bill *bill);
    void checkBillByNameAndCCCD(const vector<Customer> &customers, const vector<Room> &rooms, const vector<Service> &services);
    ~BillStaff();
};
