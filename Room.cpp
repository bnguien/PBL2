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
        return true; // Nhap dung loai phong
    }
    else
        return false; // Nhap sai loai phong, can nhap lai
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
    if (this->status == status)
        return true;

    if (status == "Unavailable" || status == "Available")
    {
        this->status = status;
        return true; // thiet lap trang thai thanh cong
    }
    else
    {
        cout << "Invalid status format. Please enter 'Available' or 'Unavailable'." << endl;
        return false;
    } // sai dinh dang trang thai, can nhap lai
}

string Room::getStatus() const
{
    return status;
}

void Room::setServiceIDs(const vector<string> serviceIDs)
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
    string border1 = "\t+-----+--------+----------+---------------+--------------+-------------------------------------+";
    string border2 = "\t|     |        |          |               |              | ";
    cout << border1 << endl;
    cout << "\t| STT | RoomID | RoomType |   RoomPrice   |    Status    |             Service IDs             |" << endl;
    cout << border1 << endl;
    int count = 0;
    for (const auto &room : rooms)
    {
        ++count;
        cout << "\t| " << setw(3) << setfill('0') << right << count << " |  "
             << setw(6) << setfill (' ') << left << room.getID() << "|  ";
        if (room.getType() == "Single")
            changeConsoleColor(10);
        else if (room.getType() == "Double")
            changeConsoleColor(14);
        else if (room.getType() == "Triple")
            changeConsoleColor(11);
        cout << setw(8) << room.getType();
        changeConsoleColor(7);
        cout << "| " << setw(14) << room.getPrice() << "| ";

        if (room.getStatus() == "Available")
            changeConsoleColor(2);
        else if (room.getStatus() == "Unavailable")
            changeConsoleColor(4);

        cout << setw(13) << room.getStatus();
        changeConsoleColor(7);
        cout << "| ";

        vector<string> serviceIDs = room.getServiceIDs();

        if (serviceIDs.empty())
        {
            cout << setw(36) << left << "None" << "|" << endl;
        }
        else
        {
            string serID = "";
            int index = 0;
            while (index < serviceIDs.size())
            {
                serID += serviceIDs[index];
                ++index;
                if (index < serviceIDs.size())
                    serID += ", ";

                if (serID.length() >= 37 || index == serviceIDs.size())
                {
                    cout << setw(36) << left << serID << "|" << endl;
                    if (index < serviceIDs.size())
                        cout << border2 << endl;
                    serID = "";
                }
            }
        }
        cout << border1 << endl;
    }
}

bool Room::updateRoomFile(const vector<Room> &rooms, const string &fileRoom)
{
    ofstream file(fileRoom);
    if (!file.is_open())
    {
        cout << "Cannot open room file!" << endl;
        return false;
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
    return false;
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

vector<string> Room::returnSerIDs (const string &roomID)
{
    vector<Room> rooms = Room::readFileRoom("Room.txt");
    for (const auto &room : rooms)
    {
        if (room.getID() == roomID)
            return room.getServiceIDs();
    }
    return {};
}
