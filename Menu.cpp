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

     if (twoBoxButton(20, 30, 15, 2, 75, 11, 150, 75, "CONTINUE", "EXIT"))
     {
          continueScreen();
     }
     else 
     {
          exitScreen();
     }

     /* int x = 20, y = 30, w = 15, h = 2, textColor = 11, backgroundColor = 150, selectedColor = 75;
     boxOneLine(x, y, w, h, textColor, backgroundColor, "CONTINUE");
     boxOneLine(x + 80, y, w, h, textColor, backgroundColor, "EXIT");
     string content = "CONTINUE";
     string newContent = "CONTINUE";
     selectedBar(x, y, w, h, selectedColor, content);

     int xp = x, yp = y;
     int xOld = xp, yOld = yp;
     bool check = true;
     while (true)
     {
          if (check)
          {
               gotoXY(xOld, yOld);
               selectedBar(xOld, yOld, w, h, backgroundColor, content);
               xOld = xp, yOld = yp;
               selectedBar(xp, yp, w, h, selectedColor, newContent);
               check = false;
          }

          if (_kbhit())
          {
               char c = _getch();
               if (c == -32)
               {
                    check = true;
                    c = _getch();
                    if (c == 77)
                    { // Mũi tên phải
                         if (xp != x + 80)
                         {
                              xp += 80;
                              content = "CONTINUE";
                              newContent = "EXIT";
                         }
                         else
                         {
                              xp = x;
                              content = "EXIT";
                              newContent = "CONTINUE";
                         }
                    }
                    else if (c == 75)
                    { // Mũi tên trái
                         if (xp != x)
                         {
                              xp -= 80;
                              content = "EXIT";
                              newContent = "CONTINUE";
                         }
                         else
                         {
                              xp = x + 80;
                              content = "CONTINUE";
                              newContent = "EXIT";
                         }
                    }
               }
               else if (c == 13)
               { // Phím Enter
                    if (xp == 20)
                    {
                         continueScreen();
                         break;
                    }
                    else
                    {
                         exitScreen();
                         break;
                    }
               }
          }
     } */
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
     cout << "Did you have your own account?";
     if(twoBoxButton(40, 33, 10, 2, 25, 11, 150, 75, "Yes", "No"))
     {
          Sleep(900);
          clearFromPosition(38,31);
          cout << "Log in by ADMINISTRATOR or CUSTOMER account?";
          string username, password;
     
          if (twoBoxButton(35, 33, 20, 2, 30, 11, 150, 75, "Administrator", "Customer"))
          {
               clearFromPosition(35,31);
               gotoXY(38, 30); 
               changeColor(2);
               cout << "You are logging in by ADMINISTRATOR account!";
               changeColor(7);
               logInBar(34, 31, 11, 150, username, password);

               system("cls");
               adminScreen();
          }
          else
          {
               clearFromPosition(35,31);
               gotoXY(38, 30); 
               changeColor(2);
               cout << "You are logging in by CUSTOMER account!";
               changeColor(7);
               logInBar(34, 32, 11, 150, username, password);

               system("cls");
               customerScreen();
          }
     }
     else
     {
          Sleep(900);
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
     gotoXY(29, 10);
     changeColor(2);
     cout << "------------------ ADMINISTRATOR ------------------" << endl;
     changeColor(7);

     vector<string> staff = {
          "1. Add New Staff",
          "2. Update Staff's Information",
          "3. Find Staff By First Name",
          "4. Find Staff By Last Name",
          "5. Find Staff By CCCD",
          "6. Find Staff By Letter",
          "7. Remove Staff By CCCD",
          "8. Remove Staff"
     };
     for (int i = 0; i < staff.size(); i++)
     {
          gotoXY(10, 15 + i);
          cout << staff[i];
     }
     vector<string> customer = {
          "1. Add New Customer",
          "2. Update Customer's Information",
          "3. Find Customer By First Name",
          "4. Find Customer By Last Name",
          "5. Find Customer By CCCD",
          "6. Find Customer By Letter",
          "7. Remove Customer By CCCD",
          "8. Remove Customer"   
     };
     for (int i = 0; i < customer.size(); i++)
     {
          gotoXY(60, 15 + i);
          cout << customer[i];
     }

     if(twoBoxButton(15, 11, 15, 2, 55, 11, 150, 75, "Staff", "Customer"));
     
     /*
     cout << "\t SHOWING" << endl;
     cout << "\t1. Show Staff" << endl;
     cout << "\t2. Show Customer" << endl;
     cout << "\t3. Show Room" << endl;
     cout << "\t4. Show Service" << endl;
     cout << "\n\t BOOKING" << endl;
     cout << "\t1. Book Room" << endl;
     cout << "\t2. Book Service" << endl;
     cout << "\n\t REMOVING" <<endl;
     cout << "\t1. Remove Staff" << endl;
     cout << "\t2. Remove Staff by CCCD" << endl;
     cout << "\t3. Remove Staff by Name" << endl; */
}

void customerScreen()
{
     cout << delLuna << endl;
     cout << "\n------------------ CUSTOMER ------------------" << endl;
     cout << "\t1. Show Room List" << endl;
     cout << "\t2. Show Service List" << endl;
     cout << "\t3. Show Book Room";
}