#ifndef DATE_H
#define DATE_H

#include "Function.h"

using namespace std;

class Date
{
private:
    int day, month, year;

public:
    Date() : day(1), month(1), year(1) {}
    Date(int day, int month, int year);
    Date(const string &dateStr);
    ~Date() {}

    void display() const;
    bool setDay(const int &day);
    int getDay() const;
    bool setMonth(const int &month);
    int getMonth() const;
    bool setYear(const int &year);
    int getYear() const;
    string toString() const;
    int daysInMonth(int month, int year) const;

    static int daysBetween(const Date &start, const Date &end);
    static Date getCurrentDate();
    static bool isValid(int day, int month, int year);
    static bool isValidDateFormat(const string &dateStr);
    static bool isLeapYear(int year);
    static bool isNumber(const string &str);

    bool operator==(const Date &other) const;
    bool operator>(const Date &other) const;
    friend ostream &operator<<(ostream &os, const Date &date);
};
#endif
