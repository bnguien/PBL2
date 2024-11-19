#include "Graphics.h"

#include "Customer.h"
#include "Login.h"

#include "Function.h"
#include "Vector.h"
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

//---Sencondary Function---
void inputPassword(string &password);
void logInBar(int x, int y, int textColor, int backgroundColor);
bool logInCheck(int x, int y, int textColor, int backgroundColor, string text);

void welcomTo();
void continueScreen();
void exitScreen();
void introScreen();

void introduceUs();
void noAccountScreen();
void adminScreen(const string &username, const string &password);
void customerScreen(const string &username, const string &password);

//---Screen for function---
void staffFunction(const string &username, const string &password, const string &account, vector<string> function);
void customerFunction(const string &username, const string &password, const string &account, vector<string> function);
void roomFunction(const string &username, const string &password, const string &account, vector<string> function);
void serBillFunction(const string &username, const string &password, const string &account, vector<string> function);
