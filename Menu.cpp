#include "Graphics.h"
#define MAX 100
using namespace std;

string welcomeMessage = R"(
                 _____      _____   _______________   ______________   _____________   _____               
                |     |    |     | |               | |              | |             | |     |        
                |     |    |     | |     _____     | |____      ____| |      _______| |     |         
                |     |____|     | |    |     |    |      |    |      |     |_______  |     |          
                |                | |    |     |    |      |    |      |             | |     |          
                |                | |    |     |    |      |    |      |      _______| |     |        
                |      ____      | |    |     |    |      |    |      |     |         |     |        
                |     |    |     | |    |_____|    |      |    |      |     |_______  |     |_______     
                |     |    |     | |               |      |    |      |             | |             |
                |_____|    |_____| |_______________|      |____|      |_____________| |_____________|

         ________     __________   __                __           __        __   _____     __       ____
        |   ___  \   |   _______| |  |              |  |         |  |      |  | |     \   |  |     /    \
        |  |   \  \  |  |_______  |  |              |  |         |  |      |  | |  |\  \  |  |    /  /\  \
        |  |    |  | |   _______| |  |              |  |         |  |      |  | |  | \  \ |  |   /  /__\  \
        |  |___/  /  |  |_______  |  |_______       |  |_______  |  |______|  | |  |  \  \|  |  /   _____  \
        |________/   |__________| |__________|      |__________| |____________| |__|   \_____| /__/      \__\

    )";

string hotel = R"(                 
                     _____      _____   _______________   ______________   _____________   _____               
                    |     |    |     | |               | |              | |             | |     |              
                    |     |    |     | |     _____     | |____      ____| |      _______| |     |              
                    |     |____|     | |    |     |    |      |    |      |     |_______  |     |              
                    |                | |    |     |    |      |    |      |             | |     |              
                    |                | |    |     |    |      |    |      |      _______| |     |              
                    |      ____      | |    |     |    |      |    |      |     |         |     |              
                    |     |    |     | |    |_____|    |      |    |      |     |_______  |     |_______       
                    |     |    |     | |               |      |    |      |             | |             |      
                    |_____|    |_____| |_______________|      |____|      |_____________| |_____________|     
   
)";

string delLuna = R"(
         ________     __________   __                __           __        __   _____     __       ____
        |   ___  \   |   _______| |  |              |  |         |  |      |  | |     \   |  |     /    \
        |  |   \  \  |  |_______  |  |              |  |         |  |      |  | |  |\  \  |  |    /  /\  \
        |  |    |  | |   _______| |  |              |  |         |  |      |  | |  | \  \ |  |   /  /__\  \
        |  |___/  /  |  |_______  |  |_______       |  |_______  |  |______|  | |  |  \  \|  |  /   _____  \
        |________/   |__________| |__________|      |__________| |____________| |__|   \_____| /__/      \__\
)";

string welcome = R"(
     ***               ***   **************   ***              **************   **************   *** ***     *** ***   **************
     ***               ***   **************   ***              **************   **************   *** ***     *** ***   **************
      ***             ***    ***              ***              ***              ***        ***   *** ***     *** ***   ***
      ***             ***    **************   ***              ***              ***        ***   ***   *** ***   ***   **************
       ***           ***     **************   ***              ***              ***        ***   ***     ***     ***   **************
       ***    ***    ***     ***              ***              ***              ***        ***   ***             ***   ***
        ***   ***   ***      **************   **************   **************   **************   ***             ***   **************
           ***   ***         **************   **************   **************   **************   ***             ***   **************
     )"; 

void welcomTo();
void continueScreen();
void exitScreen();
void introScreen();
void inputPassword(string &password);
void logInBar(int x, int y, int textColor, int backgroundColor);
void introduceUs();
void noAccountScreen();
void adminScreen();
void customerScreen();

int main()
{
     //resizeConsole(1500, 1500);
     //SetWindowSize(1500, 1500);
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
     gotoXY(20, 20);
     cout << "Day la man hinh neu bam exit";
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
     gotoXY(x - 20,y + 1);
     cout << "Your username is your full name (all lowercase, without spaces or special characters.)";
     boxTwoLine(x, y + 2, 16, 2, textColor, backgroundColor, "Username");
     boxTwoLine(x + 17, y + 2, 30, 2, textColor, backgroundColor, " ");
     gotoXY(x - 5, y + 6);
     cout << "Your password is your CCCD (exactly 12 characters)";
     boxTwoLine(x, y + 7, 16, 2, textColor, backgroundColor, "Password");
     boxTwoLine(x + 17, y + 7, 30, 2, textColor, backgroundColor, " ");
     gotoXY(x + 21, y + 3);
     ShowCur(1);
     getline(cin, username);
     gotoXY(x + 21, y + 8);
     inputPassword(password);
}

void introduceUs()
{
     cout << welcomeMessage << endl;
     
     string border1 = "+-----------+-------------------------------------+";
     string border2 = "+-----------+-------------------------+-----------+";
     gotoXY(34, 21);
     cout << border1;
     gotoXY(34, 22);
     cout << "| Advisor   | TS. Nguyen Van Hieu                 |";
     gotoXY(34, 23);
     cout << border1;
     gotoXY(34, 25);
     cout << border2 << endl;
     gotoXY(34, 26);
     cout << "| Student 1 | Nguyen Thi Bao Ngan     | 102230255 |";
     gotoXY(34, 27);
     cout << border2 << endl;
     gotoXY(34, 28);
     cout << "| Student 2 | Nguyen Dang Bao Nguyen  | 102230256 |";
     gotoXY(34, 29);
     cout << border2 << endl;

     gotoXY(43, 31);
     cout << "Do you already have an account?";
     vector<string> yesNo = {"Yes", "No"};
     int yN = buttonList(38, 33, 10, 2, 20, yesNo, "row");
     if (yN == 1)
     {
          Sleep (500);
          clearFromPosition(38, 31);
          cout << "Log in by AMINISTRATOR or CUSTOMER account?";
          string username, password;

          vector<string> adCus = {"Administrator", "Customer"};
          int aC = buttonList(27, 33, 20, 2, 25, adCus, "row");
          if (aC == 1)
          {
               clearFromPosition(38, 30);
               changeColor(2);
               cout << "You are logging in by ADMINISTRATOR account!";
               changeColor(7);
               bool check = false;
               do {
                    logInBar(34, 31, 11, 150, username, password);
                    if (check == true)
                    {
                         changeColor(4);
                         cout << "Wrong username or password for administrator account!" << endl;
                         changeColor(7);
                    }
               } while (check);

               Sleep(500);
               system("cls");
               adminScreen();
          }
          else if (aC == 2)
          {
               clearFromPosition(38, 30);
               changeColor(2);
               cout << "You are logging in by CUSTOMER account";
               changeColor(7);
               logInBar(34, 31, 11, 150, username, password);

               Sleep(500);
               system("cls");
               customerScreen();
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
     cout << delLuna << endl;
     cout << "\n------------------ NO ACCOUNT ------------------" << endl;
     cout << "\t1. Show Room List" << endl;
     cout << "\t2. Show Service List" << endl;
     cout << "\t3. Show Book Room";
}

void adminScreen()
{
     cout << delLuna << endl;
     gotoXY(29, 9);
     changeColor(2);
     cout << "------------------ ADMINISTRATOR ------------------";
     changeColor(12);
     gotoXY(35, 10);
     cout << "Please choose a function group first!";
     changeColor(7);

     vector<string> staffFunc = {
          "1. Add New",
          "2. Update Information",
          "3. Remove By CCCD",
          "4. Remove",
          "5. Show All"
     };
     for (int i = 0; i < staffFunc.size(); i++)
     {
          gotoXY(1, 15 + i);
          cout << staffFunc[i];
     }
     vector<string> customerFunc = {
          "1. Add New",
          "2. Update Information",
          "3. Find By First Name",
          "4. Find By Last Name",
          "5. Find By Letter",
          "6. Find By CCCD",
          "7. Remove By CCCD",
          "8. Remove",
          "9. Show All"   
     };
     for (int i = 0; i < customerFunc.size(); i++)
     {
          gotoXY(31, 15 + i);
          cout << customerFunc[i];
     }

     vector<string> roomFunc = {
          "1. Change Room Status",
          "2. Show All",
     };
     for (int i = 0; i < roomFunc.size(); i++)
     {
          gotoXY(61, 15 + i);
          cout << roomFunc[i];
     }

     vector<string> serviceFunc = {
          "1. Show All",
     };
     for (int i = 0; i < serviceFunc.size(); i++)
     {
          gotoXY(91, 15 + i);
          cout << serviceFunc[i];
     }

     vector<string> billFunc = {
          "1. Add New Bill",
          "2. Check By Name & Phone number"
     };
     for (int i = 0; i < billFunc.size(); i++)
     {
          gotoXY(121, 15 + i);
          cout << billFunc[i];
     }

     vector<string> groupFunc = {"Staff", "Customer", "Room", "Service", "Bill"};
     int choice = buttonList (6, 12, 15, 2, 14, groupFunc, "row");
     gotoXY (25, 30);
     cout << "You have chosen function group:\t" << groupFunc[choice - 1];
}

void customerScreen()
{
     cout << delLuna << endl;
     cout << "\n------------------ CUSTOMER ------------------" << endl;
     cout << "\t1. Show Room List" << endl;
     cout << "\t2. Show Service List" << endl;
     cout << "\t3. Show Book Room";
}