#include "Service.h"

void changeConsoleColor(int colorCode)
{
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(hConsole, colorCode);
}

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

void displayService(const vector<Service> &services)
{
     for (const auto &service : services)
     {
          string border = "+---------------+-----------------------------------+";
          Sleep(1000);
          cout << border << endl;
          cout << "| Service ID    | " << setw(34) << service.ID << "|" << endl;

          if (service.name == "Food")
               changeConsoleColor(3);
          else if (service.name == "Snack")
               changeConsoleColor(2);
          else if (service.name == "Drinks")
               changeConsoleColor(6);
          else if (service.name == "Laundary")
               changeConsoleColor(5);
          cout << border << endl;
          
          cout << "| Service Name  | " << setw(34) << service.name << "|" << endl;
          cout << border << endl;
          cout << "| Service Type  | " << setw(34) << service.type << "|" << endl;
          cout << border << endl;
          cout << "| Service Desc  | " << setw(34) << service.description << "|" << endl;
          cout << border << endl;
          changeConsoleColor(7);
          cout << "| Price         | " << setw(34) << service.price << "|" << endl;
          cout << border << endl;
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

          getline(ss, service_info[0], '|');
          getline(ss, service_info[1], '|');
          getline(ss, service_info[2], '|');
          getline(ss, service_info[3], '|');
          getline(ss, service_info[4], '|');

          Service S(service_info);
          services.push_back(S);
     }

     file.close();
     return services;
}