#include "Customer.h"

using namespace std;
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
vector<string> Customer::getServiceIDs() const
{
    return serviceIDs;
}

vector<string> Customer::getServiceNames() const
{
    return serviceNames;
}
vector<Customer> Customer::readFileCustomer(const string &fileName)
{
    ifstream file(fileName);
    vector<Customer> customers;
    string line;

    if (!file.is_open())
    {
        std::cout << "Cannot open file!" << endl;
        return customers;
    }

    while (getline(file, line))
    {
        stringstream ss(line);
        string fullName, CCCD, phone, add, gender, DOBstr, roomIDStr, arrivalDateStr, serviceIDStr, serviceNameStr;
        Date DOB, arrivalDate;

        getline(ss, fullName, '|');
        getline(ss, CCCD, '|');
        getline(ss, phone, '|');
        getline(ss, add, '|');
        getline(ss, DOBstr, '|');
        DOB = Date(DOBstr);
        getline(ss, gender, '|');

        getline(ss, roomIDStr, '|');
        getline(ss, arrivalDateStr, '|');
        arrivalDate = Date(arrivalDateStr);

        getline(ss, serviceIDStr, '|');
        getline(ss, serviceNameStr);

        vector<string> roomIDs;
        stringstream roomIDStream(roomIDStr);
        string roomID;
        while (getline(roomIDStream, roomID, ','))
        {
            roomIDs.push_back(roomID);
        }

        vector<string> serviceIDs;
        stringstream serviceIDStream(serviceIDStr);
        string serviceID;
        while (getline(serviceIDStream, serviceID, ','))
        {
            serviceIDs.push_back(serviceID);
        }

        vector<string> serviceNames;
        stringstream serviceNameStream(serviceNameStr);
        string serviceName;
        while (getline(serviceNameStream, serviceName, ','))
        {
            serviceNames.push_back(serviceName);
        }

        Person person(fullName, CCCD, phone, add, gender, DOB);
        fullName = person.standardizeString(fullName);
        add = person.standardizeString(add);
        gender = person.standardizeString(gender);

        Customer customer(person, roomIDs, arrivalDate, serviceIDs, serviceNames);
        customers.push_back(customer);
    }
}

void Customer::displayCustomer(const vector<Customer> &customers, const vector<Service> &services) {
    std::cout << "\n"
              << setw(13) << "CUSTOMERS' INFORMATION IN OUR HOTEL" << endl;

    for (const auto &customer : customers) {
        Sleep(1000); 
        string border = "+---------------+----------------------------------------+";
        std::cout << border << endl;

        // Hiển thị thông tin khách hàng
        std::cout << "| Full Name     | " << left << setw(39) << customer.getFullName() << "|" << endl;
        std::cout << border << endl;
        std::cout << "| CCCD          | " << left << setw(39) << customer.getCCCD() << "|" << endl;
        std::cout << border << endl;
        std::cout << "| Phone         | " << left << setw(39) << customer.getPhone() << "|" << endl;
        std::cout << border << endl;
        std::cout << "| Address       | " << left << setw(39) << customer.getAdd() << "|" << endl;
        std::cout << border << endl;
        std::cout << "| Gender        | " << left << setw(39) << customer.getGender() << "|" << endl;
        std::cout << border << endl;
        std::cout << "| Date of birth | " << left << setw(39);
        customer.getDOB().display();
        std::cout << "|" << endl;
        std::cout << border << endl;

        std::cout << "| Room IDs                                               |" << endl;
        for (const auto &room : customer.getRoomIDs()) {
            std::cout << room << " ";
        }
        std::cout << endl;
        std::cout << border << endl;

        std::cout << "| Arrival Date  | " << left << setw(39);
        customer.getArrivalDate().display();
        std::cout << "|" << endl;
        std::cout << border << endl;

        if (customer.getServiceIDs().empty()) {
            std::cout << "| Service      | " << left << setw(39);
            std::cout << "No services booked";
            std::cout << "|" << endl;
            std::cout << border << endl;
        } else {
             std::cout << "| ServiceIDS      | ";
            for(const auto &serviceID : customer.getServiceIDs()){
                std::cout << serviceID << ",";
            }
            std::cout << left << setw(39)<<"|" << endl;
            std::cout << border << endl;
             std::cout << "| ServiceNames      | ";
             for(const auto &serviceID : customer.getServiceNames()){
                std::cout << serviceID << ",";
            }
            std::cout << left << setw(39)<<"|" << endl;
        }
        std::cout << endl;  
    }
}

void saveCustomerToFile(const Customer &customer, const string &fileName)
{
    ofstream file(fileName, ios::app);
    if (!file.is_open())
    {
        std::cout << "Cannot open customer file!" << endl;
        return;
    }
    file.seekp(0, ios::end);
    if (file.tellp() > 0)
    {
        file << endl;
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
    file << "|" << customer.getArrivalDate().toString() << "|" << endl;
    file.seekp(0, ios::end);
    file.close();
}

void Customer::bookedRoom()
{
    Room room;
    string fileRoom = "Room.txt";
    vector<Room> rooms = room.readFileRoom(fileRoom);

    string roomType;
    std::cout << "Enter the type of room you want to book (single, double, triple): ";
    cin >> roomType;
    cin.ignore();

    vector<Room> filteredRooms;

    for (const auto &room : rooms)
    {
        if ((roomType == "single" && room.getID().front() == 'S') ||
            (roomType == "double" && room.getID().front() == 'D') ||
            (roomType == "triple" && room.getID().front() == 'T'))
        {
            filteredRooms.push_back(room);
        }
    }

    if (filteredRooms.empty())
    {
        std::cout << "No rooms available for the selected type: " << roomType << endl;
        return;
    }

    std::cout << "Available rooms of type " << roomType << ":" << endl;
    for (const auto &filteredRoom : filteredRooms)
    {
        std::cout << "ID: " << filteredRoom.getID() << endl;
        std::cout << "Type: " << filteredRoom.getType() << endl;
        std::cout << "Price (VND/night): " << filteredRoom.getPrice() << "/night" << endl;
        std::cout << "Status: " << (filteredRoom.checkAvailable() ? "Available" : "Unavailable") << endl;
        std::cout << "-----------------------------" << endl;
    }

    vector<string> availableRoomIDs;
    while (true)
    {
        std::cout << "Enter the room IDs you want to book (separated by commas): ";
        string roomIDsInput;
        getline(cin, roomIDsInput);

        vector<string> roomIDs;
        string currentRoomID = "";

        for (char ch : roomIDsInput)
        {
            if (ch == ',')
            {

                if (!currentRoomID.empty())
                {
                    roomIDs.push_back(currentRoomID);
                    currentRoomID.clear();
                }
            }
            else
            {
                currentRoomID += ch;
            }
        }

        if (!currentRoomID.empty())
        {
            roomIDs.push_back(currentRoomID);
        }

        availableRoomIDs.clear();
        vector<string> unavailableRoomIDs;
        for (const string &inputRoomID : roomIDs)
        {
            bool roomFound = false;
            for (const Room &room : filteredRooms)
            {
                if (room.getID() == inputRoomID)
                {
                    roomFound = true;
                    if (room.checkAvailable())
                    {
                        availableRoomIDs.push_back(inputRoomID);
                    }
                    else
                    {
                        unavailableRoomIDs.push_back(inputRoomID);
                    }
                    break;
                }
            }
            if (!roomFound)
            {
                unavailableRoomIDs.push_back(inputRoomID);
            }
        }

        if (!unavailableRoomIDs.empty())
        {
            std::cout << "Rooms ";
            for (size_t i = 0; i < unavailableRoomIDs.size(); ++i)
            {
                std::cout << unavailableRoomIDs[i];
                if (i < unavailableRoomIDs.size() - 1)
                {
                    std::cout << ", ";
                }
            }
            std::cout << " are unavailable. Please choose another room." << endl;
            continue;
        }

        if (!availableRoomIDs.empty())
        {
            std::cout << "Rooms ";
            for (size_t i = 0; i < availableRoomIDs.size(); ++i)
            {
                std::cout << availableRoomIDs[i];
                if (i < availableRoomIDs.size() - 1)
                {
                    std::cout << ", ";
                }
            }
            std::cout << " are available. Proceeding with booking." << endl;
            break;
        }
        else
        {
            std::cout << "No available rooms selected. Please try again." << endl;
        }
    }

    string fullName, CCCD, phone, add, gender, DOBstr, arrivalDateStr;
    Date DOB, arrivalDate;

    std::cout << "Enter your full name: ";
    getline(cin, fullName);

    std::cout << "Enter your CCCD: ";
    getline(cin, CCCD);

    std::cout << "Enter your phone number: ";
    getline(cin, phone);

    std::cout << "Enter your address: ";
    getline(cin, add);

    std::cout << "Enter your gender: ";
    getline(cin, gender);

    std::cout << "Enter your date of birth (DD/MM/YYYY): ";
    getline(cin, DOBstr);
    DOB = Date(DOBstr);

    std::cout << "Enter your arrival date (DD/MM/YYYY): ";
    getline(cin, arrivalDateStr);
    arrivalDate = Date(arrivalDateStr);

    fullName = Person::standardizeString(fullName);
    add = Person::standardizeString(add);
    gender = Person::standardizeString(gender);
    Person person(fullName, CCCD, phone, add, gender, DOB);

    Customer newCustomer(person, availableRoomIDs, arrivalDate, {"None"}, {"None"});
    string customerFile = "Customer.txt";
    saveCustomerToFile(newCustomer, customerFile);

    for (auto &roomRef : rooms)
    {
        if (find(availableRoomIDs.begin(), availableRoomIDs.end(), roomRef.getID()) != availableRoomIDs.end())
        {
            roomRef.setStatus("Unavailable");
        }
    }

    room.updateRoomFile(rooms, fileRoom);
    std::cout << "Booking successful for rooms: ";
    for (const auto &bookedID : availableRoomIDs)
    {
        std::cout << bookedID << " ";
    }
    std::cout << endl;
    std::cout << "You have an account to login to check your information." << endl;
    std::cout << "Please login with your username (Your full name without diacritics) and password (your phone number) to see your information." << endl;
}

void Customer::checkInfor(const string &inputUserName, const string &inputPassword, const vector<Customer> &customers, const vector<Service> &services)
{
    for (const auto &customer : customers)
    {
        if (createUsername(customer.getFullName()) == inputUserName && customer.getPhone() == inputPassword)
        {
            vector<Customer> loggedInCustomer = {customer};
            displayCustomer(loggedInCustomer, services);
            currentFullName = customer.getFullName();
            return;
        }
    }
    std::cout << "No customer found with the given username and password." << std::endl;
}

// Chuc nang khi login customer
void Customer::bookServices(const string &inputUserName, const string &inputPassword)
{
    string fileService = "Service.txt";
    vector<Service> services = readFileService(fileService);

    Room room;
    string fileRoom = "Room.txt";
    vector<Room> rooms = room.readFileRoom(fileRoom);

    loadingBarAnimation(5);
    string border = "*===================================================*";
    changeConsoleColor(1);
    std::cout << "\n"
              << border << endl;
    std::cout << "*" << right << setw(38);
    changeConsoleColor(4);
    std::cout << "WELCOME TO HOTEL DEL LUNA" << setw(14);
    changeConsoleColor(1);
    std::cout << "*" << endl;
    std::cout << border << endl;
    changeConsoleColor(3);
    std::cout << "\n"
              << setw(42) << "HERE ARE THE SERVICES WE OFFER" << endl;
    std::cout << setw(37) << "--------------------" << endl;
    changeConsoleColor(7);

    displayService(services);
    std::cout << setw(37) << "--------------------" << endl;

    string roomID;
    bool roomFound = false;

    while (true)
    {
        std::cout << "Enter the Room ID (eg., S101, D201, T301) to book services: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, roomID);
        if (roomID.empty())
        {
            changeConsoleColor(4);
            std::cout << "Room ID cannot be empty. Please enter a valid Room ID." << endl;
            changeConsoleColor(7);
            continue;
        }

        roomFound = false;
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
            std::cout << "\nRoom ID not found. Please check and try again." << endl;
            changeConsoleColor(7);
        }
        else
        {
            break;
        }
    }

    vector<string> serviceIDs;
    string serviceID;
    char c;
    do
    {
        std::cout << "Enter ServiceID (eg., F01, S01, D01, L01) you want to book: ";
        getline(cin, serviceID);

        bool serviceFound = false;
        for (const auto &service : services)
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
            std::cout << "Would you like to enjoy more of our services? Press (Y/N)" << endl;
            cin >> c;
            cin.ignore();
            c = toupper(c);

            while (c != 'Y' && c != 'N')
            {
                std::cout << "Press (Y/N)" << endl;
                cin >> c;
                cin.ignore();
                c = toupper(c);
            }
        }
        else
        {
            changeConsoleColor(4);
            std::cout << "ServiceID not found. Please check and try again." << endl;
            changeConsoleColor(7);
            std::cout << "Try another ServiceID? Press (Y/N)" << endl;
            cin >> c;
            cin.ignore();
            c = toupper(c);
        }

    } while (c == 'Y');

    room.addServiceByRoomID(roomID, serviceIDs);

    if (serviceIDs.empty())
        std::cout << "No services booked." << endl;
    else
    {
        std::cout << "Services booked successfully for Room ID: " << roomID << endl;
        addServicesToCustomerFile(inputUserName, inputPassword, services, serviceIDs);
    }
}

void Customer::addServicesToCustomerFile(const string &inputUserName, const string &inputPassword, const vector<Service> &services, const vector<string> &serviceIDs)
{
    string fileName = "Customer.txt";
    ifstream inputFile(fileName);
    if (!inputFile.is_open())
    {
        cerr << "Cannot open file!" << endl;
        return;
    }

    vector<string> customerLines;
    string line;

    while (getline(inputFile, line))
    {
        customerLines.push_back(line);
    }
    inputFile.close();

    ofstream outputFile(fileName, ios::out | ios::trunc);
    if (!outputFile.is_open())
    {
        cerr << "Could not open the file for writing." << endl;
        return;
    }

    for (auto &customerLine : customerLines)
    {
        size_t firstPipePos = customerLine.find('|');
        size_t secondPipePos = customerLine.find('|', firstPipePos + 1);
        string customerName = customerLine.substr(0, firstPipePos);
        string customerPhone = customerLine.substr(secondPipePos + 1, customerLine.find('|', secondPipePos + 1) - secondPipePos - 1);

        if (createUsername(customerName) == inputUserName && customerPhone == inputPassword)
        {
            size_t lastPipePos = customerLine.find_last_of('|');
            string existingServiceIDs, existingServiceNames;

            if (lastPipePos != string::npos)
            {
                existingServiceIDs = customerLine.substr(lastPipePos + 1, customerLine.find('|', lastPipePos + 1) - lastPipePos - 1);
                existingServiceNames = customerLine.substr(customerLine.find('|', lastPipePos + 1) + 1);
            }
            string newServiceIDs, newServiceNames;
            for (const auto &serviceID : serviceIDs)
            {
                string serviceName = Service::getServiceName(serviceID, services);
                if (!newServiceIDs.empty())
                {
                    newServiceIDs += ",";
                    newServiceNames += ", ";
                }
                newServiceIDs += serviceID;
                newServiceNames += serviceName;
            }
            customerLine += "|" + newServiceIDs + "|" + newServiceNames;
        }

        outputFile << customerLine << endl;
    }

    outputFile.close();
}

// nối chuỗi
string Customer::join(const vector<string> &elements, const string &delimiter)
{
    string result;
    for (size_t i = 0; i < elements.size(); ++i)
    {
        result += elements[i];
        if (i < elements.size() - 1)
            result += delimiter;
    }
    return result;
}

/*void Customer::checkout(const string &inputUserName, const vector<Customer> &customers)
{
    std::cout << "You want to checkout? Are you sure? (y/n): ";
    string choice;
    cin >> choice;
    if (choice == "y" || choice == "Y")
    {
        for (const auto &customer : customers)
        {
            if (createUsername(customer.getFullName()) == inputUserName)
            {
                setCheckedOut(true);
                vector<Customer> loggedInCustomer = {customer};
                std::cout << "Thank you for confirming your checkout!" << endl;
                return;
            }
        }
    }
    else if (choice == "n" || choice == "N")
    {
        std::cout << "Checkout cancelled" << endl;
    }
}*/
Customer::~Customer() {}