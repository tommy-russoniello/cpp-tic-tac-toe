#include "color.h"

#ifdef _WIN32

#include "windows.h"

void
 ResetColors ()
{
  SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}

void
RedOnBlack ()
{
  SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), FOREGROUND_RED);
}

void
GreenOnBlack ()
{
  SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
}

#else

void
 ResetColors ()
{
  cout << "\033[0m";
}

void
RedOnBlack ()
{
  cout << "\033[31m";
}

void
GreenOnBlack ()
{
  cout << "\033[32m";
}

#endif