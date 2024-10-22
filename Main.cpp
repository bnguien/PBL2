#include "Login.cpp" 
#include "Person.cpp"
#include "Room.cpp"
#include "Date.cpp"
#include "Customer.cpp"
#include "Staff.cpp"
#include "Service.cpp"
#include "Utility.cpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <windows.h>

using namespace std;

int main() {
    string choice;
    setColor(9);
    cout << "\t\t\tWELCOME TO HOTEL DE LUNA\t\t\t" << endl;
    setColor(3);
    cout << "Do you already have an account? (yes/no)" << endl;
    setColor(7);
    cin >> choice;

    if (choice == "no") {
        system("cls");
        setColor(9);
        cout << "\t\t\tWELCOME TO HOTEL DE LUNA\t\t\t" << endl;
        setColor(11);
        cout << "Don't miss out! Let's get your room booked right now!" << endl;
        system("pause");
        setColor(7);
        Customer customer; 
        customer.bookedRoom();
    } else if (choice == "yes") {
        system("cls");
        char option;
        cout << "******************************************************************" << endl;
        setColor(9);
        cout << "\t\t\tWELCOME TO HOTEL DE LUNA\t\t\t" << endl;
        setColor(14);
        cout << "Login as" << endl;
        cout << "ADMIN LOGIN - press a" << endl;
        cout << "CUSTOMER LOGIN - press c" << endl;
        cout << "EXIT PROGRAM - press e" << endl;
        setColor(7);
        option = _getch();
        system("cls");
        string inputUsername, inputPasswordStr;

        if (option == 'a') {
            vector<Staff> staffs = Staff::readFileStaff("Staff.txt");
            vector<pair<string, string>> accounts;

            for (const auto& staff : staffs) {
                string username = createUsername(staff.getFullName());
                accounts.push_back(make_pair(trim(username), trim(staff.getPhone())));
             }

            bool loggedIn = false;
            while (!loggedIn) {
                setColor(9);
                cout << "\t\t\tWELCOME TO HOTEL DE LUNA\t\t\t" << endl;
                setColor (3);
                cout << "Login as admin" << endl;
                setColor(6);
                cout << "|---------------------------------------------------------------------------------------------|" << endl;
                setColor(10);
                cout << "USER NAME (Your full name is written without diacritics): ";
                setColor(7);
                cin >> inputUsername;
                inputUsername = toLower(inputUsername);
                setColor(10);
                cout << "PASSWORD (Your phone number): ";
                setColor(7);
                inputPasswordStr = inputPassword();
                setColor(6);
                cout << "|---------------------------------------------------------------------------------------------|" << endl;
                loadingBarAnimation();
                bool loginResult = login(accounts, inputUsername, inputPasswordStr);
                if (loginResult) {
                    setColor(4);
                    cout << "LOGIN SUCCESSFULLY, ENTER TO CONTINUE" << endl;
                    setColor(7);
                    loggedIn = true;
                } else {
                    setColor(4);
                    cout << "PLEASE LOGIN AGAIN (Username or password is incorrect)!!!!" << endl;
                    setColor(7);
                    system("pause");
                    system("cls");
                }
            }
        } else if (option == 'c') {
            vector<Customer> customers = Customer::readFileCustomer("Customer.txt");
            vector<pair<string, string>> accounts;

            for (const auto& customer : customers) {
                string username = createUsername(customer.getFullName());
                accounts.push_back(make_pair(trim(username), trim(customer.getPhone())));
             }
            bool loggedIn = false;
            while (!loggedIn) {
                setColor(9);
                cout << "\t\t\tWELCOME TO HOTEL DE LUNA\t\t\t" << endl;
                setColor (3);
                cout << "Login as customer" << endl;
                setColor(6);
                cout << "|---------------------------------------------------------------------------------------------|" << endl;
                setColor(10);
                cout << "USER NAME (Your full name is written without diacritics): ";
                setColor(7);
                cin >> inputUsername;
                inputUsername = toLower(inputUsername);
                setColor(10);
                cout << "PASSWORD (Your phone number): ";
                setColor(7);
                inputPasswordStr = inputPassword();
                setColor(6);
                cout << "|---------------------------------------------------------------------------------------------|" << endl;

                if (login(accounts, inputUsername, inputPasswordStr)) {
                    setColor(4);
                    cout << "LOGIN SUCCESSFULLY" << endl;
                    setColor(6);
                    loadingBarAnimation();
                    system("pause");
                    loggedIn = true;
                    setColor(7);
                    system("cls");
                    bool continueUsing = true; 
                    while (continueUsing) {
                        setColor(9);
                        cout << "\t\tWELCOME TO HOTEL DE LUNA\t\t\t" << endl;
                        setColor(10);
                        string border = "+---------------+----------------------------------------+";
                        cout << border << endl;
                        setColor(3);
                        cout << "|1. Check your information" << right << setw(32) << "|" << endl;
                        setColor(10);
                        cout << border << endl;
                        setColor(3);
                        cout << "|2. Book service" << right << setw(42) << "|" << endl;
                        setColor(10);
                        cout << border << endl;
                        setColor(3);
                        cout << "|3. Checkout" << right << setw(46) << "|" << endl;
                        setColor(10);
                        cout << border << endl;
                        setColor(3);
                        cout << "|4. Check bill" << right << setw(44) << "|" << endl;
                        setColor(10);
                        cout << border << endl;
                        setColor(3);
                        cout << "|0. Exit" << right << setw(50) << "|" << endl;
                        setColor(10);
                        cout << border << endl;
                        setColor(6);
                        cout << "Please enter your option: ";
                        setColor(7);
                        int choice;
                        cin >> choice;

                        switch(choice){
                            case 1:
                            {
                                Customer cus;
                                vector<Service> services;
                                cus.checkInfor(inputUsername, customers, services); 
                                break;
                            }
                            case 2:
                            {
                                //Xử lý đặt dịch vụ 
                                break;
                            }
                            case 3: 
                            {
                                // Xử lý checkout
                                break;
                            }
                            case 4:
                            {
                                //Xử lý kiểm tra hóa đơn
                                break;
                            }
                            case 0:
                            {   
                                setColor(3);
                                cout<<"Hope to see you again~~~"<<endl;
                                setColor(7);
                                continueUsing = false;
                                break;
                            }
                            default:
                            {
                                cout << "Invalid option, please try again." << endl;
                                break;
                            }
                        }
                        if (continueUsing) {
                            char continueChoice;
                            setColor(6);
                            cout << "Do you want to continue? (y/n): ";
                            setColor(7);
                            cin >> continueChoice;
                            system("cls");
                            if (tolower(continueChoice) != 'y') {
                                continueUsing = false; 
                            }
                        }
                    }
                } else {
                    setColor(4);
                    cout << "PLEASE LOGIN AGAIN (Username or password is incorrect)!!!!" << endl;
                    setColor(7);
                    system("pause");
                    system("cls");
                }
            }
        }
    }
    return 0;
}