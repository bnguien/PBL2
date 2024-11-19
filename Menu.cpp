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

bool logInCheck(string username, string password, string text)
{
     vector<pair<string, string>> accounts;

     if (text == "ADMINISTRATOR")
     {
          vector<Staff> staffs = Staff::readFileStaff("Staff.txt");
          for (const auto &staff : staffs)
          {
               string user = createUsername(staff.getFullName());
               accounts.push_back(make_pair(trim(user), trim(staff.getCCCD())));
          }
     }
     else if (text == "CUSTOMER")
     {
          vector<Customer> customers = Customer::readFileCustomer("Customer.txt");
          for (const auto &customer : customers)
          {
               string user = createUsername(customer.getFullName());
               accounts.push_back(make_pair(trim(user), trim(customer.getCCCD())));
          }
     }
     else
     {
          cout << "Invalid user type specified: " << text << endl;
          return false;
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

          vector<string> adCus = {"Administrator", "Customer"};
          int aC = buttonList(27, 32, 20, 2, 25, adCus, "row");
          if (aC == 1)
          {
               clearFromPosition(38, 29);
               changeColor(2);
               cout << "You are logging in by ADMINISTRATOR account!";
               changeColor(7);
               bool check = false;
               do
               {
                    logInBar(34, 30, 11, 150, username, password);
                    check = logInCheck(username, password, "ADMINISTRATOR");
                    if (check == false)
                    {
                         gotoXY(32, 39);
                         changeColor(12);
                         cout << "Wrong username or password for ADMINISTRATOR account!" << endl;
                         changeColor(7);
                         Sleep(900);
                         clearFromPosition(34, 30);
                    }
                    else
                    {
                         gotoXY(32, 39);
                         changeColor(10);
                         cout << "Successfully logged in to the ADMINISTRATOR account!" << endl;
                         changeColor(7);
                    }
               } while (!check);

               Sleep(500);
               system("cls");
               adminScreen(username, password);
          }
          else if (aC == 2)
          {
               clearFromPosition(38, 29);
               changeColor(2);
               cout << "You are logging in by CUSTOMER account!";
               changeColor(7);
               bool check = false;
               do
               {
                    logInBar(34, 30, 11, 150, username, password);
                    check = logInCheck(username, password, "CUSTOMER");
                    if (check == false)
                    {
                         gotoXY(32, 39);
                         changeColor(12);
                         cout << "Wrong username or password for CUSTOMER account!" << endl;
                         changeColor(7);
                         Sleep(900);
                         clearFromPosition(34, 30);
                    }
                    else
                    {
                         gotoXY(35, 39);
                         changeColor(10);
                         cout << "Successfully logged in to the CUSTOMER account!" << endl;
                         changeColor(7);
                    }
               } while (!check);

               Sleep(500);
               system("cls");
               customerScreen(username, password);
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
          cout << "\t\t---------- NO ACCOUNT FUNCTIONS: " << function[0] << " ----------\n";
          changeConsoleColor(3);
          cout << setw(42) << "HERE ARE THE ROOMS WE OFFER" << endl;
          changeConsoleColor(7);
          cout << setw(37) << "--------------------" << endl;
          r.printRoom(rooms, services);
          break;
     case 2:
          clearFromPosition(1, 1);
          cout << "\t\t---------- NO ACCOUNT FUNCTIONS: " << function[1] << " ----------\n";
          changeConsoleColor(3);
          cout << setw(42) << "HERE ARE THE ROOMS WE OFFER" << endl;
          changeConsoleColor(7);
          cout << setw(37) << "--------------------" << endl;
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
          cout << "\t\t---------- CUSTOMER FUNCTIONS: " << function[0] << " ----------\n";
          changeConsoleColor(3);
          cout << setw(42) << "HERE ARE THE ROOMS WE OFFER" << endl;
          changeConsoleColor(7);
          cout << setw(37) << "--------------------" << endl;
          r.printRoom(rooms, services);
          break;
     case 2:
          clearFromPosition(1, 10);
          changeColor(12);
          cout << "\t\t---------- CUSTOMER FUNCTIONS: " << function[1] << " ----------\n";
          changeConsoleColor(3);
          cout << setw(42) << "HERE ARE THE SERVICES WE OFFER" << endl;
          changeConsoleColor(7);
          cout << setw(37) << "--------------------" << endl;
          displayService(services);
          break;
     case 3:
          clearFromPosition(1, 10);
          changeColor(12);
          cout << "\t\t---------- CUSTOMER FUNCTIONS: " << function[2] << " ----------\n";
          changeColor(7);
          cus.bookServices(username, password);
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
void adminScreen(const string &username, const string &password)
{
     cout << delLuna << endl;
     gotoXY(30, 9);
     changeColor(12);
     cout << "Your username: " << username; 
     gotoXY(29, 10);
     changeColor(2);
     cout << "------------------ ADMINISTRATOR ------------------";
     changeColor(12);
     gotoXY(35, 11);
     cout << "Please choose a function group first!";
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
         "4. Book",
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
         "3. Add New Bill",
         "4. Check Bill",
         "5. Remove Bill"};
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
          staffFunction(username, password, account, staffFunc);
          break;
     case 2:
          customerFunction(username, password, account, customerFunc);
          break;
     case 3:
          roomFunction(username, password, account, roomFunc);
          break;
     case 4:
          serBillFunction(username, password, account, serBillFunc);
          break;
     case 5:
          clearFromPosition(1, 1);
          introduceUs();
          break;
     }
}
//---FUNCTION OF ADMINISTRATOR---
void staffFunction(const string &username, const string &password, const string &account, vector<string> function)
{
     clearFromPosition(30, 11);
     changeColor(12);
     cout << "STAFF FUNCTIONS: Choose the function you want!";
     changeColor(7);

     function.push_back("RETURN");
     int choice = buttonList(40, 12, 28, 2, 2, function, "column");
     switch (choice)
     {
     case 1:
     {
          clearFromPosition(1, 10);
          changeColor(11);
          cout << "\t\t\t---------- STAFF FUNCTIONS: " << function[choice - 1] << " ----------\n";
          break;
     }
     case 2:
     {
          clearFromPosition(1, 10);
          changeColor(11);
          cout << "\t\t\t---------- STAFF FUNCTIONS: " << function[choice - 1] << " ----------\n";
          break;
     }
     case 3:
     {
          clearFromPosition(1, 10);
          changeColor(11);
          cout << "\t\t\t---------- STAFF FUNCTIONS: " << function[choice - 1] << " ----------\n";
          break;
     }
     case 4:
     {
          clearFromPosition(1, 10);
          changeColor(11);
          cout << "\t\t\t---------- STAFF FUNCTIONS: " << function[choice - 1] << " ----------\n";
          break;
     }
     case 5:
     {
          clearFromPosition(1, 1);
          adminScreen(username, password);
          break;
     }
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
          adminScreen(username, password);
          return;
     }
     else
     {
          system("cls");
          exitScreen();
          return;
     }
}

void customerFunction(const string &username, const string &password, const string &account, vector<string> function)
{
     clearFromPosition(30, 11);
     changeColor(12);
     cout << "CUSTOMER FUNCTIONS: Choose the function you want!";
     changeColor(7);

     function.push_back("RETURN");
     int choice = buttonList(40, 13, 28, 2, 2, function, "column");

     switch (choice)
     {
     case 1:
     {
          clearFromPosition(1, 10);
          changeColor(11);
          cout << "\t\t\t---------- CUSTOMER FUNCTIONS: " << function[choice - 1] << " ----------\n";
          break;
     }
     case 2:
     {
          clearFromPosition(1, 10);
          changeColor(11);
          cout << "\t\t\t---------- CUSTOMER FUNCTIONS: " << function[choice - 1] << " ----------\n";
          break;
     }
     case 3:
     {
          clearFromPosition(1, 10);
          changeColor(11);
          cout << "\t\t\t---------- CUSTOMER FUNCTIONS: " << function[choice - 1] << " ----------\n";
          break;
     }
     case 4:
     {
          clearFromPosition(1, 10);
          changeColor(11);
          cout << "\t\t\t---------- CUSTOMER FUNCTIONS: " << function[choice - 1] << " ----------\n";
          break;
     }
     case 5:
     {
          clearFromPosition(1, 10);
          changeColor(11);
          cout << "\t\t\t---------- CUSTOMER FUNCTIONS: " << function[choice - 1] << " ----------\n";
          break;
     }
     case 6:
     {
          clearFromPosition(1, 10);
          changeColor(11);
          cout << "\t\t\t---------- CUSTOMER FUNCTIONS: " << function[choice - 1] << " ----------\n";
          break;
     }
     case 7:
     {
          clearFromPosition(1, 1);
          adminScreen(username, password);
          break;
     }
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
          adminScreen(username, password);
          return;
     }
     else
     {
          system("cls");
          exitScreen();
          return;
     }
}

void roomFunction(const string &username, const string &password, const string &account, vector<string> function)
{
     clearFromPosition(30, 11);
     changeColor(12);
     cout << "ROOM FUNCTIONS: Choose the function you want!";
     changeColor(7);

     function.push_back("RETURN");
     int choice = buttonList(40, 13, 28, 2, 2, function, "column");
     switch (choice)
     {
     case 1:
     {
          clearFromPosition(1, 10);
          changeColor(11);
          cout << "\t\t\t---------- ROOM FUNCTIONS: " << function[choice - 1] << " ----------\n";
          break;
     }
     case 2:
     {
          clearFromPosition(1, 10);
          changeColor(11);
          cout << "\t\t\t---------- ROOM FUNCTIONS: " << function[choice - 1] << " ----------\n";
          break;
     }
     case 3:
     {
          clearFromPosition(1, 1);
          adminScreen(username, password);
          break;
     }
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
          adminScreen(username, password);
          return;
     }
     else
     {
          system("cls");
          exitScreen();
          return;
     }
}

void serBillFunction(const string &username, const string &password, const string &account, vector<string> function)
{
     clearFromPosition(30, 11);
     changeColor(12);
     cout << "SERVICE & BILL FUNCTIONS: Choose the function you want!";
     changeColor(7);

     function.push_back("RETURN");
     int choice = buttonList(40, 13, 30, 2, 2, function, "column");
     switch (choice)
     {
     case 1:
     {
          clearFromPosition(1, 10);
          changeColor(11);
          cout << "\t\t\t---------- SERVICE FUNCTIONS: " << function[choice - 1] << " ----------\n";
          break;
     }
     case 2:
     {
          clearFromPosition(1, 10);
          changeColor(11);
          cout << "\t\t\t---------- SERVICE FUNCTIONS: " << function[choice - 1] << " ----------\n";
          break;
     }
     case 3:
     {
          clearFromPosition(1, 10);
          changeColor(11);
          cout << "\t\t\t---------- BILL FUNCTIONS: " << function[choice - 1] << " ----------\n";
          break;
     }
     case 4:
     {
          clearFromPosition(1, 10);
          changeColor(11);
          cout << "\t\t\t---------- BILL FUNCTIONS: " << function[choice - 1] << " ----------\n";
          break;
     }
     case 5:
     {
          clearFromPosition(1, 10);
          changeColor(11);
          cout << "\t\t\t---------- BILL FUNCTIONS: " << function[choice - 1] << " ----------\n";
          break;clearFromPosition(1, 10);
          changeColor(11);
          cout << "\t\t\t---------- BILL FUNCTIONS: " << function[choice - 1] << " ----------\n";
          break;
     }
     case 6:
     {
          clearFromPosition(1, 1);
          adminScreen(username, password);
          break;
     }
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
          adminScreen(username, password);
          return;
     }
     else
     {
          system("cls");
          exitScreen();
          return;
     }
}

