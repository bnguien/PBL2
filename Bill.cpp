#include "Bill.h"
#include "Date.h"
#include "Login.h"

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
            cout << "Room with ID " << roomID << " not found in rooms list." << endl;
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
            cout << "Service with ID " << serviceID << " not found in services list." << endl;
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
        cout << "Error: Invalid price format in input: " << input << endl;
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

        Date checkoutDate(day, month, year);

        if (!checkoutDate.isValid())
        {
            cout << "Invalid date, please enter again." << endl;
            continue;
        }

        if (checkoutDate < checkInDate)
        {
            cout << "Check-out date must be after check-in date. Please enter again." << endl;
            continue;
        }

        return checkoutDate;
    }
}

void Bill::checkBillInfo(const string &inputUserName, const string &inputPassword, const vector<Customer> &customers, const vector<Room> &rooms, const vector<Service> &services)
{
    // Nhập ngày check-out từ người dùng
    checkoutDate = inputCheckoutDate(customer.getArrivalDate());

    for (const auto &customer : customers)
    {
        // Kiểm tra tên đăng nhập và mật khẩu
        if (createUsername(customer.getFullName()) == inputUserName && customer.getPhone() == inputPassword)
        {
            // Tạo mã hóa đơn cho khách hàng này
            string generatedBillID = createID(customer);
            calculateTotalPrice(customer, rooms, services, checkoutDate);

            // In thông tin hóa đơn
            cout << "Invoice information for customer: " << customer.getFullName() << endl;
            cout << "Bill ID: " << generatedBillID << endl;
            cout << "Payment Status: " << paymentStatus << endl;
            cout << "Payment Method: " << paymentMethod << endl;
            cout << "Check-in Date: " << customer.getArrivalDate().toString() << endl;
            cout << "Check-out Date: " << checkoutDate.toString() << endl;
            cout << scientific << setprecision(3);
            cout << "Total Bill: " << formatCurrency(static_cast<int>(totalPrice)) << " VND" << endl;

            cout << "List of booked rooms:" << endl;
            for (const auto &roomID : customer.getRoomIDs())
            {
                cout << roomID << endl;
            }

            cout << "List of used services:" << endl;
            for (const auto &serviceID : customer.getServiceIDs())
            {
                cout << serviceID << endl;
            }

            return;
        }
    }
    cout << "No customer found with the given username and password." << endl;
}

/*void Bill::displayBill() const {
    cout << "Bill ID: " << BillID << endl;
    cout << "Customer: " << customer.getFullName() << endl; // Use getter method to retrieve full name
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
}*/

Bill::~Bill() {}
