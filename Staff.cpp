#include "Function.h"

void Staff::setID (const string& ID)
{
     this->ID = ID;
}
string Staff::getID () const
{
     return this->ID;
}

bool Staff::setPosition (const string& position)
{
     static const unordered_set<string> validPositions = {"Manager", "Receptionist", "Housekeeping", "Laundry", "Server"};

     if (position.empty())
     {
          changeConsoleColor (12);
          cout << "Position cannot be empty!" << endl;
          return false;
     }

     if (validPositions.find (position) != validPositions.end())
     {
          this->position = position;
          return true;
     } 
     else
     {
          changeConsoleColor (12);
          cout << "The entered position '" << position << "' is not available in our hotel!" << endl;
          cout << "Valide position are: Manager, Receptionist, Housekeeping, Laundry, Server." << endl;
          return false;
     }
} 
string Staff::getPosition () const
{
     return this->position;
}

void Staff::setSalary (const string& salary)
{
     this->salary = salary;
}
string Staff::getSalary () const
{
     return this->salary;
}

vector<Staff> Staff :: readFileStaff (const string &fileName)
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

          getline (ss, fullName, '|');
          getline (ss, CCCD, '|');
          getline (ss, phone, '|');
          getline (ss, add, '|');
          getline (ss, gender, '|');
          getline (ss, dobstr, '|');
          dob = Date (dobstr);
          getline (ss, ID, '|');
          getline (ss, position, '|');
          getline (ss, salary, '|');

          Staff staff (fullName, CCCD, phone, add, gender, dob, ID, position, salary);
          staffs.push_back (staff);
     }

     file.close ();
     return staffs;
}

void Staff::displayStaff (const vector<Staff>& staffs)
{
     cout << "\n" << setw(13) << "STAFFS' INFORMATION IN OUR HOTEL" << endl;
     for (const auto &staff : staffs)
     {
          Sleep (1000);
          string border = "+---------------+----------------------------------------+";
          if (staff.getPosition() == "Manager")
               changeConsoleColor (4);
          else
               changeConsoleColor (7);
          cout << border << endl;
          cout << "| Full Name     | " << left << setw (39) << staff.getFullName() << "|" << endl;
          cout << border << endl;
          cout << "| CCCD          | " << left << setw (39) << staff.getCCCD() << "|" << endl;
          changeConsoleColor (7);
          cout << border << endl;
          cout << "| Phone         | " << left << setw (39) << staff.getPhone() << "|" << endl;
          cout << border << endl;
          cout << "| Address       | " << left << setw (39) << staff.getAdd() << "|" << endl;
          if (staff.getGender () == "Nam")
               changeConsoleColor (1);
          else changeConsoleColor (12);
          cout << border << endl;
          cout << "| Gender        | " << left << setw (39) << staff.getGender() << "|" << endl;
          cout << border << endl;
          cout << "| Date of birth | " << left << setw (39); 
          staff.getDOB().display();
          cout << "|" << endl;
          
          if (staff.getPosition() == "Manager")
               changeConsoleColor (2);
          else if (staff.getPosition() == "Receptionist")
               changeConsoleColor (3);
          else if (staff.getPosition() == "Housekeeping")
               changeConsoleColor (5);
          else if (staff.getPosition () == "Laundry")
               changeConsoleColor (6);
          else changeConsoleColor (8);

          cout << border << endl;
          cout << "| Staff ID      | " << left << setw (39) << staff.getID() << "|" << endl;
          cout << border << endl;
          cout << "| Staff Position| " << left << setw (39) << staff.getPosition() << "|" << endl;
          cout << border << endl;
          cout << "| Staff Salary  | " << left << setw (39) << staff.getSalary() << "|" << endl;
          cout << border << endl;
          cout << endl;
     }
}