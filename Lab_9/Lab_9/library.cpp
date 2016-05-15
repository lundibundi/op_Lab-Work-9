//
// Created by lundibundi on 5/12/16.
//

#include "library.h"
#include "menu.h"
#include <stdio.h>
#include <iostream>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <conio.h>
#else
#include <ncurses.h>
#define _getch getch
#endif

using namespace ::Library;

void ::Library::ReadFromText(const char *filename, Unit **lib, size_t &size) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        perror("file not exist ");
        _getch();
        exit(EXIT_FAILURE);
    }

    if (size < 1) size = 10;

    if (*lib == nullptr) *lib = new Unit[size];

    // just for convenience
    Unit *library = *lib;
    int i = 0;
    for (i = 0; !feof(f); ++i) {
        // extend current container as needed
        if (i >= size) {
            size *= 2;
            Unit *newLib = new Unit[size];
            for (int j = 0; j < i; ++j) {
                newLib[j] = library[j];
            }
            delete[] library;
            *lib = newLib;
            library = newLib;
        }

        // set new object in container
        library[i] = Unit{};

        // read basic features
        char ch = 'b';
        fscanf(f, "%c '%[^']' '%[^']' %d ", &ch, library[i].editionName,
               library[i].language, &library[i].id);

        // read specific according to BookType
        if (ch == 'b') {
            library[i].bookType = BookType::BOOK;
            fscanf(f, "'%[^']' %d %d\n", library[i].book.author,
                   &library[i].book.yearOfPublish, &library[i].book.genre);
        } else if (ch == 'm') {
            library[i].bookType = BookType::MAGAZINE;
            fscanf(f, "%d %d %d\n", &library[i].magazine.number,
                   &library[i].magazine.yearOfPublish, &library[i].magazine.theme);
        } else if (ch == 'p') {
            int date = 0;
            library[i].bookType = BookType::NEWSPAPER;
            fscanf(f, "%d %d %d\n", &library[i].paper.number,
                   &date, &library[i].paper.genre);
            library[i].paper.publishDate = DateFromInt(date);
        }
    }

    size = i;

    fclose(f);
}

void ::Library::Read(const char *filename, Unit **lib, size_t &size) {
    FILE *f = fopen(filename, "rb");
    // check file
    if (f == NULL) {
        perror("file not exist");
        _getch();
		exit(EXIT_FAILURE);
    }

    // determine size
    fseek(f, 0, SEEK_END);
    size = ftell(f) / sizeof(::Library::Unit);
    rewind(f);

    *lib = new Unit[size];

    fread(*lib, sizeof(::Library::Unit), size, f);

    fclose(f);
}

void ::Library::Write(const char *filename, Unit *lib, size_t size, bool newFile) {
    FILE *f;
    if (newFile) {
        f = fopen(filename, "wb");
    } else {
        f = fopen(filename, "ab");
    }

    fwrite(lib, sizeof(Library::Unit), size, f);

    fclose(f);
}

// Add new unit to the library
void ::Library::AddNewUnit(Unit &unit, Unit **lib, size_t &size) {
	if (*lib == nullptr) {
		size = 1;
		*lib = new Unit[size];
		*lib[size - 1] = unit;
	} else {
		// Just for convenience
		Unit *library = *lib;

		// Expand the container
		Unit *newLib = new Unit[size + 1];
		for (int i = 0; i < size; ++i) {
			newLib[i] = library[i];
		}
		delete[] library;
		library = newLib;

		// Add new unit to the end of library
		library[size++] = unit;
		*lib = library;
	}
}

// Creats new book
Unit* ::Library::CreatNewBook() {
	Unit *newBook = new Unit;
	newBook->bookType = ::Library::BookType::BOOK;

	std::cout << "Edition name: ";
	std::cin.getline(newBook->editionName, ::Library::maxNameLength);
	std::cout << "Language: ";
	std::cin.getline(newBook->language, ::Library::maxNameLength);
	std::cout << "ID: ";
	std::cin >> newBook->id;
	std::cin.get();
	std::cout << "Author's name: ";
	std::cin.getline(newBook->book.author, ::Library::maxNameLength);
	std::cout << "Year of publish: ";
	std::cin >> newBook->book.yearOfPublish;
	std::cin.get();

	std::cout << "Choose genre (Drama is default):\n\n";
	::Menu::ShowBookGenres();

	char choice = toupper(_getch());
	switch (choice) {
		case 'C': {
			newBook->book.genre = ::Library::BookGenre::Comedy;
			break;
		}
		case 'D': {
			newBook->book.genre = ::Library::BookGenre::Drama;
			break;
		}
		case 'N': {
			newBook->book.genre = ::Library::BookGenre::RomanceNovel;
			break;
		}
		case 'T': {
			newBook->book.genre = ::Library::BookGenre::Tragedy;
			break;
		}
		case 'H': {
			newBook->book.genre = ::Library::BookGenre::Horror;
			break;
		}
		default: {
			newBook->book.genre = ::Library::BookGenre::Drama;
			break;
		}
	}
	return newBook;
}

// Creats new magazine
Unit* ::Library::CreatNewMagazine() {
	Unit *newMagazine = new Unit;
	newMagazine->bookType = ::Library::BookType::MAGAZINE;

	std::cout << "Edition name: ";
	std::cin.getline(newMagazine->editionName, ::Library::maxNameLength);
	std::cout << "Language: ";
	std::cin.getline(newMagazine->language, ::Library::maxNameLength);
	std::cout << "ID: ";
	std::cin >> newMagazine->id;
	std::cin.get();
	std::cout << "Magazine number: ";
	std::cin >> newMagazine->magazine.number;
	std::cin.get();
	std::cout << "Year of publish: ";
	std::cin >> newMagazine->magazine.yearOfPublish;
	std::cin.get();

	std::cout << "Choose theme (Sport is default):\n\n";
	::Menu::ShowMagazineThemes();

	char choice = toupper(_getch());
	switch (choice) {
		case 'S': {
			newMagazine->magazine.theme = ::Library::MagazineTheme::Sport;
			break;
		}
		case 'P': {
			newMagazine->magazine.theme = ::Library::MagazineTheme::Politics;
			break;
		}
		case 'F': {
			newMagazine->magazine.theme = ::Library::MagazineTheme::Fashion;
			break;
		}
		case 'C': {
			newMagazine->magazine.theme = ::Library::MagazineTheme::Science;
			break;
		}
		default: {
			newMagazine->magazine.theme = ::Library::MagazineTheme::Sport;
			break;
		}
	}
	return newMagazine;
}

// Creats new newspaper
Unit* ::Library::CreatNewNewspaper() {
	Unit *newNewspaper = new Unit;
	newNewspaper->bookType = ::Library::BookType::BOOK;

	std::cout << "Edition name: ";
	std::cin.getline(newNewspaper->editionName, ::Library::maxNameLength);
	std::cout << "Language: ";
	std::cin.getline(newNewspaper->language, ::Library::maxNameLength);
	std::cout << "ID: ";
	std::cin >> newNewspaper->id;
	std::cin.get();
	std::cout << "Newspaper number: ";
	std::cin >> newNewspaper->paper.number;
	std::cin.get();

	std::cout << "Date of publish: ";
	char date[20];
	std::cin.getline(date, 20);
	newNewspaper->paper.publishDate = DateFromString(date);

	std::cout << "Choose genre (Sport is default):\n\n";
	::Menu::ShowPaperGenres();

	char choice = toupper(_getch());
	switch (choice) {
		case 'S': {
			newNewspaper->paper.genre = ::Library::PaperGenre::Sport;
			break;
		}
		case 'P': {
			newNewspaper->paper.genre = ::Library::PaperGenre::Politics;
			break;
		}
		case 'F': {
			newNewspaper->paper.genre = ::Library::PaperGenre::Fashion;
			break;
		}
		case 'C': {
			newNewspaper->paper.genre = ::Library::PaperGenre::Celebrities;
			break;
		}
		default: {
			newNewspaper->paper.genre = ::Library::PaperGenre::Sport;
			break;
		}
	}
	return newNewspaper;
}

void ::Library::DeleteUnit(Unit **lib, size_t &size) {
	// Just for convenience
	Unit *library = *lib;

	std::cout << "Enter an ID of unit: ";
	int id;
	std::cin >> id;
	std::cin.get();

	// Find the unit with that ID in the library
	int i;
	for (i = 0; i < size; ++i)
		if (library[i].id == id)
			break;

	// If there is no unit, show error and stop the function
	if (i == size) {
		std::cout << "There is no unit with this ID in the library.\n";
		_getch();
		return;
	}

	// Delete the unit by moving all units after
	for (int j = i; j < size - 1; ++j)
		library[j] = library[j + 1];

	// Decrement the size of container
	--size;

	std::cout << "Deleted.\n";
	_getch();
}

void ::Library::ChangeUnit(Unit **lib, size_t &size) {
	// Just for convenience
	Unit *library = *lib;

	std::cout << "Enter an ID of unit you want to change: ";
	int id;
	std::cin >> id;
	std::cin.get();

	// Find the unit with that ID in the library
	int i;
	for (i = 0; i < size; ++i)
		if (library[i].id == id)
			break;

	// If there is no unit, show error and stop the function
	if (i == size) {
		std::cout << "There is no unit with this ID in the library.\n";
		_getch();
		return;
	}
	std::cout << std::endl;
	// Creat new unit
	Unit *newUnit;
	::Menu::ShowMenuForNewUnit();
	std::cout << std::endl;
	char choice = toupper(_getch());
	switch (choice) {
		case 'B': {
			newUnit = ::Library::CreatNewBook();
			break;
		}
		case 'M': {
			newUnit = ::Library::CreatNewMagazine();
			break;
		}
		case 'P': {
			newUnit = ::Library::CreatNewNewspaper();
			break;
		}
		default: {
			std::cout << "No changing. Back.\n";
			_getch();
			return;
		}
	}

	// Change unit
	library[i] = *newUnit;
	std::cout << "Unit changed.\n";
	_getch();
}

void ::Library::ShowAllUnits(const Unit *library, size_t size) {
	if (!size) {
		std::cout << "There is no elements.\n";
		return;
	}

	for (int i = 0; i < size; ++i) {
		switch (library[i].bookType) {
			case BookType::BOOK: {
				::Library::ShowBook(library[i]);
				break;
			}
			case BookType::MAGAZINE: {
				::Library::ShowMagazine(library[i]);
				break;
			}
			case BookType::NEWSPAPER: {
				::Library::ShowNewspaper(library[i]);
				break;
			}
		}
		std::cout << '\n';
	}
}

void ::Library::ShowBook(const Unit &book) {
	std::cout
		<< "BOOK.\n"
		<< "Edition name: " << book.editionName << '\n'
		<< "ID: " << book.id << '\n'
		<< "Laguage: " << book.language << '\n'
		<< "Author's name: " << book.book.author << '\n'
		<< "Genre: ";
	switch (book.book.genre) {
		case BookGenre::Comedy: {
			std::cout << "Comedy\n";
			break;
		}
		case BookGenre::Drama: {
			std::cout << "Drama\n";
			break;
		}
		case BookGenre::Horror: {
			std::cout << "Horror\n";
			break;
		}
		case BookGenre::RomanceNovel: {
			std::cout << "Romance novel\n";
			break;
		}
		case BookGenre::Tragedy: {
			std::cout << "Tragedy\n";
			break;
		}
	}
	std::cout << "Year of publishing: " << book.book.yearOfPublish << '\n';
}

void ::Library::ShowMagazine(const Unit &magazine) {
	std::cout
		<< "MAGAZINE.\n"
		<< "Edition name: " << magazine.editionName << '\n'
		<< "ID: " << magazine.id << '\n'
		<< "Laguage: " << magazine.language << '\n'
		<< "Theme: ";

	switch (magazine.magazine.theme) {
		case MagazineTheme::Sport: {
			std::cout << "Sport\n";
			break;
		}
		case MagazineTheme::Politics: {
			std::cout << "Politics\n";
			break;
		}
		case MagazineTheme::Science: {
			std::cout << "Science\n";
			break;
		}
		case MagazineTheme::Fashion: {
			std::cout << "Fashion\n";
			break;
		}
	}
	std::cout
		<< "Number: " << magazine.magazine.number << '\n'
		<< "Year of publishing: " << magazine.magazine.yearOfPublish << '\n';
}

void ::Library::ShowNewspaper(const Unit &paper) {
	std::cout
		<< "NEWSPAPER.\n"
		<< "Edition name: " << paper.editionName << '\n'
		<< "ID: " << paper.id << '\n'
		<< "Laguage: " << paper.language << '\n'
		<< "Genre: ";
	switch (paper.paper.genre) {
		case PaperGenre::Sport: {
			std::cout << "Sport\n";
			break;
		}
		case PaperGenre::Celebrities: {
			std::cout << "Celebrities\n";
			break;
		}
		case PaperGenre::Fashion: {
			std::cout << "Fashoin\n";
			break;
		}
		case PaperGenre::Politics: {
			std::cout << "Politics\n";
			break;
		}
	}
	std::cout
		<< "Number: " << paper.paper.number << '\n'
		<< "Date of publishing: ";
	ShowDate(paper.paper.publishDate);
	std::cout << '\n';
}