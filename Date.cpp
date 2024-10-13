#include <iostream>
#include <string>
#include<fstream>
#include<vector>
#include <ctype.h>
#include <sstream>
#include "Date.h"
using namespace std;

Date::Date(int day, int month, int year){
    this->day=day;
    this->month=month;
    this->year=year;
}

Date::Date(const string& dateStr) {
    stringstream ss(dateStr);
    string token;

    getline(ss, token, '/');
    try {
        day = stoi(token); 
    } catch (const invalid_argument& e) {
        cout << "Invalid input for day: " << token << endl;
        return;
    }

    getline(ss, token, '/');
    try {
        month = stoi(token);
    } catch (const invalid_argument& e) {
        cout << "Invalid input for month: " << token << endl;
        return;
    }

    getline(ss, token, '/');
    try {
        year = stoi(token); 
    } catch (const invalid_argument& e) {
        cout << "Invalid input for year: " << token << endl;
        return;
    }

    if (!setDay(day) || !setMonth(month) || !setYear(year)) {
        cout << "Invalid date: " << dateStr << endl;
    }
}


Date::~Date(){}

bool Date::isLeapYear(int year) const{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        return true;
    }
    return false;
}

bool Date::setDay (const int& day){
    int daysInMonth[]= { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (isLeapYear(year)) {
        daysInMonth[1] = 29; 
    }
    if (month < 1 || month > 12) {
        cout << "Invalid month" << endl;
        return false;
    }
    if (day < 1 || day > daysInMonth[month - 1]) {
        cout << "Invalid day for the given month" << endl;
        return false;
    }
    this->day=day;
    return true;
}
int Date::getDay () const {
    return day;
}

bool Date::setMonth (const int& month){
    if (month < 1 || month > 12) {
        cout << "Invalid month" << endl;
        return false;
    }
    this->month=month;
    return true;
}
int Date::getMonth () const {
    return month;
}

bool Date::setYear (const int& year){
    if(year < 1) {
        cout << "Invalid year" << endl;
        return false;
    }
    this->year = year;
    if (month == 2 && day == 29 && !isLeapYear(year)) {
        cout << "Invalid day for non-leap year" << endl;
        return false;
    }
    return true;
}
int Date::getYear () const {
    return year;
}
void Date::display(){
		  string day = to_string(this->day);
		  string month = to_string(this->month);
		  string year = to_string(this->year);
		  if (day.length() == 1) {
			  day = "0" + day;
		  }
		  if (month.length() == 1) {
			  month = "0" + month;
		  }
		  cout << day + "/" + month + "/" + year << endl;
	 
}