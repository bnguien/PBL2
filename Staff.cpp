#include "Staff.h"
#include "Customer.h"
#include "Room.h"
#include "Service.h"
#include "Login.h"
void adminScreen(Staff &staff);

void Staff::setID(const string &ID)
{
     this->ID = ID;
}
string Staff::getID() const
{
     return this->ID;
}

bool Staff::setPosition(const string &position)
{
     if (position.empty())
     {
          changeConsoleColor(12);
          cout << "Position cannot be empty!" << endl;
          return false;
     }

     if (position == "Manager" || position == "Receptionist" || position == "Housekeeping" || position == "Laundry" || position == "Server")
     {
          this->position = position;
          return true;
     }
     else
     {
          changeConsoleColor(12);
          cout << "The entered position '" << position << "' is not available in our hotel!" << endl;
          cout << "Valide position are: Manager, Receptionist, Housekeeping, Laundry, Server." << endl;
          return false;
     }
}
string Staff::getPosition() const
{
     return this->position;
}

void Staff::setSalary(const string &salary)
{
     this->salary = salary;
}
string Staff::getSalary() const
{
     return this->salary;
}

string Staff::formatSalary(const std::string &salary)
{
     std::string formatted;
     int count = 0;

     for (int i = salary.length() - 1; i >= 0; --i)
     {
          formatted.push_back(salary[i]);
          count++;
          if (count % 3 == 0 && i != 0)
          {
               formatted.push_back('.');
          }
     }

     std::reverse(formatted.begin(), formatted.end());
     formatted += "/month";
     return formatted;
}

bool Staff::operator==(const Staff &staff) const
{
     return (this->getFullName() == staff.getFullName() && this->getCCCD() == staff.getCCCD() && this->getPhone() == staff.getPhone() && this->getAdd() == staff.getAdd() && this->getGender() == staff.getGender() && this->getDOB() == staff.getDOB() && this->getID() == staff.getID() && this->getPosition() == staff.getPosition() && this->getSalary() == staff.getSalary());
}

vector<Staff> Staff ::readFileStaff(const string &fileName)
{
     ifstream file(fileName);
     vector<Staff> staffs;
     string line;

     if (!file.is_open())
     {
          cout << "Cannot open file!" << endl;
          return staffs;
     }

     while (getline(file, line))
     {
          stringstream ss(line);
          string fullName, CCCD, phone, add, gender, dobstr, ID, position, salary;
          Date dob;

          getline(ss, fullName, '|');
          getline(ss, CCCD, '|');
          getline(ss, phone, '|');
          getline(ss, add, '|');
          getline(ss, gender, '|');
          getline(ss, dobstr, '|');
          dob = Date(dobstr);
          getline(ss, ID, '|');
          getline(ss, position, '|');
          getline(ss, salary, '|');

          Staff staff(fullName, CCCD, phone, add, gender, dob, ID, position, salary);
          staffs.push_back(staff);
     }

     file.close();
     return staffs;
}

void Staff::showList(const vector<Staff> staffs)
{
     string title = R"(
                _____     _____   ______   _________        ___   ________       ______   _________     _       ________  ________   ______   
               |_   _|   |_   _|.' ____ \ |  _   _  |     .'   `.|_   __  |    .' ____ \ |  _   _  |   / \     |_   __  ||_   __  |.' ____ \  
                 | |       | |  | (___ \_||_/ | | \_|    /  .-.  \ | |_ \_|    | (___ \_||_/ | | \_|  / _ \      | |_ \_|  | |_ \_|| (___ \_| 
                 | |   _   | |   _.____`.     | |        | |   | | |  _|        _.____`.     | |     / ___ \     |  _|     |  _|    _.____`.  
                _| |__/ | _| |_ | \____) |   _| |_       \  `-'  /_| |_        | \____) |   _| |_  _/ /   \ \_  _| |_     _| |_    | \____) | 
               |________||_____| \______.'  |_____|       `.___.'|_____|        \______.'  |_____||____| |____||_____|   |_____|    \______.' 

     )";
     string border = "+-----+------+-------------------------------+--------------+------------+-----------------------+--------+------------+--------------+--------------------+";
     changeConsoleColor(14);
     cout << title << endl;
     cout << border << endl;
     cout << "| STT |  ID  |           FULL NAME           |     CCCD     | PHONE NUM. |        ADDRESS        | GENDER |  BIRTHDAY  |   POSITION   |       SALARY       |" << endl;
     cout << border << endl;

     changeConsoleColor(7);
     int count = 0;
     for (const auto staff : staffs)
     {
          ++count;
          cout << "| " << right << setw(3) << setfill('0') << count << " | ";
          char id = staff.getID()[0];
          if (id == 'M')
               changeConsoleColor(12);
          else if (id == 'R')
               changeConsoleColor(11);
          else if (id == 'H')
               changeConsoleColor(14);
          else if (id == 'L')
               changeConsoleColor(13);
          else if (id == 'S')
               changeConsoleColor(10);

          cout << staff.getID();
          changeConsoleColor(7);
          cout << " | ";
          cout << left << setw(29) << setfill(' ') << staff.getFullName() << " | "
               << staff.getCCCD() << " | " << staff.getPhone() << " | "
               << setw(21) << staff.getAdd() << " | ";

          string gender = staff.getGender();
          if (gender == "Female")
          {
               changeConsoleColor(4);
               cout << gender << " ";
          }
          else if (gender == "Male")
          {
               changeConsoleColor(3);
               cout << " " << gender << "  ";
          }
          changeConsoleColor(7);

          cout << "| " << staff.getDOB() << " | ";
          string position = staff.getPosition();
          if (position == "Manager")
               changeConsoleColor(12);
          else if (position == "Receptionist")
               changeConsoleColor(11);
          else if (position == "Housekeeping")
               changeConsoleColor(14);
          else if (position == "Laundry")
               changeConsoleColor(13);
          else if (position == "Server")
               changeConsoleColor(10);

          cout << left << setw(12) << position;
          changeConsoleColor(7);
          cout << " | " << setw(18) << staff.getSalary() << " |" << endl;
          cout << border << endl;
     }
     cout << endl;
}

void Staff::display() const
{
     Sleep(1000);
     string border = "\t+---------------+------------------------------+";

     cout << border << endl;
     cout << "\t| Full Name     | " << left << setw(28) << getFullName() << " |" << endl;
     cout << border << endl;
     cout << "\t| CCCD          | " << left << setw(28) << getCCCD() << " |" << endl;
     changeConsoleColor(7);
     cout << border << endl;
     cout << "\t| Phone         | " << left << setw(28) << getPhone() << " |" << endl;
     cout << border << endl;
     cout << "\t| Address       | " << left << setw(28) << getAdd() << " |" << endl;

     cout << border << endl;
     cout << "\t| Gender        | ";
     if (getGender() == "Male")
          changeConsoleColor(3);
     else
          changeConsoleColor(4);
     cout << left << setw(28) << getGender();
     changeConsoleColor(7);
     cout << " |\n"
          << border << endl;

     cout << "\t| Date of birth | " << left << getDOB() << "                   |" << endl;
     cout << border << endl;
     cout << "\t| Staff ID      | ";

     if (getPosition() == "Manager")
          changeConsoleColor(2);
     else if (getPosition() == "Receptionist")
          changeConsoleColor(3);
     else if (getPosition() == "Housekeeping")
          changeConsoleColor(5);
     else if (getPosition() == "Laundry")
          changeConsoleColor(6);
     else
          changeConsoleColor(8);

     cout << left << setw(28) << getID();
     changeConsoleColor(7);
     cout << " |\n"
          << border << endl;

     cout << "\t| Staff Position| ";
     if (getPosition() == "Manager")
          changeConsoleColor(2);
     else if (getPosition() == "Receptionist")
          changeConsoleColor(3);
     else if (getPosition() == "Housekeeping")
          changeConsoleColor(5);
     else if (getPosition() == "Laundry")
          changeConsoleColor(6);
     else
          changeConsoleColor(8);
     cout << left << setw(28) << getPosition();
     changeConsoleColor(7);
     cout << " |\n"
          << border << endl;

     cout << "\t| Staff Salary  | " << left << setw(28) << getSalary() << " |" << endl;
     cout << border << endl;
     cout << endl;
}

void Staff::updateStaffFile(const vector<Staff> &staffs, const string &fileName)
{
     ifstream readFile(fileName, ios::binary);
     bool addNewLine = false;

     if (readFile.is_open())
     {
          readFile.seekg(0, ios::end);
          if (readFile.tellg() > 0)
          {
               readFile.seekg(-1, ios::end);
               char ch;
               readFile.get(ch);
               if (ch != '\n')
               {
                    addNewLine = true;
               }
          }
          readFile.close();
     }

     ofstream file(fileName, ios::app);
     if (!file.is_open())
     {
          cout << "Cannot open staff file!" << endl;
          system("pause");
          return;
     }
     if (addNewLine)
     {
          file << endl;
     }

     for (const auto &staff : staffs)
     {
          file << staff.getFullName() << "|"
               << staff.getCCCD() << "|"
               << staff.getPhone() << "|"
               << staff.getAdd() << "|"
               << staff.getGender() << "|"
               << staff.getDOB().toString() << "|"
               << staff.getID() << "|"
               << staff.getPosition() << "|"
               << staff.getSalary() << endl;
     }

     file.seekp(0, ios::end);
     file.close();
}

// Function danh cho Manager (=admin)
string Staff::generateStaffID(const vector<Staff> &staffs, const string &position)
{
     if (position.empty() || (position != "Manager" && position != "Receptionist" && position != "Laundry" && position != "Server" && position != "Housekeeping"))
     {
          cout << "Invalid position information!" << endl;
          return "";
     }

     vector<int> numberID;
     for (const auto staff : staffs)
     {
          if (staff.getPosition() == position)
          {
               numberID.push_back(stoi(staff.getID().substr(1, 3)));
          }
     }
     int max = numberID[0];
     for (size_t i = 1; i < numberID.size(); i++)
          if (numberID[i] > max)
               max = numberID[i];
     max++;
     stringstream id;
     id << position[0] << setw(3) << setfill('0') << to_string(max);
     return id.str();
}

bool Staff::addNewStaff(Staff &newStaff)
{
     string staffFile = "Staff.txt";
     if (this->position != "Manager")
     {
          changeConsoleColor(4);
          cout << "\nAccess Denied: Only Managers can add new staff members!" << endl;
          changeConsoleColor(7);
          return false;
     }

     vector<Staff> staffs = readFileStaff(staffFile);

     for (const auto &staff : staffs)
     {
          if (staff.getCCCD() == newStaff.getCCCD())
          {
               changeConsoleColor(4);
               cout << "Failed to add new staff: Duplicate CCCD detected for "
                    << newStaff.getCCCD() << "!" << endl;
               changeConsoleColor(7);
               return false;
          }

          if (staff.getID() == newStaff.getID())
          {
               string newID = generateStaffID(staffs, newStaff.getPosition());
               newStaff.setID(newID);
               cout << "Duplicate ID detected. \nAutomatically generated new ID: "
                    << newID << "for the new staff member." << endl;
          }
     }

     vector<Staff> temp = {newStaff};
     temp[0].updateStaffFile(temp, staffFile);

     cout << "Successfully added new staff member with CCCD "
          << newStaff.getCCCD() << "!\n";

     return true;
}

bool Staff::removeStaffByCCCD(vector<Staff> &staffs)
{
     if (this->position != "Manager")
     {
          changeConsoleColor(4);
          cout << "\nAccess Denied: Only Managers can add new staff members!" << endl;
          changeConsoleColor(7);
          return false;
     }

     boxTwoLine(10, 12, 29, 2, 14, 75, "Staff's CCCD to remove");
     boxTwoLine(42, 12, 25, 2, 14, 150, " ");

     string CCCD;
     do
     {
          gotoXY(46, 13);
          cout << string(CCCD.length(), ' ');
          ShowCur(1);
          gotoXY(46, 13);
          cin >> CCCD;
          if (CCCD.length() != 12 || !std::all_of(CCCD.begin(), CCCD.end(), ::isdigit))
          {
               ShowCur(0);
               gotoXY(70, 13);
               changeColor(4);
               cout << "Exactly 12 digits! Press Enter ...";
               _getch();
               changeColor(7);
               gotoXY(70, 13);
               cout << string(40, ' ');
          }
          else
          {
               ShowCur(0);
               break;
          }
     } while (true);

     if (staffs.empty())
     {
          changeConsoleColor(12);
          gotoXY(40, 15);
          cout << "+--------------------------------------------------+";
          gotoXY(40, 16);
          cout << "|                                                  |";
          gotoXY(40, 17);
          cout << "|             List of staffs is empty!             |";
          gotoXY(40, 18);
          cout << "|  Failed to remove STAFF with CCCD: " << CCCD << "  |";
          gotoXY(40, 19);
          cout << "|                                                  |";
          gotoXY(40, 20);
          cout << "+--------------------------------------------------+";
          gotoXY(53, 21);
          changeConsoleColor(7);
          cout << "Press Enter to continue ...";
          _getch();
          return false;
     }

     int index = -1;
     for (size_t i = 0; i < staffs.size(); i++)
     {
          if (staffs[i].getCCCD() == CCCD)
          {
               if (staffs[i].getPosition() == "Manager")
               {
                    changeConsoleColor(4);
                    gotoXY(30, 15);
                    cout << "+---------------------------+";
                    gotoXY(30, 16);
                    cout << "|          Warning          |";
                    gotoXY(30, 17);
                    cout << "+---------------------------+";
                    changeConsoleColor(2);
                    gotoXY(30, 18);
                    cout << "|                           |";
                    gotoXY(30, 19);
                    cout << "|   Cann't remove Manager   |";
                    gotoXY(30, 20);
                    cout << "|                           |";
                    gotoXY(30, 21);
                    cout << "+---------------------------+";
                    gotoXY(30, 22);
                    changeConsoleColor(11);
                    cout << "Press Enter to continue ...";
                    changeConsoleColor(7);
                    _getch();
                    return false;
               }
               else
               {
                    index = i;
                    break;
               }
          }
     }

     if (index == -1)
          return false;
     else
     {
          gotoXY(1, 15);
          staffs[index].display();
          vector<string> content = {"Confirm", "Cancel"};
          if (buttonList(60, 18, 14, 2, 7, content, "row"))
          {
               for (size_t i = 0; i < staffs.size() - 1; i++)
               {
                    if (i >= index)
                    {
                         staffs[i] = staffs[i + 1];
                    }
               }
               staffs.pop_back();
               return true;
          }
          else
               return false;
     }
}

bool Staff::changeRoomStatus(vector<Room> &rooms)
{
     if (this->position != "Manager" && this->position != "Receptionist")
     {
          changeConsoleColor(4);
          cout << "\nAccess Denied: Only Managers and Receptionists can change room status!" << endl;
          changeConsoleColor(7);
          system("pause");
          return false;
     }

     vector<Service> services = Service::readFileService("Service.txt");

     if (rooms.empty() || services.empty())
          return false;

     gotoXY(1, 12);
     Room::printRoom(rooms, services);

     changeColor(14);
     cout << endl;
     cout << "\n\t\t+---------------------------------------+";
     cout << "\n\t\t|              INFORMATION              |";
     cout << "\n\t\t+---------------------------------------+";
     cout << "\n\t\t| Room ID        |                      |";
     cout << "\n\t\t+----------------+----------------------+";
     cout << "\n\t\t| Current Status |                      |";
     cout << "\n\t\t+----------------+----------------------+";
     cout << "\n\t\t| New Status     |                      |";
     cout << "\n\t\t+----------------+----------------------+";
     cout << endl;
     changeColor(7);
     int y = whereY();
     string roomID;
     do
     {
          ShowCur(1);
          gotoXY(36, y - 5);
          cout << string(roomID.length(), ' ');
          gotoXY(36, y - 5);
          cin >> roomID;

          if (!(isalpha(roomID[0]) && isdigit(roomID[1]) && isdigit(roomID[2])) || roomID.length() != 4)
          {
               ShowCur(0);
               changeColor(4);
               gotoXY(59, y - 5);
               cout << "Invalid room ID format! Press Enter ...";
               _getch();
               gotoXY(59, y - 5);
               cout << string(40, ' ');
               changeColor(7);
          }
          else
          {
               ShowCur(0);
               roomID[0] = toupper(roomID[0]);
               gotoXY(36, y - 5);
               cout << roomID;
               break;
          }
     } while (true);

     bool exist = false;
     for (size_t i = 0; i < rooms.size(); i++)
     {
          if (rooms[i].getID() == roomID)
          {
               exist = true;
               gotoXY(36, y - 3);
               string status = rooms[i].getStatus();
               if (status == "Available")
                    changeColor(2);
               else
                    changeColor(4);
               cout << status;
               string newSta = (status == "Available") ? "Unavailable" : "Available";
               gotoXY(36, y - 1);
               if (newSta == "Available")
                    changeColor(2);
               else
                    changeColor(4);
               cout << newSta;
               rooms[i].setStatus(newSta);
               _getch();
          }
     }
     if (!exist)
          return false;
     if (Room::updateRoomFile(rooms, "Room.txt"))
          return true;
     else
          return false;
}

bool Staff::updateStaff(vector<Staff> &staffs, const int &index)
{
     if (this->position != "Manager")
     {
          changeConsoleColor(4);
          cout << "\nAccess Denied: Only Managers can add new staff members!" << endl;
          changeConsoleColor(7);
          return false;
     }

     clearFromPosition(1, 16);

     staffs[index].display();
     changeConsoleColor(14);

     gotoXY(60, 16);
     cout << "+--------------------------------------------------------+";
     gotoXY(60, 17);
     cout << "|                   UPDATE INFORMATION                   |";
     gotoXY(60, 18);
     cout << "|   (Enter \'-\' if you do not want to make any changes)   |";
     gotoXY(60, 19);
     cout << "+------------------------------+-------------------------+";
     gotoXY(60, 20);
     cout << "| Phone Num. (10 digits only)  |                         |";
     gotoXY(60, 21);
     cout << "+------------------------------+-------------------------+";
     gotoXY(60, 22);
     cout << "| Position                     |                         |";
     gotoXY(60, 23);
     cout << "+------------------------------+-------------------------+";
     gotoXY(60, 24);
     cout << "| Salary (Only digits)         |                         |";
     gotoXY(60, 25);
     cout << "+------------------------------+-------------------------+";

     changeConsoleColor(7);
     string phone, position, id, salary;
     do
     {
          ShowCur(1);
          changeConsoleColor(7);
          gotoXY(93, 20);
          cout << string(phone.length(), ' ');
          gotoXY(93, 20);
          cin >> phone;
          if (phone == "-")
               break;

          if (phone.length() != 10)
          {
               gotoXY(119, 20);
               ShowCur(0);
               changeConsoleColor(12);
               cout << "Exactly 10 digits. Press Enter...";
               _getch();
               gotoXY(119, 20);
               cout << string(40, ' ');
          }
          else if (!std::all_of(phone.begin(), phone.end(), ::isdigit))
          {
               gotoXY(119, 20);
               ShowCur(0);
               changeConsoleColor(12);
               cout << "Only digits allowed. Press Enter...";
               _getch();
               gotoXY(119, 20);
               cout << string(40, ' ');
          }
          else
          {
               changeConsoleColor(7);
               break;
          }
     } while (true);

     do
     {
          ShowCur(1);
          changeConsoleColor(7);
          gotoXY(93, 22);
          cout << string(position.length(), ' ');
          gotoXY(93, 22);
          cin >> position;
          if (position == "-")
               break;
          position = toLower(position);
          position[0] = toupper(position[0]);

          if (position != "Manager" &&
              position != "Receptionist" &&
              position != "Housekeeping" &&
              position != "Laundry" &&
              position != "Server")
          {
               gotoXY(119, 22);
               ShowCur(0);
               changeConsoleColor(12);
               cout << "Invalid position. Press Enter...";
               _getch();
               gotoXY(119, 22);
               cout << string(40, ' ');
          }
          else
          {
               changeConsoleColor(7);
               gotoXY(93, 22);
               cout << string(position.length(), ' ');
               gotoXY(93, 22);
               cout << position;
               break;
          }
     } while (true);

     do
     {
          ShowCur(1);
          gotoXY(93, 24);
          cout << string(salary.length(), ' ');
          gotoXY(93, 24);
          changeConsoleColor(7);
          cin >> salary;
          if (salary == "-")
               break;

          if (!std::all_of(salary.begin(), salary.end(), ::isdigit))
          {
               gotoXY(119, 24);
               ShowCur(0);
               changeConsoleColor(12);
               cout << "Only digits. Press Enter...";
               _getch();
               gotoXY(119, 24);
               cout << string(40, ' ');
          }
          else
          {
               changeConsoleColor(7);
               gotoXY(93, 24);
               cout << string(salary.length(), ' ');
               gotoXY(93, 24);
               salary = Staff::formatSalary(salary);
               cout << salary;
               break;
          }
     } while (true);

     gotoXY(60, 27);
     ShowCur(0);
     vector<string> content = {"Confirm", "Cancel"};
     if (buttonList(68, 27, 14, 2, 16, content, "row") == 2)
     {
          return false;
     }
     else
     {
          if (phone == "-" && position == "-" && salary == "-")
          {
               gotoXY(65, 30);
               cout << "Nothing to update!";
               return true;
          }
          if (phone != "-")
               staffs[index].setPhone(phone);
          if (position != "-" && position != staffs[index].getPosition())
          {
               staffs[index].setPosition(position);
               staffs[index].setID(Staff::generateStaffID(staffs, position));
          }
          if (salary != "-")
               staffs[index].setSalary(salary);
     }

     ofstream file("Staff.txt", ios::trunc);
     for (const auto &staff : staffs)
     {
          file << staff.getFullName() << "|"
               << staff.getCCCD() << "|"
               << staff.getPhone() << "|"
               << staff.getAdd() << "|"
               << staff.getGender() << "|"
               << staff.getDOB().toString() << "|"
               << staff.getID() << "|"
               << staff.getPosition() << "|"
               << staff.getSalary() << endl;
     }
     file.close();

     Sleep(900);
     gotoXY(65, 30);
     changeConsoleColor(2);
     cout << "Updated information successfully! Review new information ...";
     gotoXY(1, 16);
     changeConsoleColor(7);
     staffs[index].display();
     _getch();

     return true;
}

//--- Customer Function ---
int Staff::cusExists(const vector<Customer> &customers, const Customer &newCus)
{
     for (size_t i = 0; i < customers.size(); i++)
     {
          if (customers[i] == newCus || customers[i].getCCCD() == newCus.getCCCD())
               return i;
     }
     return -1;
}

bool Staff::hasAccess(const Staff &staff) const
{
     if (staff.getPosition() != "Manager" && staff.getPosition() != "Receptionist")
     {
          changeConsoleColor(4);
          cout << "\nAccess Denied: Only Managers and Receptionists can use this function!" << endl;
          changeConsoleColor(7);
          system("pause");
          return false;
     }
     return true;
}

bool Staff::addNewCustomer(Staff &staff)
{
     Room room;
     string fileRoom = "Room.txt";
     vector<Room> rooms = room.readFileRoom(fileRoom);
     vector<Room> filteredRooms;
     changeColor(6);
     system("cls");
     string filename = "title.txt";
     ifstream inputFile(filename);
     read_lines(filename, 25, 31);
     inputFile.close();
     changeColor(7);

     for (const auto &room : rooms)
     {
          if (!room.getID().empty() && room.getStatus() == "Available")
          {
               filteredRooms.push_back(room);
          }
     }

     if (filteredRooms.empty())
     {
          changeConsoleColor(4);
          std::cout << "\nNo available rooms at the moment." << endl;
          changeConsoleColor(7);
          return false;
     }

     Customer::showAllRooms(filteredRooms);

     cout << "\n________________________________________________________________________________________________________________\n";
     vector<string> unavailableRoomIDs;
     vector<string> availableRoomIDs;
     ShowCur(0);
     while (true)
     {
          ShowCur(1);
          std::cout << "Enter the room IDs that the customer wants to book (separated by commas): ";
          string roomIDsInput;
          getline(cin, roomIDsInput);
          ShowCur(0);

          vector<string> roomIDs;
          string currentRoomID = "";

          for (char ch : roomIDsInput)
          {
               if (ch == ',')
               {
                    if (!currentRoomID.empty())
                    {
                         roomIDs.push_back(currentRoomID);
                         currentRoomID.clear();
                    }
               }
               else
               {
                    currentRoomID += toupper(ch);
               }
          }

          if (!currentRoomID.empty())
          {
               roomIDs.push_back(currentRoomID);
          }

          availableRoomIDs.clear();
          vector<string> unavailableRoomIDs;
          for (const string &inputRoomID : roomIDs)
          {
               bool roomFound = false;
               for (const Room &room : filteredRooms)
               {
                    if (room.getID() == inputRoomID)
                    {
                         roomFound = true;
                         if (room.checkAvailable())
                         {
                              availableRoomIDs.push_back(inputRoomID);
                         }
                         else
                         {
                              unavailableRoomIDs.push_back(inputRoomID);
                         }
                         break;
                    }
               }
               if (!roomFound)
               {
                    unavailableRoomIDs.push_back(inputRoomID);
               }
          }

          if (!unavailableRoomIDs.empty())
          {
               changeColor(4);
               std::cout << "Rooms ";
               for (size_t i = 0; i < unavailableRoomIDs.size(); ++i)
               {
                    std::cout << unavailableRoomIDs[i];
                    if (i < unavailableRoomIDs.size() - 1)
                    {
                         std::cout << ", ";
                    }
               }
               std::cout << " are unavailable. Please choose another room." << endl;
               changeColor(7);
               continue;
          }

          if (!availableRoomIDs.empty())
          {
               changeColor(2);
               std::cout << "Rooms ";
               for (size_t i = 0; i < availableRoomIDs.size(); ++i)
               {
                    std::cout << availableRoomIDs[i];
                    if (i < availableRoomIDs.size() - 1)
                    {
                         std::cout << ", ";
                    }
               }
               std::cout << " are available. Press Enter to continue booking." << endl;
               _getch();
               changeColor(7);
               break;
          }
          else
          {
               changeColor(4);
               std::cout << "No available rooms selected. Please try again." << endl;
               changeColor(7);
          }
     }
     system("cls");

     string fullName, CCCD, phone, add, gender, DOBstr, arrivalDateStr;
     Date DOB, arrivalDate;
     gotoXY(40, 9);
     std::cout << "Please enter new customer's information!" << endl;
     changeConsoleColor(14);
     gotoXY(40, 11);
     std::cout << "+-------------------------------------------------------+" << std::endl;
     gotoXY(40, 12);
     std::cout << "|                   YOUR INFORMATION                    |" << std::endl;
     gotoXY(40, 13);
     std::cout << "+-------------------------------------------------------+" << std::endl;

     gotoXY(40, 14);
     std::cout << "|  Full Name               |                            |" << std::endl;
     gotoXY(40, 15);
     std::cout << "|-------------------------------------------------------|" << std::endl;

     gotoXY(40, 16);
     std::cout << "|  CCCD                    |                            |" << std::endl;
     gotoXY(40, 17);
     std::cout << "|-------------------------------------------------------|" << std::endl;

     gotoXY(40, 18);
     std::cout << "|  Phone Number            |                            |" << std::endl;
     gotoXY(40, 19);
     std::cout << "|-------------------------------------------------------|" << std::endl;

     gotoXY(40, 20);
     std::cout << "|  Address                 |                            |" << std::endl;
     gotoXY(40, 21);
     std::cout << "|-------------------------------------------------------|" << std::endl;

     gotoXY(40, 22);
     std::cout << "|  Gender(Male/Female)     |                            |" << std::endl;
     gotoXY(40, 23);
     std::cout << "|-------------------------------------------------------|" << std::endl;

     gotoXY(40, 24);
     std::cout << "|  DOB(DD/MM/YYYY)         |                            |" << std::endl;
     gotoXY(40, 25);
     std::cout << "|-------------------------------------------------------|" << std::endl;

     gotoXY(40, 26);
     std::cout << "|  Arrival Date(DD/MM/YYYY)|                            |" << std::endl;
     gotoXY(40, 27);
     std::cout << "+-------------------------------------------------------+" << std::endl;

     changeConsoleColor(15);

     do
     {
          ShowCur(1);
          gotoXY(69, 14);
          std::getline(std::cin, fullName);
          if (fullName.empty())
          {
               changeConsoleColor(4);
               gotoXY(99, 14);
               std::cout << "Customer's name cannot be empty. Please try again.";
               changeConsoleColor(7);
               _getch();
               gotoXY(99, 14);
               std::cout << string(75, ' ');
          }
          ShowCur(0);
     } while (fullName.empty());

     bool isValidCCCD = false;

     do
     {
          ShowCur(1);
          gotoXY(69, 16);
          std::getline(std::cin, CCCD);
          ShowCur(0);

          if (CCCD.length() != 12)
          {
               changeConsoleColor(4);
               gotoXY(97, 16);
               cout << "CCCD must have exactly 12 digits!Press enter to try again" << endl;
               changeConsoleColor(7);
               _getch();
               gotoXY(97, 16);
               cout << string(75, ' ');
          }
          else
          {
               bool isDigitOnly = true;
               for (size_t i = 0; i < CCCD.length(); i++)
               {
                    if (!isdigit(CCCD[i]))
                    {
                         isDigitOnly = false;
                         gotoXY(97, 16);
                         changeConsoleColor(4);
                         cout << "CCCD must have only digits!Press enter to try again" << endl;
                         changeConsoleColor(7);
                         _getch();
                         gotoXY(97, 16);
                         cout << string(75, ' ');
                         break;
                    }
               }
               if (isDigitOnly)
               {
                    isValidCCCD = true;
               }
          }

          if (!isValidCCCD)
          {
               gotoXY(69, 16);
               cout << string(CCCD.length(), ' ');
          }

     } while (!isValidCCCD);
     bool isValidPhone = false;

     do
     {
          ShowCur(1);
          gotoXY(69, 18);
          std::getline(std::cin, phone);
          ShowCur(0);

          if (phone.length() != 10)
          {
               gotoXY(97, 18);
               changeConsoleColor(4);
               cout << "Phone must have exactly 10 digits!Press enter to try again" << endl;
               changeConsoleColor(7);
               _getch();
               gotoXY(97, 18);
               cout << string(75, ' ');
          }
          else if (phone[0] != '0')
          {
               gotoXY(97, 18);
               changeConsoleColor(4);
               cout << "First number must be 0! Press enter to try again" << endl;
               changeConsoleColor(7);
               _getch();
               gotoXY(97, 18);
               cout << string(75, ' ');
          }
          else if (!std::all_of(phone.begin() + 1, phone.end(), ::isdigit))
          {
               gotoXY(97, 18);
               changeConsoleColor(4);
               std::cout << "Phone must have only digits! Press enter to try again";
               changeConsoleColor(7);
               _getch();
               gotoXY(97, 18);
               std::cout << std::string(75, ' ');
          }
          else
          {
               isValidPhone = true;
          }

          if (!isValidPhone)
          {
               gotoXY(69, 18);
               cout << string(phone.length(), ' ');
          }
     } while (!isValidPhone);

     ShowCur(1);
     gotoXY(69, 20);
     std::getline(std::cin, add);

     do
     {
          ShowCur(1);
          gotoXY(69, 22);
          cout << string(gender.length(), ' ');
          gotoXY(69, 22);
          getline(cin, gender);
          gender = toLower(gender);
          gender[0] = toupper(gender[0]);
          gotoXY(69, 22);
          cout << gender;

          if (!(gender == "Male" || gender == "Female"))
          {
               gotoXY(69, 22);
               ShowCur(0);
               changeConsoleColor(4);
               cout << "Gender must be \'Male\' or \'Female\'! Try again!";
               changeConsoleColor(7);
               _getch();
               gotoXY(97, 22);
               cout << string(50, ' ');
               continue;
          }
          break;
     } while (true);

     while (true)
     {
          gotoXY(69, 24);
          cout << string(27, ' ');
          gotoXY(69, 24);
          std::getline(std::cin, DOBstr);

          if (DOBstr.empty())
          {
               gotoXY(98, 24);
               changeConsoleColor(4);
               std::cout << "Date of Birth cannot be empty. Press enter to try again (dd/mm/yyyy).";
               changeConsoleColor(7);
               _getch();
               gotoXY(98, 24);
               cout << string(75, ' ');
               continue;
          }

          if (Date::isValidDateFormat(DOBstr))
          {
               DOB = Date(DOBstr);
               if (Date::getCurrentDate().getYear() - DOB.getYear() < 18)
               {
                    gotoXY(98, 24);
                    changeConsoleColor(4);
                    std::cout << "The customer must be at least 18 years old!";
                    changeConsoleColor(7);
                    Sleep(3000);

                    system("cls");
                    changeConsoleColor(12);
                    gotoXY(40, 5);
                    cout << "+---------------------------------------------------+";
                    gotoXY(40, 6);
                    cout << "|                                                   |";
                    gotoXY(40, 7);
                    cout << "|          Customer is under 18 years old!          |";
                    gotoXY(40, 8);
                    cout << "|                                                   |";
                    gotoXY(40, 9);
                    cout << "|   Failed to book new room for customer with CCCD  |";
                    gotoXY(40, 10);
                    cout << "|                    " << setw(31) << setfill(' ') << CCCD << "|";
                    gotoXY(40, 11);
                    cout << "|                                                   |";
                    gotoXY(40, 12);
                    cout << "+---------------------------------------------------+" << endl;
                    changeConsoleColor(7);
                    ShowCur(0);
                    return false;
               }

               break;
          }
          else
          {
               gotoXY(98, 24);
               changeConsoleColor(4);
               std::cout << "Invalid date format! Please use dd/mm/yyyy!";
               changeConsoleColor(7);
               _getch();
               gotoXY(98, 24);
               cout << string(75, ' ');
               continue;
          }
     }

     while (true)
     {
          gotoXY(69, 26);
          cout << string(25, ' ');
          gotoXY(69, 26);
          ShowCur(1);
          std::getline(std::cin, arrivalDateStr);
          ShowCur(0);

          if (arrivalDateStr.empty())
          {
               gotoXY(97, 26);
               changeConsoleColor(4);
               std::cout << "Arrival date cannot be empty. Press enter to try again (dd/mm/yyyy).";
               changeConsoleColor(7);
               _getch();
               gotoXY(97, 26);
               cout << string(75, ' ');
               continue;
          }

          if (Date::isValidDateFormat(arrivalDateStr))
          {
               arrivalDate = Date(arrivalDateStr);
               if (Date::getCurrentDate() > arrivalDate)
               {
                    gotoXY(97, 26);
                    changeConsoleColor(4);
                    std::cout << "Arrival date must be after current date: " << Date::getCurrentDate();
                    changeConsoleColor(7);
                    _getch();
                    gotoXY(97, 26);
                    cout << string(75, ' ');
                    continue;
               }

               break;
          }
          else
          {
               gotoXY(97, 26);
               changeConsoleColor(4);
               std::cout << "Invalid date format! Please use dd/mm/yyyy!";
               changeConsoleColor(7);
               _getch();
               gotoXY(97, 26);
               cout << string(75, ' ');
               continue;
          }
     }

     vector<string> Options = {"Confirm", "Cancel"};
     int optionIndex = buttonList(45, 29, 15, 2, 18, Options, "row");
     string selectedOption = Options[optionIndex - 1];
     if (selectedOption == "Cancel")
     {
          clearFromPosition(1, 1);
          adminScreen(staff);
          return false;
     }
     else if (selectedOption == "Confirm")
     {
          fullName = Person::standardizeString(fullName);
          add = Person::standardizeString(add);
          gender = Person::standardizeString(gender);

          Customer newCustomer(fullName, CCCD, phone, add, gender, DOB, availableRoomIDs, arrivalDate, {"None"}, {"None"});
          string customerFile = "Customer.txt";
          if (!Customer::saveCustomerToFile(newCustomer, customerFile))
          {
               gotoXY(25, 35);
               changeConsoleColor(4);
               cout << "\nFailed to save to our hotel's customer file!" << endl;
               changeConsoleColor(7);
               system("pause");
               return false;
          }

          for (auto &roomRef : rooms)
          {
               if (find(availableRoomIDs.begin(), availableRoomIDs.end(), roomRef.getID()) != availableRoomIDs.end())
               {
                    roomRef.setStatus("Unavailable");
               }
          }
          std::cout << endl;
          room.updateRoomFile(rooms, fileRoom);
          gotoXY(25, 35);
          std::cout << "Booking successful for rooms: ";
          for (const auto &bookedID : availableRoomIDs)
          {
               std::cout << bookedID << " ";
          }
          std::cout << endl;
          return true;
     }
     return true;
}

bool Staff::writeRemainingCus(const vector<Customer> &remainingCustomers, const string &fileName)
{
     ofstream file(fileName, ios::trunc);
     if (!file.is_open())
     {
          changeConsoleColor(4);
          cout << "Cannot open customer file for writing!" << endl;
          changeConsoleColor(7);
          return false;
     }

     for (const auto &customer : remainingCustomers)
     {
          file << customer.getFullName() << "|"
               << customer.getCCCD() << "|"
               << customer.getPhone() << "|"
               << customer.getAdd() << "|"
               << customer.getDOB().toString() << "|"
               << customer.getGender() << "|";

          const vector<string> roomIDs = customer.getRoomIDs();
          for (size_t j = 0; j < roomIDs.size(); j++)
          {
               file << roomIDs[j];
               if (j < roomIDs.size() - 1)
                    file << ",";
          }
          file << "|" << customer.getArrivalDate().toString() << "|" << endl;
     }

     file.close();
     return true;
}

bool Staff::removeCustomerByCCCD(const Staff &staff, const string &CCCDToRemove)
{
     string customerFile = "Customer.txt";
     if (hasAccess(staff))
     {
          ifstream inFile(customerFile);
          if (!inFile)
          {
               changeConsoleColor(4);
               cout << "\nFailed to open customer file!" << endl;
               changeConsoleColor(7);
               return false;
          }

          vector<string> customers;
          string line;
          while (getline(inFile, line))
          {
               customers.push_back(line);
          }
          inFile.close();

          bool found = false;
          vector<string> remainingCustomers;
          for (const auto &customer : customers)
          {
               size_t pos = customer.find('|');
               if (pos != string::npos)
               {

                    size_t start = pos + 1;
                    size_t end = customer.find('|', start);
                    string CCCD = customer.substr(start, end - start);

                    if (CCCD == CCCDToRemove)
                    {
                         found = true;
                         continue;
                    }
               }
               remainingCustomers.push_back(customer);
          }

          if (!found)
          {
               changeConsoleColor(4);
               cout << "\nCannot find this customer's information to remove!" << endl;
               changeConsoleColor(7);
               return false;
          }
          ofstream outFile(customerFile);
          if (!outFile)
          {
               changeConsoleColor(4);
               cout << "\nFailed to write to customer file!" << endl;
               changeConsoleColor(7);
               return false;
          }

          for (const auto &customer : remainingCustomers)
          {
               outFile << customer << endl;
          }
          outFile.close();
          changeConsoleColor(2);
          cout << "\nSuccessfully removed customer with CCCD: " << CCCDToRemove << endl;
          changeConsoleColor(7);
          return true;
     }
     else
          return false;
}

bool Staff::findCustomer(vector<Customer> &findCus)
{
     vector<string> content = {"Find by CCCD",
                               "Find by First Name",
                               "Find by Last Name",
                               "Find by Full Name",
                               "Find by A Letter"};

     vector<Customer> customers = Customer::readFileCustomer("Customer.txt");
     if (customers.empty())
          return false;

     string attribute;
     string nameType;
     char att;
     int button = buttonList(5, 12, 25, 2, 6, content, "row");
     switch (button)
     {
     case 1: // Find by CCCD
          boxTwoLine(30, 16, 11, 2, 14, 235, "CCCD");
          boxTwoLine(46, 16, 19, 2, 14, 235, " ");

          do
          {
               gotoXY(50, 17);
               cout << string(attribute.length(), ' ');
               gotoXY(50, 17);
               ShowCur(1);
               changeConsoleColor(11);
               cin >> attribute;
               ShowCur(0);
               if (attribute.length() != 12 &&
                   !(std::all_of(attribute.begin(), attribute.end(), ::isdigit)))
               {
                    gotoXY(67, 17);
                    changeColor(4);
                    cout << "Exactly 12 digits. Press Enter...";
                    _getch();
                    gotoXY(67, 17);
                    cout << string(65, ' ');
               }
               else
               {
                    changeColor(7);
                    break;
               }
          } while (true);

          for (const auto &cus : customers)
          {
               if (cus.getCCCD() == attribute)
               {
                    findCus.push_back(cus);
               }
          }
          break;

     case 2: // FirstName
     case 3: // Last Name
          nameType = (button == 2) ? "First Name" : "Last Name";
          boxTwoLine(30, 16, 17, 2, 14, 235, nameType);
          boxTwoLine(49, 16, 19, 2, 14, 235, " ");

          do
          {
               gotoXY(53, 17);
               cout << string(attribute.length(), ' ');
               gotoXY(53, 17);
               changeColor(11);
               ShowCur(1);
               cin >> attribute;
               ShowCur(0);

               if (!std::all_of(attribute.begin(), attribute.end(), ::isalpha))
               {
                    gotoXY(70, 17);
                    changeColor(4);
                    cout << "Only alphabetic characters. Press Enter...";
                    _getch();
                    gotoXY(70, 17);
                    cout << string(65, ' ');
               }
               else
               {
                    attribute = toLower(attribute);
                    attribute[0] = toupper(attribute[0]);
                    changeColor(7);
                    break;
               }
          } while (true);

          for (auto cus : customers)
          {
               if ((button == 2 && cus.getFirstName() == attribute) ||
                   (button == 3 && cus.getLastName() == attribute))
                    findCus.push_back(cus);
          }
          break;

     case 4: // Find by Full Name
          boxTwoLine(30, 16, 17, 2, 14, 235, "Full Name");
          boxTwoLine(49, 16, 30, 2, 14, 235, " ");

          do
          {
               gotoXY(53, 17);
               cout << string(attribute.length(), ' ');
               gotoXY(53, 17);
               changeColor(11);
               ShowCur(1);
               getline(cin, attribute);
               attribute = Person::standardizeString(attribute);
               gotoXY(53, 17);
               cout << attribute;
               ShowCur(0);

               if (!std::all_of(attribute.begin(), attribute.end(), [](char c)
                                { return ::isalpha(c) || ::isspace(c); }))
               {
                    gotoXY(81, 17);
                    changeColor(4);
                    cout << "Only alphabetic characters. Press Enter...";
                    _getch();
                    gotoXY(81, 17);
                    cout << string(65, ' ');
               }
               else
               {
                    changeColor(7);
                    break;
               }
          } while (true);

          for (const auto &cus : customers)
          {
               if (cus.getFullName() == attribute)
                    findCus.push_back(cus);
          }
          break;

     case 5: // Find By A Letter
          vector<string> options = {
              "Find by First Name",
              "Find by Last Name",
          };
          int choice = buttonList(18, 17, 25, 2, 5, options, "row");

          switch (choice)
          {
          case 1:
               boxTwoLine(78, 17, 17, 2, 14, 235, "Letter");
               boxTwoLine(97, 17, 19, 2, 14, 235, " ");
               do
               {
                    gotoXY(101, 18);
                    cout << " ";
                    gotoXY(101, 18);
                    changeColor(11);
                    ShowCur(1);
                    cin >> att;
                    att = tolower(att);
                    gotoXY(101, 18);
                    cout << att;
                    ShowCur(0);

                    if (!isalpha(att))
                    {
                         gotoXY(70, 19);
                         changeColor(4);
                         cout << "Only alphabetic letters. Press Enter...";
                         _getch();
                         gotoXY(70, 19);
                         cout << string(65, ' ');
                    }
                    else
                    {
                         changeColor(7);
                         break;
                    }
               } while (true);

               for (auto cus : customers)
               {
                    string fullName = toLower(cus.getFirstName());
                    size_t firstSpace = fullName.find(' ');

                    string lastName = (firstSpace != string::npos) ? fullName.substr(0, firstSpace) : fullName;
                    if (lastName[0] == att)
                    {
                         findCus.push_back(cus);
                    }
               }

               if (findCus.empty())
               {
                    changeColor(4);
                    gotoXY(70, 19);
                    cout << "No customers found with last name starting with \'" << att << "\'.";
                    changeColor(7);
                    _getch();
               }
               break;
          case 2:
               boxTwoLine(78, 17, 17, 2, 14, 235, "Letter");
               boxTwoLine(97, 17, 19, 2, 14, 235, " ");
               do
               {
                    gotoXY(101, 18);
                    cout << " ";
                    gotoXY(101, 18);
                    changeColor(11);
                    ShowCur(1);
                    cin >> att;
                    att = tolower(att);
                    gotoXY(101, 18);
                    cout << att;
                    ShowCur(0);
                    if (!isalpha(att))
                    {
                         gotoXY(70, 19);
                         changeColor(4);
                         cout << "Only alphabetic letters. Press Enter...";
                         _getch();
                         gotoXY(70, 19);
                         cout << string(65, ' ');
                    }
                    else
                    {
                         changeColor(7);
                         break;
                    }
               } while (true);

               for (auto cus : customers)
               {
                    string fullName = toLower(cus.getLastName());
                    size_t firstSpace = fullName.find(' ');

                    string lastName = (firstSpace != string::npos) ? fullName.substr(0, firstSpace) : fullName;
                    if (lastName[0] == att)
                    {
                         findCus.push_back(cus);
                    }
               }
          }
     }

     if (findCus.empty())
          return false;
     else
          return true;
}

void Staff::changeServicePrice(vector<Service> &services)
{
     changeConsoleColor(14);
     cout << endl;
     cout << "\t\t+---------------------------------------------------+" << endl;
     cout << "\t\t|                    INFORMATION                    |" << endl;
     cout << "\t\t+---------------------------------------------------+" << endl;
     cout << "\t\t| Service ID              |                         |" << endl;
     cout << "\t\t+---------------------------------------------------+" << endl;
     cout << "\t\t| Service Description     |                         |" << endl;
     cout << "\t\t+---------------------------------------------------+" << endl;
     cout << "\t\t| Old price               |                         |" << endl;
     cout << "\t\t+---------------------------------------------------+" << endl;
     cout << "\t\t| New price (Only digits) |                         |" << endl;
     cout << "\t\t+---------------------------------------------------+" << endl;
     changeColor(7);
     int y = whereY();
     string serID, newPrice, desc, oldPrice;
     do // id
     {
          ShowCur(1);
          gotoXY(45, y - 7);
          cout << string(serID.length(), ' ');
          gotoXY(45, y - 7);
          cin >> serID;
          if (!(isalpha(serID[0]) && isdigit(serID[1]) && isdigit(serID[2])))
          {
               ShowCur(0);
               changeColor(4);
               gotoXY(71, y - 7);
               cout << "Wrong SERVICE ID format! Press Enter ...";
               _getch();
               gotoXY(71, y - 7);
               changeColor(7);
               cout << string(40, ' ');
          }
          else
          {
               serID[0] = toupper(serID[0]);
               gotoXY(45, y - 7);
               cout << serID;
               break;
          }
     } while (true);

     int index = -1;
     for (size_t i = 0; i < services.size(); i++)
     {
          if (services[i].getID() == serID)
          {
               index = i;
               desc = services[i].getDesc();
               oldPrice = services[i].getPrice();
               break;
          }
     }

     if (index == -1)
     {
          gotoXY(1, y + 1);
          ShowCur(0);
          cout << "\n\t+-------------------------------------------+";
          cout << "\n\t|                                           |";
          cout << "\n\t|            Cannot find service            |";
          cout << "\n\t|               with ID: " << serID << "!               |";
          cout << "\n\t|                                           |";
          cout << "\n\t+-------------------------------------------+\n";
          return;
     }
     else
     {
          gotoXY(45, y - 5);
          cout << desc;
          gotoXY(45, y - 3);
          changeConsoleColor(2);
          cout << oldPrice;
          changeConsoleColor(7);
     }

     do // newPrice
     {
          ShowCur(1);
          gotoXY(45, y - 1);
          cout << string(newPrice.length(), ' ');
          gotoXY(45, y - 1);
          cin >> newPrice;
          if (!(std::all_of(newPrice.begin(), newPrice.end(), ::isdigit)))
          {
               ShowCur(0);
               changeColor(4);
               gotoXY(71, y - 1);
               cout << "Please, only DIGITS! Press Enter ...";
               _getch();
               changeColor(7);
               gotoXY(71, y - 1);
               cout << string(40, ' ');
          }
          else
          {
               ShowCur(0);
               gotoXY(45, y - 1);
               cout << string(newPrice.length(), ' ');
               newPrice = Service::standardizePrice(newPrice, desc);
               gotoXY(45, y - 1);
               cout << newPrice;
               break;
          }
     } while (true);

     cout << "\n\n\n\n\n\n";

     vector<string> content = {"Confirm", "Cancel"};
     if (buttonList(20, whereY() - 3, 14, 2, 9, content, "row") == 1)
     {
          services[index].setPrice(newPrice);
          if (!Service::updateServiceFile(services, "Service.txt"))
          {
               changeColor(4);
               cout << "\n\t+-------------------------------------------+";
               cout << "\n\t|                                           |";
               cout << "\n\t|   Failed to update new Price of service   |";
               cout << "\n\t|               with ID: " << serID << "!               |";
               cout << "\n\t|                                           |";
               cout << "\n\t+-------------------------------------------+";
               changeColor(7);
          }
          else
          {
               system("cls");
               changeConsoleColor(2);
               cout << "\n\t\t+----------------------------------------------+";
               cout << "\n\t\t|                                              |";
               cout << "\n\t\t|     Successfully change price of service     |";
               cout << "\n\t\t|                 with ID: " << serID << "                 |";
               cout << "\n\t\t|                                              |";
               cout << "\n\t\t+----------------------------------------------+\n"
                    << endl;
               changeColor(7);
               displayService(services);
          }
     }
     else
          cout << endl;
}

bool Staff::updateCustomer(Staff &staff, const string &fileName, vector<Customer> &customers)
{
     while (true)
     {
          gotoXY(35, 12);
          changeConsoleColor(9);
          std::cout << "ENTER CUSTOMER'S NAME AND CUSTOMER'S ID CARD(CCCD)" << endl;
          changeConsoleColor(14);
          gotoXY(25, 14);
          std::cout << "+---------------------------+----------------------------------------+" << std::endl;
          gotoXY(25, 15);
          std::cout << "| Customer's Name           |                                        |" << std::endl;
          gotoXY(25, 16);
          std::cout << "+---------------------------+----------------------------------------+" << std::endl;
          gotoXY(25, 17);
          std::cout << "| Customer's CCCD (ID card) |                                        |" << std::endl;
          gotoXY(25, 18);
          std::cout << "+---------------------------+----------------------------------------+" << std::endl;
          string inputName, inputCCCD;
          changeConsoleColor(7);
          do
          {
               ShowCur(1);
               gotoXY(55, 15);
               getline(cin, inputName);
               ShowCur(0);
               if (inputName.empty())
               {
                    changeConsoleColor(4);
                    gotoXY(98, 15);
                    std::cout << "Customer's name cannot be empty. Please try again.";
                    changeConsoleColor(7);
                    _getch();
                    gotoXY(98, 15);
                    std::cout << string(75, ' ');
               }
          } while (inputName.empty());
          bool isValidCCCD = false;
          do
          {
               ShowCur(1);
               gotoXY(55, 17);
               getline(cin, inputCCCD);
               ShowCur(0);

               if (inputCCCD.length() != 12)
               {
                    changeConsoleColor(4);
                    gotoXY(97, 17);
                    std::cout << "CCCD must have exactly 12 digits!Press enter to try again" << endl;
                    changeConsoleColor(7);
                    _getch();
                    gotoXY(97, 17);
                    std::cout << string(75, ' ');
               }
               else
               {
                    bool isDigitOnly = true;
                    for (size_t i = 0; i < inputCCCD.length(); i++)
                    {
                         if (!isdigit(inputCCCD[i]))
                         {
                              ShowCur(0);
                              isDigitOnly = false;
                              gotoXY(97, 17);
                              changeConsoleColor(4);
                              std::cout << "CCCD must have only digits!Press enter to try again" << endl;
                              changeConsoleColor(7);
                              _getch();
                              gotoXY(97, 17);
                              std::cout << string(75, ' ');
                              break;
                         }
                    }
                    if (isDigitOnly)
                    {
                         isValidCCCD = true;
                    }
               }

               if (!isValidCCCD)
               {
                    ShowCur(0);
                    gotoXY(55, 17);
                    std::cout << string(inputCCCD.length(), ' ');
               }

          } while (!isValidCCCD);

          bool customerFound = false;
          for (Customer &customer : customers)
          {
               if (customer.getFullName() == inputName && customer.getCCCD() == inputCCCD)
               {
                    customerFound = true;
                    system("cls");
                    gotoXY(1, 1);
                    changeConsoleColor(3);
                    std::cout << "HOTEL DEL LUNA" << endl;
                    changeConsoleColor(7);
                    std::cout << "______________" << endl;
                    gotoXY(37, 5);
                    changeConsoleColor(6);
                    std::cout << "WHICH CUSTOMER'S INFORMATION WOULD YOU LIKE TO UPDATE" << endl;
                    changeConsoleColor(7);
                    vector<string> options = {"Change phone number", "Change address", "Change Date of Birth (DOB)", "Return"};
                    int choice = buttonList(40, 8, 34, 2, 2, options, "column");

                    if (choice < 1 || choice > options.size())
                    {
                         std::cout << "Invalid selection!\n";
                         return false;
                    }

                    string selectedOption = options[choice - 1];
                    system("cls");
                    gotoXY(1, 1);
                    changeConsoleColor(3);
                    std::cout << "HOTEL DEL LUNA" << endl;
                    changeConsoleColor(7);
                    std::cout << "______________" << endl;
                    if (selectedOption == "Change phone number")
                    {
                         string newPhone;
                         while (true)
                         {
                              gotoXY(10, 5);
                              changeConsoleColor(9);
                              std::cout << "Enter the new phone number: ";
                              changeConsoleColor(7);
                              ShowCur(1);
                              getline(cin, newPhone);
                              ShowCur(0);
                              if (customer.getPhone() == newPhone)
                              {
                                   gotoXY(10, 7);
                                   changeConsoleColor(4);
                                   std::cout << "The new phone number is the same as the old one. Please enter a different phone number." << endl;
                                   changeConsoleColor(7);
                                   _getch();
                                   gotoXY(30, 5);
                                   std::cout << string(75, ' ');
                                   gotoXY(10, 7);
                                   std::cout << string(150, ' ');
                              }
                              else
                              {
                                   if (customer.setPhone(newPhone))
                                   {
                                        vector<string> Options = {"Cancel", "Confirm"};
                                        int optionIndex = buttonList(40, 7, 15, 2, 18, Options, "row");
                                        string selectedOption = Options[optionIndex - 1];
                                        if (selectedOption == "Cancel")
                                        {
                                             clearFromPosition(1, 1);
                                             adminScreen(staff);
                                             return false;
                                        }
                                        else if (selectedOption == "Confirm")
                                        {
                                             system("cls");
                                             gotoXY(1, 1);
                                             changeConsoleColor(3);
                                             std::cout << "HOTEL DEL LUNA" << endl;
                                             changeConsoleColor(7);
                                             std::cout << "______________" << endl;
                                             changeConsoleColor(14);
                                             gotoXY(40, 5);
                                             std::cout << "|=========================================================|";
                                             gotoXY(40, 6);
                                             std::cout << "|                                                         |";
                                             gotoXY(40, 7);
                                             std::cout << "|=========================================================|";
                                             gotoXY(53, 6);
                                             changeColor(2);
                                             std::cout << "Phone number updated successfully";
                                             changeConsoleColor(7);
                                             break;
                                        }
                                   }
                                   else
                                   {
                                        changeColor(4);
                                        _getch();
                                        gotoXY(10, 7);
                                        std::cout << string(100, ' ');
                                        gotoXY(30, 5);
                                        std::cout << string(75, ' ');
                                        gotoXY(1, 7);
                                        std::cout << string(150, ' ');
                                   }
                              }
                              changeConsoleColor(7);
                         }
                    }
                    else if (selectedOption == "Change address")
                    {
                         while (true)
                         {
                              gotoXY(10, 5);
                              string newAddress;
                              changeConsoleColor(9);
                              std::cout << "Enter the new address: ";
                              changeConsoleColor(7);
                              ShowCur(1);
                              getline(cin, newAddress);
                              ShowCur(0);
                              if (customer.getAdd() == newAddress)
                              {
                                   gotoXY(10, 7);
                                   changeConsoleColor(4);
                                   std::cout << "The new address is the same as the old one. Please enter a different address." << endl;
                                   changeConsoleColor(7);
                                   _getch();
                                   gotoXY(30, 5);
                                   std::cout << string(75, ' ');
                                   gotoXY(10, 7);
                                   std::cout << string(150, ' ');
                              }
                              else
                              {
                                   newAddress = Person::standardizeString(newAddress);
                                   customer.setAdd(newAddress);
                                   changeConsoleColor(2);
                                   vector<string> Options = {"Cancel", "Confirm"};
                                   int optionIndex = buttonList(40, 7, 15, 2, 18, Options, "row");
                                   string selectedOption = Options[optionIndex - 1];
                                   if (selectedOption == "Cancel")
                                   {
                                        clearFromPosition(1, 1);
                                        adminScreen(staff);
                                        return false;
                                   }
                                   else if (selectedOption == "Confirm")
                                   {
                                        system("cls");
                                        gotoXY(1, 1);
                                        changeConsoleColor(3);
                                        std::cout << "HOTEL DEL LUNA" << endl;
                                        changeConsoleColor(7);
                                        std::cout << "______________" << endl;
                                        changeConsoleColor(14);
                                        gotoXY(40, 5);
                                        std::cout << "|==========================================|";
                                        gotoXY(40, 6);
                                        std::cout << "|                                          |";
                                        gotoXY(40, 7);
                                        std::cout << "|==========================================|";
                                        gotoXY(47, 6);
                                        changeColor(2);
                                        std::cout << "Address updated successfully";
                                        changeConsoleColor(7);
                                        break;
                                   }
                              }
                         }
                    }
                    else if (selectedOption == "Change Date of Birth (DOB)")
            {
                gotoXY(10, 5);
                changeConsoleColor(9);
                cout << "Enter the new Date of Birth (DD/MM/YYYY): ";
                changeConsoleColor(7);
                string newDOB;
                while (true)
                {
                    std::getline(std::cin, newDOB);
                    if (customer.getDOB() == newDOB)
                    {
                         gotoXY(10, 5);
                         changeConsoleColor(9);
                         std::cout << "Enter the new Date of Birth (DD/MM/YYYY): ";
                         changeConsoleColor(7);
                         string newDOB;
                         while (true)
                         {
                              gotoXY(52, 5);
                              ShowCur(1);
                              std::getline(std::cin, newDOB);
                              ShowCur(0);
                              if (customer.getDOB() == newDOB)
                              {
                                   gotoXY(10, 7);
                                   changeConsoleColor(4);
                                   std::cout << "The new date of birth is the same as the old one. Please enter a different date of birth." << endl;
                                   changeConsoleColor(7);
                                   _getch();
                                   gotoXY(52, 5);
                                   std::cout << string(75, ' ');
                                   gotoXY(10, 7);
                                   std::cout << string(150, ' ');
                              }
                              else
                              {
                                   if (newDOB.empty())
                                   {
                                        changeConsoleColor(4);
                                        gotoXY(10, 7);
                                        std::cout << "Date of Birth cannot be empty!" << endl;
                                        changeConsoleColor(7);
                                        _getch();
                                        gotoXY(10, 7);
                                        std::cout << string(150, ' ');
                                        continue;
                                   }
                              }
                              if (!Date::isValidDateFormat(newDOB))
                              {
                                   _getch();
                                   gotoXY(52, 5);
                                   std::cout << string(75, ' ');
                                   gotoXY(1, 6);
                                   std::cout << string(150, ' ');
                                   gotoXY(52, 5);
                              }
                              else if (Date::getCurrentDate().getYear() - Date(newDOB).getYear() < 18)
                              {
                                   changeConsoleColor(4);
                                   gotoXY(10, 7);
                                   std::cout << "The customer must be at least 18 years old!" << endl;
                                   changeConsoleColor(7);
                                   _getch();
                                   gotoXY(52, 5);
                                   std::cout << string(75, ' ');
                                   gotoXY(10, 7);
                                   std::cout << string(150, ' ');
                                   continue;
                              }
                              else
                              {
                                   vector<string> Options = {"Cancel", "Confirm"};
                                   int optionIndex = buttonList(40, 7, 15, 2, 18, Options, "row");
                                   string selectedOption = Options[optionIndex - 1];
                                   if (selectedOption == "Cancel")
                                   {
                                        clearFromPosition(1, 1);
                                        adminScreen(staff);
                                        return false;
                                   }
                                   else if (selectedOption == "Confirm")
                                   {
                                        system("cls");
                                        gotoXY(1, 1);
                                        changeConsoleColor(3);
                                        std::cout << "HOTEL DEL LUNA" << endl;
                                        changeConsoleColor(7);
                                        std::cout << "______________" << endl;
                                        changeConsoleColor(14);
                                        gotoXY(40, 5);
                                        std::cout << "|==================================================|";
                                        gotoXY(40, 6);
                                        std::cout << "|                                                  |";
                                        gotoXY(40, 7);
                                        std::cout << "|==================================================|";
                                        gotoXY(49, 6);
                                        changeColor(2);
                                        std::cout << "Date of birth updated successfully";
                                        changeConsoleColor(7);
                                        break;
                                   }
                              }
                         }
                    }
                    else
                    {
                        if (newDOB.empty())
                        {
                            changeConsoleColor(4);
                            gotoXY(10, 7);
                            cout << "Date of Birth cannot be empty!" << endl;
                            changeConsoleColor(7);
                            _getch();
                            gotoXY(10, 7);
                            cout << string(150, ' ');
                            continue;
                        }

                        if (!Date::isValidDateFormat(newDOB))
                        {
                            _getch();
                            gotoXY(52, 5);
                            cout << string(75, ' ');
                            gotoXY(1, 6);
                            cout << string(150, ' ');
                            gotoXY(52, 5);
                        }
                        else
                        {
                            vector<string> Options = {"Cancel", "Confirm"};
                            int optionIndex = buttonList(40, 7, 15, 2, 18, Options, "row");
                            string selectedOption = Options[optionIndex - 1];
                            if (selectedOption == "Cancel")
                            {
                                clearFromPosition(1, 1);
                                adminScreen(staff);
                                return false;
                            }
                            else if (selectedOption == "Confirm")
                            {
                                customer.setDOB(newDOB);
                                system("cls");
                                gotoXY(1, 1);
                                changeConsoleColor(3);
                                std::cout << "HOTEL DEL LUNA" << endl;
                                changeConsoleColor(7);
                                std::cout << "______________" << endl;
                                changeConsoleColor(14);
                                gotoXY(40, 5);
                                std::cout << "|==================================================|";
                                gotoXY(40, 6);
                                std::cout << "|                                                  |";
                                gotoXY(40, 7);
                                std::cout << "|==================================================|";
                                gotoXY(49, 6);
                                changeColor(2);
                                std::cout << "Date of birth updated successfully";
                                changeConsoleColor(7);
                                break;
                            }
                        }
                    }
                }
            }
               else if (selectedOption == "Return")
                    {
                         clearFromPosition(1, 1);
                         adminScreen(staff);
                         return false;
                    }
               }
          }

          if (!customerFound)
          {
               gotoXY(97, 15);
               changeConsoleColor(4);
               std::cout << "Customer not found. Press enter to try again or ESC to cancel.";
               changeConsoleColor(7);
               int key = _getch();
               if (key == 27)
               {
                    clearFromPosition(1, 1);
                    adminScreen(staff);
                    return false;
               }
          }

          ofstream file(fileName, ios::trunc);
          if (!file.is_open())
          {
               cout << "Cannot open file!" << endl;
               return false;
          }
          for (const Customer &customer : customers)
          {
               file << customer.getFullName() << "|"
                    << customer.getCCCD() << "|"
                    << customer.getPhone() << "|"
                    << customer.getAdd() << "|"
                    << customer.getDOB().toString() << "|"
                    << customer.getGender() << "|";
               vector<string> roomIDs = customer.getRoomIDs();
               for (size_t i = 0; i < roomIDs.size(); ++i)
               {
                    file << roomIDs[i];
                    if (i < roomIDs.size() - 1)
                    {
                         file << ",";
                    }
               }
               file << "|" << customer.getArrivalDate().toString() << "|";
               vector<string> serviceIDs = customer.getServiceIDs();
               for (size_t i = 0; i < serviceIDs.size(); ++i)
               {
                    file << serviceIDs[i];
                    if (i < serviceIDs.size() - 1)
                    {
                         file << ",";
                    }
               }
               file << endl;
          }

          file.close();
          return true;
     }
}

void Staff::displayCustomer(const vector<Customer> customers)
{
     string border1 = "+-----+--------------------------------+--------------+------------+-----------------------+------------+--------+--------------+---------+----------------+";
     string border2 = "|     |                                |              |            |                       |            |        |              |---------+----------------+";
     string border3 = "|     |                                |              |            |                       |            |        |              |         | ";
     string border4 = "|     |                                |              |            |                       |            |        |              | ";
     cout << border1 << endl;
     cout << "| STT |              NAME              |     CCCD     | PHONE NUM. |        ADDRESS        |  BIRTHDAY  | GENDER | ARRIVAL DATE | ROOM ID |   SERVICE ID   |";
     cout << border1 << endl;

     int count = 0;
     for (const auto &customer : customers)
     {
          ++count;
          cout << "| " << setw(3) << setfill('0') << right << count << " | "
               << setw(31) << setfill(' ') << left << customer.getFullName() << "| "
               << setw(13) << customer.getCCCD() << "| "
               << setw(11) << customer.getPhone() << "| "
               << setw(22) << customer.getAdd() << "| "
               << customer.getDOB() << " | ";

          if (customer.getGender() == "Male")
               changeConsoleColor(11);
          else if (customer.getGender() == "Female")
               changeConsoleColor(12);

          cout << left << setw(7) << setfill(' ') << customer.getGender();
          changeConsoleColor(7);
          cout << "|  " << customer.getArrivalDate() << "  | ";

          vector<string> roomIDs = customer.getRoomIDs();
          for (size_t i = 0; i < roomIDs.size(); i++)
          {
               cout << left << setw(8) << setfill(' ') << roomIDs[i] << "| ";
               string service = "";
               vector<string> serIDs = Room::returnSerIDs(roomIDs[i]);

               for (size_t j = 0; j < serIDs.size(); j++)
               {
                    if (service.length() + serIDs[j].length() + (service.empty() ? 0 : 2) <= 15)
                    {
                         if (!service.empty())
                         {
                              service += ", ";
                         }
                         service += serIDs[j];
                    }
                    else
                    {
                         service += ",";
                         cout << setw(15) << service << "|" << endl;
                         service = serIDs[j]; 
                         cout << border3;
                    }
               }

               cout << setw(15) << service << "|" << endl;

               if (i < roomIDs.size() - 1)
               {
                    cout << border2 << endl;
                    cout << border4;
               }
          }
          cout << border1 << endl;
     }
}