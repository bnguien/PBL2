#include "Customer.h"
#include "Room.h"
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

void saveCustomerToFile(const Customer& customer, const string& fileName) {
    ofstream file(fileName, ios::app); // Mở file trong chế độ append

    if (!file.is_open()) {
        cout << "Cannot open customer file!" << endl;
        return;
    }

    // Lưu thông tin khách hàng vào file
    file << customer.getFullName() << "|"
         << customer.getCCCD() << "|"
         << customer.getPhone() << "|"
         << customer.getAdd() << "|"
         << customer.getDOB().toString() << "|"  // Đảm bảo lớp Date có hàm toString()
         << customer.getGender() << "|";

    // Lưu Room IDs (các phòng mà khách hàng đã đặt)
    for (size_t i = 0; i < customer.roomIDs.size(); ++i) {
        file << customer.roomIDs[i];
        if (i < customer.roomIDs.size() - 1) {
            file << ",";  // Ngăn cách các Room ID bằng dấu phẩy
        }
    }

    file << "|" << customer.getArrivalDate().toString() << endl;  // Ngày đến
    file.close();
}

void Customer::bookedRoom()
{
    string fileRoom = "Room.txt"; 
    vector<Room> rooms = readFileRoom(fileRoom);

    cout << "List of hotel rooms:" << endl;
    printRoom(rooms);
    cout << "-------------------------------------" << endl;
    cout << "Enter the room ID you want to book: ";
    
    string roomID;
    cin >> roomID;

    bool roomFound = false;
    for (auto &room : rooms) {
        if (room.getID() == roomID) {
            roomFound = true;
            if (room.checkAvailable()) {
                cout << "Room is available. Proceed with booking." << endl;

                string fullName, CCCD, phone, add, gender, DOBstr;
                cout << "Enter your full name: ";
                cin.ignore();
                getline(cin, fullName);

                cout << "Enter your CCCD: ";
                getline(cin, CCCD);

                cout << "Enter your phone number: ";
                getline(cin, phone);

                cout << "Enter your address: ";
                getline(cin, add);

                cout << "Enter your gender: ";
                getline(cin, gender);

                cout << "Enter your date of birth (YYYY-MM-DD): ";
                getline(cin, DOBstr);
                Date DOB(DOBstr); 

                string arrivalDateStr;
                cout << "Enter your arrival date (YYYY-MM-DD): ";
                getline(cin, arrivalDateStr);
                Date arrivalDate(arrivalDateStr);

               Person person(fullName, CCCD, phone, add, gender, DOB);
                vector<string> roomIDs = {roomID}; 
                Customer newCustomer(person, roomIDs, arrivalDate);

                room.setStatus("Unavailable");

                string customerFile = "Customer.txt"; 
                saveCustomerToFile(newCustomer, customerFile);

                cout << "Booking successful for room: " << roomID << endl;
            } else {
                cout << "Room is unavailable. Please choose another room." << endl;
            }
            break;
        }
    }

    if (!roomFound) {
        cout << "Room ID not found. Please check and try again." << endl;
    }
}

Customer::~Customer() {}
