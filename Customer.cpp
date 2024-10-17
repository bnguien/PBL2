#include "Customer.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

vector<Customer> readFileCustomer(const string& fileName) {
    ifstream file(fileName);
    vector<Customer> customers;
    string line;

    if (!file.is_open()) {
        cout << "Cannot open file!" << endl;
        return customers;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string fullName, CCCD, phone, add, gender, DOBstr, roomIDStr, arrivalDateStr;
        Date DOB, arrivalDate;

        getline(ss, fullName, '|');
        getline(ss, CCCD, '|');
        getline(ss, phone, '|');
        getline(ss, add, '|');
        getline(ss, DOBstr, '|');
        DOB = Date(DOBstr); 
        getline(ss, gender, '|');

        vector<string> roomIDs;
        getline(ss, roomIDStr, '|');  
       
        stringstream roomIDStream(roomIDStr);
        string roomID;
        while (getline(roomIDStream, roomID, ',')) {
            roomIDs.push_back(roomID);
        }

        getline(ss, arrivalDateStr);
        arrivalDate = Date(arrivalDateStr);

        Person person(fullName, CCCD, phone, add, gender, DOB);
        Customer customer(person, roomIDs, arrivalDate);
        customers.push_back(customer);
    }

    file.close();
    return customers;
}


void Customer::displayCustomer(const vector<Customer>& customers) {
    for (const auto &customer : customers) {
        cout << "Full Name: " << customer.getFullName() << endl;
        cout << "CCCD: " << customer.getCCCD() << endl;
        cout << "Phone: " << customer.getPhone() << endl;
        cout << "Address: " << customer.getAdd() << endl;
        cout << "DOB: ";
        customer.getDOB().display(); 
        cout << "Gender: " << customer.getGender() << endl;
        
        cout << "Room IDs: ";
        for (const auto &room : customer.roomIDs) {
            cout << room << " ";
        }
        cout << endl;
        cout << "Arrival Date: ";
        arrivalDate.display(); 
        cout << "-----------------------------" << endl;
    }
}

Customer::~Customer() {}
