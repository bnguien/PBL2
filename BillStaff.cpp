#include "BillStaff.h"

void BillStaff::addBill(Bill *bill)
{
    bills.push_back(bill);
}
void BillStaff::checkBillByNameAndPhone(const vector<Customer> &customers, const vector<Room> &rooms, const vector<Service> &services)
{
    std::string customerName;
    std::string phone;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter customer name: ";
    std::getline(std::cin, customerName);

    std::cout << "Enter phone number: ";
    std::getline(std::cin, phone);

    bool found = false;
    std::string lowerCustomerName = toLower(customerName);

    for (const auto &customer : customers)
    {
        std::string fullName = toLower(customer.getFullName());
        if (fullName == lowerCustomerName && customer.getPhone() == phone)
        {
            found = true;
            std::cout << "Check-in Date: ";
            customer.getArrivalDate().display();
            std::cout << endl;
            checkoutDate = inputCheckoutDate(customer.getArrivalDate());
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::string paymentMethod;
            std::cout << "Enter Payment Method: ";
            std::getline(std::cin, paymentMethod);
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

            changeConsoleColor(7);
            std::string paymentConfirmation;
            std::cout << "Has the customer paid? (yes/no): ";
            std::getline(std::cin, paymentConfirmation);

            if (paymentConfirmation == "yes" || paymentConfirmation == "Yes")
            {
                // Xử lý trạng thái thanh toán đã hoàn thành
                // Ví dụ: Xóa thông tin khách hàng
                // Giả sử có một phương thức removeCustomer()
                /*removeCustomer(customer);*/
                std::cout << "Customer information has been removed successfully." << std::endl;
            }
            else if (paymentConfirmation == "no" || paymentConfirmation == "No")
            {
                std::cout << "The customer has not paid yet." << std::endl;
            }
            else
            {
                std::cout << "Invalid input. Please enter 'yes' or 'no'." << std::endl;
            }

            return;
        }
    }

    if (!found)
    {
        std::cout << "No customer found with the given name and phone number." << std::endl;
    }
}

BillStaff::~BillStaff()
{
    for (Bill *bill : bills)
    {
        delete bill;
    }
}