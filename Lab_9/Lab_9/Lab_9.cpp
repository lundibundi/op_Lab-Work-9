// Lab_9.cpp : Defines the entry point for the console application.
//


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include "stdafx.h"
#include <conio.h>
#include <iostream>
#else

#include <ncurses.h>
#include <iostream>

#define _getch getch
#endif

#include "date.h"
#include "library.h"
#include "menu.h"

const char *binLibFile = "test/test-bin-library";		// name of binary file of library
const char *txtLibFile = "test/test-text-library.txt";	// name of text file of library

int main() {
	Library::Unit *lib = nullptr;
	size_t size = 0;

	// Choose a file
	Menu::ShowReadingFileMenu();
	char fileChoice = toupper(_getch());
	Menu::ReadingFileSwitch(fileChoice, &lib, size);

	// Show main menu
	Menu::ShowMainMenu();

	// Choose an option
	char choice = toupper(_getch());
	while (choice != 'Q') {
		Menu::MainMenuSwitch(choice, &lib, size);

		system("cls");
		Menu::ShowMainMenu();
		choice = toupper(_getch());
	}

	return 0;
}