#include "Room.cpp"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main()
{
     string fileRoom = "Room.txt";
     vector<Room> rooms = Room::readFileRoom(fileRoom);
     string border1 = "+-----+--------+----------+---------------+--------------+-------------------------------------+";
     string border2 = "|     |        |          |               |              | ";
     cout << border1 << endl;
     cout << "| STT | RoomID | RoomType |   RoomPrice   |    Status    |             Service IDs             |" << endl;
     int count = 0;
     for (auto room : rooms)
     {
          ++count;
          cout << "| " << setw(3) << setfill('0') << count << " |  "
               << setw(6) << room.getID() << "|  "
               << setw(8) << room.getType() << "| "
               << setw(14) << room.getPrice() << "| "
               << setw(13) << room.getStatus() << "| ";

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
               cout << border1 << endl;
          }
     }
     return 0;
}