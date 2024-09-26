#ifndef DATE_H
#define DATE_H
#include <string>
#include <iostream> 

using namespace std; 
class Date{
    private:
        int day, month, year;
    public:
        Date(){};
        Date(const Date& d);
        Date(int day, int month, int year);
        void display();
        void standardizeDate();
        bool isLeapYear(int year) const;
        ~Date();

        bool setDay (const int& day);
        int getDay () const;
        bool setMonth (const int& month);
        int getMonth () const;
        bool setYear (const int& year);
        int getYear () const;
};
#endif