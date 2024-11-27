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
#include <cctype>
#include <initializer_list>
#include <stdexcept>
#include <ctime>
#include <limits>
#include <ctime> 
#include <chrono>

void inline changeConsoleColor(int colorCode)
{
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(hConsole, colorCode);
}

#endif 
