/*void loadingBarAnimation() {
    const int totalProgress = 100; // Total progress value (e.g., 100%)
    const int barWidth = 50; // Width of the loading bar in characters

    for (int progress = 0; progress <= totalProgress; ++progress) {
        int completedWidth = barWidth * progress / totalProgress;

        cout << "\r[";
        for (int i = 0; i < barWidth; ++i) {
            if (i < completedWidth) {
                cout << "=";
            } else {
                cout << " ";
            }
        }
        cout << "] " << progress << "%";
        cout.flush();

        // Add a small delay to control the speed of the animation
        Sleep(5);
    }

    cout << std::endl;
}*/
/*string getCurrentDate() {
    // Get the current time
    time_t now = time(nullptr);
    // Create a buffer to store the formatted date
    char buffer[80];
    // Format the current time as a string with the desired format
    strftime(buffer, sizeof(buffer), "%d-%m-%Y", localtime(&now));
    // Convert the buffer to a string and return it
    return string(buffer);
}
*/
/*Test thử thoi chứ chưa chính thức nha*/
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

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
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
    while ((ch = _getch()) != 13) { 
        if (ch == 8) {
            if (!password.empty()) {
                cout << "\b \b";
                password.pop_back();
            }
        } else {
            password.push_back(ch);
            cout << '*';
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
    cout<<"\t\t\tWELCOME TO HOTEL DE LUNA\t\t\t"<<endl;
    cout<<"******************************************************************"<<endl;
    cout<<"Login as"<<endl;
    cout<<"ADMIN LOGIN - press a"<<endl;
    cout<<"CUSTOMER LOGIN - press c"<<endl;
    cout<<"EXIT PROGRAM - press e"<<endl;
    int option = getch();
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
        setColor(6);
        cout<<"|---------------------------------------------------------------------------------------------|"<<endl;
        setColor(10);
        cout << "USER NAME (Your full name is written without diacritics): ";
        setColor(7);
        cin >> inputUsername;
        inputUsername = toLower(inputUsername);
        setColor(10);
        cout <<"PASSWORD (Your phone number)                            : ";
        setColor(7);
        inputPasswordStr = inputPassword();
        setColor(6);
        cout<<"|---------------------------------------------------------------------------------------------|"<<endl;
        
        if (login(accounts, inputUsername, inputPasswordStr)) {
            setColor(4);
            cout << "LOGIN SUCCESSFULLY, ENTER TO CONTINUE" << endl;
            setColor(7);
        } else {
            setColor(4);
            cout << "PLEASE LOGIN AGAIN (Username or password is incorrect)!!!!" << endl;
            setColor(7);
        }
    } else if (option == 'c') {
        ifstream file("Customer.txt");
        vector<pair<string, string>> accounts; // Changed from customers to accounts
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
            arrivalDate = Date(arrivalDateStr); // Fixed spelling mistake here

            // Create Customer object but you only need username and phone for login
            string username = createUsername(fullName);
            accounts.push_back(make_pair(trim(username), trim(phone))); // Add to accounts for login
        }

        file.close();
        setColor(6);
        cout<<"|---------------------------------------------------------------------------------------------|"<<endl;
        setColor(10);
        cout << "USER NAME (Your full name is written without diacritics): ";
        setColor(7);
        cin >> inputUsername;
        inputUsername = toLower(inputUsername);
        setColor(10);
        cout <<"PASSWORD (Your phone number)                            : ";
        setColor(7);
        inputPasswordStr = inputPassword();
        setColor(6);
        cout<<"|---------------------------------------------------------------------------------------------|"<<endl;
        
        if (login(accounts, inputUsername, inputPasswordStr)) { // Corrected to accounts
            setColor(4);
            cout << "LOGIN SUCCESSFULLY, ENTER TO CONTINUE" << endl;
            setColor(7);
        } else {
            setColor(4);
            cout << "PLEASE LOGIN AGAIN (Username or password is incorrect)!!!!" << endl;
            setColor(7);
        }
    }
    else if (option == 'e')
    {
        return 0;
    }
    return 0;
}
