//
// Created by lundibundi on 5/12/16.
//

#ifndef OP_LAB_WORK_9_DATE_H
#define OP_LAB_WORK_9_DATE_H

struct Date {
    int day;
    int month;
    int year;
};

Date DateFromString(const char* text);
Date DateFromInt(int num);
void ShowDate(const Date &date);

#endif //OP_LAB_WORK_9_DATE_H
