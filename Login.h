#ifndef LOGIN_H
#define LOGIN_H

#include "Vector.h"
using namespace std;

string toLower(string s);
string createUsername(const string& fullName);
string inputPassword();
bool login(const vector<pair<string, string>>& accounts, const string& username, const string& password);
void loadingBarAnimation(int color=7);
string trim(string s);

#endif 
