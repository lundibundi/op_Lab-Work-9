// Lab_9.cpp : Defines the entry point for the console application.
//


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include "stdafx.h"
#include <conio.h>
#else

#include <ncurses.h>
#include <iostream>

#define _getch getch
#endif

#include "date.h"
#include "library.h"

int main() {
    Library::Unit *lib = nullptr;
    size_t size = 0;
    Library::ReadFromText("test/test-text-library.txt", &lib, size);
    Library::Write("test/test-bin-library", lib, size, true);

    Library::Unit *anLib = nullptr;
    size_t anSize = 0;
    Library::Read("test/test-bin-library", &anLib, anSize);

    _getch();
    return 0;
}

