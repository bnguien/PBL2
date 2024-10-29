#include "Bill.h"
#include "Customer.h"
using namespace std;

Date Bill::getCheckoutDate() const {
    return checkoutDate;
}

void Bill::setCheckoutDate(const Date& date) {
    checkoutDate = date;
}
string Bill::createID(const Customer& customer)
{
    string customerID = customer.getCCCD().substr(0, 4);
    int randomPart = rand() % 10000; 
    string BillID = "PBL-" + customerID + "-" + to_string(randomPart);
    return BillID;
}

void Bill::calculateTotalPrice(const vector<Customer>& customers, const vector<Room>& rooms, const vector<Service>& services) {
    totalPrice = 0.0;
    int daysBetween = Date::daysBetween(checkinDate, checkoutDate); 

    for (const auto& roomID : customer.getRoomIDs()) {
        for (const auto& room : rooms) {
            if (room.getID() == roomID) {
                double roomPrice = convert(room.getPrice());
                totalPrice += roomPrice * daysBetween; 
                break;
            }
        }
    }

    for (const auto& serviceID : customer.getServiceIDs()) {
        for (const auto& service : services) {
            if (service.getID() == serviceID) { 
                double servicePrice = convert(service.getPrice()); 
                totalPrice += servicePrice; 
                break;
            }
        }
    }
}

int Bill::convert(const string& input)
{
    string result = input;
    result.erase(remove(result.begin(), result.end(),'.'), result.end());

    size_t pos = result.find("/");
    if(pos!=string::npos)
    {
        result.erase(pos);
    }
    return stoi(result);
}
void Bill::inputCheckoutDate() {
    int day, month, year;

    while (true) {
        cout << "Enter check-out date (DD MM YYYY): ";
        cin >> day >> month >> year;
        Date checkoutDate(day, month, year);
        if (checkoutDate.isValid()) {  
            setCheckoutDate(checkoutDate);
            break;
        } else {
            cout << "Invalid date, please enter again." << endl;
        }
    }
}
void Bill::checkBillInfo(const string &inputUserName, const string &inputPassword, const vector<Customer> &customers) {
    for (const auto &customer : customers) {
        if (createUsername(customer.getFullName()) == inputUserName && customer.getPhone() == inputPassword) {
            cout << "Invoice information for customer: " << customer.getFullName() << endl;
            cout << "Bill ID: " << BillID << endl;
            cout << "Payment Status: " << paymentStatus << endl;
            cout << "Payment Method: " << paymentMethod << endl;
            cout << "Check-in Date: " << checkinDate.toString() << endl;
            cout << "Check-out Date: " << checkoutDate.toString() << endl;
            cout << "Total Bill: " << totalPrice << endl;
            cout << "List of booked rooms:" << endl;
            for (const auto& roomID : roomIDs) {
                cout << roomID << endl; 
            }
            cout << "List of used services:" << endl;
            for (const auto& serviceID : services) {
                cout << serviceID << endl;
            }

            return; 
        }
    }
    std::cout << "No customer found with the given username and password." << std::endl;
}
void Bill::displayBill() const {
    cout << "Bill ID: " << BillID << endl;
    cout << "Customer: " << customer.Person::getFullName() << endl;
    cout << "Check-in Date: " << checkinDate.toString() << endl;
    cout << "Check-out Date: " << checkoutDate.toString() << endl;
    cout << "Rooms: ";
    for (const auto& room : roomIDs) {
        cout << room << " ";
    }
    cout << "\nServices: ";
    for (const auto& service : services) {
        cout << service << " ";
    }
    cout << "\nTotal Price: " << totalPrice << " VND" << endl;
    cout << "Payment Method: " << paymentMethod << endl;
    cout << "Payment Status: " << paymentStatus << endl;
}

Bill::~Bill() {}
