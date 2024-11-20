#include "Service.h"

Service::Service() {}
Service::Service(const Service &s) : ID(s.ID), name(s.name), type(s.type), description(s.description), price(s.price) {}
Service::Service(const string &ID, const string &name, const string &type, const string &description, const string &price)
        : ID(ID), name(name), type(type), description(description), price(price) {}
Service::~Service() {}

string Service::getID() const
{
     return this->ID;
}
string Service::getName() const
{
     return this->name;
}
string Service::getType() const
{
     return this->type;
}
string Service::getDesc() const
{
     return this->description;
}
string Service::getPrice() const
{
     return this->price;
}
bool Service::setPrice(const string &price)
{
     if (price.empty())
     {
          changeColor(4);
          cout << "Price can not be empty!\n";
          changeColor(7);
          return false;
     }
     
     this->price = price;
     return true;
}

void displayService(const vector<Service> &services)
{
     for (const auto &service : services)
     {
          string border = "+---------------+-----------------------------------+";
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
          changeConsoleColor(12);
          cout << "| Service Type  | " << left << setw(34) << service.type << "|" << endl;
          cout << border << endl;
          changeConsoleColor(8);
          cout << "| Service Desc  | " << left << setw(34) << service.description << "|" << endl;
          cout << border << endl;
          changeConsoleColor(7);
          cout << "| Price         | " << left << setw(34) << service.price << "|" << endl;
          cout << border << endl;
          cout << endl;
     }
}

vector<Service> Service::readFileService(const string &fileName) {
    ifstream file(fileName);
    vector<Service> services;
    string line;

    if (!file.is_open()) {
        cout << "Cannot open file!" << endl;
        return services;
    }
    while (getline(file, line)) {
        stringstream ss(line);
        string ID, name, type, description, price;
        getline(ss, ID, '|');
        getline(ss, name, '|');
        getline(ss, type, '|');
        getline(ss, description, '|');
        getline(ss, price, '|');
        Service service(ID, name, type, description, price);
        services.push_back(service);
    }

    file.close();
    return services;
}

string Service::getServiceName(const string &serviceID, const vector<Service> &services)
{
    for (const auto &service : services)
    {
        if (service.getID() == serviceID)
        {
            return service.getName();
        }
    }
    return "Unknown Service";
}


string Service::generateSerID(const vector<Service> &services, const string &name)
{
     if (name.empty())
     {
          cout << "Invalid position information!" << endl;
          return "";
     }

     vector<Service> temp;
     for (const auto &service : services)
     {
          if (service.getName() == name)
               temp.push_back(service);
     }

     if (temp.empty())
     {
          return string(1, name[0]) + "01";
     }
     else
     {
          string lastID = temp[temp.size() - 1].getID();

          int lastNumber = stoi(lastID.substr(1));
          lastNumber++;

          stringstream newID;
          newID << name[0] << setw(2) << setfill('0') << lastNumber;
          return newID.str();
     }
}

bool Service::updateServiceFile(const vector<Service> &services, const string &fileName)
{
     ofstream file(fileName, ios::trunc);
     if (!file.is_open())
     {
          cout << "Cannot open file for writing!" << endl;
          return false;
     }

     for (const auto &service : services)
     {
          file << service.getID() << "|"
               << service.getName() << "|"
               << service.getType() << "|"
               << service.getDesc() << "|"
               << service.getPrice() << endl;
     }

     file.close();
     return true;
}