#include "Function.h"

using namespace std;

void loadingBarAnimation(int color)
{
    const int totalProgress = 100; 
    const int barWidth = 40;       
    string spinner = "|/-\\";    

    changeConsoleColor(color);
    for (int progress = 0; progress <= totalProgress; ++progress)
    {
        int completedWidth = barWidth * progress / totalProgress;

        cout << "\rLoading [";
        for (int i = 0; i < barWidth; ++i)
        {
            if (i < completedWidth)
            {
                cout << "-"; // Thanh đầy
            }
            else
            {
                cout << " "; // Thanh trống
            }
        }
        cout << "] " << progress << "% "
             << spinner[progress % spinner.size()]; // Hiệu ứng xoay

        cout.flush(); // Đảm bảo in ra ngay lập tức

        Sleep(30); // Windows (30ms)
    }
    cout << endl;
    changeConsoleColor(7);
}

void changeConsoleColor(int colorCode)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
}
