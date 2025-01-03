#include "Customer.h"

#include "Date.h"
#include "Room.h"
#include "Service.h"
#include "Login.h"
#include "Bill.h"
#include "Graphics.h"

using namespace std;
Customer currentLoggedInCustomer;
void noAccountScreen();
void customerScreen(const string &username, const string &password);
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
void Customer::setServiceIDs(const vector<string> &ids)
{
    serviceIDs = ids;
}
vector<string> Customer::getServiceNames() const
{
    return serviceNames;
}
void Customer::setServiceNames(const vector<string> &names)
{
    serviceNames = names;
}
bool Customer::operator==(const Customer &customer) const
{
    return (static_cast<const Person &>(*this) == static_cast<const Person &>(customer)) && // So sánh các thành phần từ lớp cha Person
           (roomIDs == customer.roomIDs) &&
           (serviceIDs == customer.serviceIDs) &&
           (serviceNames == customer.serviceNames) &&
           (arrivalDate == customer.arrivalDate) &&
           (currentFullName == customer.currentFullName);
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

        string standardizedFullName = Person::standardizeString(fullName);
        string standardizedAdd = Person::standardizeString(add);
        string standardizedGender = Person::standardizeString(gender);

        Customer customer(standardizedFullName, CCCD, phone, standardizedAdd, standardizedGender, DOB, roomIDs, arrivalDate, serviceIDs, serviceNames);

        customers.push_back(customer);
    }
    return customers;
}

void Customer::display() const
{
    const Customer& customer = currentLoggedInCustomer; 
    vector<Service> services = Service::readFileService("Service.txt");

    size_t maxColumnWidth = 39;

    size_t roomWidth = 0;
    for (const auto &room : customer.getRoomIDs())
    {
        roomWidth += room.size() + 1;
    }
    maxColumnWidth = max(maxColumnWidth, roomWidth);

    size_t serviceWidth = 0;
    for (const auto &serviceID : currentLoggedInCustomer.getServiceIDs())
    {
        serviceWidth += Service::getServiceName(serviceID, services).size() + 2;
    }
    maxColumnWidth = max(maxColumnWidth, serviceWidth);

    const int consoleWidth = 120;

    system("cls");
    changeColor(12);
    string filename = "title.txt";
    ifstream inputFile(filename);
    read_lines(filename, 33, 42);
    inputFile.close();
    changeColor(7);

    string border = "+---------------+" + string(maxColumnWidth + 2, '-') + "+";
    size_t tableWidth = border.length();
    int startX = (consoleWidth - tableWidth) / 2;
    int currentY = 12;
    gotoXY(startX, currentY++);
    cout << border << endl;

    gotoXY(startX, currentY++);
    cout << "| Full Name     | " << left << setw(maxColumnWidth) << customer.getFullName() << " |" << endl;

    gotoXY(startX, currentY++);
    cout << border << endl;

    gotoXY(startX, currentY++);
    cout << "| CCCD          | " << left << setw(maxColumnWidth) << customer.getCCCD() << " |" << endl;

    gotoXY(startX, currentY++);
    cout << border << endl;

    gotoXY(startX, currentY++);
    cout << "| Phone         | " << left << setw(maxColumnWidth) << customer.getPhone() << " |" << endl;

    gotoXY(startX, currentY++);
    cout << border << endl;

    gotoXY(startX, currentY++);
    cout << "| Address       | " << left << setw(maxColumnWidth) << customer.getAdd() << " |" << endl;

    gotoXY(startX, currentY++);
    cout << border << endl;

    gotoXY(startX, currentY++);
    cout << "| Gender        | " << left << setw(maxColumnWidth) << customer.getGender() << " |" << endl;

    gotoXY(startX, currentY++);
    cout << border << endl;

    gotoXY(startX, currentY++);
    cout << "| Date of birth | " << left << setw(maxColumnWidth);
    customer.getDOB().display();
    cout << " |" << endl;

    gotoXY(startX, currentY++);
    cout << border << endl;

    gotoXY(startX, currentY++);
    cout << "| Room IDs      | ";
    string roomsStr;
    for (const auto &room : customer.getRoomIDs())
    {
        roomsStr += room + " ";
    }
    cout << left << setw(maxColumnWidth) << roomsStr << " |" << endl;

    gotoXY(startX, currentY++);
    cout << border << endl;

    gotoXY(startX, currentY++);
    cout << "| Arrival Date  | " << left << setw(maxColumnWidth);
    customer.getArrivalDate().display();
    cout << " |" << endl;

    gotoXY(startX, currentY++);
    cout << border << endl;

    if (customer.getServiceIDs().empty())
    {
        gotoXY(startX, currentY++);
        cout << "| Service       | " << left << setw(maxColumnWidth) << "No services booked" << " |" << endl;

        gotoXY(startX, currentY++);
        cout << border << endl;
    }
    else
    {
        gotoXY(startX, currentY++);
        cout << "| ServiceIDs    | ";
        string serviceIDsStr;
        for (size_t i = 0; i < customer.getServiceIDs().size(); ++i)
        {
            serviceIDsStr += customer.getServiceIDs()[i];
            if (i < customer.getServiceIDs().size() - 1)
            {
                serviceIDsStr += ", ";
            }
        }
        cout << left << setw(maxColumnWidth) << serviceIDsStr << " |" << endl;

        gotoXY(startX, currentY++);
        cout << border << endl;

        gotoXY(startX, currentY++);
        cout << "| ServiceNames  | ";
        string servicesStr;
        for (size_t i = 0; i < currentLoggedInCustomer.getServiceIDs().size(); ++i)
        {
            servicesStr += Service::getServiceName(currentLoggedInCustomer.getServiceIDs()[i], services);
            if (i < customer.getServiceIDs().size() - 1)
            {
                servicesStr += ", ";
            }
        }
        cout << left << setw(maxColumnWidth) << servicesStr << " |" << endl;

        gotoXY(startX, currentY++);
        cout << border << endl;
    }

    gotoXY(startX, currentY++);
    cout << endl;
}


bool Customer::saveCustomerToFile(const Customer &customer, const string &fileName)
{
    ifstream readfile(fileName, ios::binary);
    bool addNewLine = false;

    if (readfile.is_open())
    {
        readfile.seekg(0, ios::end);
        if (readfile.tellg() > 0)
        {
            readfile.seekg(-1, ios::end);
            char ch;
            readfile.get(ch);
            if (ch != '\n')
                addNewLine = true;
        }
        readfile.close();
    }

    ofstream file(fileName, ios::app);
    if (!file.is_open())
    {
        std::cout << "Cannot open customer file!" << endl;
        return false;
    }

    if (addNewLine)
        file << std::endl;

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
    file << "|" << customer.getArrivalDate().toString() << endl;

    file.seekp(0, ios::end);
    file.close();
    return true;
}

void Customer::bookedRoom()
{
    Room room;
    string fileRoom = "Room.txt";
    vector<Room> rooms = room.readFileRoom(fileRoom);
    vector<Room> filteredRooms;
    changeColor(6);
    system("cls");
    string filename = "title.txt";
    read_lines(filename, 1, 11);
    changeColor(7);

    for (const auto &room : rooms)
    {
        if (!room.getID().empty() && room.getStatus() == "Available")
        {
            filteredRooms.push_back(room);
        }
    }

    if (filteredRooms.empty())
    {
        changeConsoleColor(4);
        std::cout << "\nNo available rooms at the moment." << endl;
        changeConsoleColor(7);
        return;
    }

    Customer::showAllRooms(filteredRooms);

    cout << "\n________________________________________________________________________________________________________________\n";
    vector<string> unavailableRoomIDs;
    vector<string> availableRoomIDs;
    ShowCur(1);
    while (true)
    {
        unavailableRoomIDs.clear();
        availableRoomIDs.clear();
        std::cout << "\nEnter ALL the room IDs you want to book (separated by commas): ";
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
            else if (ch == ' ')
            {
                continue;
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

        for (const auto &roomID : roomIDs)
        {
            bool idFound = false;
            for (const auto &room : filteredRooms)
                if (roomID == room.getID())
                    idFound = true;

            if (idFound)
                availableRoomIDs.push_back(roomID);
            else
                unavailableRoomIDs.push_back(roomID);
        }

        if (!unavailableRoomIDs.empty())
        {
            std::cout << "\nRooms with ID: ";
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
            std::cout << "\nRooms with ID: ";
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
            char choice;
            do
            {
                changeConsoleColor(4);
                std::cout << "\nNo available rooms selected.\n"
                          << "Would you like to try again? Press \'y\' to continue or \'n\' to exit!" << endl;
                std::cin >> choice;
                choice = std::tolower(choice); // Chuyển ký tự thành chữ thường
                if (choice != 'y' && choice != 'n')
                {
                    std::cout << "Invalid choice! Please press 'y' or 'n'." << std::endl;
                }
                if (choice == 'n')
                    return;
            } while (choice != 'y' && choice != 'n');
            changeConsoleColor(7);
        }
    }
    system("cls");

    string fullName, CCCD, phone, add, gender, DOBstr, arrivalDateStr;
    Date DOB, arrivalDate;
    changeConsoleColor(9);
    system("cls");
    gotoXY(25, 0);
    read_lines(filename, 14, 23);
    changeConsoleColor(14);
    gotoXY(40, 11);
    std::cout << "+-------------------------------------------------------+" << std::endl;
    gotoXY(40, 12);
    std::cout << "|                   YOUR INFORMATION                    |" << std::endl;
    gotoXY(40, 13);
    std::cout << "+-------------------------------------------------------+" << std::endl;

    gotoXY(40, 14);
    std::cout << "|  Full Name               |                            |" << std::endl;
    gotoXY(40, 15);
    std::cout << "|-------------------------------------------------------|" << std::endl;

    gotoXY(40, 16);
    std::cout << "|  CCCD                    |                            |" << std::endl;
    gotoXY(40, 17);
    std::cout << "|-------------------------------------------------------|" << std::endl;

    gotoXY(40, 18);
    std::cout << "|  Phone Number            |                            |" << std::endl;
    gotoXY(40, 19);
    std::cout << "|-------------------------------------------------------|" << std::endl;

    gotoXY(40, 20);
    std::cout << "|  Address                 |                            |" << std::endl;
    gotoXY(40, 21);
    std::cout << "|-------------------------------------------------------|" << std::endl;

    gotoXY(40, 22);
    std::cout << "|  Gender(Male/Female)     |                            |" << std::endl;
    gotoXY(40, 23);
    std::cout << "|-------------------------------------------------------|" << std::endl;

    gotoXY(40, 24);
    std::cout << "|  DOB(DD/MM/YYYY)         |                            |" << std::endl;
    gotoXY(40, 25);
    std::cout << "|-------------------------------------------------------|" << std::endl;

    gotoXY(40, 26);
    std::cout << "|  Arrival Date(DD/MM/YYYY)|                            |" << std::endl;
    gotoXY(40, 27);
    std::cout << "+-------------------------------------------------------+" << std::endl;

    changeConsoleColor(15);
    do
    {
        gotoXY(69, 14);
        std::getline(std::cin, fullName);
        if (fullName.empty())
        {
            changeConsoleColor(4);
            gotoXY(99, 14);
            std::cout << "Customer's name cannot be empty. Please try again.";
            changeConsoleColor(7);
            _getch();
            gotoXY(99, 14);
            std::cout << string(75, ' ');
        }
    } while (fullName.empty());
    bool isValidCCCD = false;
    do
    {
        gotoXY(69, 16);
        std::getline(std::cin, CCCD);

        if (CCCD.length() != 12)
        {
            changeConsoleColor(4);
            gotoXY(98, 16);
            cout << "CCCD must have exactly 12 digits!Press enter to try again" << endl;
            changeConsoleColor(7);
            _getch();
            gotoXY(98, 16);
            cout << string(75, ' ');
        }
        else
        {
            bool isDigitOnly = true;
            for (size_t i = 0; i < CCCD.length(); i++)
            {
                if (!isdigit(CCCD[i]))
                {
                    isDigitOnly = false;
                    gotoXY(98, 16);
                    changeConsoleColor(4);
                    cout << "CCCD must have only digits!Press enter to try again" << endl;
                    changeConsoleColor(7);
                    _getch();
                    gotoXY(98, 16);
                    cout << string(75, ' ');
                    break;
                }
            }
            if (isDigitOnly)
            {
                isValidCCCD = true;
            }
        }

        if (!isValidCCCD)
        {
            gotoXY(69, 16);
            cout << string(CCCD.length(), ' ');
        }

    } while (!isValidCCCD);
    bool isValidPhone = false;

    do
    {
        gotoXY(69, 18);
        std::getline(std::cin, phone);

        if (phone.length() != 10)
        {
            gotoXY(98, 18);
            changeConsoleColor(4);
            cout << "Phone must have exactly 10 digits!Press enter to try again" << endl;
            changeConsoleColor(7);
            _getch();
            gotoXY(98, 18);
            cout << string(75, ' ');
        }
        else if (phone[0] != '0')
        {
            gotoXY(98, 18);
            changeConsoleColor(4);
            cout << "First number must be 0! Press enter to try again" << endl;
            changeConsoleColor(7);
            _getch();
            gotoXY(98, 18);
            cout << string(75, ' ');
        }
        else
        {
            bool isDigitOnly = true;
            for (size_t i = 1; i < phone.length(); i++)
            {
                if (!isdigit(phone[i]))
                {
                    isDigitOnly = false;
                    gotoXY(98, 18);
                    changeConsoleColor(4);
                    cout << "Phone must have only digits! Press enter to try again" << endl;
                    changeConsoleColor(7);
                    gotoXY(98, 18);
                    _getch();
                    cout << string(75, ' ');
                    break;
                }
            }
            if (isDigitOnly)
            {
                isValidPhone = true;
            }
        }

        if (!isValidPhone)
        {
            gotoXY(69, 18);
            cout << string(phone.length(), ' ');
        }

    } while (!isValidPhone);

    do
    {
        gotoXY(69, 20);
        cout << string(27, ' ');
        gotoXY(69, 20);
        std::getline(std::cin, add);
    } while (add.empty());

    do
    {
        gotoXY(69, 22);
        cout << string(27, ' ');
        gotoXY(69, 22);
        std::getline(std::cin, gender);
        gender = toLower(gender);

        if (gender != "male" && gender != "female")
        {
            gotoXY(98, 22);
            changeConsoleColor(4);
            std::cout << "Gender must be \"Male\" or \"Female\". Press Enter to try again!";
            changeConsoleColor(7);
            _getch();
            gotoXY(98, 22);
            cout << string(75, ' ');
            continue;
        }
        break;

    } while (true);

    while (true)
    {
        gotoXY(69, 24);
        cout << string(27, ' ');
        gotoXY(69, 24);
        std::getline(std::cin, DOBstr);

        if (DOBstr.empty())
        {
            gotoXY(98, 24);
            changeConsoleColor(4);
            std::cout << "Date of Birth cannot be empty. Press enter to try again (dd/mm/yyyy).";
            changeConsoleColor(7);
            _getch();
            gotoXY(98, 24);
            cout << string(75, ' ');
            continue;
        }

        if (Date::isValidDateFormat(DOBstr))
        {
            DOB = Date(DOBstr);
            if (Date::getCurrentDate().getYear() - DOB.getYear() < 18)
            {
                gotoXY(98, 24);
                changeConsoleColor(4);
                std::cout << "The customer must be at least 18 years old!";
                changeConsoleColor(7);
                Sleep(3000);

                system("cls");
                changeConsoleColor(12);
                gotoXY(40, 5);
                cout << "+---------------------------------------------------+";
                gotoXY(40, 6);
                cout << "|                                                   |";
                gotoXY(40, 7);
                cout << "|          Customer is under 18 years old!          |";
                gotoXY(40, 8);
                cout << "|                                                   |";
                gotoXY(40, 9);
                cout << "|   Failed to book new room for customer with CCCD  |";
                gotoXY(40, 10);
                cout << "|                    " << setw(31) << setfill(' ') << CCCD << "|";
                gotoXY(40, 11);
                cout << "|                                                   |";
                gotoXY(40, 12);
                cout << "+---------------------------------------------------+" << endl;
                changeConsoleColor(7);
                ShowCur(0);
                return;
            }

            break;
        }
        else
        {
            gotoXY(98, 24);
            changeConsoleColor(4);
            std::cout << "Invalid date format! Please use dd/mm/yyyy!";
            changeConsoleColor(7);
            _getch();
            gotoXY(98, 24);
            cout << string(75, ' ');
            continue;
        }
    }

    while (true)
    {
        gotoXY(69, 26);
        cout << string(27, ' ');
        gotoXY(69, 26);
        std::getline(std::cin, arrivalDateStr);

        if (arrivalDateStr.empty())
        {
            gotoXY(98, 26);
            changeConsoleColor(4);
            std::cout << "Arrival date cannot be empty. Press enter to try again (dd/mm/yyyy).";
            changeConsoleColor(7);
            _getch();
            gotoXY(98, 26);
            cout << string(75, ' ');
            continue;
        }

        if (Date::isValidDateFormat(arrivalDateStr))
        {
            arrivalDate = Date(arrivalDateStr);
            if (Date::getCurrentDate() > arrivalDate)
            {
                gotoXY(98, 26);
                changeConsoleColor(4);
                std::cout << "Arrival date must be after current date: " << Date::getCurrentDate();
                changeConsoleColor(7);
                _getch();
                gotoXY(98, 26);
                cout << string(75, ' ');
                continue;
            }

            break;
        }
        else
        {
            gotoXY(98, 26);
            changeConsoleColor(4);
            std::cout << "Invalid date format! Please use dd/mm/yyyy!";
            changeConsoleColor(7);
            _getch();
            gotoXY(98, 26);
            cout << string(75, ' ');
            continue;
        }
    }

    vector<string> Options = {"Cancel", "Confirm"};
    int optionIndex = buttonList(45, 29, 15, 2, 18, Options, "row");
    string selectedOption = Options[optionIndex - 1];
    if (selectedOption == "Cancel")
    {
        clearFromPosition(1, 1);
        noAccountScreen();
        return;
    }
    else if (selectedOption == "Confirm")
    {
        fullName = Person::standardizeString(fullName);
        add = Person::standardizeString(add);
        gender = Person::standardizeString(gender);

        Customer newCustomer(fullName, CCCD, phone, add, gender, DOB, availableRoomIDs, arrivalDate, {"None"}, {"None"});
        string customerFile = "Customer.txt";
        if (!saveCustomerToFile(newCustomer, customerFile))
        {
            changeConsoleColor(4);
            gotoXY(25, 34);
            cout << "\nFailed to save to our hotel's customer file!" << endl;
            changeConsoleColor(7);
            system("pause");
            return;
        }

        for (auto &roomRef : rooms)
        {
            if (find(availableRoomIDs.begin(), availableRoomIDs.end(), roomRef.getID()) != availableRoomIDs.end())
            {
                roomRef.setStatus("Unavailable");
            }
        }
        std::cout << endl;
        room.updateRoomFile(rooms, fileRoom);
        gotoXY(25, 34);
        changeColor(2);
        std::cout << "Booking successful for rooms: ";
        changeColor(7);
        for (const auto &bookedID : availableRoomIDs)
        {
            std::cout << bookedID << " ";
        }
        std::cout << endl;
        gotoXY(25, 35);
        changeColor(14);
        std::cout << "You have an account to login to check your information." << endl;
        gotoXY(25, 36);
        std::cout << "Please login with your username (Your full name without diacritics) and password (your phone number) to see your information." << endl;
    }
    ShowCur(0);
}

void Customer::checkInfor(const string &inputUserName, const string &inputPassword, const vector<Customer> &customers, const vector<Service> &services)
{
    for (const auto &customer : customers)
    {
        if (createUsername(customer.getFullName()) == inputUserName && customer.getCCCD() == inputPassword)
        {
            currentLoggedInCustomer = customer;
            customer.display();
            currentFullName = customer.getFullName();
            return; 
        }
    }
    std::cout << "No customer found with the given username and password." << std::endl;
}

// Chuc nang khi login customer
void Customer::bookServices(const string &inputUserName, const string &inputPassword, const vector<Customer> &customers)
{
    string fileService = "Service.txt";
    vector<Service> services = Service::readFileService(fileService);

    string fileRoom = "Room.txt";
    vector<Room> rooms = Room::readFileRoom(fileRoom);
    string border = "*===================================================*";
    changeConsoleColor(1);
    std::cout << "\n";
    gotoXY(20, 12);
    std::cout << border;
    gotoXY(30, 13);
    std::cout << "*" << setw(38);
    changeConsoleColor(4);
    gotoXY(32, 13);
    std::cout << setw(20) << "WELCOME TO HOTEL DEL LUNA";
    changeConsoleColor(1);
    gotoXY(58, 13);
    std::cout << "*" << endl;
    gotoXY(20, 14);
    std::cout << border << endl;
    changeConsoleColor(3);
    std::cout << "\n";
    gotoXY(30, 15);
    std::cout << "HERE ARE THE SERVICES WE OFFER" << endl;
    gotoXY(37, 16);
    std::cout << setw(37) << "--------------------" << endl;
    changeConsoleColor(7);

    displayService(services);
    std::cout << left << setw(37) << "--------------------" << endl;

    string roomID;
    bool roomFound = false;

    while (true)
    {
        for (const auto &customer : customers)
        {
            if (createUsername(customer.getFullName()) == inputUserName && customer.getCCCD() == inputPassword)
            {
                changeColor(2);
                std::cout << "Customer's ID room(s): ";
                std::string roomsStr;
                changeColor(7);
                for (const auto &room : customer.getRoomIDs())
                {
                    roomsStr += room + " ";
                }

                std::cout << roomsStr << endl;
                changeColor(14);
                std::cout << "Enter to continue.....";
                changeColor(7);
            }
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        std::cout << "Enter the Room ID (eg., S101, D201, T301) to book services: ";
        cin.clear();
        getline(cin, roomID);
        if (roomID.empty())
        {
            changeConsoleColor(4);
            std::cout << "Room ID cannot be empty. Please enter a valid Room ID." << endl;
            changeConsoleColor(7);
            continue;
        }
        roomFound = false;
        for (const auto &customer : customers)
        {
            if (createUsername(customer.getFullName()) == inputUserName && customer.getCCCD() == inputPassword)
            {
                roomID.erase(remove(roomID.begin(), roomID.end(), ' '), roomID.end());
                std::transform(roomID.begin(), roomID.end(), roomID.begin(), ::tolower);

                for (auto id : customer.getRoomIDs())
                {
                    id.erase(remove(id.begin(), id.end(), ' '), id.end());
                    std::transform(id.begin(), id.end(), id.begin(), ::tolower);

                    if (id == roomID)
                    {
                        roomFound = true;
                        break;
                    }
                }

                if (roomFound)
                    break;
            }
        }

        if (!roomFound)
        {
            changeConsoleColor(4);
            std::cout << "\nRoom ID not found for the logged-in customer. Please try again." << endl;
            changeConsoleColor(7);
        }
        else
        {
            changeConsoleColor(2);
            std::cout << "Room ID is valid. Proceeding with service booking..." << endl;
            changeConsoleColor(7);
            break;
        }
    }

    vector<string> serviceIDs;
    string serviceID;
    char c;

    do
    {
        std::cout << "\nEnter ServiceID (eg., F01) you want to book: ";
        getline(cin, serviceID);
        serviceID[0] = toupper(serviceID[0]);

        if (serviceID.length() != 3 ||
            (toupper(serviceID[0]) != 'F' && toupper(serviceID[0]) != 'S' && toupper(serviceID[0]) != 'D' && toupper(serviceID[0]) != 'L') ||
            !isdigit(serviceID[1]) || !isdigit(serviceID[2]))
        {
            changeColor(4);
            std::cout << "Invalid ServiceID format. Please enter a valid ServiceID (e.g., F01).\n";
            changeColor(7);
            std::cout << "Try another ServiceID? Press (Y/N): ";
            cin >> c;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            c = toupper(c);
            while (c != 'Y' && c != 'N')
            {
                std::cout << "Invalid input. Press (Y/N): ";
                cin >> c;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                c = toupper(c);
            }
            continue;
        }

        bool serviceFound = false;
        for (const auto &service : services)
        {
            if (service.getID() == serviceID)
            {
                changeColor(2);
                std::cout << "Press Enter to confirm or ESC to cancel.\n";
                changeColor(7);
                char key = _getch();

                if (key == 13)
                {
                    serviceIDs.push_back(serviceID);
                    std::cout << "Service " << serviceID << " has been successfully booked.\n";
                }
                else if (key == 27)
                {
                    clearFromPosition(1, 1);
                    customerScreen(inputUserName, inputPassword);
                    return;
                }
                else
                {
                    std::cout << "Invalid key. Operation canceled.\n";
                }

                serviceFound = true;
                break;
            }
        }

        if (!serviceFound)
        {
            changeColor(4);
            std::cout << "ServiceID " << serviceID << " not found. Please try again.\n";
            changeColor(7);
            std::cout << "Try another ServiceID? Press (Y/N): ";
            cin >> c;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            c = toupper(c);
            while (c != 'Y' && c != 'N')
            {
                std::cout << "Invalid input. Press (Y/N): ";
                cin >> c;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                c = toupper(c);
            }
            continue;
        }

        std::cout << "Would you like to book more services? Press (Y/N): ";
        cin >> c;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        c = toupper(c);
        while (c != 'Y' && c != 'N')
        {
            std::cout << "Invalid input. Press (Y/N): ";
            cin >> c;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            c = toupper(c);
        }
    } while (c == 'Y');

    Room::addServiceByRoomID(roomID, serviceIDs);
    addServicesToCustomerFile(inputUserName, inputPassword, services, serviceIDs);

    if (serviceIDs.empty())
        std::cout << "No services booked." << endl;
    else
    {
        system("cls");
        changeColor(9);
        string filename = "title.txt";
        read_lines(filename, 54, 58);
        changeColor(2);
        gotoXY(40, 10);
        cout << "+----------------------------------------------------------------------+";
        gotoXY(40, 11);
        cout << "|  Services booked successfully for Room ID:                           |";
        gotoXY(40, 12);
        cout << "+----------------------------------------------------------------------+";
        gotoXY(87, 11);
        for (size_t i = 0; i < roomID.length(); i++)
        {
            roomID[i] = toupper(roomID[i]);
        }
        std::cout << roomID;
        changeColor(7);
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
        string customerCCCD = customerLine.substr(firstPipePos + 1, secondPipePos - firstPipePos - 1);

        if (createUsername(customerName) == inputUserName && customerCCCD == inputPassword)
        {
            size_t lastPipePos = customerLine.find_last_of('|');
            string existingServiceIDs;
            if (lastPipePos != string::npos)
            {
                existingServiceIDs = customerLine.substr(lastPipePos + 1);
            }
            string newServiceIDs = existingServiceIDs;
            for (const auto &serviceID : serviceIDs)
            {
                if (!newServiceIDs.empty())
                {
                    newServiceIDs += ",";
                }
                newServiceIDs += serviceID;
            }
            customerLine = customerLine.substr(0, lastPipePos + 1) + newServiceIDs;
        }
        outputFile << customerLine << endl;
    }

    outputFile.close();
}

void Customer::updateCustomerInfo(const string &inputUserName, const string &inputPassword, vector<Customer> &customers, const string &fileName)
{
    bool customerFound = false;

    for (Customer &customer : customers)
    {
        if (createUsername(customer.getFullName()) == inputUserName && customer.getCCCD() == inputPassword)
        {
            customerFound = true;
            gotoXY(53, 12);
            changeConsoleColor(6);
            std::cout << "WHICH INFORMATION WOULD YOU LIKE TO UPDATE" << endl;
            changeConsoleColor(7);
            vector<string> options = {"Change phone number", "Change address", "Change Date of Birth (DOB)", "Return"};
            int choice = buttonList(52, 15, 34, 2, 2, options, "column");

            if (choice < 1 || choice > options.size())
            {
                cout << "Invalid selection!\n";
                return;
            }

            string selectedOption = options[choice - 1];
            system("cls");
            gotoXY(1, 1);
            changeConsoleColor(3);
            cout << "HOTEL DEL LUNA" << endl;
            changeConsoleColor(7);
            cout << "______________" << endl;

            if (selectedOption == "Change phone number")
            {
                string newPhone;
                while (true)
                {
                    gotoXY(10, 5);
                    changeConsoleColor(9);
                    cout << "Enter the new phone number: ";
                    changeConsoleColor(7);
                    getline(cin, newPhone);
                    if (customer.getPhone() == newPhone)
                    {
                        gotoXY(10, 7);
                        changeConsoleColor(4);
                        cout << "The new phone number is the same as the old one. Please enter a different phone number." << endl;
                        changeConsoleColor(7);
                        _getch();
                        gotoXY(30, 5);
                        cout << string(75, ' ');
                        gotoXY(10, 7);
                        cout << string(150, ' ');
                    }
                    else
                    {
                        if (customer.setPhone(newPhone))
                        {
                            vector<string> Options = {"Cancel", "Confirm"};
                            int optionIndex = buttonList(40, 7, 15, 2, 18, Options, "row");
                            string selectedOption = Options[optionIndex - 1];
                            if (selectedOption == "Cancel")
                            {
                                clearFromPosition(1, 1);
                                customerScreen(inputUserName, inputPassword);
                                return;
                            }
                            else if (selectedOption == "Confirm")
                            {

                                changeConsoleColor(2);
                                gotoXY(40, 11);
                                cout << "Phone number updated successfully.\n";
                                changeConsoleColor(7);
                                break;
                            }
                        }
                        else
                        {
                            system("cls");
                            gotoXY(1, 1);
                            changeConsoleColor(3);
                            std::cout << "HOTEL DEL LUNA" << endl;
                            changeConsoleColor(7);
                            std::cout << "______________" << endl;
                            changeConsoleColor(14);
                            gotoXY(40, 5);
                            std::cout << "|=========================================================|";
                            gotoXY(40, 6);
                            std::cout << "|                                                         |";
                            gotoXY(40, 7);
                            std::cout << "|=========================================================|";
                            gotoXY(53, 6);
                            changeColor(2);
                            std::cout << "Phone number updated successfully";
                            changeConsoleColor(7);
                            break;
                        }
                    }
                    changeConsoleColor(7);
                }
            }
            else if (selectedOption == "Change address")
            {
                while (true)
                {
                    gotoXY(10, 5);
                    string newAddress;
                    changeConsoleColor(9);
                    cout << "Enter the new address: ";
                    changeConsoleColor(7);
                    getline(cin, newAddress);
                    if (customer.getAdd() == newAddress)
                    {
                        gotoXY(10, 7);
                        changeConsoleColor(4);
                        cout << "The new address is the same as the old one. Please enter a different address." << endl;
                        changeConsoleColor(7);
                        _getch();
                        gotoXY(30, 5);
                        cout << string(75, ' ');
                        gotoXY(10, 7);
                        cout << string(150, ' ');
                    }
                    else
                    {
                        newAddress = Person::standardizeString(newAddress);
                        customer.setAdd(newAddress);
                        changeConsoleColor(2);
                        vector<string> Options = {"Cancel", "Confirm"};
                        int optionIndex = buttonList(40, 7, 15, 2, 18, Options, "row");
                        string selectedOption = Options[optionIndex - 1];
                        if (selectedOption == "Cancel")
                        {
                            clearFromPosition(1, 1);
                            customerScreen(inputUserName, inputPassword);
                            return;
                        }
                        else if (selectedOption == "Confirm")
                        {
                            system("cls");
                            gotoXY(1, 1);
                            changeConsoleColor(3);
                            std::cout << "HOTEL DEL LUNA" << endl;
                            changeConsoleColor(7);
                            std::cout << "______________" << endl;
                            changeConsoleColor(14);
                            gotoXY(40, 5);
                            std::cout << "|==========================================|";
                            gotoXY(40, 6);
                            std::cout << "|                                          |";
                            gotoXY(40, 7);
                            std::cout << "|==========================================|";
                            gotoXY(47, 6);
                            changeColor(2);
                            std::cout << "Address updated successfully";
                            changeConsoleColor(7);
                            break;
                        }
                    }
                }
            }
            else if (selectedOption == "Change Date of Birth (DOB)")
            {
                gotoXY(10, 5);
                changeConsoleColor(9);
                cout << "Enter the new Date of Birth (DD/MM/YYYY): ";
                changeConsoleColor(7);
                string newDOB;
                while (true)
                {
                    std::getline(std::cin, newDOB);
                    if (customer.getDOB() == newDOB)
                    {
                        gotoXY(10, 7);
                        changeConsoleColor(4);
                        cout << "The new date of birth is the same as the old one. Please enter a different date of birth." << endl;
                        changeConsoleColor(7);
                        _getch();
                        gotoXY(52, 5);
                        cout << string(75, ' ');
                        gotoXY(10, 7);
                        cout << string(150, ' ');
                        gotoXY(52, 5);
                    }
                    else
                    {
                        if (newDOB.empty())
                        {
                            changeConsoleColor(4);
                            gotoXY(10, 7);
                            cout << "Date of Birth cannot be empty!" << endl;
                            changeConsoleColor(7);
                            _getch();
                            gotoXY(10, 7);
                            cout << string(150, ' ');
                            continue;
                        }

                        if (!Date::isValidDateFormat(newDOB))
                        {
                            _getch();
                            gotoXY(52, 5);
                            cout << string(75, ' ');
                            gotoXY(1, 6);
                            cout << string(150, ' ');
                            gotoXY(52, 5);
                        }
                        else
                        {
                            vector<string> Options = {"Cancel", "Confirm"};
                            int optionIndex = buttonList(40, 7, 15, 2, 18, Options, "row");
                            string selectedOption = Options[optionIndex - 1];
                            if (selectedOption == "Cancel")
                            {
                                clearFromPosition(1, 1);
                                customerScreen(inputUserName, inputPassword);
                                return;
                            }
                            else if (selectedOption == "Confirm")
                            {
                                customer.setDOB(newDOB);
                                system("cls");
                                gotoXY(1, 1);
                                changeConsoleColor(3);
                                std::cout << "HOTEL DEL LUNA" << endl;
                                changeConsoleColor(7);
                                std::cout << "______________" << endl;
                                changeConsoleColor(14);
                                gotoXY(40, 5);
                                std::cout << "|==================================================|";
                                gotoXY(40, 6);
                                std::cout << "|                                                  |";
                                gotoXY(40, 7);
                                std::cout << "|==================================================|";
                                gotoXY(49, 6);
                                changeColor(2);
                                std::cout << "Date of birth updated successfully";
                                changeConsoleColor(7);
                                break;
                            }
                        }
                    }
                }
            }

            else if (selectedOption == "Return")
            {
                clearFromPosition(1, 1);
                customerScreen(inputUserName, inputPassword);
                return;
            }

            break;
        }
    }

    if (!customerFound)
    {
        cout << "Customer not found.\n";
        return;
    }

    ofstream file(fileName, ios::trunc);
    if (!file.is_open())
    {
        cout << "Cannot open file!" << endl;
        return;
    }
    for (const Customer &customer : customers)
    {
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
        file << "|" << customer.getArrivalDate().toString() << "|";
        vector<string> serviceIDs = customer.getServiceIDs();
        for (size_t i = 0; i < serviceIDs.size(); ++i)
        {
            file << serviceIDs[i];
            if (i < serviceIDs.size() - 1)
            {
                file << ",";
            }
        }
        file << endl;
    }

    file.close();
}

void Customer::showAllRooms(const vector<Room> &rooms)
{
    string border1 = "\t+-----+--------+----------+---------------+--------------+";
    cout << border1 << endl;
    cout << "\t| STT | RoomID | RoomType |   RoomPrice   |    Status    |" << endl;
    cout << border1 << endl;
    int count = 0;

    if (rooms.empty())
    {
        changeConsoleColor(4);
        cout << "\nThe list of rooms is currently empty. Unable to display any rooms!" << endl;
        changeConsoleColor(7);
        return;
    }

    for (const auto &room : rooms)
    {
        ++count;
        cout << "\t| " << setw(3) << setfill('0') << right << count << " |  "
             << setw(6) << setfill(' ') << left << room.getID() << "|  ";
        if (room.getType() == "Single")
            changeConsoleColor(10);
        else if (room.getType() == "Double")
            changeConsoleColor(14);
        else if (room.getType() == "Triple")
            changeConsoleColor(11);
        cout << setw(8) << room.getType();
        changeConsoleColor(7);
        cout << "| " << setw(14) << room.getPrice() << "| ";

        if (room.getStatus() == "Available")
            changeConsoleColor(2);
        else if (room.getStatus() == "Unavailable")
            changeConsoleColor(4);

        cout << setw(13) << room.getStatus();
        changeConsoleColor(7);
        cout << "|" << endl;
        cout << border1 << endl;
    }
    cout << endl;
}

Customer::~Customer() {}