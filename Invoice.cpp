#include "Invoice.h"
#include "Customer.h"
using namespace std;

string Invoice::createID(const Customer& customer)
{
    string customerID = customer.getCCCD().substr(0, 4);
    int randomPart = rand() % 10000; 
    string invoiceID = "PBL-" + customerID + "-" + to_string(randomPart);
    return invoiceID;
}

/*void Invoice::calculateTotalPrice(const string& roomFile, const string& serviceFile) {
    ifstream roomData(roomFile);
    ifstream serviceData(serviceFile);
    string line;
    double roomTotal = 0.0;
    double serviceTotal = 0.0;

    while (getline(roomData, line)) {
        size_t pos = line.find('|');
        string roomID = line.substr(0, pos);
        double roomPrice = stod(line.substr(pos + 1, line.find('|', pos + 1) - pos - 1)); 

        for (const auto& id : roomIDs) {
            if (id == roomID) {
                roomTotal += roomPrice;
                break;
            }
        }
    }
    roomData.close();

    while (getline(serviceData, line)) {
        size_t pos = line.find('|');
        string serviceName = line.substr(0, pos);
        double servicePrice = stod(line.substr(pos + 1, line.find('|', pos + 1) - pos - 1)); 

        for (const auto& service : customer.getServices()) {
            if (service == serviceName) {
                serviceTotal += servicePrice;
                break;
            }
        }
    }
    serviceData.close();
    totalPrice = roomTotal + serviceTotal;
}*/

void Invoice::displayInvoice() const {
    cout << "Invoice ID: " << invoiceID << endl;
    cout << "Customer: " << customer.getFullName() << endl;
    cout << "Check-in Date: " << checkinDate.toString() << endl;
    cout << "Check-out Date: " << checkoutDate.toString() << endl;
    cout << "Total Price: " << totalPrice << endl;
    cout << "Payment Method: " << paymentMethod << endl;
}

Invoice::~Invoice() {}
