#include "Service.h"
#include "Utility.h"

Service::Service() {}
Service::Service(const Service &s) : ID(s.ID), name(s.name), type(s.type), description(s.description), price(s.price) {}
Service::Service(const vector<string> &service_info)
{
     ID = service_info[0];
     name = service_info[1];
     type = service_info[2];
     description = service_info[3];
     price = service_info[4];
}
Service::~Service () {}
void displayService(const vector<Service> &services)
{
     for (const auto &service : services)
     {
          string border = "+---------------+-----------------------------------+";
          Sleep(1000);
          cout << border << endl;
          cout << "| Service ID    | " << left << setw(34) << service.ID << "|" << endl;

          if (service.name == "Food")
               changeConsoleColor(9);
          else if (service.name == "Snack")
               changeConsoleColor(10);
          else if (service.name == "Drinks")
               changeConsoleColor(6);
          else if (service.name == "Laundary")
               changeConsoleColor(5);
          cout << border << endl;
          
          cout << "| Service Name  | " << left << setw(34) << service.name << "|" << endl;
          cout << border << endl;
          changeConsoleColor (12);
          cout << "| Service Type  | " << left << setw(34) << service.type << "|" << endl;
          cout << border << endl;
          changeConsoleColor (8);
          cout << "| Service Desc  | " << left << setw(34) << service.description << "|" << endl;
          cout << border << endl;
          changeConsoleColor(7);
          cout << "| Price         | " << left << setw(34) << service.price << "|" << endl;
          cout << border << endl;
          cout << endl;
     }
}

vector<Service> readFileService(const string &fileName)
{
     ifstream file(fileName);
     vector<Service> services;
     string line;

     if (!file.is_open())
     {
          cout << "Cannot open file!" << endl;
          return services;
     }

     while (getline(file, line))
     {
          stringstream ss(line);
          vector<string> service_info;
          string temp;

          getline(ss, temp, '|');
          service_info.push_back(temp);
          getline(ss, temp, '|');
          service_info.push_back(temp);
          getline(ss, temp, '|');
          service_info.push_back(temp);
          getline(ss, temp, '|');
          service_info.push_back(temp);
          getline(ss, temp, '|');
          service_info.push_back(temp);

          Service S(service_info);
          services.push_back(S);
     }

     file.close();
     return services;
}

string Service::getServiceName(const string& id, const vector<Service>& services) {
   for (const auto& service : services) {
    if (service.ID == id) {
        return service.name; 
    }
}
return "Unknown Service"; 
}