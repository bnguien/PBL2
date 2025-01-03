#include "Menu.h"

#include "Person.cpp"
#include "Customer.cpp"
#include "Room.cpp"
#include "Service.cpp"
#include "Staff.cpp"
#include "Date.cpp"
#include "Login.cpp"
#include "Bill.cpp"
#include "BillStaff.cpp"
#include "Function.h"
#include "Vector.h"

int main()
{
     ShowCur(0);
     introScreen();
}

void welcomeTo()
{
     for (int line = 0; line < 8; line++)
     {
          switch (line)
          {
          case (0):
               cout << "***               ***   **************   ***              **************   **************   *** ***     *** ***   **************";
               Sleep(50);
               cout << endl;
               break;
          case (1):
               cout << "***               ***   **************   ***              **************   **************   *** ***     *** ***   **************";
               Sleep(50);
               cout << endl;
               break;
          case (2):
               cout << " ***             ***    ***              ***              ***              ***        ***   *** ***     *** ***   ***";
               Sleep(50);
               cout << endl;
               break;
          case (3):
               cout << " ***             ***    **************   ***              ***              ***        ***   ***   *** ***   ***   **************";
               Sleep(50);
               cout << endl;
               break;
          case (4):
               cout << "  ***           ***     **************   ***              ***              ***        ***   ***     ***     ***   **************";
               Sleep(50);
               cout << endl;
               break;
          case (5):
               cout << "  ***    ***    ***     ***              ***              ***              ***        ***   ***             ***   ***";
               Sleep(50);
               cout << endl;
               break;
          case (6):
               cout << "   ***   ***   ***      **************   **************   **************   **************   ***             ***   **************";
               Sleep(50);
               cout << endl;
               break;
          case (7):
               cout << "      ***   ***         **************   **************   **************   **************   ***             ***   **************";
               Sleep(50);
               cout << endl;
               break;
          }
     }
}

void continueScreen()
{
     Sleep(300);
     system("cls");
     introduceUs();
}

void exitScreen()
{
     Sleep(300);
     system("cls");
     gotoXY(20, 10);
     cout << "Thanks for using our system!";
     gotoXY(20, 12);
     cout << "Existing in a few seconds" << endl;
     loadingBarAnimation(12);

     exit;
}

void introScreen()
{
     gotoXY(18, 2);
     changeColor(2);
     cout << "Waiting for our program!" << endl;
     loadingBarAnimation(4);
     Sleep(900);
     system("cls");

     cout << "\n";
     changeColor(3);
     welcomeTo();
     int i = 1;
     ShowCur(0);
     while (true)
     {
          gotoXY(30, 15);
          changeColor(i);
          cout << hotel << endl;
          i = i % 7 + 1;

          if (_kbhit())
          {
               char c = _getch();
               if (c == 13)
               {
                    break; // Thoát khỏi vòng lặp nếu nhận phím Enter
               }
          }
          Sleep(100); // Thời gian nghỉ để dễ quan sát hơn
     }
     vector<string> cE = {"CONTINUE", "EXIT"};
     if (buttonList(20, 30, 15, 2, 55, cE, "row") == 1)
     {
          continueScreen();
     }
     else
     {
          exitScreen();
     }
}

void inputPassword(string &password)
{
     char ch;
     password = "";
     while (true)
     {
          ch = _getch();
          if (ch == 13)
          { // Nếu nhấn Enter (mã ASCII là 13)
               break;
          }
          else if (ch == 8)
          { // Nếu nhấn Backspace (mã ASCII là 8)
               if (!password.empty())
               {
                    password.pop_back();
                    cout << "\b \b";
               }
          }
          else
          {
               password += ch;
               cout << '*';
          }
     }
     cout << endl;
}

void logInBar(int x, int y, int textColor, int backgroundColor, string &username, string &password)
{
     gotoXY(x - 20, y + 1);
     cout << "Your username is your full name (all lowercase, without spaces or special characters.)";
     boxTwoLine(x, y + 2, 16, 2, textColor, backgroundColor, "Username");
     boxTwoLine(x + 17, y + 2, 30, 2, textColor, backgroundColor, " ");
     gotoXY(x - 5, y + 5);
     cout << "Your password is your CCCD (exactly 12 characters)";
     boxTwoLine(x, y + 6, 16, 2, textColor, backgroundColor, "Password");
     boxTwoLine(x + 17, y + 6, 30, 2, textColor, backgroundColor, " ");
     gotoXY(x + 21, y + 3);
     ShowCur(1);
     getline(cin, username);
     gotoXY(x + 21, y + 7);
     inputPassword(password);
     ShowCur(0);
}

Staff logInStaff(const string &username, const string &password)
{
     vector<Staff> staffs = Staff::readFileStaff("Staff.txt");
     for (const auto &staff : staffs)
     {
          string user = trim(createUsername(staff.getFullName()));
          string pass = trim(staff.getCCCD());
          if (username == user && password == pass)
               return staff; // Đăng nhập thành công
     }

     return Staff();
}

bool logInCus(const string &username, const string &password)
{
     vector<pair<string, string>> accounts;

     vector<Customer> customers = Customer::readFileCustomer("Customer.txt");
     for (const auto &customer : customers)
     {
          string user = createUsername(customer.getFullName());
          accounts.push_back(make_pair(trim(user), trim(customer.getCCCD())));
     }

     return login(accounts, username, password);
}

void introduceUs()
{
     cout << welcomeMessage << endl;

     string border1 = "+-----------+-------------------------------------+";
     string border2 = "+-----------+-------------------------+-----------+";
     gotoXY(34, 20);
     cout << border1;
     gotoXY(34, 21);
     cout << "| Advisor   | TS. Nguyen Van Hieu                 |";
     gotoXY(34, 22);
     cout << border1;
     gotoXY(34, 24);
     cout << border2 << endl;
     gotoXY(34, 25);
     cout << "| Student 1 | Nguyen Thi Bao Ngan     | 102230255 |";
     gotoXY(34, 26);
     cout << border2 << endl;
     gotoXY(34, 27);
     cout << "| Student 2 | Nguyen Dang Bao Nguyen  | 102230256 |";
     gotoXY(34, 28);
     cout << border2 << endl;

     gotoXY(43, 30);
     changeColor(2);
     cout << "Do you want to exit our system?";
     changeColor(7);
     vector<string> yesNo = {"Yes", "No"};
     if (buttonList(38, 32, 10, 2, 20, yesNo, "row") == 1)
     {
          exitScreen();
          return;
     }

     clearFromPosition(43, 30);
     gotoXY(43, 30);
     changeColor(2);
     cout << "Do you already have an account?";
     changeColor(7);
     int yN = buttonList(38, 32, 10, 2, 20, yesNo, "row");
     if (yN == 1)
     {
          Sleep(500);
          clearFromPosition(38, 30);
          changeColor(2);
          cout << "Log in by AMINISTRATOR or CUSTOMER account?";
          changeColor(7);
          string username, password;
          Staff staff;

          vector<string> adCus = {"Administrator", "Customer"};
          int aC = buttonList(27, 32, 20, 2, 25, adCus, "row");
          if (aC == 1)
          {
               clearFromPosition(38, 29);
               changeColor(2);
               cout << "You are logging in by ADMINISTRATOR account!";
               changeColor(7);
               int count = 1;

               do
               {
                    logInBar(34, 30, 11, 150, username, password);
                    staff = logInStaff(username, password);

                    if (count >= 3)
                    {
                         clearFromPosition(32, 30);
                         changeColor(4);
                         gotoXY(35, 31);
                         cout << "+-------------------------------------------------------+";
                         gotoXY(35, 32);
                         cout << "|         WRONG username or password OVER 3 TIME!       |";
                         gotoXY(35, 33);
                         cout << "| Our system will pause for 5 seconds before RETURNING. |";
                         gotoXY(35, 34);
                         cout << "+-------------------------------------------------------+";
                         changeColor(7);
                         Sleep(5000);

                         clearFromPosition(1, 1);
                         introScreen();
                         break;
                    }

                    if (staff.getPosition() == "Manager" || staff.getPosition() == "Receptionist")
                    {
                         gotoXY(32, 39);
                         changeColor(10);
                         cout << "Successfully logged in to the ADMINISTRATOR account!" << endl;
                         changeColor(7);
                         Sleep(500);
                         system("cls");
                         adminScreen(staff);
                         break;
                    }
                    else if (!staff.getPosition().empty())
                    {
                         gotoXY(32, 39);
                         changeColor(12);
                         cout << "Wrong username or password for ADMINISTRATOR account!" << endl;
                         changeColor(7);
                         Sleep(900);
                         clearFromPosition(34, 30);
                         ++count;
                    }
                    else
                    {
                         gotoXY(32, 39);
                         changeColor(12);
                         cout << "ADMINISTRATOR account is only for MANAGER or RECEPTIONIST!" << endl;
                         changeColor(7);
                         Sleep(900);
                         clearFromPosition(34, 30);
                         ++count;
                    }
               } while (true);
          }
          else if (aC == 2)
          {
               clearFromPosition(38, 29);
               changeColor(2);
               cout << "You are logging in by CUSTOMER account!";
               changeColor(7);
               bool check = false;

               int count = 1;
               do
               {
                    logInBar(34, 30, 11, 150, username, password);
                    check = logInCus(username, password);

                    if (count >= 3)
                    {
                         clearFromPosition(32, 30);
                         changeColor(4);
                         gotoXY(35, 31);
                         cout << "+-------------------------------------------------------+";
                         gotoXY(35, 32);
                         cout << "|         WRONG username or password OVER 3 TIME!       |";
                         gotoXY(35, 33);
                         cout << "| Our system will pause for 5 seconds before RETURNING. |";
                         gotoXY(35, 34);
                         cout << "+-------------------------------------------------------+";
                         changeColor(7);
                         Sleep(5000);

                         clearFromPosition(1, 1);
                         introScreen();
                         break;
                    }

                    if (check == false)
                    {
                         gotoXY(32, 39);
                         changeColor(12);
                         cout << "Wrong username or password for CUSTOMER account!" << endl;
                         changeColor(7);
                         Sleep(900);
                         clearFromPosition(34, 30);
                         ++count;
                    }
                    else
                    {
                         gotoXY(35, 39);
                         changeColor(10);
                         cout << "Successfully logged in to the CUSTOMER account!" << endl;
                         changeColor(7);
                         Sleep(500);
                         system("cls");
                         customerScreen(username, password);
                         break;
                    }
               } while (!check);
          }
     }
     else if (yN == 2)
     {
          Sleep(500);
          system("cls");
          noAccountScreen();
     }
}

void noAccountScreen()
{
     vector<Service> services = Service::readFileService("Service.txt");
     vector<Room> rooms = Room::readFileRoom("Room.txt");
     Customer cus;
     Room r;
     cout << delLuna << endl;
     gotoXY(29, 9);
     changeColor(2);
     cout << "------------------ NO ACCOUNT ------------------";
     changeColor(12);
     gotoXY(35, 10);
     cout << "Please choose the function you want!";
     gotoXY(28, 12);
     cout << "\"Book Rooms\" will help you create your own account!";
     changeColor(7);

     vector<string> function = {
         "1. Show Rooms",
         "2. Show Services",
         "3. Book Rooms",
         "4. Return"};

     switch (buttonList(38, 15, 31, 2, 2, function, "column"))
     {
     case 1:
          clearFromPosition(1, 1);
          cout << "\t\t\t---------- NO ACCOUNT FUNCTIONS: " << function[0] << " ----------\n";
          changeConsoleColor(3);
          cout << "\n\t\t\tHERE ARE THE ROOMS WE OFFER\n"
               << endl;
          changeConsoleColor(7);

          Customer::showAllRooms(rooms);
          break;
     case 2:
          clearFromPosition(1, 1);
          cout << "\t\t---------- NO ACCOUNT FUNCTIONS: " << function[1] << " ----------\n";
          changeConsoleColor(3);
          cout << setw(42) << "\n\t\t\t\tHERE ARE THE SERVICES WE OFFER\n"
               << endl;
          changeConsoleColor(7);
          displayService(services);
          break;
     case 3:
          clearFromPosition(1, 1);
          cout << "\t\t---------- NO ACCOUNT FUNCTIONS: " << function[2] << " ----------\n";
          cus.bookedRoom();
          break;
     case 4:
          clearFromPosition(1, 1);
          introduceUs();
          return;
     }

     cout << "Press Enter to continue..." << endl;
     cin.ignore();
     Sleep(900);
     system("cls");
     gotoXY(25, 4);
     changeColor(10);
     cout << "Do you want to continue using our system?";
     changeColor(7);
     vector<string> yesNo = {"Yes", "No"};
     if (buttonList(25, 6, 10, 2, 20, yesNo, "row") == 1)
     {
          system("cls");
          noAccountScreen();
          return;
     }
     else
     {
          system("cls");
          exitScreen();
          return;
     }
}

void customerScreen(const string &username, const string &password)
{
     vector<Customer> customers = Customer::readFileCustomer("Customer.txt");
     vector<Service> services = Service::readFileService("Service.txt");
     vector<Room> rooms = Room::readFileRoom("Room.txt");
     string fileName = "Customer.txt";
     Customer cus;
     Bill tempBill;
     Service ser;
     Room r;
     cout << delLuna << endl;
     gotoXY(30, 9);
     cout << "Your username: " << username << endl;
     gotoXY(29, 10);
     changeColor(2);
     cout << "------------------ CUSTOMER ------------------";
     changeColor(12);
     gotoXY(35, 11);
     cout << "Please choose the function you want!";
     changeColor(7);
     vector<string> function = {
         "1. Show Rooms",
         "2. Show Services",
         "3. Book Services",
         "4. Check Information",
         "5. Change Information",
         "6. Check Bill",
         "7. Log Out"};

     switch (buttonList(35, 13, 36, 2, 2, function, "column"))
     {
     case 1:
          clearFromPosition(1, 10);
          changeColor(12);
          cout << "\t\t\t---------- CUSTOMER FUNCTIONS: " << function[0] << " ----------\n";
          changeConsoleColor(3);
          cout << "\n\t\t\tHERE ARE THE ROOMS WE OFFER\n"
               << endl;
          changeConsoleColor(7);

          Customer::showAllRooms(rooms);
          break;
     case 2:
          clearFromPosition(1, 10);
          changeColor(12);
          cout << "\t\t---------- CUSTOMER FUNCTIONS: " << function[1] << " ----------\n";
          changeConsoleColor(3);
          cout << "\n\t\t\t\tHERE ARE THE SERVICES WE OFFER\n"
               << endl;
          changeConsoleColor(7);

          displayService(services);
          break;
     case 3:
          clearFromPosition(1, 10);
          changeColor(12);
          cout << "\t\t---------- CUSTOMER FUNCTIONS: " << function[2] << " ----------\n";
          changeColor(7);
          cus.bookServices(username, password, customers);
          break;
     case 4:
          clearFromPosition(1, 10);
          changeColor(12);
          cout << "\t\t---------- CUSTOMER FUNCTIONS: " << function[3] << " ----------\n";
          changeColor(7);
          cus.checkInfor(username, password, customers, services);
          Sleep(1000);
          break;
     case 5:
          clearFromPosition(1, 10);
          changeColor(12);
          cout << "\t\t---------- CUSTOMER FUNCTIONS: " << function[4] << " ----------\n";
          changeColor(7);
          cus.updateCustomerInfo(username, password, customers, fileName);
          break;
     case 6:
          clearFromPosition(1, 10);
          changeColor(12);
          cout << "\t\t---------- CUSTOMER FUNCTIONS: " << function[5] << " ----------\n";
          changeColor(7);
          tempBill.checkBillInfo(username, password, customers, rooms, services);
          Sleep(1000);
          break;
     case 7:
          system("cls");
          introduceUs();
          return;
     }

     cout << "\nPress Enter to continue..." << endl;
     cin.ignore();
     Sleep(900);
     system("cls");
     gotoXY(25, 4);
     changeColor(10);
     cout << "Do you want to continue using our system?";
     changeColor(7);
     vector<string> yesNo = {"Yes", "No"};
     if (buttonList(25, 6, 10, 2, 20, yesNo, "row") == 1)
     {
          system("cls");
          customerScreen(username, password);
          return;
     }
     else
     {
          system("cls");
          exitScreen();
          return;
     }
}
//---ADMINISTRATOR SCREEN---
void adminScreen(Staff &staff)
{
     cout << delLuna << endl;
     gotoXY(30, 9);
     changeColor(12);
     string username = trim(createUsername(staff.getFullName()));
     cout << "Your username: " << username;
     gotoXY(29, 10);
     changeColor(2);
     cout << "------------------ ADMINISTRATOR ------------------";
     changeColor(12);
     gotoXY(20, 11);
     cout << "Please choose a function group first! STAFF FUNCTION is only for MANAGER!";
     changeColor(7);

     vector<string> staffFunc = {
         "1. Add New",
         "2. Update Information",
         "3. Remove",
         "4. Show All"};
     for (int i = 0; i < staffFunc.size(); i++)
     {
          gotoXY(3, 17 + i);
          cout << staffFunc[i];
     }
     vector<string> customerFunc = {
         "1. Add New",
         "2. Update Information",
         "3. Find",
         "4. Book Services",
         "5. Remove",
         "6. Show All"};
     for (int i = 0; i < customerFunc.size(); i++)
     {
          gotoXY(36, 17 + i);
          cout << customerFunc[i];
     }
     vector<string> roomFunc = {
         "1. Change Status",
         "2. Show All",
     };
     for (int i = 0; i < roomFunc.size(); i++)
     {
          gotoXY(69, 17 + i);
          cout << roomFunc[i];
     }

     vector<string> serBillFunc = {
         "1. Change Service Price",
         "2. Show All Services",
         "3. Check Bill",
     };
     for (int i = 0; i < serBillFunc.size(); i++)
     {
          gotoXY(102, 17 + i);
          cout << serBillFunc[i];
     }
     vector<string> groupFunc = {"Staff", "Customer", "Room", "Ser&Bill", "Log Out"};
     string account = "Administrator";

     switch (buttonList(6, 13, 15, 2, 18, groupFunc, "row"))
     {
     case 1:
          if (staff.getPosition() == "Manager")
          {
               staffFunction(staff, staffFunc);
          }
          else
          {
               clearFromPosition(1, 11);
               changeColor(15);
               gotoXY(40, 13);
               cout << "+--------------------------------------------------------+";
               gotoXY(40, 14);
               cout << "|                                                        |";
               gotoXY(40, 15);
               cout << "|                         ERROR!                         |";
               gotoXY(40, 16);
               cout << "|                                                        |";
               gotoXY(40, 17);
               cout << "|      STAFF FUNCTION is only for MANAGER's account      |";
               gotoXY(40, 18);
               cout << "|                                                        |";
               gotoXY(40, 19);
               cout << "+--------------------------------------------------------+";
               changeColor(7);
               gotoXY(40, 21);
               cout << "Wait for 3 seconds ...!";
               Sleep(3000);

               system("cls");
               adminScreen(staff);
          }
          break;
     case 2:
          customerFunction(staff, customerFunc);
          break;
     case 3:
          roomFunction(staff, roomFunc);
          break;
     case 4:
          serBillFunction(staff, serBillFunc);
          break;
     case 5:
          clearFromPosition(1, 1);
          introduceUs();
          break;
     }
}
//---FUNCTION OF ADMINISTRATOR---
void staffFunction(Staff &staff, vector<string> &function)
{
     clearFromPosition(20, 11);
     gotoXY(30, 11);
     changeColor(12);
     cout << "STAFF FUNCTIONS: Choose the function you want!";
     changeColor(7);

     vector<Staff> staffs = Staff::readFileStaff("Staff.txt");

     function.push_back("RETURN");
     int choice = buttonList(40, 13, 28, 2, 2, function, "column");
     switch (choice)
     {
     case 1: // Add new staff
     {
          clearFromPosition(1, 10);
          changeColor(11);

          cout << "\t\t\t---------- STAFF FUNCTIONS: " << function[choice - 1] << " ----------\n\n";
          changeColor(7);

          do
          {
               string fullName, CCCD, phone, add, gender, dob, ID, position, salary;
               Date DOB;

               changeColor(2);
               gotoXY(38, 12);
               cout << "Please enter new staff's information!";
               changeColor(14);

               gotoXY(25, 14);
               cout << "+---------------------------------------------------------------------+";
               gotoXY(25, 15);
               cout << "|                         STAFF's INFORMATION                         |";
               gotoXY(25, 16);
               cout << "+---------------------------------------------------------------------+";
               gotoXY(25, 17);
               cout << "| Full Name                  |                                        |";
               gotoXY(25, 18);
               cout << "+---------------------------------------------------------------------+";
               gotoXY(25, 19);
               cout << "| CCCD                       |                                        |";
               gotoXY(25, 20);
               cout << "+---------------------------------------------------------------------+";
               gotoXY(25, 21);
               cout << "| Phone                      |                                        |";
               gotoXY(25, 22);
               cout << "+---------------------------------------------------------------------+";
               gotoXY(25, 23);
               cout << "| Address                    |                                        |";
               gotoXY(25, 24);
               cout << "+---------------------------------------------------------------------+";
               gotoXY(25, 25);
               cout << "| Gender (Male/ Female)      |                                        |";
               gotoXY(25, 26);
               cout << "+---------------------------------------------------------------------+";
               gotoXY(25, 27);
               cout << "| Date of birth (dd/mm/yyyy) |                                        |";
               gotoXY(25, 28);
               cout << "+---------------------------------------------------------------------+";
               gotoXY(25, 29);
               cout << "| Position                   |                                        |";
               gotoXY(25, 30);
               cout << "+---------------------------------------------------------------------+";
               gotoXY(25, 31);
               cout << "| Salary (only digits)       |                                        |";
               gotoXY(25, 32);
               cout << "+---------------------------------------------------------------------+";
               gotoXY(25, 33);
               cout << "| Staff ID (automatically)   |                                        |";
               gotoXY(25, 34);
               cout << "+---------------------------------------------------------------------+";

               changeColor(7);
               do
               {
                    ShowCur(1);
                    gotoXY(56, 17);
                    getline(cin, fullName);
               } while (fullName.empty());
               fullName = Person::standardizeString(fullName);
               gotoXY(56, 17);
               cout << fullName;

               do
               {
                    ShowCur(1);
                    gotoXY(56, 19);
                    cout << string(CCCD.length(), ' ');
                    gotoXY(56, 19);
                    getline(cin, CCCD);

                    if (CCCD.length() != 12)
                    {
                         gotoXY(97, 19);
                         ShowCur(0);
                         changeConsoleColor(4);
                         cout << "Exactly 12 digits! Try again!";
                         changeConsoleColor(7);
                         _getch();
                         gotoXY(97, 19);
                         cout << string(50, ' ');
                         continue;
                    }

                    if (!std::all_of(CCCD.begin(), CCCD.end(), ::isdigit))
                    {
                         gotoXY(97, 19);
                         ShowCur(0);
                         changeConsoleColor(4);
                         cout << "Only DIGITS! Try again!";
                         changeConsoleColor(7);
                         _getch();
                         gotoXY(97, 19);
                         cout << string(50, ' ');
                         continue;
                    }

                    break;
               } while (true);

               do
               {
                    ShowCur(1);
                    gotoXY(56, 21);
                    cout << string(phone.length(), ' ');
                    gotoXY(56, 21);
                    getline(cin, phone);

                    if (phone.length() != 10)
                    {
                         gotoXY(97, 21);
                         ShowCur(0);
                         changeConsoleColor(4);
                         cout << "Exactly 10 digits! Try again!";
                         changeConsoleColor(7);
                         _getch();
                         gotoXY(97, 21);
                         cout << string(50, ' ');
                         continue;
                    }

                    if (!std::all_of(phone.begin(), phone.end(), ::isdigit))
                    {
                         gotoXY(97, 21);
                         ShowCur(0);
                         changeConsoleColor(4);
                         cout << "Only DIGITS! Try again!";
                         changeConsoleColor(7);
                         _getch();
                         gotoXY(97, 21);
                         cout << string(50, ' ');
                         continue;
                    }

                    if (phone[0] != '0')
                    {
                         gotoXY(97, 21);
                         ShowCur(0);
                         changeConsoleColor(4);
                         cout << "Phone must start with 0! Try again!";
                         changeConsoleColor(7);
                         _getch();
                         gotoXY(97, 21);
                         cout << string(50, ' ');
                         continue;
                    }

                    break;
               } while (true);

               do
               {
                    ShowCur(1);
                    gotoXY(56, 23);
                    getline(cin, add);
               } while (add.empty());

               do
               {
                    ShowCur(1);
                    gotoXY(56, 25);
                    cout << string(gender.length(), ' ');
                    gotoXY(56, 25);
                    getline(cin, gender);
                    gender = toLower(gender);
                    gender[0] = toupper(gender[0]);
                    gotoXY(56, 25);
                    cout << gender;

                    if (!(gender == "Male" || gender == "Female"))
                    {
                         gotoXY(97, 25);
                         ShowCur(0);
                         changeConsoleColor(4);
                         cout << "Gender must be \'Male\' or \'Female\'! Try again!";
                         changeConsoleColor(7);
                         _getch();
                         gotoXY(97, 25);
                         cout << string(50, ' ');
                         continue;
                    }

                    break;
               } while (true);

               do
               {
                    ShowCur(1);
                    gotoXY(56, 27);
                    cout << string(dob.length(), ' ');
                    gotoXY(56, 27);
                    getline(cin, dob);

                    if (!Date::isValidDateFormat(dob))
                    {
                         gotoXY(97, 27);
                         ShowCur(0);
                         changeConsoleColor(4);
                         cout << "Invalid format! Please enter dd/mm/yyyy!";
                         changeConsoleColor(7);
                         _getch();
                         gotoXY(97, 27);
                         cout << string(50, ' ');
                         continue;
                    }

                    DOB = Date(dob);

                    if (Date::getCurrentDate().getYear() - DOB.getYear() < 18)
                    {
                         gotoXY(97, 27);
                         ShowCur(0);
                         changeConsoleColor(4);
                         cout << "The staff must be at least 18 years old!";
                         changeConsoleColor(7);
                         _getch();
                         gotoXY(97, 27);
                         cout << string(50, ' ');
                         continue;
                    }

                    break;
               } while (true);

               do
               {
                    ShowCur(1);
                    gotoXY(56, 29);
                    cout << string(position.length(), ' ');
                    gotoXY(56, 29);
                    getline(cin, position);
                    position = toLower(position);
                    position[0] = toupper(position[0]);
                    gotoXY(56, 29);
                    cout << position;

                    if (!(position == "Manager" || position == "Receptionist" || position == "Housekeeping" || position == "Laundry" || position == "Server"))
                    {
                         gotoXY(97, 29);
                         ShowCur(0);
                         changeConsoleColor(4);
                         cout << "Manager, Receptionist, Housekeeping, Laundry, Server!";
                         changeConsoleColor(7);
                         _getch();
                         gotoXY(97, 29);
                         cout << string(80, ' ');
                         continue;
                    }

                    break;
               } while (true);

               do
               {
                    ShowCur(1);
                    gotoXY(56, 31);
                    cout << string(salary.length(), ' ');
                    gotoXY(56, 31);
                    getline(cin, salary);

                    if (!std::all_of(salary.begin(), salary.end(), ::isdigit))
                    {
                         gotoXY(97, 31);
                         ShowCur(0);
                         changeConsoleColor(4);
                         cout << "Only DIGITS! Try again!";
                         changeConsoleColor(7);
                         _getch();
                         gotoXY(97, 31);
                         cout << string(50, ' ');
                         continue;
                    }

                    salary = Staff::formatSalary(salary);
                    Sleep(500);
                    gotoXY(56, 31);
                    cout << string(salary.length(), ' ');
                    gotoXY(56, 31);
                    cout << salary;
                    break;
               } while (true);

               gotoXY(56, 33);
               ID = Staff::generateStaffID(staffs, position);
               cout << ID;

               ShowCur(0);
               Staff newStaff(fullName, CCCD, phone, add, gender, DOB, ID, position, salary);
               vector<string> confirmation = {"Confirm", "Cancel"};
               int confirm = buttonList(30, 35, 14, 2, 28, confirmation, "row");

               clearFromPosition(30, 35);

               if (confirm == 1)
               {
                    if (!staff.addNewStaff(newStaff))
                    {
                         gotoXY(40, 36);
                         changeConsoleColor(4);
                         cout << "Do you want to try again?";
                         changeConsoleColor(7);
                         vector<string> yN = {"Try again", "Cancel"};
                         int ch = buttonList(32, 37, 16, 2, 10, yN, "row");

                         if (ch == 1)
                         {
                              clearFromPosition(38, 12);
                              continue;
                         }
                         else
                              break;
                    }
                    else
                    {
                         _getch();
                         break;
                    }
               }
               else
                    break;

          } while (true);

          break;
     }

     case 2: // Update Information
     {
          clearFromPosition(1, 10);
          changeColor(11);

          cout << "\t\t\t---------- STAFF FUNCTIONS: " << function[choice - 1] << " ----------\n\n";
          changeColor(7);

          boxTwoLine(10, 13, 17, 2, 11, 75, "Staff's ID");
          boxTwoLine(28, 13, 17, 2, 11, 150, " ");

          string id;
          int index;
          do //Staff's ID
          {
               gotoXY(32, 14);
               cout << string(id.length(), ' ');
               gotoXY(32, 14);
               ShowCur(1);
               changeConsoleColor(7);
               cin >> id;

               changeConsoleColor(3);
               gotoXY(48, 14);
               ShowCur(0);
               if (id.length() != 4)
               {
                    cout << "ID has exactly 4 characters! Press Enter ...";
                    _getch();
                    gotoXY(48, 14);
                    cout << string(60, ' ');
               }
               else if (!(isalpha(id[0]) && isdigit(id[1]) && isdigit(id[2]) && isdigit(id[3])))
               {
                    cout << "Invalid ID format! Valid format ex.: M001.  Press Enter ...";
                    _getch();
                    gotoXY(48, 14);
                    cout << string(60, ' ');
               }
               else
               {
                    changeConsoleColor(7);
                    id[0] = toupper(id[0]);
                    gotoXY(32, 14);
                    cout << id;
                    vector<Staff> staffs = Staff::readFileStaff("Staff.txt");
                    bool found = false;
                    for (int i = 0; i < staffs.size(); i++)
                    {
                         if (staffs[i].getID() == id)
                         {
                              found = true;
                              index = i;
                              break;
                         }
                    }

                    if (found == false)
                    {
                         gotoXY(20, 17);
                         changeConsoleColor(4);
                         cout << "Cannot found staff's ID: " << id << ". Press Y to continue/ N to return!";
                         changeConsoleColor(2);
                         char c;
                         int x = whereX() + 1, y = whereY() + 1;
                         do
                         {
                              gotoXY(x, y);
                              cout << string(1, ' ');
                              gotoXY(x, y);
                              ShowCur(1);
                              cin >> c;
                              ShowCur(0);
                              c = toupper(c);
                              if (c == 'Y')
                              {
                                   gotoXY(20, 17);
                                   cout << string(72, ' ');
                                   break;
                              }
                              else if (c == 'N')
                              {
                                   clearFromPosition(1,11);
                                   staffFunction(staff, function);
                                   break;
                              }
                              else continue;
                         } while(true);
                    } 
                    else
                         break;
               }
          } while (true);

          gotoXY(20, 17);
          changeConsoleColor(2);
          cout << "The staff's ID was successfully found.! Press Enter to continue...";
          changeConsoleColor(7);
          _getch();

          if (!staff.updateStaff(staffs, index))
          {
               changeConsoleColor(4);
               gotoXY(65, 30);
               cout << "+-----------------------------------+";
               gotoXY(65, 31);
               cout << "|                                   |";
               gotoXY(65, 32);
               cout << "|               ERROR               |";
               gotoXY(65, 33);
               cout << "|   Failed to update information!   |";
               gotoXY(65, 34);
               cout << "|                                   |";
               gotoXY(65, 35);
               cout << "+-----------------------------------+";
          }

          gotoXY(1, 35);
          break;
     }

     case 3: // Remove staff
     {
          clearFromPosition(1, 10);
          changeColor(11);

          cout << "\t\t\t---------- STAFF FUNCTIONS: " << function[choice - 1] << " ----------\n";
          changeColor(7);

          vector<Staff> staffs = Staff::readFileStaff("Staff.txt");
          if (!staff.removeStaffByCCCD(staffs))
          {
               clearFromPosition(1, 11);
               changeConsoleColor(4);
               gotoXY(40, 13);
               cout << "+--------------------------------+";
               gotoXY(40, 14);
               cout << "|     Failed to remove staff     |";
               gotoXY(40, 15);
               cout << "|   Press Enter to continue...   |";
               gotoXY(40, 16);
               cout << "+--------------------------------+";

               changeConsoleColor(7);
               _getch();
               clearFromPosition(1, 10);
               staffFunction(staff, function);
          }
          else
          {
               clearFromPosition(1, 12);
               Staff::showList(staffs);

               cout << "\n\tSuccessfully remove staff!" << endl;
               _getch();
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
          }
          break;
     }

     case 4: // Show All
     {
          clearFromPosition(1, 10);
          changeColor(11);

          cout << "\t\t\t---------- STAFF FUNCTIONS: " << function[choice - 1] << " ----------\n\n";
          changeColor(7);

          vector<Staff> staffs = Staff::readFileStaff("Staff.txt");
          Staff::showList(staffs);

          break;
     }

     case 5:
     {
          clearFromPosition(1, 1);
          adminScreen(staff);
          break;
     }
     }

     cout << "\nPress Enter to continue..." << endl;
     _getch();
     Sleep(900);
     system("cls");
     gotoXY(25, 4);
     changeColor(10);
     cout << "Do you want to continue using our system?";
     changeColor(7);
     vector<string> yesNo = {"Yes", "No"};
     if (buttonList(25, 6, 10, 2, 20, yesNo, "row") == 1)
     {
          system("cls");
          adminScreen(staff);
          return;
     }
     else
     {
          system("cls");
          exitScreen();
          return;
     }
}

void customerFunction(Staff &staff, vector<string> &function)
{
     clearFromPosition(20, 11);
     gotoXY(30, 11);
     changeColor(12);
     cout << "CUSTOMER FUNCTIONS: Choose the function you want!";
     changeColor(7);

     string username = createUsername(trim(staff.getFullName()));
     string password = staff.getCCCD();
     string fileName = "Customer.txt";
     Customer cus;
     vector<Customer> customers = Customer::readFileCustomer("Customer.txt");
     vector<Service> services = Service::readFileService("Service.txt");
     vector<Room> rooms = Room::readFileRoom("Room.txt");
     function.push_back("RETURN");
     int choice = buttonList(40, 13, 28, 2, 2, function, "column");

     switch (choice)
     {
     case 1:
     {
          clearFromPosition(1, 10);
          changeColor(11);
          // Add New
          cout << "\t\t\t---------- CUSTOMER FUNCTIONS: " << function[choice - 1] << " ----------\n";
          changeColor(2);
          do
          {
               if (!staff.addNewCustomer(staff))
               {
                    cout << "\nDo you want to try again? (y/n)";
                    string ch;
                    cin >> ch;
                    ch = toLower(ch);
                    if (ch == "n")
                         break;
               }
               else
                    break;

          } while (true);
          changeColor(7);
          break;
     }
     case 2:
     {
          clearFromPosition(1, 10);
          changeColor(11);
          // Update information
          cout << "\t\t\t---------- CUSTOMER FUNCTIONS: " << function[choice - 1] << " ----------\n";
          staff.updateCustomer(staff, fileName, customers);
          changeColor(7);

          break;
     }
     case 3: // Find
     {
          clearFromPosition(1, 10);
          changeColor(11);

          cout << "\t\t\t---------- CUSTOMER FUNCTIONS: " << function[choice - 1] << " ----------\n";

          vector<Customer> findCus;
          if (staff.findCustomer(findCus))
          {
               gotoXY(1, 21);
               staff.displayCustomer(findCus);
               _getch();
          }
          else
          {
               changeColor(4);
               gotoXY(40, 21);
               cout << "+-------------------------------------+";
               gotoXY(40, 22);
               cout << "|                                     |";
               gotoXY(40, 23);
               cout << "|      Failed to find Customers!      |";
               gotoXY(40, 24);
               cout << "|                                     |";
               gotoXY(40, 25);
               cout << "+-------------------------------------+";
               changeColor(7);
               _getch();
          }
          break;
     }
     case 4: //Book services
     { 
          clearFromPosition(1, 10);
          changeColor(11);
          
          cout << "\t\t\t---------- CUSTOMER FUNCTIONS: " << function[choice - 1] << " ----------\n\n";
          changeColor(7);

          gotoXY(35, 12);
          changeColor(15);
          cout << "Please enter the details of the customer who wants to book the service! <(*.*)>";

          gotoXY(40, 14);
          cout << "+----------------------------------------------------------------------+";
          gotoXY(40, 15);
          cout << "|                        CUSTOMER'S INFORMATION                        |";
          gotoXY(40, 16);
          cout << "+----------------------------------------------------------------------+";
          gotoXY(40, 17);
          cout << "| Customer's Full Name    |                                            |";
          gotoXY(40, 18);
          cout << "+----------------------------------------------------------------------+";
          gotoXY(40, 19);
          cout << "| Customer's CCCD         |                                            |";
          gotoXY(40, 20);
          cout << "+----------------------------------------------------------------------+";

          ShowCur(1);
          string FullName, CCCD;
          do
          {
               do
               {
                    gotoXY(68, 17);
                    cout << string(FullName.length(), ' ');
                    gotoXY(68, 19);
                    cout << string(CCCD.length(), ' ');
                    gotoXY(68, 17);
                    std::getline(std::cin, FullName);
                    if (FullName.empty())
                    {
                         changeConsoleColor(4);
                         gotoXY(113, 17);
                         std::cout << "Customer's name cannot be empty";
                         changeConsoleColor(7);
                         _getch();
                         gotoXY(113, 17);
                         std::cout << string(75, ' ');
                    }
               } while (FullName.empty());

               do
               {
                    gotoXY(68, 19);
                    cout << string(CCCD.length(), ' ');
                    gotoXY(68, 19);
                    getline(cin, CCCD);

                    if (CCCD.length() != 12)
                    {
                         changeConsoleColor(4);
                         gotoXY(113, 19);
                         cout << "Exactly 12 digits! Try again!";
                         _getch();
                         gotoXY(113, 19);
                         cout << string(30, ' ');
                         changeConsoleColor(7);
                         continue;
                    }
                    else
                    {
                         for (size_t i = 0; i < CCCD.length(); i++)
                         {
                              if (!isdigit(CCCD[i]))
                              {
                                   changeConsoleColor(4);
                                   gotoXY(113, 19);
                                   cout << "Only DIGITS! Try again!";
                                   _getch();
                                   gotoXY(113, 19);
                                   cout << string(30, ' ');
                                   changeConsoleColor(7);
                                   continue;
                              }
                         }
                         break;
                    }
               } while (true);

               bool foundCustomer = false;
               for (const auto &customer : customers)
               {
                    if (customer.getFullName() == FullName && customer.getCCCD() == CCCD)
                    {
                         foundCustomer = true;
                         break;
                    }
               }

               if (!foundCustomer)
               {
                    changeConsoleColor(4);
                    gotoXY(40, 22);
                    cout << "Error: Customer not found. Please check customer's information again!!";
                    changeConsoleColor(7);
                    _getch();
                    gotoXY(40, 22);
                    cout << string(75, ' ');
                    gotoXY(68, 17);
                    continue;
               }
               else
               {
                    foundCustomer = true;
                    break;
               }
          } while (true);

          changeColor(14);
          system("cls");
          string filename = "title.txt";
          read_lines(filename, 43, 52);
          changeColor(7);
          string username1 = createUsername(trim(FullName));
          string password1 = trim(CCCD);
          cus.bookServices(username1, password1, customers);
          ShowCur(0);
          break;
     }
     case 5:
     {
          clearFromPosition(1, 10);
          changeColor(11);
          // Remove
          cout << "\t\t\t---------- CUSTOMER FUNCTIONS: " << function[choice - 1] << " ----------\n\n";
          changeColor(7);

          changeColor(14);
          gotoXY(30, 12);
          cout << "+--------------------------------------------+";
          gotoXY(30, 13);
          cout << "|      CUSTOMER'S INFORMATION TO REMOVE      |";
          gotoXY(30, 14);
          cout << "+-----------+--------------------------------+";
          gotoXY(30, 15);
          cout << "| CCCD      |                                |";
          gotoXY(30, 16);
          cout << "+-----------+--------------------------------+";
          gotoXY(30, 17);
          cout << "| Full Name |                                |";
          gotoXY(30, 18);
          cout << "+-----------+--------------------------------+";
          gotoXY(30, 19);
          cout << "| Phone     |                                |";
          gotoXY(30, 20);
          cout << "+-----------+--------------------------------+";
          gotoXY(30, 21);
          cout << "| Address   |                                |";
          gotoXY(30, 22);
          cout << "+-----------+--------------------------------+";

          changeColor(7);
          string cccd;
          do
          {
               gotoXY(44, 15);
               cout << string(cccd.length(), ' ');
               gotoXY(44, 15);
               ShowCur(1);
               cin >> cccd;

               if (cccd.length() != 12 || cccd[0] != '0' || !(std::all_of(cccd.begin(), cccd.end(), ::isdigit)))
               {
                    ShowCur(0);
                    gotoXY(77, 15);
                    changeColor(4);
                    cout << "Invalid CCCD format! Press Enter ...";
                    _getch();
                    gotoXY(77, 15);
                    cout << string(40, ' ');
                    changeColor(7);
               }
               else
               {
                    ShowCur(0);
                    break;
               }
          } while (true);

          vector<Customer> customers = Customer::readFileCustomer("Customer.txt");
          for (const auto &cus : customers)
          {
               if (cus.getCCCD() == cccd)
               {
                    gotoXY(44, 17);
                    cout << cus.getFullName();
                    gotoXY(44, 19);
                    cout << cus.getPhone();
                    gotoXY(44, 21);
                    cout << cus.getAdd();
               }
          }
          vector<string> content = {"Confirm", "Cancel"};
          if (buttonList(30, 24, 14, 2, 18, content, "row") == 1)
          {
               gotoXY(1, 28);
               staff.removeCustomerByCCCD(staff, cccd);
          }

          break;
     }
     case 6:
     {
          clearFromPosition(1, 10);
          changeColor(11);
          // Show All
          cout << "\t\t\t---------- CUSTOMER FUNCTIONS: " << function[choice - 1] << " ----------\n";
          changeColor(7);

          vector<Customer> customers = Customer::readFileCustomer("Customer.txt");
          vector<Service> services = Service::readFileService("Service.txt");
          if (customers.empty())
          {
               changeConsoleColor(4);
               cout << "No customers found. Please add customer information.\n";
               changeConsoleColor(7);
          }
          else
               Staff::displayCustomer(customers);
          break;
     }
     case 7:
     {
          clearFromPosition(1, 1);
          adminScreen(staff);
          break;
     }
     }

     cout << "\nPress Enter to continue..." << endl;
     _getch();
     Sleep(900);
     system("cls");
     gotoXY(25, 4);
     changeColor(10);
     cout << "Do you want to continue using our system?";
     changeColor(7);
     vector<string> yesNo = {"Yes", "No"};
     if (buttonList(25, 6, 10, 2, 20, yesNo, "row") == 1)
     {
          system("cls");
          adminScreen(staff);
          return;
     }
     else
     {
          system("cls");
          exitScreen();
          return;
     }
}

void roomFunction(Staff &staff, vector<string> &function)
{
     clearFromPosition(20, 11);
     gotoXY(30, 11);
     changeColor(12);
     cout << "ROOM FUNCTIONS: Choose the function you want!";
     changeColor(7);

     function.push_back("RETURN");
     int choice = buttonList(40, 13, 28, 2, 2, function, "column");
     switch (choice)
     {
     case 1: // Change Status
     {
          clearFromPosition(1, 10);
          changeColor(11);

          cout << "\t\t\t---------- ROOM FUNCTIONS: " << function[choice - 1] << " ----------\n";
          changeColor(7);

          vector<Room> rooms = Room::readFileRoom("Room.txt");
          vector<Service> services = Service::readFileService("Service.txt");

          if (staff.changeRoomStatus(rooms))
          {
               system("cls");
               changeConsoleColor(2);
               gotoXY(30, 10);
               cout << "+-------------------------------------+";
               gotoXY(30, 11);
               cout << "|                                     |";
               gotoXY(30, 12);
               cout << "|   Successfully change Room status   |";
               gotoXY(30, 13);
               cout << "|                                     |";
               gotoXY(30, 14);
               cout << "+-------------------------------------+";

               gotoXY(30, 16);
               cout << "Do you want to check ROOM INFORMATION?";
               vector<string> content = {"Yes", "No"};
               if (buttonList(35, 17, 10, 2, 8, content, "row") == 1)
               {
                    gotoXY(1, 21);
                    Room::printRoom(rooms, services);
               }
          }
          else
          {
               system("cls");
               changeConsoleColor(2);
               gotoXY(30, 10);
               cout << "+-------------------------------------+";
               gotoXY(30, 11);
               cout << "|                                     |";
               gotoXY(30, 12);
               cout << "|    Failed to change Room status!    |";
               gotoXY(30, 13);
               cout << "|                                     |";
               gotoXY(30, 14);
               cout << "+-------------------------------------+";
          }
          changeColor(7);
          break;
     }

     case 2:
     {
          clearFromPosition(1, 10);
          changeColor(11);
          // Show All
          cout << "\t\t\t---------- ROOM FUNCTIONS: " << function[choice - 1] << " ----------\n\n";
          changeColor(7);
          vector<Room> rooms = Room::readFileRoom("Room.txt");
          vector<Service> services = Service::readFileService("Service.txt");

          if (rooms.empty())
          {
               changeConsoleColor(4);
               cout << "No rooms available.\n";
               changeConsoleColor(7);
          }
          else if (services.empty())
          {
               changeConsoleColor(4);
               cout << "No services available.\n";
               changeConsoleColor(7);
          }
          else
          {
               Room::printRoom(rooms, services);
          }

          break;
     }

     case 3:
     {
          clearFromPosition(1, 1);
          adminScreen(staff);
          break;
     }
     }

     cout << "\nPress Enter to continue..." << endl;
     _getch();
     Sleep(900);
     system("cls");
     gotoXY(25, 4);
     changeColor(10);
     cout << "Do you want to continue using our system?";
     changeColor(7);
     vector<string> yesNo = {"Yes", "No"};
     if (buttonList(25, 6, 10, 2, 20, yesNo, "row") == 1)
     {
          system("cls");
          adminScreen(staff);
          return;
     }
     else
     {
          system("cls");
          exitScreen();
          return;
     }
}

void serBillFunction(Staff &staff, vector<string> &function)
{
     clearFromPosition(20, 11);
     gotoXY(30, 11);
     changeColor(12);
     cout << "SERVICE & BILL FUNCTIONS: Choose the function you want!";
     changeColor(7);
     vector<Customer> customers = Customer::readFileCustomer("Customer.txt");
     vector<Service> services = Service::readFileService("Service.txt");
     vector<Room> rooms = Room::readFileRoom("Room.txt");
     BillStaff Bill;
     function.push_back("RETURN");
     int choice = buttonList(40, 13, 30, 2, 2, function, "column");
     switch (choice)
     {
     case 1: // Change Service Price
     {
          clearFromPosition(1, 10);
          changeColor(11);
          cout << "\t\t\t---------- SERVICE FUNCTIONS: " << function[choice - 1] << " ----------\n";
          changeColor(7);

          vector<Service> services = Service::readFileService("Service.txt");
          gotoXY(1, 12);
          displayService(services);

          staff.changeServicePrice(services);

          break;
     }

     case 2:
     {
          clearFromPosition(1, 10);
          changeColor(11);
          // Show All Services
          cout << "\t\t\t---------- SERVICE FUNCTIONS: " << function[choice - 1] << " ----------\n";
          changeColor(7);

          vector<Service> services = Service::readFileService("Service.txt");

          if (services.empty())
          {
               changeConsoleColor(4);
               cout << "No services available. Please add services to the system.\n";
               changeConsoleColor(7);
          }
          else
          {
               displayService(services);
          }

          break;
     }

     case 3:
     {
          clearFromPosition(1, 10);
          changeColor(11);
          cout << "\t\t\t---------- BILL FUNCTIONS: " << function[choice - 1] << " ----------\n";
          Bill.checkBillByNameAndCCCD(staff, customers, rooms, services);
          changeColor(7);
          break;
     }
     case 4:
     {
          clearFromPosition(1, 1);
          adminScreen(staff);
          break;
     }
     }

     cout << "\nPress Enter to continue..." << endl;
     _getch();
     Sleep(900);
     system("cls");
     gotoXY(25, 4);
     changeColor(10);
     cout << "Do you want to continue using our system?";
     changeColor(7);
     vector<string> yesNo = {"Yes", "No"};
     if (buttonList(25, 6, 10, 2, 20, yesNo, "row") == 1)
     {
          system("cls");
          adminScreen(staff);
          return;
     }
     else
     {
          system("cls");
          exitScreen();
          return;
     }
}
