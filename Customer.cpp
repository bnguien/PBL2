#include "Customer.h"
#include "Room.h"
#include "Service.h"
#include "Login.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <windows.h>
#include <algorithm>
using namespace std;

void loadingBarAnimation(int color)
{
    const int totalProgress = 100; // 100%
    const int barWidth = 40;       // Độ rộng thanh tiến trình
    string spinner = "|/-\\";      // Hiệu ứng xoay

    changeConsoleColor(color);
    for (int progress = 0; progress <= totalProgress; ++progress)
    {
        int completedWidth = barWidth * progress / totalProgress;

        cout << "\rLoading [";
        for (int i = 0; i < barWidth; ++i)
        {
            if (i < completedWidth)
            {
                cout << "-"; // Thanh đầy
            }
            else
            {
                cout << " "; // Thanh trống
            }
        }
        cout << "] " << progress << "% "
             << spinner[progress % spinner.size()]; // Hiệu ứng xoay

        cout.flush(); // Đảm bảo in ra ngay lập tức

        Sleep(30); // Windows (30ms)
    }
    cout << endl;
    changeConsoleColor(7);
}

void changeConsoleColor(int colorCode)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
}

void Customer::setArrivalDate(const Date &arrivalDate)
{
    this->arrivalDate = arrivalDate;
}

Date Customer ::getArrivalDate() const
{
    return arrivalDate;
}

vector<string> Customer::getRoomIDs() const
{
    return roomIDs;
}

void Customer::setRoomIDs(const vector<string> &roomIDs)
{
    this->roomIDs = roomIDs;
}

bool Customer::getCheckedOut() const {
    return checkedOut;
}

void Customer::setCheckedOut(bool status) {
    this->checkedOut = status;
}
vector<Customer> Customer::readFileCustomer(const string& fileName) {
    ifstream file(fileName);
    vector<Customer> customers;
    string line;

    if (!file.is_open())
    {
        cout << "Cannot open file!" << endl;
        return customers;
    }

    while (getline(file, line))
    {
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
        while (getline(roomIDStream, roomID, ','))
        {
            roomIDs.push_back(roomID);
        }
        getline(ss, arrivalDateStr);
        arrivalDate = Date(arrivalDateStr);

        Person person(fullName, CCCD, phone, add, gender, DOB);
        fullName = person.standardizeString(fullName);
        Customer customer(person, roomIDs, arrivalDate);
        customers.push_back(customer);
    }

    file.close();
    return customers;
}

void Customer::displayCustomer(const vector<Customer>& customers, const vector<Service>& services) {
    cout << "\n" << setw(13) << "CUSTOMERS' INFORMATION IN OUR HOTEL" << endl;

    for (const auto &customer : customers) {
        Sleep(1000);
        string border = "+---------------+----------------------------------------+";
        cout << border << endl;
        cout << "| Full Name     | " << left << setw(39) << customer.getFullName() << "|" << endl;
        cout << border << endl;
        cout << "| CCCD          | " << left << setw(39) << customer.getCCCD() << "|" << endl;
        cout << border << endl;
        cout << "| Phone         | " << left << setw(39) << customer.getPhone() << "|" << endl;
        cout << border << endl;
        cout << "| Address       | " << left << setw(39) << customer.getAdd() << "|" << endl;
        cout << border << endl;
        cout << "| Gender        | " << left << setw(39) << customer.getGender() << "|" << endl;
        cout << border << endl;
        cout << "| Date of birth | " << left << setw(39);
        customer.getDOB().display();
        cout << "|" << endl;        
        cout << border << endl;
        cout << "| Room IDs                                               |" << endl;

        for (const auto &room : customer.roomIDs) {
            cout << room << " ";
        }
        cout << endl;
        cout << border << endl;

        cout << "| Arrival Date  | " << left << setw(39);
        customer.arrivalDate.display();
        cout << "|" << endl;
        cout << border << endl;
        cout << "| Services      | " << left << setw(39);

        if (customer.serviceIDs.empty()) {
            cout << "No services booked";
        } else {
            bool first = true;
            for (const auto &serviceID : customer.serviceIDs) {
                if (!first) {
                    cout << ",";
                }
                string serviceName = Service::getServiceName(serviceID, services);
                cout << serviceName << " (" << serviceID << ")";
                first = false;
            }
        }
        cout << "|" << endl;
        cout << border << endl;

        cout << endl;
    }
}

/*<<<<<<< _ydragn._
void saveCustomerToFile(const Customer &customer, const string &fileName)
{
    ofstream file(fileName, ios::app);
    static bool isFirstWrite = true;
    if (!file.is_open())
    {
        cout << "Cannot open customer file!" << endl;
        return;
    }

    if (!isFirstWrite)
    {
        file << endl;
        isFirstWrite = false;
=======*/

void saveCustomerToFile(const Customer& customer, const string& fileName) {
    ofstream file(fileName, ios::app);     
    if (!file.is_open()) {
        cout << "Cannot open customer file!" << endl;
        return;
    }
    file.seekp(0, ios::end); 
    if (file.tellp() > 0) { 
        file << endl; 
//>>>>>>> main
    }

    file << customer.getFullName() << "|"
         << customer.getCCCD() << "|"
         << customer.getPhone() << "|"
         << customer.getAdd() << "|"
         << customer.getDOB().toString() << "|"
         << customer.getGender() << "|";

    vector<string> roomIDs = customer.getRoomIDs();
    for (size_t i = 0; i < roomIDs.size(); ++i)
    {
        file << roomIDs[i];
        if (i < roomIDs.size() - 1)
        {
            file << ",";
        }
    }

/*<<<<<<< _ydragn._
    file << "|" << customer.getArrivalDate().toString() << endl;
=======*/
    file << "|" << customer.getArrivalDate().toString() << "|" << endl;
    file.seekp(0, ios::end);  
//>>>>>>> main
    file.close();
}

void updateRoomFile(const vector<Room> &rooms, const string &fileRoom)
{
    ofstream file(fileRoom);
    if (!file.is_open())
    {
        cout << "Cannot open room file!" << endl;
        return;
    }

    for (const auto &room : rooms)
    {
        file << room.getID() << "|"
             << room.getType() << "|"
             << room.getPrice() << "|"
             << room.getStatus() << endl;
    }

    file.close();
}

void Customer::bookedRoom() { 
    Room room;
    string fileRoom = "Room.txt"; 
    vector<Room> rooms = room.readFileRoom(fileRoom);

    cout << "List of hotel rooms:" << endl;
    room.printRoom(rooms);
    cout << "-------------------------------------" << endl;
/*<<<<<<< _ydragn._
    cout << "Enter the room ID you want to book: ";

    string roomID;
    cin >> roomID;

    bool roomFound = false;
    for (auto &room : rooms)
    {
        if (room.getID() == roomID)
        {
            roomFound = true;
            if (room.checkAvailable())
            {
                cout << "Room is available. Proceed with booking." << endl;
=======*/

    vector<string> availableRoomIDs; 
    while (true) {
        cout << "Enter the room IDs you want to book (separated by commas): ";     
        string roomIDsInput;
        cin.ignore();
        getline(cin, roomIDsInput); 

        vector<string> roomIDs;
        stringstream ss(roomIDsInput);
        string roomID;

        while (getline(ss, roomID, ',')) {
            roomID.erase(remove_if(roomID.begin(), roomID.end(), ::isspace), roomID.end());
            if (!roomID.empty()) { 
                roomIDs.push_back(roomID);
            }
        }
//>>>>>>> main

        availableRoomIDs.clear(); 
        vector<string> unavailableRoomIDs;

        for (const auto &roomID : roomIDs) {
            bool roomFound = false;
            for (auto &room : rooms) {
                if (room.getID() == roomID) {
                    roomFound = true;
                    if (room.checkAvailable()) {
                        availableRoomIDs.push_back(roomID);
                    } else {
                        unavailableRoomIDs.push_back(roomID);
                    }
                    break; 
                }
            }

            if (!roomFound) { 
                cout << "Room ID " << roomID << " not found. Please check and try again." << endl;
            }
        }

        if (!unavailableRoomIDs.empty()) {
            cout << "Rooms ";
            for (size_t i = 0; i < unavailableRoomIDs.size(); ++i) {
                cout << unavailableRoomIDs[i];
                if (i < unavailableRoomIDs.size() - 1) {
                    cout << ", ";  
                }
            }
            cout << " are unavailable. Please choose another room." << endl;
            continue; 
        }

        if (!availableRoomIDs.empty()) {
            cout << "Rooms ";
            for (size_t i = 0; i < availableRoomIDs.size(); ++i) {
                cout << availableRoomIDs[i];
                if (i < availableRoomIDs.size() - 1) {
                    cout << " and ";
                }
            }
            cout << " are available. Proceeding with booking." << endl;
            break; 
        } else {
            cout << "No available rooms selected. Please try again." << endl;
        }
    }

    string fullName, CCCD, phone, add, gender, DOBstr, arrivalDateStr;
    Date DOB, arrivalDate;

    cout << "Enter your full name: ";
    getline(cin, fullName);

    cout << "Enter your CCCD: ";
    getline(cin, CCCD);

    cout << "Enter your phone number: ";
    getline(cin, phone);

/*<<<<<<< _ydragn._
                cout << "Enter your date of birth (DD/MM/YYYY): ";
                getline(cin, DOBstr);
                Date DOB(DOBstr);
=======*/
    cout << "Enter your address: ";
    getline(cin, add);
//>>>>>>> main

    cout << "Enter your gender: ";
    getline(cin, gender);

/*<<<<<<< _ydragn._
                Person person(fullName, CCCD, phone, add, gender, DOB);
                vector<string> roomIDs = {roomID};
                Customer newCustomer(person, roomIDs, arrivalDate);
=======*/
    cout << "Enter your date of birth (DD/MM/YYYY): ";
    getline(cin, DOBstr);
    DOB = Date(DOBstr); 
//>>>>>>> main

    cout << "Enter your arrival date (DD/MM/YYYY): ";
    getline(cin, arrivalDateStr);
    arrivalDate = Date(arrivalDateStr);

/*<<<<<<< _ydragn._
                string customerFile = "Customer.txt";
                saveCustomerToFile(newCustomer, customerFile);
                updateRoomFile(rooms, fileRoom);

                cout << "Booking successful for room: " << roomID << endl;
            }
            else
            {
                cout << "Room is unavailable. Please choose another room." << endl;
            }
            break;
=======*/
    fullName = Person::standardizeString(fullName); 
    add = Person::standardizeString(add); 
    gender = Person::standardizeString(gender);
    Person person(fullName, CCCD, phone, add, gender, DOB);

    Customer newCustomer(person, availableRoomIDs, arrivalDate);
    string customerFile = "Customer.txt"; 
    saveCustomerToFile(newCustomer, customerFile);

    for (auto &room : rooms) {
        if (find(availableRoomIDs.begin(), availableRoomIDs.end(), room.getID()) != availableRoomIDs.end()) {
            room.setStatus("Unavailable");
//>>>>>>> main
        }
    }
    updateRoomFile(rooms, fileRoom);
    cout << "Booking successful for rooms: ";
    for (const auto& bookedID : availableRoomIDs) {
        cout << bookedID << " ";
    }
    cout << endl;
    cout << "You have an account to login to check your information." << endl;
    cout << "Please login with your username (Your full name is written without diacritics) and password (your phone number) to see your information." << endl;
}

/*<<<<<<< _ydragn._
    if (!roomFound)
    {
        cout << "Room ID not found. Please check and try again." << endl;
=======*/
void Customer::checkInfor(const string& inputUserName, const vector<Customer>& customers, const vector<Service>& services) {
    for (const auto& customer : customers) {
        if (createUsername(customer.getFullName()) == inputUserName) {
            vector<Customer> loggedInCustomer = { customer }; 
            displayCustomer(loggedInCustomer, services);
            return; 
        }
//>>>>>>> main
    }
    cout << "No customer found with the username: " << inputUserName << endl;
}
//Chuc nang khi login customer
void Customer::bookServices()
{
    string fileService = "Service.txt";
    vector<Service> services = readFileService(fileService);

    Room room;
    string fileRoom = "Room.txt";
    vector<Room> rooms = room.readFileRoom(fileRoom);

    loadingBarAnimation(5);
    string border = "*===================================================*";
    changeConsoleColor(1);
    cout << "\n" << border << endl;
    cout << "*" << right << setw(38);
    changeConsoleColor(4);
    cout << "WELCOME TO HOTEL DEL LUNA" << setw(14);
    changeConsoleColor(1);
    cout << "*" << endl;
    cout << border << endl;
    changeConsoleColor(3);
    cout << "\n" << setw(42) << "HERE ARE THE SERVICES WE OFFER" << endl;
    cout << setw(37) << "--------------------" << endl;
    changeConsoleColor(7);

    displayService(services);
    cout << setw(37) << "--------------------" << endl;
    
    string roomID;
    bool roomFound = false;
    do
    {
        cout << "Enter the Room ID (eg., S101, D201, T301) to book services: ";
        getline (cin, roomID);
        for (const auto &room : rooms)
        {
            if (room.getID() == roomID)
            {
                roomFound = true;
                break;
            }
        }
        if (!roomFound)
        {
            changeConsoleColor(4);
            cout << "\nRoom ID not found. Please check and try again." << endl;
            changeConsoleColor(7);
        }
    } while (!roomFound);

    vector<string> serviceIDs;
    string serviceID;
    char c;
    do 
    {
        cout << "Enter ServiceID (eg.,F01,S01,D01,L01) you want to book:";
        getline (cin, serviceID);

        bool serviceFound = false;
        for (auto &service : services)
        {
            if (service.getID() == serviceID)
            {
                serviceIDs.push_back(serviceID);
                serviceFound = true;
                break;
            }
            
        }

        if (serviceFound)
        {
            cout << "Would you like to enjoy more of our services? Press (Y/N)" << endl;
            cin >> c;
            cin.ignore();
            c = toupper(c);

            while (c != 'Y' && c != 'N')
            {
                cout << "Press (Y/N)" << endl;
                cin >> c;
                cin.ignore();
                c = toupper(c);
            }
        }
        else 
        {
            changeConsoleColor(4);
            cout << "ServiceID not found. Please check and try again." << endl;
            changeConsoleColor(7);
            cout << "Try another ServiceID? Press (Y/N)" << endl;
            cin >> c;
            cin.ignore();
            c = toupper(c);
        }

    } while (c == 'Y');

    room.addServiceByRoomID(roomID, serviceIDs);

    if (serviceIDs.empty())
        cout << "No services booked." << endl;
    else 
        cout << "Service booked successfully for Room ID: " << roomID << endl;
}

void Customer::checkout(const string& inputUserName, const vector<Customer>& customers)
{
    cout<<"You want to checkout? Are you sure? (y/n): ";
    string choice;
    cin>>choice;
    if (choice =="y" || choice == "Y")
    {
        for (const auto& customer : customers)
        {
            if(createUsername(customer.getFullName()) == inputUserName)
            {
                setCheckedOut(true);
                vector<Customer> loggedInCustomer = { customer };
                cout << "Thank you for confirming your checkout!" << endl;
                return;
    }
            }
        }
    else if (choice == "n" || choice == "N")
    {
        cout<<"Checkout cancelled"<<endl;
    }
}
Customer::~Customer() {}
