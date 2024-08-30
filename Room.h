#ifndef ROOM_H
#define ROOM_H
#include <string>

class Room {
private:
     string ID;
     string type; //1. single, 2. double, 3. suite, 4. delux, 5. standard
     string price;
     int status; //1. booked, 2. unbooked
     int view;
public:
     Room () {}
     Room (string ID, string type, string price, int status, int view) : ID(ID), type(type), price(price), status(status), view(view) {}

     void setID (const string& ID);
     string getID ();
     void setType (const string& type);
     string getType ();
     void setPrice (const string& price);
     string getPrice ();
     bool setStatus (const int& status);
     int getStatus ();
     bool setView (const int& view);
     int getView ();
};

#endif