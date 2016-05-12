//
// Created by lundibundi on 5/12/16.
//

#include <stdio.h>
#include "date.h"

Date DateFromString(const char* text) {
    Date date{};
    sscanf(text, "%d %d %d", &date.day, &date.month, &date.year);
    return date;
}

Date DateFromInt(int num) {
    Date date{};
    date.year = num % 10000;
    num /= 10000;
    date.month = num % 100;
    num /= 100;
    date.day = num % 100;
    return date;
}
