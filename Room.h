#ifndef ROOM_H
#define ROOM_H
#include <string>
#include <vector>

class Room
{
private:
     string ID;
     string type;
     string price;
     string status;
     vector<string> serviceIDs;
public:
     Room() {}
     Room(string ID, string type, string price, string status, vector<string> serviceIDs = {"None"}) : 
                              ID(ID), type(type), price(price), status(status), serviceIDs(serviceIDs) {}
     Room(const Room &R) : ID(R.ID), type(R.type), price(R.price), status(R.status), serviceIDs(R.serviceIDs) {}

     void setID(const string &ID);
     string getID() const;
     bool setType(const string &type);
     string getType() const;
     void setPrice(const string &price);
     string getPrice() const;
     bool setStatus(const string &status);
     string getStatus() const;
     void setServiceIDs (const vector<string> serviceIDs);
     vector<string> getServiceIDs() const;

     bool checkAvailable ();
     static vector<Room> readFileRoom(const string& fileName);
     static void printRoom(const vector<Room>& rooms);
     static void updateRoomFile(const vector<Room> &rooms, const string &fileRoom);
     void addServiceByRoomID(const string &roomID, const vector<string> &serviceIDs);
     ~Room() {}
};

#endif