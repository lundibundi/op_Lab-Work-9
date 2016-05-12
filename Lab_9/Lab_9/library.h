//
// Created by lundibundi on 5/12/16.
//

#ifndef OP_LAB_WORK_9_LIBRARY_H
#define OP_LAB_WORK_9_LIBRARY_H

namespace Library {

    enum class BookGenre { };
    enum class PaperGenre { };
    enum class MagazineTheme { };

    const int maxLength = 100;

    enum class BookType { BOOK, MAGAZINE, NEWSPAPER };

    struct Unit {

        BookType bookType;

        char editionName[maxLength];
        char language[maxLength];
        int id;

        union {
            struct {
                char author[maxLength];
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

    void ReadText(const char *filename);
    void Read(const char *filename);
    void Write(const char *filename, bool newFile = false);
}

#endif //OP_LAB_WORK_9_LIBRARY_H
