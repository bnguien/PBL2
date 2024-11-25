#include "Room.cpp"
#include <iostream>
#include <string>
using namespace std;

int main ()
{
     vector<Room> rooms = Room::readFileRoom("Room.txt");
     string border1 = "+-----+--------+----------+---------------+-------------+-------------------------------------+";
     string border2 = "|     |        |          |               |             | ";
     cout << border1 << endl;
     cout << "| STT | RoomID | RoomType |   RoomPrice   |    Status    |             Service IDs             |";
     int count = 0;
     for (auto room : rooms)
     {
          ++ count;
          cout << "| " << setw(3) << setfill('0') << count << " |  "
               << setw(6) << room.getID() << "|  " 
               << setw(8) << room.getType() << "| "
               << setw(14) << room.getPrice() << "| "
               << setw(13) << room.getStatus() << "| ";
          string serID = "";
          int index = 0;
          while (index < room.getServiceIDs().size() - 1)
          {
               serID += room.getServiceIDs()[index] + ", ";
               ++ index;
               if (serID.length() == 37)
               {
                    serID.erase(serID.length() - 2);
                    cout << serID << " |" << endl;
                    cout << border2;
                    serID = "";
               }
          }
          serID += room.getServiceIDs()[index + 1];
          cout << setw(36) << serID << "|" << endl;
     }
}