#include "BillStaff.h"
using namespace std;
void BillStaff::addBill(Bill *bill)
{
    bills.push_back(bill);
}
void BillStaff::checkBillByNameAndCCCD(Staff &staff, const vector<Customer> &customers, const vector<Room> &rooms, const vector<Service> &services)
{
    std::string customerName;
    std::string CCCD;
    changeConsoleColor(7);
    std::cout << "Enter customer name: ";
    std::getline(std::cin, customerName);

    std::cout << "Enter CCCD number: ";
    std::getline(std::cin, CCCD);

    bool found = false;
    std::string lowerCustomerName = toLower(customerName);

    for (const auto &customer : customers)
    {
        std::string fullName = toLower(customer.getFullName());
        if (fullName == lowerCustomerName && customer.getCCCD() == CCCD)
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

            size_t maxColumnWidth = 39;
            size_t roomWidth = 0;
            size_t serviceWidth = 0;

            for (const auto &room : customer.getRoomIDs())
            {
                roomWidth += room.size() + 1;
            }

            for (const auto &serviceID : customer.getServiceIDs())
            {
                serviceWidth += Service::getServiceName(serviceID, services).size() + 2;
            }

            maxColumnWidth = std::max(maxColumnWidth, std::max(roomWidth, serviceWidth));

            const int consoleWidth = 120; 
            string border = "+---------------+" + string(maxColumnWidth + 2, '-') + "+";
            size_t tableWidth = border.length();        
            int startX = (consoleWidth - tableWidth) / 2; 
            int currentY = 5;                             

            changeConsoleColor(10);
            gotoXY(startX, currentY++);
            std::cout << border << std::endl;

            gotoXY(startX, currentY++);
            std::cout << "                       INVOICE INFORMATION                     " << std::endl;

            gotoXY(startX, currentY++);
            std::cout << border << std::endl;
            changeConsoleColor(7);

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

            changeConsoleColor(7);
            std::string paymentConfirmation;
            gotoXY(startX, currentY++);
            std::cout << "Has the customer paid? (yes/no): ";
            std::getline(std::cin, paymentConfirmation);

            if (paymentConfirmation == "yes" || paymentConfirmation == "Yes")
            {
                if (staff.removeCustomerByCCCD(staff, CCCD))
                {
                    gotoXY(startX, currentY++);
                    changeConsoleColor(3);
                    std::cout << "Customer information has been removed successfully." << std::endl;
                }
            }
            else if (paymentConfirmation == "no" || paymentConfirmation == "No")
            {
                gotoXY(startX, currentY++);
                changeConsoleColor(4);
                std::cout << "The customer has not paid yet." << std::endl;
            }
            else
            {
                gotoXY(startX, currentY++);
                changeConsoleColor(4);
                std::cout << "Invalid input. Please enter 'yes' or 'no'." << std::endl;
            }

            return;
        }
    }

    if (!found)
    {
        changeConsoleColor(4);
        std::cout << "No customer found with the given name and CCCD number." << std::endl;
    }
}

BillStaff::~BillStaff()
{
    for (Bill *bill : bills)
    {
        delete bill;
    }
}