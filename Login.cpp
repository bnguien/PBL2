#include "login.h"
#include <windows.h>

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
