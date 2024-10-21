#include "Person.cpp"
#include "Room.cpp"
#include "Date.cpp"
#include "Customer.cpp"
#include "Staff.cpp"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <windows.h>
#include <algorithm>

using namespace std;

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void loadingBarAnimation() {
    const int totalProgress = 100; 
    const int barWidth = 50;

    for (int progress = 0; progress <= totalProgress; ++progress) {
        int completedWidth = barWidth * progress / totalProgress;

        cout << "\r[";
        for (int i = 0; i < barWidth; ++i) {
            cout << (i < completedWidth ? "=" : " ");
        }
        cout << "] " << progress << "%";
        cout.flush();

        Sleep(5);
    }

    cout << endl;
}

static inline string trim(string s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !isspace(ch);
    }));
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !isspace(ch);
    }).base(), s.end());
    return s;
}

string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

string createUsername(const string& fullName) {
    string username = fullName;
    username.erase(remove(username.begin(), username.end(), ' '), username.end());
    return toLower(username); 
}

string inputPassword() {
    string password;
    char ch;
    while ((ch = _getch()) != 13) { // 13 is Enter
        if (ch == 8) { // 8 is Backspace
            if (!password.empty()) {
                cout << "\b \b"; // erase last '*'
                password.pop_back();
            }
        } else if (isprint(ch)) {
            password.push_back(ch);
            cout << '*'; // show '*' for each character
        }
    }
    cout << endl;
    return password;
}

bool login(const vector<pair<string, string>>& accounts, const string& username, const string& password) {
    for (const auto& account : accounts) {
        if (account.first == username && account.second == password) {
            return true;
        }
    }
    return false;
}

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
            ifstream file("Staff.txt");
            vector<pair<string, string>> accounts;
            string line;

            if (!file.is_open()) {
                cout << "Cannot open file!" << endl;
                return 1;
            }

            while (getline(file, line)) {
                stringstream ss(line);
                string fullName, CCCD, phone, address, gender, dob, position, salary;

                getline(ss, fullName, '|');
                getline(ss, CCCD, '|');
                getline(ss, phone, '|');
                getline(ss, address, '|');
                getline(ss, gender, '|');
                getline(ss, dob, '|');
                getline(ss, position, '|');
                getline(ss, salary, '|');

                string username = createUsername(fullName);
                accounts.push_back(make_pair(trim(username), trim(phone)));
            }

            file.close();

            bool loggedIn = false;
            while (!loggedIn) {
                setColor(9);
                cout << "\t\t\tWELCOME TO HOTEL DE LUNA\t\t\t" << endl;
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
            ifstream file("Customer.txt");
            vector<pair<string, string>> accounts;
            string line;

            if (!file.is_open()) {
                cout << "Cannot open file!" << endl;
                return 1;
            }

            while (getline(file, line)) {
                stringstream ss(line);
                string fullName, CCCD, phone, add, gender, DOBstr, roomIDStr, arrivalDateStr;
                Date DOB, arrivalDate;

                getline(ss, fullName, '|');
                getline(ss, CCCD, '|');
                getline(ss, phone, '|');
                getline(ss, add, '|');
                getline(ss, DOBstr, '|');
                DOB = Date(DOBstr);
                getline(ss, gender, '|');

                vector<string> roomIDs;
                getline(ss, roomIDStr, '|');

                stringstream roomIDStream(roomIDStr);
                string roomID;
                while (getline(roomIDStream, roomID, ',')) {
                    roomIDs.push_back(roomID);
                }
                getline(ss, arrivalDateStr);
                arrivalDate = Date(arrivalDateStr);

                string username = createUsername(fullName);
                accounts.push_back(make_pair(trim(username), trim(phone)));
            }

            file.close();
            bool loggedIn = false;
            while (!loggedIn) {
                setColor(9);
                cout << "\t\t\tWELCOME TO HOTEL DE LUNA\t\t\t" << endl;
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
                    setColor(9);
                    cout << "\t\tWELCOME TO HOTEL DE LUNA\t\t\t" << endl;
                    setColor(10);
                    string border = "+---------------+----------------------------------------+";
                    cout << border << endl;
                    setColor(3);
                    cout << "|1. Search for available room" << right << setw(31) << "|" << endl;
                    setColor(10);
                    cout << border << endl;
                    setColor(3);
                    cout << "|2. Book room" << right << setw(46) << "|" << endl;
                    setColor(10);
                    cout << border << endl;
                    setColor(3);
                    cout << "|3. Check your information" << right << setw(33) << "|" << endl;
                    setColor(10);
                    cout << border << endl;
                    setColor(3);
                    cout << "|4. Checkout" << right << setw(47) << "|" << endl;
                    setColor(10);
                    cout << border << endl;
                    setColor(3);
                    cout << "|5. Exit" << right << setw(51) << "|" << endl;
                    setColor(10);
                    cout << border << endl;
                    setColor(6);
                    cout << "Please enter your option: ";
                    setColor(7);
                } else {
                    setColor(4);
                    cout << "PLEASE LOGIN AGAIN (Username or password is incorrect)!!!!" << endl;
                    system("pause");
                    setColor(7);
                    system("cls");
                }
            }
        } else if (option == 'e') {
            return 0;
        }
    }
    return 0;
}
