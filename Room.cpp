#include "Function.h"
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
          for (int i = 0; i < serviceIDs.size(); ++i)
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
          string ID, type, price, status;

          getline(ss, ID, '|');
          getline(ss, type, '|');
          getline(ss, price, '|');
          getline(ss, status, '|');

          Room R(ID, type, price, status);
          rooms.push_back(R);
     }

     file.close();
     return rooms;
}
void Room::printRoom(const vector<Room> &rooms)
{
     for (int i = 0; i < rooms.size(); ++i)
     {
          const Room &room = rooms[i];
          cout << "ID: " << room.getID() << endl;
          cout << "Type: " << room.getType() << endl;
          cout << "Price (VND/night): " << room.getPrice() << endl;
          cout << "Status: " << room.getStatus() << endl;
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

     for (int i = 0; i < rooms.size(); ++i)
     {
          const Room &room = rooms[i];
          file << room.getID() << "|"
               << room.getType() << "|"
               << room.getPrice() << "|"
               << room.getStatus() << endl;
     }

     file.close();
}

void Room::addServiceByRoomID(const string &roomID, const vector<string> &serviceIDs)
{
    if (serviceIDs.size() == 0) // Sử dụng size() để kiểm tra
    {
        cout << "No services to add." << endl;
        return;
    }

    string fileRoom = "Room.txt";
    vector<Room> rooms = readFileRoom(fileRoom);
    bool roomFound = false;

    for (int i = 0; i < rooms.size(); ++i)
    {
        Room &room = rooms[i];

        if (room.getID() == roomID)
        {
            roomFound = true;
            if (room.getServiceIDs().size() == 1 && room.getServiceIDs().get(0) == "None") 
            {
                room.setServiceIDs(serviceIDs);
            }
            else
            {
                for (size_t j = 0; j < serviceIDs.size(); ++j) 
                {
                    room.getServiceIDs().push_back(serviceIDs.get(j)); 
                }
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


