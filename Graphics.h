#pragma once

#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include <iomanip>
#include <ctime>
#include "Vector.h"

using namespace std;

#define KEY_NONE -1

// Toa do X cua con tro hien tai
int whereX()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return csbi.dwCursorPosition.X;
    return -1;
}
// Toa do Y cua con tro hien tai
int whereY()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return csbi.dwCursorPosition.Y;
    return -1;
}
// Ham dich chuyen con tro den toa do (x,y), truc Oy huong xuong la chieu duong
void gotoXY(int x, int y)
{
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Cursor_an_Pos = {static_cast<SHORT>(x - 1), static_cast<SHORT>(y - 1)};

    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

// Thay doi kich co khung cmd
void resizeConsole(int width, int height)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}

// Thay doi kich thuoc noi dung Console
void SetWindowSize(SHORT width, SHORT height)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Right = width;
    WindowSize.Bottom = height;

    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}

// Ham to mau 0-255 (vuot qua thi reset lai vd: 256->0)
void changeColor(int colorCode)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
}

// Di chuyen den toa do x,y. To mau cho chuoi can to
void setColor(int x, int y, char *a, int colorCode)
{
    gotoXY(x, y);
    changeColor(colorCode);
    cout << a;
    changeColor(7);
}

// An con tro chuot
void ShowCur(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = {1, CursorVisibility};
    SetConsoleCursorInfo(handle, &cursor);
}

// Ham in chuoi o giua console
void printCentered(const char *message, int colorCode, int consoleWidth, int consoleHeight)
{
    int x = (consoleWidth - strlen(message)) / 2;
    int y = consoleHeight / 2;

    gotoXY(x, y);
    changeColor(colorCode);
    cout << message;
    changeColor(7);
    cout << endl;
}

void loadingBarAnimation(int colorCode)
{
    const int totalProgress = 100; // 100%
    const int barWidth = 40;       // Độ rộng thanh tiến trình
    string spinner = "|/-\\";      // Hiệu ứng xoay

    changeColor(colorCode);
    for (int progress = 0; progress <= totalProgress; ++progress)
    {
        int completedWidth = barWidth * progress / totalProgress;

        cout << "\rLoading " << char(91) << " ";
        for (int i = 0; i < barWidth; ++i)
        {
            if (i < completedWidth)
            {
                cout << char(254);
            }
            else
            {
                cout << " ";
            }
        }
        cout << " " << char(93) << " " << progress << "% "
             << spinner[progress % spinner.size()]; // Hiệu ứng xoay

        cout.flush();

        Sleep(20);
    }
    changeColor(7);
}

// Dat mau cho chu
void SetColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

//======= trả về mã phím người dùng bấm =========
int inputKey()
{
    if (_kbhit())
    {
        int key = _getch();

        if (key == 224)
        {
            key = _getch();
            return key + 1000;
        }

        return key;
    }
    else
    {
        return KEY_NONE;
    }

    return KEY_NONE;
}

void boxOneLine(int x, int y, int w, int h, int textColor, int backgroundColor, string content)
{
    changeColor(backgroundColor);
    for (int iy = y; iy <= y + h; iy++)
    {
        for (int ix = x; ix <= x + w; ix++)
        {
            gotoXY(ix, iy);
            cout << " ";
        }
    }
    //**
    changeColor(7);
    gotoXY(x + 3, y + 1);
    cout << " " << left << setw(w - 6) << content;
    changeColor(textColor);
    if (h <= 1 || w <= 1)
        return; // khong xu ly
    for (int ix = x; ix <= x + w; ix++)
    {
        gotoXY(ix, y);
        cout << char(196);
        gotoXY(ix, y + h);
        cout << char(196);
    }
    for (int iy = y; iy <= y + h; iy++)
    {
        gotoXY(x, iy);
        cout << char(179);
        gotoXY(x + w, iy);
        cout << char(179);
    }

    gotoXY(x, y);
    cout << char(218);
    gotoXY(x + w, y);
    cout << char(191);
    gotoXY(x, y + h);
    cout << char(192);
    gotoXY(x + w, y + h);
    cout << char(217);
    changeColor(7);
}

void boxTwoLine(int x, int y, int w, int h, int textColor, int backgroundColor, string content)
{
    changeColor(backgroundColor);
    for (int iy = y; iy <= y + h; iy++)
    {
        for (int ix = x; ix <= x + w; ix++)
        {
            gotoXY(ix, iy);
            cout << " ";
        }
    }
    //**
    changeColor(7);
    gotoXY(x + 3, y + 1);
    cout << " " << left << setw(w - 6) << content;
    changeColor(textColor);
    if (h <= 1 || w <= 1)
        return; // khong xu ly
    for (int ix = x; ix <= x + w; ix++)
    {
        gotoXY(ix, y);
        cout << char(205);
        gotoXY(ix, y + h);
        cout << char(205);
    }
    for (int iy = y; iy <= y + h; iy++)
    {
        gotoXY(x, iy);
        cout << char(186);
        gotoXY(x + w, iy);
        cout << char(186);
    }

    gotoXY(x, y);
    cout << char(201);
    gotoXY(x + w, y);
    cout << char(187);
    gotoXY(x, y + h);
    cout << char(200);
    gotoXY(x + w, y + h);
    cout << char(188);
    changeColor(7);
}

void selectedBar(int x, int y, int w, int h, int backgroundColor, string content)
{
    changeColor(backgroundColor);
    for (int iy = y + 1; iy <= y + h - 1; iy++)
    {
        for (int ix = x + 1; ix <= x + w - 1; ix++)
        {
            gotoXY(ix, iy);
            cout << " ";
        }
    }
    changeColor(7);
    gotoXY(x + 3, y + 1);
    cout << " " << left << setw(w - 6) << content;
}

int buttonList(int x, int y, int w, int h, int space, vector<string> content, string model)
{
    int number = content.size();
    if (model == "row")
    {
        for (int i = 0; i < number; i++)
            boxTwoLine(x + (space + w) * i, y, w, h, 11, 150, content[i]);
    }
    else if (model == "column")
    {
        for (int i = 0; i < number; i++)
            boxOneLine(x, y + (space + h) * i, w, h, 11, 150, content[i]);
    }

    int iold = 0, inew = 0;
    selectedBar(x, y, w, h, 75, content[iold]);

    int xp = x, yp = y, xOld = xp, yOld = yp;
    bool check = true;
    
    while (true)
    {
        if (check)
        {
            gotoXY(xOld, yOld);
            selectedBar(xOld, yOld, w, h, 150, content[iold]);
            xOld = xp, yOld = yp;
            selectedBar(xp, yp, w, h, 75, content[inew]);
            check = false;
        }

        if (_kbhit())
        {
            char c = _getch();

            if (c == -32)
            {
                check = true;
                c = _getch();
                if (model == "row")
                {
                    if (c == 77)
                    {
                        if (inew < number - 1)
                        {
                            xp += (space + w);
                            iold = inew;
                            inew++;
                        }
                        else
                        {
                            xp = x;
                            iold = inew;
                            inew = 0;
                        }
                    }
                    else if (c == 75)
                    {
                        if (inew > 0)
                        {
                            xp -= (space + w);
                            iold = inew;
                            inew--;
                        }
                        else
                        {
                            xp += (space + w) * (number - 1);
                            iold = inew;
                            inew = number - 1;
                        }
                    }
                }
                else if (model == "column")
                {
                    if (c == 80)
                    {
                        if (inew < number - 1)
                        {
                            yp += (space + h);
                            iold = inew;
                            inew++;
                        }
                        else
                        {
                            yp = y;
                            iold = inew;
                            inew = 0;
                        }
                    }
                    else if (c == 72)
                    {
                        if (inew > 0)
                        {
                            yp -= (space + h);
                            iold = inew;
                            inew--;
                        }
                        else
                        {
                            yp += (space + h) * (number - 1);
                            iold = inew;
                            inew = number - 1;
                        }
                    }
                }
            }
            else if (c == 13)
            {
                return inew + 1;
            }
        }
    }
}

// Ham xoa man hinh tu vi tri x, y tro ve cuoi console
void clearFromPosition(int x, int y)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Lấy kích thước của console
    if (GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        int consoleWidth = csbi.dwSize.X;
        int consoleHeight = csbi.dwSize.Y;

        // Bắt đầu xóa từ vị trí (x, y) đến cuối màn hình
        for (int iy = y; iy < consoleHeight; iy++)
        {
            for (int ix = (iy == y ? x : 0); ix < consoleWidth; ix++)
            {
                gotoXY(ix, iy);
                cout << " ";
            }
        }
    }
    gotoXY(x, y); // Đưa con trỏ về lại vị trí ban đầu sau khi xóa
}
