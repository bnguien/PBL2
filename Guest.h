#ifndef GUEST_H
#define GUEST_H
#include "Person.h"
#include "Date.h"
#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Guest : public Person
{
    private: 
        string ID; //ID của khách
        string status; //Trạng thái của khách
        vector<string> roomID; //Danh sách ID phòng
        Date arrivalDate; //Ngày đến
    public:
        Guest(): Person() {}
        Guest(const Guest &g) : Person(g) 
            {
                this->ID=g.ID;
                this->status=g.status;
                this->roomID=g.roomID;
                this->arrivalDate=g.arrivalDate
            }
        Guest(vector<string>info, vector<string>ID, vector<Date> dates);
        void display();
        ~Guest();
};
#endif