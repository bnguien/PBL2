#include "Person.cpp"
#include "Customer.cpp"
#include "Room.cpp"
#include "Service.cpp"
#include "Staff.cpp"
#include "Date.cpp"
#include "Login.cpp"
#include "Bill.cpp"

#include "Function.h"
#include "Vector.h"
using namespace std;

int main()
{
    string choice;
    changeConsoleColor(9);
    cout << "\t\t\tWELCOME TO HOTEL DE LUNA\t\t\t" << endl;
    changeConsoleColor(3);
    cout << "Do you already have an account? (yes/no)" << endl;
    changeConsoleColor(7);
    cin >> choice;

    if (choice == "no")
    {
        system("cls");
        changeConsoleColor(9);
        cout << "\t\t\tWELCOME TO HOTEL DE LUNA\t\t\t" << endl;
        changeConsoleColor(11);
        cout << "Don't miss out! Let's get your room booked right now!" << endl;
        system("pause");
        changeConsoleColor(7);
        Customer customer;
        customer.bookedRoom();
    }
    else if (choice == "yes")
    {
        system("cls");
        char option;
        cout << "******************************************************************" << endl;
        changeConsoleColor(9);
        cout << "\t\t\tWELCOME TO HOTEL DE LUNA\t\t\t" << endl;
        changeConsoleColor(14);
        cout << "Login as" << endl;
        cout << "ADMIN LOGIN - press a" << endl;
        cout << "CUSTOMER LOGIN - press c" << endl;
        cout << "EXIT PROGRAM - press e" << endl;
        changeConsoleColor(7);
        option = _getch();
        system("cls");
        string inputUsername, inputPasswordStr;

        if (option == 'a')
        {
            vector<Staff> staffs = Staff::readFileStaff("Staff.txt");
            vector<pair<string, string>> accounts;

            for (const auto &staff : staffs)
            {
                string username = createUsername(staff.getFullName());
                accounts.push_back(make_pair(trim(username), trim(staff.getPhone())));
            }

            bool loggedIn = false;
            while (!loggedIn)
            {
                changeConsoleColor(9);
                cout << "\t\t\tWELCOME TO HOTEL DE LUNA\t\t\t" << endl;
                changeConsoleColor(3);
                cout << "Login as admin" << endl;
                changeConsoleColor(6);
                cout << "|---------------------------------------------------------------------------------------------|" << endl;
                changeConsoleColor(10);
                cout << "USER NAME (Your full name is written without diacritics): ";
                changeConsoleColor(7);
                cin >> inputUsername;
                inputUsername = toLower(inputUsername);
                changeConsoleColor(10);
                cout << "PASSWORD (Your phone number): ";
                changeConsoleColor(7);
                inputPasswordStr = inputPassword();
                changeConsoleColor(6);
                cout << "|---------------------------------------------------------------------------------------------|" << endl;
                loadingBarAnimation(6);
                bool loginResult = login(accounts, inputUsername, inputPasswordStr);
                if (loginResult)
                {
                    changeConsoleColor(4);
                    cout << "LOGIN SUCCESSFULLY, ENTER TO CONTINUE" << endl;
                    changeConsoleColor(7);
                    loggedIn = true;
                }
                else
                {
                    changeConsoleColor(4);
                    cout << "PLEASE LOGIN AGAIN (Username or password is incorrect)!!!!" << endl;
                    changeConsoleColor(7);
                    system("pause");
                    system("cls");
                }
            }
        }
        else if (option == 'c')
        {
            vector<Customer> customers = Customer::readFileCustomer("Customer.txt");
            vector<pair<string, string>> accounts;

            for (const auto &customer : customers)
            {
                string username = createUsername(customer.getFullName());
                accounts.push_back(make_pair(trim(username), trim(customer.getPhone())));
            }
            bool loggedIn = false;
            while (!loggedIn)
            {
                changeConsoleColor(9);
                cout << "\t\t\tWELCOME TO HOTEL DE LUNA\t\t\t" << endl;
                changeConsoleColor(3);
                cout << "Login as customer" << endl;
                changeConsoleColor(6);
                cout << "|---------------------------------------------------------------------------------------------|" << endl;
                changeConsoleColor(10);
                cout << "USER NAME (Your full name is written without diacritics): ";
                changeConsoleColor(7);
                cin >> inputUsername;
                inputUsername = toLower(inputUsername);
                changeConsoleColor(10);
                cout << "PASSWORD (Your phone number): ";
                changeConsoleColor(7);
                inputPasswordStr = inputPassword();
                changeConsoleColor(6);
                cout << "|---------------------------------------------------------------------------------------------|" << endl;

                if (login(accounts, inputUsername, inputPasswordStr))
                {
                    changeConsoleColor(4);
                    cout << "LOGIN SUCCESSFULLY" << endl;
                    changeConsoleColor(6);
                    loadingBarAnimation(7);
                    system("pause");
                    loggedIn = true;
                    changeConsoleColor(7);
                    system("cls");
                    bool continueUsing = true;
                    while (continueUsing)
                    {
                        changeConsoleColor(9);
                        cout << "\t\tWELCOME TO HOTEL DE LUNA\t\t\t" << endl;
                        changeConsoleColor(10);
                        string border = "+---------------+----------------------------------------+";
                        cout << border << endl;
                        changeConsoleColor(3);
                        cout << "|1. Check your information" << right << setw(32) << "|" << endl;
                        changeConsoleColor(10);
                        cout << border << endl;
                        changeConsoleColor(3);
                        cout << "|2. Book service" << right << setw(42) << "|" << endl;
                        changeConsoleColor(10);
                        cout << border << endl;
                        changeConsoleColor(3);
                        cout << "|3. Checkout" << right << setw(46) << "|" << endl;
                        changeConsoleColor(10);
                        cout << border << endl;
                        changeConsoleColor(3);
                        cout << "|4. Check bill" << right << setw(44) << "|" << endl;
                        changeConsoleColor(10);
                        cout << border << endl;
                        changeConsoleColor(3);
                        cout << "|0. Exit" << right << setw(50) << "|" << endl;
                        changeConsoleColor(10);
                        cout << border << endl;
                        changeConsoleColor(6);
                        cout << "Please enter your option: ";
                        changeConsoleColor(7);
                        int choice;
                        cin >> choice;

                        switch (choice)
                        {
                        case 1:
                        {
                            Customer cus;
                            vector<Service> services;
                            cus.checkInfor(inputUsername, inputPasswordStr, customers, services);
                            break;
                        }
                        case 2:
                        {
                            Customer cus;
                            cus.bookServices(inputUsername, inputPasswordStr);
                            break;
                            break;
                        }
                        case 4:
                        {
                            Bill tempBill; 
                            vector<Service> services = readFileService ("Service.txt");
                            vector<Room> rooms = Room::readFileRoom("Room.txt");
                            tempBill.checkBillInfo(inputUsername, inputPasswordStr, customers, rooms, services);

                            system("pause"); 
                            break;
                        }
                        case 0:
                        {
                            changeConsoleColor(3);
                            cout << "Hope to see you again~~~" << endl;
                            changeConsoleColor(7);
                            continueUsing = false;
                            break;
                        }
                        default:
                        {
                            cout << "Invalid option, please try again." << endl;
                            break;
                        }
                        }
                        if (continueUsing)
                        {
                            char continueChoice;
                            changeConsoleColor(6);
                            cout << "Do you want to continue? (y/n): ";
                            changeConsoleColor(7);
                            cin >> continueChoice;
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
                    cout << "PLEASE LOGIN AGAIN (Username or password is incorrect)!!!!" << endl;
                    changeConsoleColor(7);
                    system("pause");
                    system("cls");
                }
            }
        }
    }
    return 0;
}