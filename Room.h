#ifndef ROOM_H
#define ROOM_H
#include <string>

class Room {
private:
     string ID;
     string type; //single, double, suite, delux, standard
     string price;
     string status; //booked, unbooked
public:
     Room () {}
     Room (string ID, string type, string price, string status) : ID(ID), type(type), price(price), status(status) {}
     Room (const Room &R) {
          this->ID = R.ID;
          this->type = R.type;
          this->price = R.price;
          this->status = R.status;
    }

     void setID (const string& ID);
     string getID () const ;
     bool setType (const string& type);
     string getType () const ;
     void setPrice (const string& price);
     string getPrice () const ;
     bool setStatus (const string& status);
     string getStatus () const;
     bool setView (const int& view);
     
     ~ Room () {}
};

#endif