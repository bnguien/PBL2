#include "Date.h"

using namespace std;

Date::Date(int day, int month, int year)
{
    if (!isValid(day, month, year))
    {
        changeConsoleColor(4);
        cout << "\nInvalid day, month, year!" << endl;
        changeConsoleColor(7);
        this->day = 1;
        this->month = 1;
        this->year = 1;
    }
    else
    {
        this->day = day;
        this->month = month;
        this->year = year;
    }
}

Date::Date(const string &dateStr)
{
    if (!isValidDateFormat(dateStr))
    {
        changeConsoleColor(4);
        cout << "Invalid date format!\n";
        changeConsoleColor(7);
        this->day = 1;
        this->month = 1;
        this->year = 1;
    }
    else
    {
        std::stringstream ss(dateStr);
        std::string token;
        getline(ss, token, '/');
        day = std::stoi(token);

        getline(ss, token, '/');
        month = std::stoi(token);

        getline(ss, token, '/');
        year = std::stoi(token);
        
        if (!isValid(day, month, year))
        {
            changeConsoleColor(4);
            cout << "\nInvalid day, month, year!" << endl;
            changeConsoleColor(7);
            this->day = 1;
            this->month = 1;
            this->year = 1;
        }
        else
        {
            this->day = day;
            this->month = month;
            this->year = year;
        }
    }
}

bool Date::isValidDateFormat(const string &dateStr)
{
    if (dateStr.length() != 10)
        return false;
    if (dateStr[2] != '/' || dateStr[5] != '/')
        return false;

    int day, month, year;
    std::string dayStr = dateStr.substr(0, 2);
    std::string monthStr = dateStr.substr(3, 2);
    std::string yearStr = dateStr.substr(6, 4);

    if (!isNumber(dayStr) || !isNumber(monthStr) || !isNumber(yearStr))
        return false;

    day = std::stoi(dayStr);
    month = std::stoi(monthStr);
    year = std::stoi(yearStr);

    return isValid(day, month, year);
}

bool Date::isValid(int day, int month, int year)
{
    if (year <= 0)
        return false;
    if (month < 1 || month > 12)
        return false;

    int daysInMonth[] = {31, isLeapYear(year) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (day < 1 || day > daysInMonth[month - 1])
        return false;

    return true;
}

bool Date::isNumber(const string &str)
{
    for (char c : str)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

bool Date::isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool Date::setDay(const int &day)
{
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month < 1 || month > 12)
    {
        return false;
    }

    if (isLeapYear(year))
    {
        daysInMonth[1] = 29;
    }

    if (day < 1 || day > daysInMonth[month - 1])
    {
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
        return false;
    }
    this->year = year;

    if (month == 2 && day == 29 && !isLeapYear(year))
    {
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

Date Date::getCurrentDate()
{
    auto now = std::chrono::system_clock::now();
    std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
    std::tm localTime = *std::localtime(&nowTime);

    int day = localTime.tm_mday;
    int month = localTime.tm_mon + 1;
    int year = localTime.tm_year + 1900;

    return Date(day, month, year);
}

int Date::daysInMonth(int month, int year) const
{
    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2:
        return isLeapYear(year) ? 29 : 28;
    default:
        return 0;
    }
}

int Date::daysBetween(const Date &start, const Date &end)
{
    if (start.year > end.year ||
        (start.year == end.year && start.month > end.month) ||
        (start.year == end.year && start.month == end.month && start.day > end.day))
    {
        return -daysBetween(end, start);
    }

    int days = 0;
    if (start.year == end.year && start.month == end.month)
    {
        return end.day - start.day;
    }
    if (start.year == end.year)
    {
        days += start.daysInMonth(start.month, start.year) - start.day;
        for (int m = start.month + 1; m < end.month; ++m)
        {
            days += start.daysInMonth(m, start.year);
        }
        days += end.day;
        return days;
    }
    days += start.daysInMonth(start.month, start.year) - start.day;
    for (int m = start.month + 1; m <= 12; ++m)
    {
        days += start.daysInMonth(m, start.year);
    }
    for (int y = start.year + 1; y < end.year; ++y)
    {
        days += start.isLeapYear(y) ? 366 : 365;
    }
    for (int m = 1; m < end.month; ++m)
    {
        days += end.daysInMonth(m, end.year);
    }
    days += end.day;

    return days;
}

bool Date::operator==(const Date &other) const
{
    return (day == other.day && month == other.month && year == other.year);
}
bool Date::operator>(const Date &other) const
{
    if (year != other.year)
        return year > other.year;
    if (month != other.month)
        return month > other.month;
    return day > other.day;
}

ostream &operator<<(ostream &os, const Date &date)
{
    os << setw(2) << setfill('0') << date.getDay() << "/"
       << setw(2) << setfill('0') << date.getMonth() << "/"
       << date.getYear();
    return os;
}