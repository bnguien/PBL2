#ifndef LOGIN_H
#define LOGIN_H

#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <conio.h>
#include <iostream>

using namespace std;

static inline string trim(string s);
string toLower(string s);
string createUsername(const string& fullName);
string inputPassword();
bool login(const vector<pair<string, string>>& accounts, const string& username, const string& password);

#endif
