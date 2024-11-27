#include "Bill.h"
#include "Date.h"
#include "Login.h"
#define int_max 2147483647

using namespace std;

Date Bill::getCheckoutDate() const
{
    return checkoutDate;
}
void Bill::setCheckoutDate(const Date &date)
{
    checkoutDate = date;
}

string Bill::createID(const Customer &customer)
{
    string customerID = customer.getCCCD().substr(0, 4);
    int randomPart = rand() % 10000;
    string BillID = "PBL-" + customerID + "-" + to_string(randomPart);
    return BillID;
}

// dùng để in ra số tiền cho đúng định dạng ví dụ 1150000 -> 1,105,000
std::string Bill::formatCurrency(int amount)
{
    std::string result;
    std::string number = std::to_string(amount);

    int count = 0;
    for (int i = number.length() - 1; i >= 0; --i)
    {
        result = number[i] + result;
        count++;
        if (count % 3 == 0 && i != 0)
        {
            result = "," + result;
        }
    }

    return result;
}
void Bill::calculateTotalPrice(const Customer &customer, const vector<Room> &rooms, const vector<Service> &services, Date checkoutDate)
{
    totalPrice = 0.0;
    int daysBetween = Date::daysBetween(customer.getArrivalDate(), checkoutDate);
    // Tính tiền phòng
    for (const auto &roomID : customer.getRoomIDs())
    {
        bool roomFound = false;
        for (const auto &room : rooms)
        {
            if (room.getID() == roomID)
            {
                roomFound = true;
                double roomPrice = convert(room.getPrice());
                totalPrice += roomPrice * daysBetween;
                break;
            }
        }
        if (!roomFound)
        {
            std::cout << "Room with ID " << roomID << " not found in rooms list." << endl;
        }
    }

    for (const auto &serviceID : customer.getServiceIDs())
    {
        bool serviceFound = false;
        for (const auto &service : services)
        {
            if (service.getID() == serviceID)
            {
                serviceFound = true;
                double servicePrice = convert(service.getPrice());
                totalPrice += servicePrice;
                break;
            }
        }
        if (!serviceFound)
        {
            std::cout << "Service with ID " << serviceID << " not found in services list." << endl;
        }
    }
}

int Bill::convert(const string &input)
{
    string result = input;
    result.erase(remove(result.begin(), result.end(), '.'), result.end());

    size_t pos = result.find("/");
    if (pos != string::npos)
    {
        result.erase(pos);
    }
    try
    {
        return stoi(result);
    }
    catch (const std::invalid_argument &)
    {
        std::cout << "Error: Invalid price format in input: " << input << endl;
        return 0;
    }
}

Date Bill::inputCheckoutDate(const Date &checkInDate)
{
    int day, month, year;
    while (true)
    {
        cout << "Enter check-out date (DD MM YYYY): ";
        cin >> day >> month >> year;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(int_max, '\n');
            cout << "Invalid input format. Please enter numeric values (DD MM YYYY)." << endl;
            continue;
        }

        if (!Date::isValid(day, month, year))
        {
            cout << "Invalid date, please enter again." << endl;
            continue;
        }
        else
            Date checkoutDate(day, month, year);
            
        if (checkInDate > checkoutDate)
        {
            cout << "Check-out date must be after check-in date. Please enter again." << endl;
            continue;
        }
        return checkoutDate;
    }
}

void Bill::checkBillInfo(const string &inputUserName, const string &inputPassword, const vector<Customer> &customers, const vector<Room> &rooms, const vector<Service> &services)
{
    size_t maxColumnWidth = 39;
    for (const auto &customer : customers)
    {
        size_t roomWidth = 0;
        for (const auto &room : customer.getRoomIDs())
        {
            roomWidth += room.size() + 1;
        }
        maxColumnWidth = std::max(maxColumnWidth, roomWidth);

        size_t serviceWidth = 0;
        for (const auto &serviceID : customer.getServiceIDs())
        {
            serviceWidth += Service::getServiceName(serviceID, services).size() + 2;
        }
        maxColumnWidth = std::max(maxColumnWidth, serviceWidth);
    }
    const int consoleWidth = 120;

    for (const auto &customer : customers)
    {
        if (createUsername(customer.getFullName()) == inputUserName && customer.getCCCD() == inputPassword)
        {
            std::cout << "Check-in Date: ";
            customer.getArrivalDate().display();
            std::cout << std::endl;

            checkoutDate = inputCheckoutDate(customer.getArrivalDate());

            string generatedBillID = createID(customer);
            calculateTotalPrice(customer, rooms, services, checkoutDate);
            system("cls");

            string border = "+---------------+" + string(maxColumnWidth + 2, '-') + "+";
            size_t tableWidth = border.length(); 
            int startX = (consoleWidth - tableWidth) / 2; 
            int currentY = 2; 
            gotoXY(startX, currentY++);
            std::cout << "INVOICE INFORMATION" << std::endl;

            gotoXY(startX, currentY++);
            std::cout << border << std::endl;
            gotoXY(startX, currentY++);
            std::cout << "| Full Name     | " << std::left << std::setw(maxColumnWidth) << customer.getFullName() << " |" << std::endl;

            gotoXY(startX, currentY++);
            std::cout << border << std::endl;

            gotoXY(startX, currentY++);
            std::cout << "| Bill ID       | " << std::left << std::setw(maxColumnWidth) << generatedBillID << " |" << std::endl;

            gotoXY(startX, currentY++);
            std::cout << border << std::endl;

            gotoXY(startX, currentY++);
            std::cout << "| Payment Status| " << std::left << std::setw(maxColumnWidth) << paymentStatus << " |" << std::endl;

            gotoXY(startX, currentY++);
            std::cout << border << std::endl;

            gotoXY(startX, currentY++);
            std::cout << "| Payment Method| " << std::left << std::setw(maxColumnWidth) << paymentMethod << " |" << std::endl;

            gotoXY(startX, currentY++);
            std::cout << border << std::endl;

            gotoXY(startX, currentY++);
            std::cout << "| Check-in Date | " << std::left << std::setw(maxColumnWidth);
            customer.getArrivalDate().display();
            std::cout << " |" << std::endl;

            gotoXY(startX, currentY++);
            std::cout << border << std::endl;

            gotoXY(startX, currentY++);
            std::cout << "| Check-out Date| " << std::left << std::setw(maxColumnWidth);
            checkoutDate.display();
            std::cout << " |" << std::endl;

            gotoXY(startX, currentY++);
            std::cout << border << std::endl;

            gotoXY(startX, currentY++);
            std::cout << "| Total Bill    | " << std::left << std::setw(maxColumnWidth)
                      << formatCurrency(static_cast<int>(totalPrice)) + " VND" << " |" << std::endl;

            gotoXY(startX, currentY++);
            std::cout << border << std::endl;

            gotoXY(startX, currentY++);
            std::cout << "| Room IDs      | ";
            std::string roomsStr;
            for (const auto &room : customer.getRoomIDs())
            {
                roomsStr += room + " ";
            }
            std::cout << std::left << std::setw(maxColumnWidth) << roomsStr << " |" << std::endl;

            gotoXY(startX, currentY++);
            std::cout << border << std::endl;

            if (customer.getServiceIDs().empty())
            {
                gotoXY(startX, currentY++);
                std::cout << "| Service       | " << std::left << std::setw(maxColumnWidth) << "No services booked" << " |" << std::endl;

                gotoXY(startX, currentY++);
                std::cout << border << std::endl;
            }
            else
            {
                gotoXY(startX, currentY++);
                std::cout << "| ServiceIDs    | ";
                std::string serviceIDsStr;
                for (size_t i = 0; i < customer.getServiceIDs().size(); ++i)
                {
                    serviceIDsStr += customer.getServiceIDs()[i];
                    if (i < customer.getServiceIDs().size() - 1)
                    {
                        serviceIDsStr += ", ";
                    }
                }
                std::cout << std::left << std::setw(maxColumnWidth) << serviceIDsStr << " |" << std::endl;

                gotoXY(startX, currentY++);
                std::cout << border << std::endl;

                gotoXY(startX, currentY++);
                std::cout << "| ServiceNames  | ";
                std::string servicesStr;
                for (size_t i = 0; i < customer.getServiceIDs().size(); ++i)
                {
                    servicesStr += Service::getServiceName(customer.getServiceIDs()[i], services);
                    if (i < customer.getServiceIDs().size() - 1)
                    {
                        servicesStr += ", ";
                    }
                }
                std::cout << std::left << std::setw(maxColumnWidth) << servicesStr << " |" << std::endl;

                gotoXY(startX, currentY++);
                std::cout << border << std::endl;
            }

            changeConsoleColor(10);
            gotoXY(startX, currentY++);
            std::cout << "THANK YOU FOR YOUR BUSINESS!" << std::endl;
            changeConsoleColor(7);
            _getch();
            return;
        }
    }
    changeConsoleColor(4);
    std::cout << "No customer found with the given username and password." << std::endl;
}

Bill::~Bill() {}
