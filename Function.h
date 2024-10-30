#ifndef FUNCTION_H
#define FUNCTION_H
#include <math.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <algorithm>
#include <iomanip>
#include <ctype.h>
#include <utility>
#include <cstdlib>
#include <string.h>
#include <conio.h>
#include <unordered_set>
#include <cctype>
#include <initializer_list>
#include <stdexcept>
#include <ctime>


void changeConsoleColor(int colorCode)
{
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(hConsole, colorCode);
}

#endif 
