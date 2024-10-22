#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <ctype.h>
#include <sstream>
#include "Date.h"

using namespace std;

Date::Date() : day(1), month(1), year(1) {}

Date::Date(int day, int month, int year)
{
    setYear(year);
    setMonth(month);
    setDay(day);
}

Date::Date(const string &dateStr)
{
    stringstream ss(dateStr);
    string token;
    getline(ss, token, '/');
    try
    {
        day = stoi(token);
    }
    catch (const invalid_argument &e)
    {
        cout << "Invalid input for day: " << token << endl;
        return;
    }
    getline(ss, token, '/');
    try
    {
        month = stoi(token);
    }
    catch (const invalid_argument &e)
    {
        cout << "Invalid input for month: " << token << endl;
        return;
    }
    getline(ss, token, '/');
    try
    {
        year = stoi(token);
    }
    catch (const invalid_argument &e)
    {
        cout << "Invalid input for year: " << token << endl;
        return;
    }
    if (!setMonth(month) || !setYear(year) || !setDay(day))
    {
        cout << "Invalid date: " << dateStr << endl;
    }
}

Date::~Date() {}

bool Date::isLeapYear(int year) const
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool Date::setDay(const int &day)
{
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month < 1 || month > 12)
    {
        cout << "Invalid month" << endl;
        return false;
    }

    if (isLeapYear(year))
    {
        daysInMonth[1] = 29;
    }

    if (day < 1 || day > daysInMonth[month - 1])
    {
        cout << "Invalid day for the given month" << endl;
        return false;
    }
    this->day = day;
    return true;
}

int Date::getDay() const
{
    return day;
}

bool Date::setMonth(const int &month)
{
    if (month < 1 || month > 12)
    {
        cout << "Invalid month" << endl;
        return false;
    }
    this->month = month;
    return true;
}

int Date::getMonth() const
{
    return month;
}

bool Date::setYear(const int &year)
{
    if (year < 1)
    {
        cout << "Invalid year" << endl;
        return false;
    }
    this->year = year;

    if (month == 2 && day == 29 && !isLeapYear(year))
    {
        cout << "Invalid day for non-leap year" << endl;
        return false;
    }
    return true;
}

int Date::getYear() const
{
    return year;
}

void Date::display() const
{
    string dayStr = to_string(this->day);
    string monthStr = to_string(this->month);
    string yearStr = to_string(this->year);

    if (dayStr.length() == 1)
    {
        dayStr = "0" + dayStr;
    }
    if (monthStr.length() == 1)
    {
        monthStr = "0" + monthStr;
    }
    cout << dayStr + "/" + monthStr + "/" + yearStr;
}

string Date::toString() const
{
    stringstream ss;
    ss << setw(2) << setfill('0') << day << "/"
       << setw(2) << setfill('0') << month << "/"
       << year;
    return ss.str();   
}

ostream& operator << (ostream& os, const Date& date)
{
    os << setw(2) << setfill('0') << date.getDay() << "/"
       << setw(2) << setfill('0') << date.getMonth() << "/"
       << date.getYear();
    return os;
}