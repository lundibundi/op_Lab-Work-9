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

void ShowMainMenu();
void MainMenuSwitch(char menu);

int main() {
	Library::Unit *lib = nullptr;
	size_t size = 0;
	Library::ReadFromText("test/test-text-library.txt", &lib, size);
	Library::Write("test/test-bin-library", lib, size, true);

	// Show main menu
	ShowMainMenu();

	// Get chosen option
	char menu = toupper(_getch());

	// Choose an option
	while (menu != 'Q') {
		MainMenuSwitch(menu);

		system("cls");
		ShowMainMenu();
		menu = toupper(_getch());
	}


	Library::Unit *anLib = nullptr;
	size_t anSize = 0;
	Library::Read("test/test-bin-library", &anLib, anSize);

	_getch();
	return 0;
}

// Show the main menu
void ShowMainMenu() {
	std::cout <<
		"Add new unit <N>\n"
		"Delete unit <D>\n"
		"Change unit <C>\n\n"

		"Show Authors' books <B>\n"
		"Show number of Ukrainian newspapers and magazines <U>\n"
		"Creat new sorted catalog of English magazines <E>\n\n"

		"Quit <Q>\n";
}

// Choose selected option
void MainMenuSwitch(char menu) {
	switch (menu) {
	case 'N': {
		system("cls");
		// Case Add new unit

		break;
	}
	case 'D': {
		system("cls");
		// Case Delete unit

		break;
	}
	case 'C': {
		system("cls");
		// Case Change unit

		break;
	}
	case 'B': {
		system("cls");
		// Case Show Authors' books

		break;
	}
	case 'U': {
		system("cls");
		// Case Show number of Ukrainian newspapers and magazines

		break;
	}
	case 'E': {
		system("cls");
		// Case Creat new sorted catalog of English magazines

		break;
	}
	default:
		break;
	}
}