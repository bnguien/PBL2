#include "Bill.h"
#include "Date.h"
#include "Login.h"
#define INT_MAX 2147483647 

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
            cin.ignore(INT_MAX, '\n'); 
            cout << "Invalid input format. Please enter numeric values (DD MM YYYY)." << endl;
            continue;
        }

        Date checkoutDate(day, month, year);
        if (!checkoutDate.isValid())
        {
            cout << "Invalid date, please enter again." << endl;
            continue;
        }
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
    for (const auto &customer : customers)
    {
        if (createUsername(customer.getFullName()) == inputUserName && customer.getCCCD() == inputPassword)
        {
            std::cout << "Check-in Date: ";
            customer.getArrivalDate().display();
            std::cout<<endl;
            checkoutDate = inputCheckoutDate(customer.getArrivalDate());
            system("cls");
            string generatedBillID = createID(customer);
            calculateTotalPrice(customer, rooms, services, checkoutDate);
            changeConsoleColor(10);
            std::cout << "+---------------------------------------------------------------+" << std::endl;
            std::cout << "|                       INVOICE INFORMATION                     |" << std::endl;
            std::cout << "+---------------------------------------------------------------+" << std::endl;
            changeConsoleColor(7);

            std::cout << "| Customer Name: " << left << setw(47) << customer.getFullName() << "|" << std::endl;
            std::cout << "| Bill ID: " << left << setw(53) << generatedBillID << "|" << std::endl;
            std::cout << "| Payment Status: " << left << setw(46) << paymentStatus << "|" << std::endl;
            std::cout << "| Payment Method: " << left << setw(46) << paymentMethod << "|" << std::endl;
            std::cout << "| Check-in Date: " << left << setw(47);
            customer.getArrivalDate().display();
            std::cout << "|" << std::endl;
            std::cout << "| Check-out Date: " << left << setw(46);
            checkoutDate.display();
            std::cout << "|" << std::endl;
            std::cout << "| Total Bill: " << left << setw(12) << formatCurrency(static_cast<int>(totalPrice)) << " VND" << right << setw(35) << "|" << std::endl;
            std::cout << "+---------------------------------------------------------------+" << std::endl;

            std::cout << "| List of booked rooms                                          |" << std::endl;
            std::cout << "| ";
            std::cout << "Room IDs: ";
            for (const auto &roomID : customer.getRoomIDs())
            {
                std::cout << roomID << " ";
            }
            std::cout << right << setw(48) << "|" << std::endl;
            std::cout << "+---------------------------------------------------------------+" << std::endl;

            std::cout << "| List of used services                                         |" << std::endl;
            if (customer.getServiceIDs().empty())
            {
                std::cout << "| No services booked                                            |" << std::endl;
            }
            else
            {
                std::cout << "| Service IDs: ";
                for (const auto &serviceID : customer.getServiceIDs())
                {
                    std::cout << serviceID << " ";
                }
                std::cout << right << setw(42) << "|" << std::endl;
            }
            std::cout << "+---------------------------------------------------------------+" << std::endl;

            changeConsoleColor(10);
            std::cout << "| Thank you for your business!                                  |" << std::endl;
            std::cout << "+---------------------------------------------------------------+" << std::endl;
            changeConsoleColor(7);

            return;
        }
    }
    std::cout << "No customer found with the given username and password." << std::endl;
}
Bill::~Bill() {}
