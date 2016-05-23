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

extern const char *binLibFile;
extern const char *txtLibFile;

// Shows the main menu
void ::Menu::ShowMainMenu() {
	std::cout <<
		"Choose an option:\n\n"

		"Add new unit <N>\n"
		"Delete unit <D>\n"
		"Change unit <C>\n\n"

		"Show all units <A>\n"
		"Show Authors' books <B>\n"
		"Show the number of Ukrainian newspapers and magazines <U>\n"
		"Creat new sorted catalog of English magazines <E>\n\n"

		"Save library in a bin file <S>\n\n"

		"Quit <Q>\n";
}

// Chooses selected option in main menu
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
		// Case Show all units
		case 'A': {
			system("cls");
			::Library::ShowAllUnits(*lib, size);
			_getch();
			break;
		}
		// Case Show Authors' books
		case 'B': {
			system("cls");
			::Library::ShowAuthorBooks(*lib, size);
			_getch();
			break;
		}
		// Case Show number of Ukrainian newspapers and magazines
		case 'U': {
			system("cls");
			::Library::ShowUkrainian(*lib, size);
			_getch();
			break;
		}
		// Case Creat new sorted catalog of English magazines
		case 'E': {
			system("cls");

			break;
		}
		// Case Save library
		case 'S': {
			system("cls");
			Library::Write("test/test-bin-library", *lib, size, true);
			break;
		}
		default:
			break;
	}
}

// Shows menu in option "Add new unit"
void ::Menu::ShowMenuForNewUnit() {
	std::cout <<
		"What kind of unit?\n\n"

		"A book <B>\n"
		"A magazine <M>\n"
		"A newspaper <P>\n\n"
		
		"Cancel <Q>\n";
}

// Chooses selected option in "Add new unit"
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
			::Library::Unit *newMagazine = ::Library::CreatNewMagazine();
			::Library::AddNewUnit(*newMagazine, lib, size);
			printf("\nAdded.\n");
			_getch();
			break;
		}
		case 'P': {
			system("cls");
			// Case Add new newspaper to the library
			::Library::Unit *newNewspaper = ::Library::CreatNewNewspaper();
			::Library::AddNewUnit(*newNewspaper, lib, size);
			printf("\nAdded.\n");
			_getch();
			break;
		}
		default:
			break;
	}
}

// Shows all book gengres
void ::Menu::ShowBookGenres() {
	std::cout <<
		"Comedy <C>\n"
		"Drama <D>\n"
		"Romance novel <N>\n"
		"Tragedy <T>\n"
		"Horror <H>\n\n";
}

// Shows all magazine themes
void ::Menu::ShowMagazineThemes() {
	std::cout <<
		"Sport <S>\n"
		"Politics <P>\n"
		"Fashion <F>\n"
		"Science <C>\n\n";
}

// Show all newspaper genres
void ::Menu::ShowPaperGenres() {
	std::cout <<
		"Sport <S>\n"
		"Politics <P>\n"
		"Fashion <F>\n"
		"Celebrities <C>\n\n";
}

// Shows menu for reading library from file
void ::Menu::ShowReadingFileMenu() {
	std::cout
		<< "Open: \n\n"

		<< "Binary library <B>\n"
		<< "Text library <T>\n\n";
}

void ::Menu::ReadingFileSwitch(char choice, ::Library::Unit **lib, size_t &size) {
	switch (choice) {
		case 'B': {
			::Library::Read(binLibFile, lib, size);
			break;
		}
		case 'T': {
			::Library::ReadFromText(txtLibFile, lib, size);
			break;
		}
		default: {
			::Library::ReadFromText(txtLibFile, lib, size);
			break;
		}
	}
}