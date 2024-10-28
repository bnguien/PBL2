// Login.h
#ifndef LOGIN_H
#define LOGIN_H
#include <math.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <algorithm>
#include <iomanip>
#include <ctype.h>
#include <utility>
#include <cstdlib>
#include <string.h>
#include <conio.h>
#include <unordered_set>
#include <cctype>
#include <initializer_list>
#include <stdexcept>
#include "Vector.h"

using namespace std;

string toLower(string s);
string createUsername(const string& fullName);
string inputPassword();
bool login(const vector<pair<string, string>>& accounts, const string& username, const string& password);
void changeConsoleColor(int colorCode=7);
void loadingBarAnimation(int color=7);
string trim(string s);

#endif // LOGIN_H
