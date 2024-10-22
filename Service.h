#ifndef SERVICE_H
#define SERVICE_H
#include <vector>
#include <iostream>
#include <string>
#include <windows.h>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;
class Service {
private:
     string ID, name, type, description, price;
public:
     Service ();
     Service (const Service &s);
     Service (const vector<string> &service_info);

     static string getServiceName(const string& id, const vector<Service>& services);
     friend void displayService (const vector<Service> &services);

     ~Service ();
     //friend class Admin;
};

vector<Service> readFileService(const string &fileName);

#endif