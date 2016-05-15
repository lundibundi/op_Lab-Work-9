//
// Created by Dspade0 on 5/15/16.
//

#include "menu.h"
#include "library.h"
#include <iostream>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <conio.h>
#else
#include <ncurses.h>
#define _getch getch
#endif

// Show the main menu
void ::Menu::ShowMainMenu() {
	std::cout <<
		"Choose an option:\n\n"

		"Add new unit <N>\n"
		"Delete unit <D>\n"
		"Change unit <C>\n\n"

		"Show Authors' books <B>\n"
		"Show number of Ukrainian newspapers and magazines <U>\n"
		"Creat new sorted catalog of English magazines <E>\n\n"

		"Quit <Q>\n";
}

// Choose selected option
void ::Menu::MainMenuSwitch(char choice, ::Library::Unit **lib, size_t &size) {
	switch (choice) {
		// Case Add new unit
		case 'N': {
			system("cls");
			ShowMenuForNewUnit();
			char nextChoice = toupper(_getch());
			NewUnitSwitch(nextChoice, lib, size);
			break;
		}
		// Case Delete unit
		case 'D': {
			system("cls");
			::Library::DeleteUnit(lib, size);
			break;
		}
		// Case Change unit
		case 'C': {
			system("cls");
			::Library::ChangeUnit(lib, size);
			break;
		}
		// Case Show Authors' books
		case 'B': {
			system("cls");

			break;
		}
		// Case Show number of Ukrainian newspapers and magazines
		case 'U': {
			system("cls");

			break;
		}
		// Case Creat new sorted catalog of English magazines
		case 'E': {
			system("cls");

			break;
		}
		default:
			break;
	}
}

void ::Menu::ShowMenuForNewUnit() {
	std::cout <<
		"What kind of unit?\n\n"

		"A book <B>\n"
		"A magazine <M>\n"
		"A newspaper <P>\n\n"
		
		"Cancel <Q>\n";
}

void ::Menu::NewUnitSwitch(char choice, ::Library::Unit **lib, size_t &size) {
	switch (choice) {
		case 'B': {
			system("cls");
			// Case Add new book to the library
			::Library::Unit *newBook = ::Library::CreatNewBook();
			::Library::AddNewUnit(*newBook, lib, size);
			printf("\nAdded.\n");
			_getch();
			break;
		}
		case 'M': {
			system("cls");
			// Case Add new magazine to the library
			::Library::Unit *newMagazine = ::Library::CreatNewBook();
			::Library::AddNewUnit(*newMagazine, lib, size);
			printf("\nAdded.\n");
			_getch();
			break;
		}
		case 'P': {
			system("cls");
			// Case Add new newspaper to the library
			::Library::Unit *newNewspaper = ::Library::CreatNewBook();
			::Library::AddNewUnit(*newNewspaper, lib, size);
			printf("\nAdded.\n");
			_getch();
			break;
		}
		default:
			break;
	}
}

void ::Menu::ShowBookGenres() {
	std::cout <<
		"Comedy <C>\n"
		"Drama <D>\n"
		"Romance novel <N>\n"
		"Tragedy <T>\n"
		"Horror <H>\n\n";
}

void ::Menu::ShowMagazineThemes() {
	std::cout <<
		"Sport <S>\n"
		"Politics <P>\n"
		"Fashion <F>\n"
		"Science <C>\n\n";
}

void ::Menu::ShowPaperGenres() {
	std::cout <<
		"Sport <S>\n"
		"Politics <P>\n"
		"Fashion <F>\n"
		"Celebrities <C>\n\n";
}