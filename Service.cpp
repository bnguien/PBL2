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
     string border = "\t+-----+------+----------+--------------+-----------------+---------------------+";
     cout << border << endl;
     cout << "\t| STT |  ID  |   NAME   |     TYPE     |   DESCRIPTION   |        PRICE        |" << endl;
     cout << border << endl;

     int count = 0;
     for (const auto &service : services)
     {
          ++count;
          cout << "\t| " << setw(3) << setfill('0') << right << count << " | "
               << setw(5) << setfill(' ') << left << service.getID() << "| ";

          if (service.getName() == "Food")
               changeConsoleColor(2);
          else if (service.getName() == "Snack")
               changeConsoleColor(14);
          else if (service.getName() == "Drinks")
               changeConsoleColor(11);
          else if (service.getName() == "Laundary")
               changeConsoleColor(9);

          cout << setw(9) << service.getName();
          changeConsoleColor(7);
          cout << "| " << setw(13) << service.getType() << "| "
               << setw(16) << service.getDesc() << "| "
               << setw(20) << service.getPrice() << "|" << endl;
          cout << border << endl;
     }
}

string Service::standardizePrice(const string &price, const string &desc)
{
     std::string formatted;
     int count = 0;

     for (int i = price.length() - 1; i >= 0; --i)
     {
          formatted.push_back(price[i]);
          count++;
          if (count % 3 == 0 && i != 0)
          {
               formatted.push_back('.');
          }
     }

     std::reverse(formatted.begin(), formatted.end());

     if (desc == "Breakfast" || desc == "Launch" || desc == "Dinner" || desc == "Combo")
     {
          formatted += "/person";
     }
     else if (desc == "Family combo")
     {
          formatted += "/4 people";
     }
     else if (desc == "Potato chips" || desc == "Peanuts")
     {
          formatted += "/bag";
     }
     else if (desc == "Chocolate bars")
     {
          formatted += "/piece";
     }
     else if (desc == "Soft drinks" || desc == "Soda" || desc == "Milk" ||
              desc == "Beer" || desc == "Fruit juice" || desc == "Coffee" ||
              desc == "Soju" || desc == "Strongbow" || desc == "Mineral water")
     {
          formatted += "/can";
     }
     else if (desc == "Shirt" || desc == "Trousers" || desc == "Suit Jacket" ||
              desc == "Dress" || desc == "Skirt")
     {
          formatted += "/item";
     }

     return formatted;
}

vector<Service> Service::readFileService(const string &fileName)
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
          cout << "\n\tCannot open file for writing!" << endl;
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