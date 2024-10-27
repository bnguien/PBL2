#ifndef LOGIN_H
#define LOGIN_H

#include "Function.h"
#include "Vector.h"

using namespace std;

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
void changeConsoleColor(int colorCode=7)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
}
void loadingBarAnimation(int color=7)
{
    const int totalProgress = 100; 
    const int barWidth = 40;       
    string spinner = "|/-\\";    

    changeConsoleColor(color);
    for (int progress = 0; progress <= totalProgress; ++progress)
    {
        int completedWidth = barWidth * progress / totalProgress;

        cout << "\rLoading [";
        for (int i = 0; i < barWidth; ++i)
        {
            if (i < completedWidth)
            {
                cout << "-"; // Thanh đầy
            }
            else
            {
                cout << " "; // Thanh trống
            }
        }
        cout << "] " << progress << "% "
             << spinner[progress % spinner.size()]; // Hiệu ứng xoay

        cout.flush(); // Đảm bảo in ra ngay lập tức

        Sleep(30); // Windows (30ms)
    }
    cout << endl;
    changeConsoleColor(7);
}

inline string trim(string s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
    return s;
}
#endif
