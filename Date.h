#ifndef DATE_H
#define DATE_H
#include <string>
#include <iostream> 

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
};
#endif
