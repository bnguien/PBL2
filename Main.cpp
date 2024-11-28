 #include "Person.cpp"
#include "Customer.cpp"
#include "Room.cpp"
#include "Service.cpp"
#include "Staff.cpp"
#include "Date.cpp"
#include "Login.cpp"
#include "Bill.cpp"
#include "BillStaff.cpp"

#include "Function.h"
#include "Vector.h"

int main()
{
    bool programRunning = true;
    while (programRunning)
    {
        string choice;
        changeConsoleColor(9);
        std::cout << "\t\t\tWELCOME TO HOTEL DEL LUNA\t\t\t" << std::endl;
        changeConsoleColor(3);
        std::cout << "Do you already have an account? (yes/no)" << std::endl;
        changeConsoleColor(7);
        std::cin >> choice;

        if (choice == "no")
        {
            system("cls");
            changeConsoleColor(9);
            std::cout << "\t\t\tWELCOME TO HOTEL DEL LUNA\t\t\t" << std::endl;
            changeConsoleColor(11);
            std::cout << "Don't miss out! Let's get your room booked right now!" << std::endl;
            system("pause");
            changeConsoleColor(7);
            Customer customer;
            customer.bookedRoom();
        }
        else if (choice == "yes")
        {
            system("cls");
            bool userLoggedIn = false;

            while (!userLoggedIn)
            {
                char option;
                std::cout << "******************************************************************" << std::endl;
                changeConsoleColor(9);
                std::cout << "\t\t\tWELCOME TO HOTEL DEL LUNA\t\t\t" << std::endl;
                changeConsoleColor(14);
                std::cout << "Login as" << std::endl;
                std::cout << "ADMIN LOGIN - press a" << std::endl;
                std::cout << "CUSTOMER LOGIN - press c" << std::endl;
                std::cout << "EXIT PROGRAM - press e" << std::endl;
                changeConsoleColor(7);
                option = _getch();
                system("cls");
                string inputUsername, inputPasswordStr;

                if (option == 'e')
                {
                    programRunning = false;
                    break;
                }
                else if (option == 'a')
                {
                    vector<Customer> customers = Customer::readFileCustomer("Customer.txt");
                    vector<Service> services = Service::readFileService("Service.txt");
                    vector<Room> rooms = Room::readFileRoom("Room.txt");
                    vector<Staff> staffs = Staff::readFileStaff("Staff.txt");
                    vector<pair<string, string>> accounts;

                    for (const auto &staff : staffs)
                    {
                        string username = createUsername(staff.getFullName());
                        accounts.push_back(make_pair(trim(username), trim(staff.getCCCD())));
                    }

                    bool loggedIn = false;
                    while (!loggedIn)
                    {
                        changeConsoleColor(9);
                        std::cout << "\t\t\tWELCOME TO HOTEL DEL LUNA\t\t\t" << std::endl;
                        changeConsoleColor(3);
                        std::cout << "Login as admin" << std::endl;
                        changeConsoleColor(6);
                        std::cout << "|---------------------------------------------------------------------------------------------|" << std::endl;
                        changeConsoleColor(10);
                        std::cout << "USER NAME (Your full name is written without diacritics): ";
                        changeConsoleColor(7);
                        std::cin >> inputUsername;
                        inputUsername = toLower(inputUsername);
                        changeConsoleColor(10);
                        std::cout << "PASSWORD (Your CIC *Citizen Identification Card*): ";
                        changeConsoleColor(7);
                        inputPasswordStr = inputPassword();
                        changeConsoleColor(6);
                        std::cout << "|---------------------------------------------------------------------------------------------|" << std::endl;
                        if (login(accounts, inputUsername, inputPasswordStr))
                        {
                            changeConsoleColor(4);
                            std::cout << "LOGIN SUCCESSFULLY" << std::endl;
                            changeConsoleColor(6);
                       
                            system("pause");
                            loggedIn = true;
                            userLoggedIn = true;
                            changeConsoleColor(7);
                            system("cls");
                            bool continueUsing = true;
                            while (continueUsing)
                            {
                                changeConsoleColor(9);
                                std::cout << "\t\tWELCOME TO HOTEL DEL LUNA\t\t\t" << std::endl;
                                changeConsoleColor(10);
                                string border = "+---------------+----------------------------------------+";
                                std::cout << border << std::endl;
                                changeConsoleColor(3);
                                std::cout << "|1. Check customer information" << std::right << std::setw(32) << "|" << std::endl;
                                changeConsoleColor(10);
                                std::cout << border << std::endl;
                                changeConsoleColor(3);
                                std::cout << "|2. Check customer bill" << std::right << std::setw(42) << "|" << std::endl;
                                changeConsoleColor(10);
                                std::cout << border << std::endl;
                                changeConsoleColor(3);
                                std::cout << "|3. Search customer" << std::right << std::setw(46) << "|" << std::endl;
                                changeConsoleColor(10);
                                std::cout << border << std::endl;
                                changeConsoleColor(3);
                                std::cout << "|4. Remove customer" << std::right << std::setw(44) << "|" << std::endl;
                                changeConsoleColor(10);
                                std::cout << border << std::endl;
                                changeConsoleColor(3);
                                std::cout << "|0. Exit" << std::right << std::setw(50) << "|" << std::endl;
                                changeConsoleColor(10);
                                std::cout << border << std::endl;
                                changeConsoleColor(6);
                                std::cout << "Please enter your option: ";
                                changeConsoleColor(7);
                                int choice;
                                std::cin >> choice;

                                switch (choice)
                                {
                                case 1:
                                {

                                    break;
                                }
                                case 2:
                                {
                                    BillStaff billTemp;
                                    
                                    break;
                                }
                                case 4:
                                {

                                    break;
                                }
                                case 0:
                                {
                                    changeConsoleColor(3);
                                    std::cout << "Hope to see you again~~~" << std::endl;
                                    changeConsoleColor(7);
                                    continueUsing = false;
                                    break;
                                }
                                default:
                                {
                                    std::cout << "Invalid option, please try again." << std::endl;
                                    break;
                                }
                                }
                                if (continueUsing)
                                {
                                    char continueChoice;
                                    changeConsoleColor(6);
                                    std::cout << "Do you want to continue? (y/n): ";
                                    changeConsoleColor(7);
                                    std::cin >> continueChoice;
                                    system("cls");
                                    if (tolower(continueChoice) != 'y')
                                    {
                                        continueUsing = false;
                                    }
                                }
                            }
                        }
                        else
                        {
                            changeConsoleColor(4);
                            std::cout << "PLEASE LOGIN AGAIN (Username or password is incorrect)!!!!" << std::endl;
                            changeConsoleColor(7);
                            system("pause");
                            system("cls");
                        }
                    }
                }
                else if (option == 'c')
                {
                    vector<Customer> customers = Customer::readFileCustomer("Customer.txt");
                    vector<Service> services = Service::readFileService("Service.txt");
                    vector<Room> rooms = Room::readFileRoom("Room.txt");
                    vector<pair<string, string>> accounts;

                    for (const auto &customer : customers)
                    {
                        string username = createUsername(customer.getFullName());
                        accounts.push_back(make_pair(trim(username), trim(customer.getCCCD())));
                    }
                    bool loggedIn = false;
                    while (!loggedIn)
                    {
                        changeConsoleColor(9);
                        std::cout << "\t\t\tWELCOME TO HOTEL DEL LUNA\t\t\t" << std::endl;
                        changeConsoleColor(3);
                        std::cout << "Login as customer" << std::endl;
                        changeConsoleColor(6);
                        std::cout << "|---------------------------------------------------------------------------------------------|" << std::endl;
                        changeConsoleColor(10);
                        std::cout << "USER NAME (Your full name is written without diacritics): ";
                        changeConsoleColor(7);
                        std::cin >> inputUsername;
                        inputUsername = toLower(inputUsername);
                        changeConsoleColor(10);
                        std::cout << "PASSWORD (Your CIC *Citizen Identification Card*): ";
                        changeConsoleColor(7);
                        inputPasswordStr = inputPassword();
                        changeConsoleColor(6);
                        std::cout << "|---------------------------------------------------------------------------------------------|" << std::endl;

                        if (login(accounts, inputUsername, inputPasswordStr))
                        {
                            changeConsoleColor(4);
                            std::cout << "LOGIN SUCCESSFULLY" << std::endl;
                            changeConsoleColor(6);
                       
                            system("pause");
                            loggedIn = true;
                            changeConsoleColor(7);
                            system("cls");
                            bool continueUsing = true;
                            while (continueUsing)
                            {
                                changeConsoleColor(9);
                                std::cout << "\t\tWELCOME TO HOTEL DEL LUNA\t\t\t" << std::endl;
                                changeConsoleColor(10);
                                string border = "+---------------+----------------------------------------+";
                                std::cout << border << std::endl;
                                changeConsoleColor(3);
                                std::cout << "|1. Check your information" << std::right << std::setw(32) << "|" << std::endl;
                                changeConsoleColor(10);
                                std::cout << border << std::endl;
                                changeConsoleColor(3);
                                std::cout << "|2. Book service" << std::right << std::setw(42) << "|" << std::endl;
                                changeConsoleColor(10);
                                std::cout << border << std::endl;
                                changeConsoleColor(3);
                                std::cout << "|3. Update information" << std::right << std::setw(36) << "|" << std::endl;
                                changeConsoleColor(10);
                                std::cout << border << std::endl;
                                changeConsoleColor(3);
                                std::cout << "|4. Check bill" << std::right << std::setw(44) << "|" << std::endl;
                                changeConsoleColor(10);
                                std::cout << border << std::endl;
                                changeConsoleColor(3);
                                std::cout << "|0. Exit" << std::right << std::setw(50) << "|" << std::endl;
                                changeConsoleColor(10);
                                std::cout << border << std::endl;
                                changeConsoleColor(6);
                                std::cout << "Please enter your option: ";
                                changeConsoleColor(7);
                                int choice;
                                std::cin >> choice;
                                Customer cus;
                                switch (choice)
                                {
                                case 1:
                                {
                                    vector<Customer> customers = Customer::readFileCustomer("Customer.txt");
                                    cus.checkInfor(inputUsername, inputPasswordStr, customers, services);
                                    break;
                                }
                                case 2:
                                {
                                    cus.bookServices(inputUsername, inputPasswordStr, customers);
                                    break;
                                }
                                case 3:
                                {
                                    string fileName = "Customer.txt";
                                    cus.updateCustomerInfo(inputUsername, inputPasswordStr, customers, fileName);
                                    break;
                                }
                                case 4:
                                {
                                    vector<Customer> customers = Customer::readFileCustomer("Customer.txt");
                                    Bill tempBill;
                                    tempBill.checkBillInfo(inputUsername, inputPasswordStr, customers, rooms, services);
                                    break;
                                }
                                case 0:
                                {
                                    changeConsoleColor(3);
                                    std::cout << "Hope to see you again~~~" << std::endl;
                                    changeConsoleColor(7);
                                    system("cls");
                                    continueUsing = false;
                                    break;
                                }
                                default:
                                {
                                    std::cout << "Invalid option, please try again." << std::endl;
                                    break;
                                }
                                }
                                if (continueUsing)
                                {
                                    char continueChoice;
                                    changeConsoleColor(6);
                                    std::cout << "Do you want to continue? (y/n): ";
                                    changeConsoleColor(7);
                                    std::cin >> continueChoice;
                                    system("cls");
                                    if (tolower(continueChoice) != 'y')
                                    {
                                        continueUsing = false;
                                    }
                                }
                            }
                        }
                        else
                        {
                            changeConsoleColor(4);
                            std::cout << "PLEASE LOGIN AGAIN (Username or password is incorrect)!!!!" << std::endl;
                            changeConsoleColor(7);
                            system("pause");
                            system("cls");
                        }
                    }
                }
            }
        }
    }
    return 0;
}