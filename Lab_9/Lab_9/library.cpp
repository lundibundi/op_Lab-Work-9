//
// Created by lundibundi on 5/12/16.
//

#include "library.h"
#include <stdio.h>
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
        return;
    }

    char line[2048]{0};
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
        return;
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

