#ifndef ROOM_H
#define ROOM_H
#include <string>

class Room {
private:
     string ID;
     string type; //single, double, suite, delux, standard
     string price;
     string status; //booked, unbooked
     int view;
public:
     Room () {}
     Room (string ID, string type, string price, string status, int view) : ID(ID), type(type), price(price), status(status), view(view) {}
     Room (const Room &R) {
          this->ID = R.ID;
          this->type = R.type;
          this->price = R.price;
          this->status = R.status;
          this->view = R.view;
     }

     void setID (const string& ID);
     string getID ();
     bool setType (const string& type);
     string getType ();
     void setPrice (const string& price);
     string getPrice ();
     bool setStatus (const string& status);
     string getStatus ();
     bool setView (const int& view);
     int getView ();

     ~ Room () {}
};

#endif