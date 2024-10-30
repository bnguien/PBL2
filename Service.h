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
     Service(const vector<string> &service_info);

     string getID() const;
     string getName() const;
     string getType() const;
     string getDesc() const;
     string getPrice() const;

     static string getServiceName(const string &id, const vector<Service> &services);
     friend void displayService(const vector<Service> &services);

     ~Service();
     // friend class Admin;
};
vector<Service> readFileService(const string &fileName);
#endif