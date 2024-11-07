#ifndef SERVICE_H
#define SERVICE_H

#include "Customer.h"

using namespace std;
class Service
{
private:
     string ID, name, type, description, price;

public:
     Service();
     Service(const Service &s);
     Service(const string &ID, const string &name, const string &type, const string &description, const string &price);

     string getID() const;
     string getName() const;
     string getType() const;
     string getDesc() const;
     string getPrice() const;

     static string generateSerID(const vector<Service> &services, const string &name);
     static string getServiceName(const string &serviceID, const vector<Service> &services);
     friend void displayService(const vector<Service> &services);
     static vector<Service> readFileService(const string &fileName);
     ~Service();
     // friend class Admin;
};

#endif