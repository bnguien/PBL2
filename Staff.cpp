#include "Staff.h"
#include "Customer.h"
#include "Room.h"
#include "Service.h"

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
               cout << "\nFailed to add new staff: Duplicate CCCD detected for "
                    << newStaff.getCCCD() << "!" << endl;
               changeConsoleColor(7);
               return false;
          }

          if (staff.getID() == newStaff.getID())
          {
               string newID = generateStaffID(staffs, newStaff.getPosition());
               newStaff.setID(newID);
               cout << "\nDuplicate ID detected. \nAutomatically generated new ID: "
                    << newID << "for the new staff member." << endl;
          }
     }

     vector<Staff> temp = {newStaff};
     temp[0].updateStaffFile(temp, staffFile);

     cout << "\nSuccessfully added new staff member with CCCD "
          << newStaff.getCCCD() << "!\n";
     cout << "\nReview the new staff's information: " << endl;
     newStaff.displayStaff(temp);

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
     if (!(this->position == "Manager" || this->position == "Receptionist"))
     {
          changeConsoleColor(4);
          cout << "\nAccess Denied: Only Managers and Receptionists can change room status!" << endl;
          changeConsoleColor(7);
          system("pause");
          return false;
     }

     string roomFile = "Room.txt";
     vector<Room> rooms = Room::readFileRoom(roomFile);
     bool exists = false;

     for (auto &room : rooms)
     {
          if (room.getID() == roomID)
          {
               exists = true;
               if (room.checkAvailable())
               {
                    if (room.setStatus("Unavailable"))
                    {
                         changeConsoleColor(2);
                         cout << "Successfully changed room status from AVAILABLE to UNAVAILABLE." << endl;
                         changeConsoleColor(7);
                    }
               }
               else
               {
                    if (room.setStatus("Available"))
                    {
                         changeConsoleColor(2);
                         cout << "Successfully changed room status from UNAVAILABLE to AVAILABLE" << endl;
                         changeConsoleColor(7);
                    }
               }
               break;
          }
     }

     if (!exists)
     {
          cout << "Failed to find room with ID: " << roomID << ". Please try adding a new one." << endl;
          return false;
     }
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

bool Staff::hasAccess() const
{
     if (this->position == "Manager" || this->position == "Receptionist")
     {
          return true;
     }
     changeConsoleColor(4);
     cout << "\nAccess Denied: Only Managers and Receptionists can change room status!" << endl;
     changeConsoleColor(7);
     system("pause");
     return false;
}

bool Staff::addNewCustomer()
{
    Room room;
    string fileRoom = "Room.txt";
    vector<Room> rooms = room.readFileRoom(fileRoom);
    if (!hasAccess()) 
        return false;

    vector<string> availableRoomIDs;
    while (true)
    {
        std::cout << "Enter the room IDs that the customer want to book (separated by commas): ";
        string roomIDsInput;
        getline(cin, roomIDsInput);

        vector<string> roomIDs;
        string currentRoomID = "";

        // Tách mã phòng nhập vào, bỏ qua khoảng trắng
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
            else if (ch != ' ')  // Bỏ qua dấu cách
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

        // Kiểm tra trạng thái của từng phòng trong danh sách
        for (const string &inputRoomID : roomIDs)
        {
            bool roomFound = false;

            // Tìm phòng trong danh sách các phòng
            for (const Room& roomRef : rooms)
            {
                if (roomRef.getID() == inputRoomID)
                {
                    roomFound = true;
                    if (roomRef.checkAvailable())
                    {
                        availableRoomIDs.push_back(inputRoomID);
                    }
                    else
                    {
                        unavailableRoomIDs.push_back(inputRoomID);
                    }
                    break;  // Không cần phải kiểm tra thêm nếu đã tìm thấy phòng
                }
            }

            // Nếu không tìm thấy phòng trong danh sách
            if (!roomFound)
            {
                unavailableRoomIDs.push_back(inputRoomID);
            }
        }

        // Thông báo phòng không có sẵn
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

        // Thông báo phòng có sẵn và tiếp tục với việc đặt phòng
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

    changeConsoleColor(14);
    gotoXY(50, 11);
    std::cout << "+-------------------------------------------+" << std::endl;
    gotoXY(50, 12);
    std::cout << "|            YOUR INFORMATION               |" << std::endl;
    gotoXY(50, 13);
    std::cout << "+-------------------------------------------+" << std::endl;

    gotoXY(50, 14);
    std::cout << "|  Full Name      :                         |" << std::endl;
    gotoXY(50, 15);
    std::cout << "|-------------------------------------------|" << std::endl;

    gotoXY(50, 16);
    std::cout << "|  CCCD           :                         |" << std::endl;
    gotoXY(50, 17);
    std::cout << "|-------------------------------------------|" << std::endl;

    gotoXY(50, 18);
    std::cout << "|  Phone Number   :                         |" << std::endl;
    gotoXY(50, 19);
    std::cout << "|-------------------------------------------|" << std::endl;

    gotoXY(50, 20);
    std::cout << "|  Address        :                         |" << std::endl;
    gotoXY(50, 21);
    std::cout << "|-------------------------------------------|" << std::endl;

    gotoXY(50, 22);
    std::cout << "|  Gender         :                         |" << std::endl;
    gotoXY(50, 23);
    std::cout << "|-------------------------------------------|" << std::endl;

    gotoXY(50, 24);
    std::cout << "|  Birth Date     :                         |" << std::endl;
    gotoXY(50, 25);
    std::cout << "|-------------------------------------------|" << std::endl;

    gotoXY(50, 26);
    std::cout << "|  Arrival Date   :                         |" << std::endl;
    gotoXY(50, 27);
    std::cout << "+-------------------------------------------+" << std::endl;

    changeConsoleColor(15);

    gotoXY(70, 14);
    std::getline(std::cin, fullName);

    gotoXY(70, 16);
    std::getline(std::cin, CCCD);

    gotoXY(70, 18);
    std::getline(std::cin, phone);

    gotoXY(70, 20);
    std::getline(std::cin, add);

    gotoXY(70, 22);
    std::getline(std::cin, gender);

    gotoXY(70, 24);
    std::getline(std::cin, DOBstr);
    DOB = Date(DOBstr);

    gotoXY(70, 26);
    std::getline(std::cin, arrivalDateStr);
    arrivalDate = Date(arrivalDateStr);

    fullName = Person::standardizeString(fullName);
    add = Person::standardizeString(add);
    gender = Person::standardizeString(gender);
    Person person(fullName, CCCD, phone, add, gender, DOB);

    Customer newCustomer(person, availableRoomIDs, arrivalDate, {"None"}, {"None"});
    string customerFile = "Customer.txt";
    if (!Customer::saveCustomerToFile(newCustomer, customerFile))
    {
        changeConsoleColor(4);
        cout << "\nFailed to save to our hotel's customer file!" << endl;
        changeConsoleColor(7);
        system("pause");
        return false;
    }

    // Cập nhật trạng thái phòng
    for (auto &roomRef : rooms)
    {
        if (find(availableRoomIDs.begin(), availableRoomIDs.end(), roomRef.getID()) != availableRoomIDs.end())
        {
            roomRef.setStatus("Unavailable");
        }
    }
    std::cout << endl;
    room.updateRoomFile(rooms, fileRoom);
    std::cout << "Booking successful for rooms: ";
    for (const auto &bookedID : availableRoomIDs)
    {
        std::cout << bookedID << " ";
    }
    std::cout << endl;
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

bool Staff::removeCustomerByCCCD(const string &CCCDToRemove)
{
     string customerFile = "Customer.txt";
     if (!hasAccess())
          return false;

     vector<Customer> customers = Customer::readFileCustomer(customerFile);
     Customer tempCustomer;
     tempCustomer.setCCCD(CCCDToRemove);
     int index = cusExists(customers, tempCustomer);
     if (index < 0)
     {
          changeConsoleColor(4);
          cout << "Cannot find this customer's information to remove!" << endl;
          changeConsoleColor(7);
          return false;
     }

     vector<Customer> remainingCustomers;
     for (size_t i = 0; i < customers.size(); i++)
          if (i != index)
               remainingCustomers.push_back(customers[i]);

     if (writeRemainingCus(remainingCustomers, customerFile))
     {
          changeConsoleColor(2);
          cout << "Successfully removed customer with CCCD: " << CCCDToRemove << endl;

          return true;
     }
     return false;
}

bool Staff::findCustomerByCCCD(const string &CCCD)
{
     string customerFile = "Customer.txt";
     if (!hasAccess())
          return false;

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

bool Staff::findCustomerByAttribute(const string &attributeName, const string &attributeValue)
{
     if (!hasAccess())
          return false;

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

bool Staff::findCustomerByFirstName(const string &firstName)
{
     return findCustomerByAttribute("firstName", firstName);
}

bool Staff::findCustomerByLastName(const string &lastName)
{
     return findCustomerByAttribute("lastName", lastName);
}

bool Staff::findCustomerByLetter(const char &letter)
{
     string customerFile = "Customer.txt";
     if (!hasAccess())
          return false;

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

/* bool updateCustomer(const string &type, const string &infor)
{
} */

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
