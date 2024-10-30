#ifndef DATE_H
#define DATE_H

#include "Function.h"

using namespace std; 

class Date {
private:
    int day, month, year;

public:
    Date(); 
    Date(int day, int month, int year);
    Date(const string& dateStr);
    ~Date();

    void display() const;
    bool isLeapYear(int year) const;
    bool setDay(const int& day);
    int getDay() const;
    bool setMonth(const int& month);
    int getMonth() const;
    bool setYear(const int& year);
    int getYear() const;
    string toString() const;
    static string getCurrentDate();
    int daysInMonth(int month, int year) const;
    static int daysBetween(const Date &start, const Date &end);
    bool isValid() const;

    friend ostream& operator << (ostream& os, const Date& date);
};
#endif
