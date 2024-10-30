#include "Staff.h"

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
     static const unordered_set<string> validPositions = {"Manager", "Receptionist", "Housekeeping", "Laundry", "Server"};

     if (position.empty())
     {
          changeConsoleColor(12);
          cout << "Position cannot be empty!" << endl;
          return false;
     }

     if (validPositions.find(position) != validPositions.end())
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
void Staff::addNewStaff(const Staff &newStaff)
{
     string staffFile = "Staff.txt";
     if (this->position != "Manager")
     {
          changeConsoleColor(4);
          cout << "\nAccess Denied: Only Managers can add new staff members!" << endl;
          changeConsoleColor(7);
          return;
     }

     vector<Staff> staffs = readFileStaff(staffFile);
     bool exists = false;
     bool positionChanged = false;

     for (const auto &staff : staffs)
     {
          if (staff == newStaff)
          {
               exists = true;
               changeConsoleColor(4);
               cout << "This staff member's information is already recorded in staff file!" << endl;
               changeConsoleColor(7);
               return;
          }

          if (staff.getCCCD() == newStaff.getCCCD())
          {
               positionChanged = (staff.getPosition() != newStaff.getPosition());
          }
     }

     if (exists && !positionChanged)
     {
          cout << "Failed to add new staff due to duplicate CCCD information.\n"
               << "No new position was assigned for this staff member!" << endl;
          return;
     }

     vector<Staff> temp;
     temp.push_back(newStaff);
     temp[0].updateStaffFile(temp, staffFile);

     if (exists && positionChanged)
     {
          cout << "New position assigned to the existing staff member having CCCD "
               << newStaff.getCCCD() << "!\n";
          return;
     }

     cout << "Successfully added new staff member with CCCD " 
          << newStaff.getCCCD() << "!\n";
}

void Staff::removeStaff(Staff &staffToRemove)
{
     string staffFile = "Staff.txt";
     vector<Staff> staffs = readFileStaff(staffFile);

     if (staffs.empty())
     {
          changeConsoleColor(4);
          cout << "No staff members found in the file!" << endl;
          changeConsoleColor(7);
          return;
     }
     
     vector<Staff> updatedStaffs;
     bool found = false;

     for (const auto& staff : staffs)
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
          return;
     }

     updateStaffFile(updatedStaffs,staffFile);
     changeConsoleColor(2);
     cout << "Successfully removed staff member with these details!" << endl;
     changeConsoleColor(7);
}

void Staff::removeStaffByCCCD(const string &CCCDToRemove)
{
     string staffFile = "Staff.txt";
     vector<Staff> staffs = readFileStaff(staffFile);

     if (staffs.empty())
     {
          changeConsoleColor(4);
          cout << "No staff members found in the file!" << endl;
          changeConsoleColor(7);
          return;
     }

     vector<Staff> updatedStaffs;
     bool found = false;

     for (const auto& staff : staffs)
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
          cout << "No staff member found with CCCD: "  << CCCDToRemove << endl;
          changeConsoleColor(7);
          return;
     }

     updateStaffFile(updatedStaffs,staffFile);
     changeConsoleColor(2);
     cout << "Successfully removed staff member with CCCD: "  << CCCDToRemove << endl;
     changeConsoleColor(7);
}
