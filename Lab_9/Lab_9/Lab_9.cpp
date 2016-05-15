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

int main() {
	Library::Unit *lib = nullptr;
	size_t size = 0;
	Library::ReadFromText("test/test-text-library.txt", &lib, size);

	// Show main menu
	Menu::ShowMainMenu();

	// Get chosen option
	char choice = toupper(_getch());

	// Choose an option
	while (choice != 'Q') {
		Menu::MainMenuSwitch(choice, &lib, size);

		system("cls");
		Menu::ShowMainMenu();
		choice = toupper(_getch());
	}

	Library::Write("test/test-bin-library", lib, size, true);
	return 0;
}