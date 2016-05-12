//
// Created by lundibundi on 5/12/16.
//

#ifndef OP_LAB_WORK_9_LIBRARY_H
#define OP_LAB_WORK_9_LIBRARY_H

#include <cstddef>
#include "date.h"

namespace Library {

    enum class BookGenre { };
    enum class PaperGenre { };
    enum class MagazineTheme { };

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
}

#endif //OP_LAB_WORK_9_LIBRARY_H
