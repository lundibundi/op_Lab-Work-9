//
// Created by lundibundi on 5/12/16.
//

#ifndef OP_LAB_WORK_9_LIBRARY_H
#define OP_LAB_WORK_9_LIBRARY_H

#include <cstddef>
#include "date.h"

namespace Library {

    enum class BookGenre { Comedy, Drama, RomanceNovel, Tragedy, Horror };
    enum class PaperGenre { Sport, Politics, Fashion, Celebrities };
    enum class MagazineTheme { Sport, Politics, Fashion, Science };

    const int maxNameLength = 100;

    enum class BookType { BOOK, MAGAZINE, NEWSPAPER };

    struct Unit {

        BookType bookType;

        char editionName[maxNameLength];
        char language[maxNameLength];
        int id;

        union {
            struct {
                char author[maxNameLength];
                unsigned int yearOfPublish;
                BookGenre genre;
            } book;
            struct {
                unsigned int number;
                unsigned int yearOfPublish;
                MagazineTheme theme;
            } magazine;
            struct {
                unsigned int number;
                Date publishDate;
                PaperGenre genre;
            } paper;
        };
    };

    void ReadFromText(const char *filename, Unit **lib, size_t &size);
    void Read(const char *filename, Unit **lib, size_t &size);
    void Write(const char *filename, Unit *lib, size_t size, bool newFile = false);

	void AddNewUnit(Unit &unit, Unit **lib, size_t &size);
	Unit* CreatNewBook();
	Unit* CreatNewMagazine();
	Unit* CreatNewNewspaper();

	void DeleteUnit(Unit **lib, size_t &size);

	void ChangeUnit(Unit **lib, size_t &size);
}

#endif //OP_LAB_WORK_9_LIBRARY_H
