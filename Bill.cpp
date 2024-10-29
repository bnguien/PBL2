#include "Bill.h"
#include "Customer.h"
using namespace std;

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
