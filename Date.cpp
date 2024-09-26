#include<iostream>
#include "Date.h"

Date::Date(const Date& d){
    this->day=d.day;
    this->month=d.month;
    this->year=d.year;
}

Date::Date(int day, int month, int year){
    this->day=day;
    this->month=month;
    this->year=year;
}

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