#include "Room.h"

#include "Service.h"

using namespace std;

void Room::setID(const string &ID)
{
     this->ID = ID;
}
string Room::getID() const
{
     return ID;
}

bool Room::setType(const string &type)
{
     if (type == "Single" || type == "Double" || type == "Triple")
     {
          this->type = type;
          return 1; // Nhap dung loai phong
     }
     else
          return 0; // Nhap sai loai phong, can nhap lai
}
string Room::getType() const
{
     return type;
}

void Room::setPrice(const string &price)
{
     this->price = price;
}
string Room::getPrice() const
{
     return price;
}

bool Room::setStatus(const string &status)
{
     if (status == "Unavailable" || status == "Available")
     {
          this->status = status;
          return 1; // thiet lap trang thai thanh cong
     }
     else
          return 0; // sai dinh dang trang thai, can nhap lai
}

string Room::getStatus() const
{
     return status;
}

void Room::setServiceIDs (const vector<string> serviceIDs)
{
     this->serviceIDs = vector<string>();
     if (serviceIDs.size() == 0)
     {
          this->serviceIDs.push_back("None");
     }
     else
     {
          for (size_t i = 0; i < serviceIDs.size(); ++i)
          {
               this->serviceIDs.push_back(serviceIDs[i]);
          }
     }
}

vector<string> Room::getServiceIDs() const
{
     return this->serviceIDs;
}

bool Room::checkAvailable() const
{
     if (this->status == "Available")
          return true;
     else if (this->status == "Unavailable")
          return false;
     else
     {
          cout << "\nInvalid information" << endl;
          return false;
     }
}

vector<Room> Room::readFileRoom(const string &fileName)
{
    ifstream file(fileName);
    vector<Room> rooms;
    string line;

    if (!file.is_open())
    {
        cout << "Cannot open file!" << endl;
        return rooms;
    }

    while (getline(file, line))
    {
        stringstream ss(line);
        string ID, type, price, status, services;
        vector<string> setServicesID;

        getline(ss, ID, '|');
        getline(ss, type, '|');
        getline(ss, price, '|');
        getline(ss, status, '|');
        getline(ss, services, '|');

        stringstream ssServices(services);
        string service;
        while (getline(ssServices, service, ','))
        {
            setServicesID.push_back(service);
        }

        Room R(ID, type, price, status);
        R.setServiceIDs(setServicesID);
        rooms.push_back(R);
    }

    file.close();
    return rooms;
}

void Room::printRoom(const vector<Room> &rooms, const vector<Service> &services)
{
    for (size_t i = 0; i < rooms.size(); ++i)
    {
        const Room &room = rooms[i];
        cout << "ID: " << room.getID() << endl;
        cout << "Type: " << room.getType() << endl;
        cout << "Price (VND/night): " << room.getPrice() << endl;
        cout << "Status: " << room.getStatus() << endl;

        cout << "Services: ";
        const vector<string> &serviceIDs = room.getServiceIDs();
        if (serviceIDs.size() == 1 && serviceIDs[0] == "None")
        {
            cout << "None";
        }
        else
        {
            for (size_t j = 0; j < serviceIDs.size(); ++j)
            {
                if (j > 0) cout << ", ";
                cout << Service::getServiceName(serviceIDs[j], services);
            }
        }
        cout << endl;

        cout << "-----------------------------" << endl;
    }
}

void Room::updateRoomFile(const vector<Room> &rooms, const string &fileRoom)
{
    ofstream file(fileRoom);
    if (!file.is_open())
    {
        cout << "Cannot open room file!" << endl;
        return;
    }

    for (size_t i = 0; i < rooms.size(); ++i)
    {
        const Room &r = rooms[i];
        string svList = r.getServiceIDs().empty() ? "None" : r.getServiceIDs()[0];
        for (size_t j = 1; j < r.getServiceIDs().size(); ++j)
        {
            svList += "," + r.getServiceIDs()[j];
        }
        file << r.getID() << "|"
             << r.getType() << "|"
             << r.getPrice() << "|"
             << r.getStatus() << "|"
             << svList << endl;
    }

    file.close();
}


void Room::addServiceByRoomID(const string &roomID, const vector<string> &serviceIDs)
{
    if (serviceIDs.empty())
    {
        cout << "No services to add." << endl;
        return;
    }

    string fileRoom = "Room.txt";
    vector<Room> rooms = readFileRoom(fileRoom);
    bool roomFound = false;

    for (size_t i = 0; i < rooms.size(); ++i)
    {
        Room &room = rooms[i];

        if (room.getID() == roomID)
        {
            roomFound = true;
            vector<string> setServiceIDs = room.getServiceIDs();

            if (setServiceIDs.size() == 1 && setServiceIDs[0] == "None")
            {
                room.setServiceIDs(serviceIDs);
            }
            else
            {
                for (size_t j = 0; j < serviceIDs.size(); ++j)
                {
                    setServiceIDs.push_back(serviceIDs[j]);
                }
                room.setServiceIDs(setServiceIDs);
            }

            cout << "Services added successfully to room ID: " << roomID << endl;
            break;
        }
    }

    if (roomFound)
    {
        updateRoomFile(rooms, fileRoom);
    }
    else
    {
        cout << "Room ID not found." << endl;
    }
}




