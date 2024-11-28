#include "Staff.h"
#include "Customer.h"
#include "Room.h"
#include "Service.h"
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
     this->salary = formatSalary(salary);
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

void Staff::displayStaff(const vector<Staff> &staffs)
{
     cout << "\n"
          << setw(13) << "STAFFS' INFORMATION IN OUR HOTEL" << endl;
     for (const auto &staff : staffs)
     {
          Sleep(1000);
          string border = "+---------------+----------------------------------------+";
          if (staff.getPosition() == "Manager")
               changeConsoleColor(4);
          else
               changeConsoleColor(7);
          cout << border << endl;
          cout << "| Full Name     | " << left << setw(39) << staff.getFullName() << "|" << endl;
          cout << border << endl;
          cout << "| CCCD          | " << left << setw(39) << staff.getCCCD() << "|" << endl;
          changeConsoleColor(7);
          cout << border << endl;
          cout << "| Phone         | " << left << setw(39) << staff.getPhone() << "|" << endl;
          cout << border << endl;
          cout << "| Address       | " << left << setw(39) << staff.getAdd() << "|" << endl;
          if (staff.getGender() == "Nam")
               changeConsoleColor(1);
          else
               changeConsoleColor(12);
          cout << border << endl;
          cout << "| Gender        | " << left << setw(39) << staff.getGender() << "|" << endl;
          cout << border << endl;
          cout << "| Date of birth | " << left << setw(39);
          staff.getDOB().display();
          cout << "|" << endl;

          if (staff.getPosition() == "Manager")
               changeConsoleColor(2);
          else if (staff.getPosition() == "Receptionist")
               changeConsoleColor(3);
          else if (staff.getPosition() == "Housekeeping")
               changeConsoleColor(5);
          else if (staff.getPosition() == "Laundry")
               changeConsoleColor(6);
          else
               changeConsoleColor(8);

          cout << border << endl;
          cout << "| Staff ID      | " << left << setw(39) << staff.getID() << "|" << endl;
          cout << border << endl;
          cout << "| Staff Position| " << left << setw(39) << staff.getPosition() << "|" << endl;
          cout << border << endl;
          cout << "| Staff Salary  | " << left << setw(39) << staff.getSalary() << "|" << endl;
          cout << border << endl;
          cout << endl;
     }
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
     if (position.empty())
     {
          cout << "Invalid position information!" << endl;
          return "";
     }

     vector<Staff> temp;
     for (const auto &staff : staffs)
     {
          if (staff.getPosition() == position)
               temp.push_back(staff);
     }
     if (temp.empty())
     {
          return string(1, position[0]) + "01";
     }
     else
     {
          string lastID = temp[temp.size() - 1].getID();

          int lastNumber = stoi(lastID.substr(1));
          lastNumber++;

          stringstream newID;
          newID << position[0] << setw(2) << setfill('0') << lastNumber;
          return newID.str();
     }
}

bool Staff::addNewStaff(Staff &newStaff)
{
     string staffFile = "Staff.txt";
     if (this->position != "Manager")
     {
          changeConsoleColor(4);
          cout << "Access Denied: Only Managers can add new staff members!" << endl;
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

bool Staff::removeStaff(Staff &staffToRemove)
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

     if (staffs.empty())
     {
          changeConsoleColor(4);
          cout << "No staff members found in the file!" << endl;
          changeConsoleColor(7);
          return false;
     }

     vector<Staff> updatedStaffs;
     bool found = false;

     for (const auto &staff : staffs)
     {
          if (staff == staffToRemove)
          {
               found = true;
               cout << "Removing staff member with CCCD ("
                    << staffToRemove.getCCCD() << ") and position ("
                    << staffToRemove.getPosition() << ")\n";
               continue;
          }
          updatedStaffs.push_back(staff);
     }

     if (!found)
     {
          changeConsoleColor(4);
          cout << "No staff member found with these details!" << endl;
          changeConsoleColor(7);
          return false;
     }

     ofstream file(staffFile, ios::trunc);
     if (!file.is_open())
     {
          cout << "Cannot open staff file!" << endl;
          return false;
     }

     for (const auto &staff : updatedStaffs)
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

     changeConsoleColor(2);
     cout << "Successfully removed staff member with these details!" << endl;
     changeConsoleColor(7);
     return true;
}

bool Staff::removeStaffByCCCD(const string &CCCDToRemove)
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

     if (staffs.empty())
     {
          changeConsoleColor(4);
          cout << "No staff members found in the file!" << endl;
          changeConsoleColor(7);
          return false;
     }

     vector<Staff> updatedStaffs;
     bool found = false;

     for (const auto &staff : staffs)
     {
          if (staff.getCCCD() == CCCDToRemove)
          {
               found = true;
               cout << "Removing staff member with CCCD: " << CCCDToRemove << "!.\n";
               continue;
          }
          updatedStaffs.push_back(staff);
     }

     if (!found)
     {
          changeConsoleColor(4);
          cout << "No staff member found with CCCD: " << CCCDToRemove << endl;
          changeConsoleColor(7);
          return false;
     }

     ofstream file(staffFile, ios::trunc);
     if (!file.is_open())
     {
          cout << "Cannot open staff file!" << endl;
          return false;
     }

     for (const auto &staff : updatedStaffs)
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

     changeConsoleColor(2);
     cout << "Successfully removed staff member with CCCD: " << CCCDToRemove << endl;
     changeConsoleColor(7);
     return true;
}

bool Staff::changeRoomStatus(const string &roomID)
{
     if (this->position != "Manager" && this->position != "Receptionist")
     {
          changeConsoleColor(4);
          cout << "\nAccess Denied: Only Managers and Receptionists can change room status!" << endl;
          changeConsoleColor(7);
          system("pause");
          return false;
     }

     string roomFile = "Room.txt";
     vector<Room> rooms = Room::readFileRoom(roomFile);
     if (rooms.empty())
     {
          changeConsoleColor(4);
          cout << "\nError: Unable to load room data. Please check the file!" << endl;
          changeConsoleColor(7);
          return false;
     }

     bool exists = false;

     for (auto &room : rooms)
     {
          if (room.getID() == roomID)
          {
               exists = true;
               room.setStatus(room.checkAvailable() ? "Unavailable" : "Available");
               break;
          }
     }

     if (!exists)
     {
          changeConsoleColor(4);
          cout << "Error: Room with ID " << roomID << " not found. Please try adding a new one." << endl;
          changeConsoleColor(7);
          return false;
     }

     if (!Room::updateRoomFile(rooms, roomFile))
     {
          changeConsoleColor(4);
          cout << "Error: Failed to update room file. Please try again!" << endl;
          changeConsoleColor(7);
          return false;
     }

     changeConsoleColor(2);
     cout << "Successfully changed room status for ID: " << roomID << endl;
     changeConsoleColor(7);
     return true;
}

bool Staff::updateStaff(const string &type, const string &infor, const string &ID)
{
     if (this->position != "Manager")
     {
          changeConsoleColor(4);
          cout << "\nAccess Denied: Only Managers can add new staff members!" << endl;
          changeConsoleColor(7);
          return false;
     }

     string staffFile = "Staff.txt";
     vector<Staff> staffs = readFileStaff(staffFile);
     bool check = false;

     for (auto &staff : staffs)
     {
          if (staff.getID() == ID)
          {
               if (type == "Phone")
               {
                    check = staff.setPhone(infor);
               }
               else if (type == "Position")
               {
                    check = staff.setPosition(infor);
               }
               else if (type == "Salary")
               {
                    staff.setSalary(infor);
                    check = true;
               }
               else
               {
                    cout << "Invalid update type: " << type << endl;
                    return false;
               }
               break;
          }
     }

     if (!check)
     {
          changeConsoleColor(12);
          cout << "Failed to update Staff's information. Invalid ID: " << ID << endl;
          changeConsoleColor(7);
          return false;
     }

     staffs[0].updateStaffFile(staffs, staffFile);

     changeConsoleColor(2);
     cout << "Successfully updated Staff's " << type << " to \""
          << infor << "\" for ID: " << ID << endl;
     changeConsoleColor(7);

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
     gotoXY(55, 15);
     changeConsoleColor(6);
     std::cout << "SELECT TYPE OF ROOM" << endl;
     changeConsoleColor(7);
     vector<string> roomTypeOptions = {"Single", "Double", "Triple", "Return"};
     int roomTypeIndex = buttonList(6, 17, 15, 2, 18, roomTypeOptions, "row");

     if (roomTypeIndex < 0 || roomTypeIndex > roomTypeOptions.size())
     {
          std::cout << "Invalid selection!" << endl;
          return false;
     }

     string selectedRoomType = roomTypeOptions[roomTypeIndex - 1];
     char roomTypeChar = (selectedRoomType == "Single")   ? 'S'
                         : (selectedRoomType == "Double") ? 'D'
                         : (selectedRoomType == "Triple") ? 'T'
                                                          : '\0';

     system("cls");
     if (selectedRoomType == "Return")
     {
          clearFromPosition(1, 1);
          adminScreen(staff);
          return false;
     }
     vector<Room> filteredRooms;
     for (const auto &room : rooms)
     {
          if (!room.getID().empty() && room.getID().front() == roomTypeChar)
          {
               filteredRooms.push_back(room);
          }
     }

     if (filteredRooms.empty())
     {
          std::cout << "No rooms available for the selected type: " << selectedRoomType << endl;
          return false;
     }

     std::cout << "Available rooms of type " << selectedRoomType << ":" << endl;
     for (const auto &filteredRoom : filteredRooms)
     {
          Sleep(100);
          string border = "+---------------+-----------------------------------+";
          cout << border << endl;
          changeConsoleColor(9);
          cout << "| Room ID       | " << left << setw(34) << filteredRoom.getID() << "|" << endl;
          cout << border << endl;
          changeConsoleColor(12);
          cout << "| Room Type     | " << left << setw(34) << filteredRoom.getType() << "|" << endl;
          cout << border << endl;
          changeConsoleColor(8);
          cout << "| Room Price    | " << left << setw(34) << filteredRoom.getPrice() << "|" << endl;
          cout << border << endl;
          if (filteredRoom.checkAvailable())
          {
               changeConsoleColor(2);
          }
          else
          {
               changeConsoleColor(4);
          }
          cout << "| Room Status   | " << left << setw(34)
               << (filteredRoom.checkAvailable() ? "Available" : "Unavailable") << "|" << endl;
          cout << border << endl;
          changeConsoleColor(7);
     }
     changeConsoleColor(7);
     vector<string> availableRoomIDs;
     while (true)
     {
          std::cout << "Enter the room IDs you want to book (separated by commas): ";
          string roomIDsInput;
          getline(cin, roomIDsInput);

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
                    currentRoomID += ch;
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
               continue;
          }

          if (!availableRoomIDs.empty())
          {
               std::cout << "Rooms ";
               for (size_t i = 0; i < availableRoomIDs.size(); ++i)
               {
                    std::cout << availableRoomIDs[i];
                    if (i < availableRoomIDs.size() - 1)
                    {
                         std::cout << ", ";
                    }
               }
               std::cout << " are available. Proceeding with booking." << endl;
               break;
          }
          else
          {
               std::cout << "No available rooms selected. Please try again." << endl;
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

     gotoXY(69, 14);
     std::getline(std::cin, fullName);

     bool isValidCCCD = false;

     do
     {
          gotoXY(69, 16);
          std::getline(std::cin, CCCD);

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
          gotoXY(69, 18);
          std::getline(std::cin, phone);

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
          else
          {
               bool isDigitOnly = true;
               for (size_t i = 1; i < phone.length(); i++)
               {
                    if (!isdigit(phone[i]))
                    {
                         isDigitOnly = false;
                         gotoXY(97, 18);
                         changeConsoleColor(4);
                         cout << "Phone must have only digits! Press enter to try again" << endl;
                         changeConsoleColor(7);
                         gotoXY(97, 18);
                         _getch();
                         cout << string(75, ' ');
                         break;
                    }
               }
               if (isDigitOnly)
               {
                    isValidPhone = true;
               }
          }

          if (!isValidPhone)
          {
               gotoXY(69, 18);
               cout << string(phone.length(), ' ');
          }

     } while (!isValidPhone);

     gotoXY(69, 20);
     std::getline(std::cin, add);

     gotoXY(69, 22);
     std::getline(std::cin, gender);

     while (true)
     {
          gotoXY(69, 24);
          cout << string(25, ' ');
          gotoXY(69, 24);
          std::getline(std::cin, DOBstr);

          if (DOBstr.empty())
          {
               gotoXY(97, 24);
               changeConsoleColor(4);
               std::cout << "Date of Birth cannot be empty. Press enter to try again (dd/mm/yyyy).";
               changeConsoleColor(7);
               _getch();
               gotoXY(97, 24);
               cout << string(75, ' ');
               continue;
          }

          stringstream ss(DOBstr);
          string token;
          int day = 0, month = 0, year = 0;
          bool validDate = true;

          Date DOBDate(DOBstr);
          if (!DOBDate.isValidDateFormat(DOBstr))
          {
               validDate = false;
          }
          else
          {
               getline(ss, token, '/');
               if (DOBDate.isNumber(token))
               {
                    day = stoi(token);
               }
               else
               {
                    validDate = false;
               }

               getline(ss, token, '/');
               if (DOBDate.isNumber(token))
               {
                    month = stoi(token);
               }
               else
               {
                    validDate = false;
               }

               getline(ss, token, '/');
               if (DOBDate.isNumber(token))
               {
                    year = stoi(token);
               }
               else
               {
                    validDate = false;
               }
          }

          if (!validDate || day == 0 || month == 0 || year == 0)
          {
               gotoXY(97, 24);
               changeConsoleColor(4);
               std::cout << "Invalid date format. Press enter to try again (dd/mm/yyyy).";
               changeConsoleColor(7);
               _getch();
               gotoXY(97, 24);
               cout << string(75, ' ');
               continue;
          }
          else
          {
               DOB = Date(DOBstr);
               break;
          }
     }

     while (true)
     {
          gotoXY(69, 26);
          cout << string(25, ' ');
          gotoXY(69, 26);
          std::getline(std::cin, arrivalDateStr);

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

          stringstream ss(arrivalDateStr);
          string token;
          int day = 0, month = 0, year = 0;
          bool validDate = true;

          Date arrivalDateTemp(arrivalDateStr);
          if (!arrivalDateTemp.isValidDateFormat(arrivalDateStr))
          {
               validDate = false;
          }
          else
          {
               getline(ss, token, '/');
               if (arrivalDateTemp.isNumber(token))
               {
                    day = stoi(token);
               }
               else
               {
                    validDate = false;
               }

               getline(ss, token, '/');
               if (arrivalDateTemp.isNumber(token))
               {
                    month = stoi(token);
               }
               else
               {
                    validDate = false;
               }

               getline(ss, token, '/');
               if (arrivalDateTemp.isNumber(token))
               {
                    year = stoi(token);
               }
               else
               {
                    validDate = false;
               }
          }

          if (!validDate || day == 0 || month == 0 || year == 0)
          {
               gotoXY(97, 26);
               changeConsoleColor(4);
               std::cout << "Invalid date format. Press enter to try again (dd/mm/yyyy).";
               changeConsoleColor(7);
               _getch();
               gotoXY(97, 26);
               cout << string(75, ' ');
               continue;
          }
          else
          {
               arrivalDate = Date(arrivalDateStr);
               break;
          }
     }
     vector<string> Options = {"Cancel", "Confirm"};
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
          Person person(fullName, CCCD, phone, add, gender, DOB);

          Customer newCustomer(person, availableRoomIDs, arrivalDate, {"None"}, {"None"});
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
               cout << "Failed to open customer file!" << endl;
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
               cout << "Cannot find this customer's information to remove!" << endl;
               changeConsoleColor(7);
               return false;
          }
          ofstream outFile(customerFile);
          if (!outFile)
          {
               changeConsoleColor(4);
               cout << "Failed to write to customer file!" << endl;
               changeConsoleColor(7);
               return false;
          }

          for (const auto &customer : remainingCustomers)
          {
               outFile << customer << endl;
          }
          outFile.close();
          changeConsoleColor(2);
          cout << "Successfully removed customer with CCCD: " << CCCDToRemove << endl;
          changeConsoleColor(7);
          return true;
     }
     else
          return false;
}

bool Staff::findCustomerByCCCD(const Staff &staff, const string &CCCD)
{
     string customerFile = "Customer.txt";
     if (hasAccess(staff))
     {
          vector<Customer> customers = Customer::readFileCustomer(customerFile);
          Customer tempCustomer;
          tempCustomer.setCCCD(CCCD);
          int index = cusExists(customers, tempCustomer);

          if (index < 0)
          {
               changeConsoleColor(4);
               cout << "Cannot find this customer's information!" << endl;
               changeConsoleColor(7);
               return false;
          }

          vector<Customer> tempCustomers;
          tempCustomers.push_back(tempCustomer);
          vector<Service> services = Service::readFileService("Service.txt");
          tempCustomer.displayCustomer(tempCustomers, services);
          return true;
     }
     return false;
}

bool Staff::findCustomerByAttribute(const Staff &staff, const string &attributeName, const string &attributeValue)
{
     if (hasAccess(staff))
     {
          vector<Customer> customers = Customer::readFileCustomer("Customer.txt");
          vector<Customer> customerList;

          for (auto &customer : customers)
          {
               if ((attributeName == "firstName" && customer.getFirstName() == attributeValue) ||
                   (attributeName == "lastName" && customer.getLastName() == attributeValue))
               {
                    customerList.push_back(customer);
               }
          }

          if (!customerList.empty())
          {
               vector<Service> services = Service::readFileService("Service.txt");
               customers[0].displayCustomer(customerList, services);
               return true;
          }
          else
          {
               changeConsoleColor(4);
               cout << "No customer found with the " << attributeName << ": " << attributeValue << endl;
               changeConsoleColor(7);
               return false;
          }
     }

     return false;
}

bool Staff::findCustomerByFirstName(const Staff &staff, const string &firstName)
{
     return findCustomerByAttribute(staff, "firstName", firstName);
}

bool Staff::findCustomerByLastName(const Staff &staff, const string &lastName)
{
     return findCustomerByAttribute(staff, "lastName", lastName);
}

bool Staff::findCustomerByLetter(const Staff &staff, const char &letter)
{
     string customerFile = "Customer.txt";
     if (hasAccess(staff))
          return false;
     {
          vector<Customer> customers = Customer::readFileCustomer(customerFile);
          vector<Customer> customerList;

          for (const auto &customer : customers)
          {
               if (tolower(customer.getFullName().find(tolower(letter)) != string::npos) ||
                   toupper(customer.getFullName().find(toupper(letter)) != string::npos))
                    customerList.push_back(customer);
          }

          if (!customerList.empty())
          {
               vector<Service> services = Service::readFileService("Service.txt");
               customers[0].displayCustomer(customerList, services);
               return true;
          }
          else
          {
               changeConsoleColor(4);
               cout << "No customer found with the character '" << toupper(letter) << "' in their name." << endl;
               changeConsoleColor(7);
               return false;
          }
     }
}

bool Staff::changeServicePrice(const string &serID, const string &price)
{
     vector<Service> services = Service::readFileService("Service.txt");
     bool found = false;

     for (auto &service : services)
     {
          if (service.getID() == serID)
          {
               service.setPrice(price);
               found = true;
               break;
          }
     }

     if (!found)
     {
          cout << "\nCannot find service's ID: " << serID << endl;
          return false;
     }

     if (services[0].updateServiceFile(services, "Service.txt"))
     {
          cout << "Successfully changed price of service with ID: " << serID << " to " << price << endl;
          return true;
     }
     else
     {
          cout << "Failed to update service file!" << endl;
          return false;
     }
}
bool Staff::updateCustomer(Staff &staff, const string &fileName, vector<Customer> &customers)
{
     while (true)
     {
          gotoXY(35, 12);
          changeConsoleColor(9);
          cout << "ENTER CUSTOMER'S NAME AND CUSTOMER'S ID CARD(CCCD)" << endl;
          changeConsoleColor(14);
          gotoXY(25, 14);
          std::cout << "|---------------------------------------------------------------------|" << std::endl;
          gotoXY(25, 15);
          std::cout << "|  Customer's Name           |                                        |" << std::endl;
          gotoXY(25, 16);
          std::cout << "|---------------------------------------------------------------------|" << std::endl;
          gotoXY(25, 17);
          std::cout << "|  Customer's CCCD (ID card) |                                        |" << std::endl;
          gotoXY(25, 18);
          std::cout << "|---------------------------------------------------------------------|" << std::endl;
          string inputName, inputCCCD;
          changeConsoleColor(7);
          gotoXY(55, 15);
          getline(cin, inputName);
          bool isValidCCCD = false;
          do
          {
               gotoXY(55, 17);
               getline(cin, inputCCCD);

               if (inputCCCD.length() != 12)
               {
                    changeConsoleColor(4);
                    gotoXY(97, 17);
                    cout << "CCCD must have exactly 12 digits!Press enter to try again" << endl;
                    changeConsoleColor(7);
                    _getch();
                    gotoXY(97, 17);
                    cout << string(75, ' ');
               }
               else
               {
                    bool isDigitOnly = true;
                    for (size_t i = 0; i < inputCCCD.length(); i++)
                    {
                         if (!isdigit(inputCCCD[i]))
                         {
                              isDigitOnly = false;
                              gotoXY(97, 17);
                              changeConsoleColor(4);
                              cout << "CCCD must have only digits!Press enter to try again" << endl;
                              changeConsoleColor(7);
                              _getch();
                              gotoXY(97, 17);
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
                    gotoXY(55, 17);
                    cout << string(inputCCCD.length(), ' ');
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
                    cout << "HOTEL DEL LUNA" << endl;
                    changeConsoleColor(7);
                    cout << "______________" << endl;
                    gotoXY(37, 5);
                    changeConsoleColor(6);
                    std::cout << "WHICH CUSTOMER'S INFORMATION WOULD YOU LIKE TO UPDATE" << endl;
                    changeConsoleColor(7);
                    vector<string> options = {"Change phone number", "Change address", "Change Date of Birth (DOB)", "Return"};
                    int choice = buttonList(40, 8, 34, 2, 2, options, "column");

                    if (choice < 1 || choice > options.size())
                    {
                         cout << "Invalid selection!\n";
                         return false;
                    }

                    string selectedOption = options[choice - 1];
                    system("cls");
                    gotoXY(1, 1);
                    changeConsoleColor(3);
                    cout << "HOTEL DEL LUNA" << endl;
                    changeConsoleColor(7);
                    cout << "______________" << endl;
                    if (selectedOption == "Change phone number")
                    {
                         string newPhone;
                         while (true)
                         {
                              gotoXY(10, 5);
                              changeConsoleColor(9);
                              cout << "Enter the new phone number: ";
                              changeConsoleColor(7);
                              getline(cin, newPhone);
                              if (customer.getPhone() == newPhone)
                              {
                                   gotoXY(10, 7);
                                   changeConsoleColor(4);
                                   cout << "The new phone number is the same as the old one. Please enter a different phone number." << endl;
                                   changeConsoleColor(7);
                                   _getch();
                                   gotoXY(30, 5);
                                   cout << string(75, ' ');
                                   gotoXY(10, 7);
                                   cout << string(150, ' ');
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

                                             changeConsoleColor(2);
                                             gotoXY(40, 11);
                                             cout << "Phone number updated successfully.\n";
                                             changeConsoleColor(7);
                                             break;
                                        }
                                   }
                                   else
                                   {
                                        changeColor(4);
                                        _getch();
                                        gotoXY(10, 7);
                                        cout << string(100, ' ');
                                        gotoXY(30, 5);
                                        cout << string(75, ' ');
                                        gotoXY(1, 7);
                                        cout << string(150, ' ');
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
                              cout << "Enter the new address: ";
                              changeConsoleColor(7);
                              getline(cin, newAddress);
                              if (customer.getAdd() == newAddress)
                              {
                                   gotoXY(10, 7);
                                   changeConsoleColor(4);
                                   cout << "The new address is the same as the old one. Please enter a different address." << endl;
                                   changeConsoleColor(7);
                                   _getch();
                                   gotoXY(30, 5);
                                   cout << string(75, ' ');
                                   gotoXY(10, 7);
                                   cout << string(150, ' ');
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
                                        gotoXY(40, 11);
                                        changeConsoleColor(2);
                                        cout << "Address updated successfully.\n";
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
                                   gotoXY(10, 7);
                                   changeConsoleColor(4);
                                   cout << "The new date of birth is the same as the old one. Please enter a different date of birth." << endl;
                                   changeConsoleColor(7);
                                   _getch();
                                   gotoXY(52, 5);
                                   cout << string(75, ' ');
                                   gotoXY(10, 7);
                                   cout << string(150, ' ');
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
                                        continue;
                                   }

                                   stringstream ss(newDOB);
                                   string token;
                                   int day = 0, month = 0, year = 0;
                                   bool validDate = true;

                                   Date DobDate(newDOB);
                                   if (!DobDate.isValidDateFormat(newDOB))
                                   {
                                        validDate = false;
                                   }
                                   else
                                   {
                                        getline(ss, token, '/');
                                        if (DobDate.isNumber(token))
                                        {
                                             day = stoi(token);
                                        }
                                        else
                                        {
                                             validDate = false;
                                        }

                                        getline(ss, token, '/');
                                        if (DobDate.isNumber(token))
                                        {
                                             month = stoi(token);
                                        }
                                        else
                                        {
                                             validDate = false;
                                        }

                                        getline(ss, token, '/');
                                        if (DobDate.isNumber(token))
                                        {
                                             year = stoi(token);
                                        }
                                        else
                                        {
                                             validDate = false;
                                        }
                                   }

                                   if (!validDate || day == 0 || month == 0 || year == 0)
                                   {
                                        changeConsoleColor(4);
                                        gotoXY(10, 7);
                                        cout << "Invalid date format. Please enter a valid Date of Birth (DD/MM/YYYY): ";
                                        changeConsoleColor(7);
                                        _getch();
                                        gotoXY(52, 5);
                                        cout << string(150, ' ');
                                        gotoXY(10, 7);
                                        cout << string(150, ' ');
                                        gotoXY(52, 5);
                                        continue;
                                   }

                                   Date dobDate(newDOB);
                                   customer.setDOB(dobDate);

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
                                        changeConsoleColor(2);
                                        gotoXY(40, 11);
                                        cout << "Date of Birth updated successfully.\n";
                                        changeConsoleColor(7);
                                        break;
                                   }
                              }
                         }
                    }
                    else if (selectedOption == "Return")
                    {
                         clearFromPosition(1, 1);
                         adminScreen(staff);
                    }

                    break;
               }
          }
          if (!customerFound)
          {
               changeConsoleColor(4);
               gotoXY(25, 20);
               cout << "Customer not found. Please try again!" << endl;
               changeConsoleColor(7);
               _getch();
               gotoXY(55, 15);
               cout << string(75, ' ');
               gotoXY(55, 17);
               cout << string(75, ' ');
               gotoXY(25, 20);
               cout << string(75, ' ');
          }
          else
          {
               break;
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

               for (size_t j = 0; j < serIDs.size() - 1; j++)
               {
                    if (service.length() + serIDs[j].length() + 2 <= 15)
                    {
                         service += serIDs[j];
                         if (!service.empty())
                              service += ", ";
                    }
                    else
                    {
                         cout << service << "|" << endl;
                         cout << border3;
                         service.clear();
                    }
               }
               service += serIDs[serIDs.size() - 1];
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