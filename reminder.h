#ifndef REMINDER_H
#define REMINDER_H

#include "linked_list.h"
#include <time.h>

// Structure for storing month details and reminders
typedef struct Month {
    int month_days;
    int start_day;
    int month_idx;
    Node* reminders[31];         // Array of linked lists for reminders
} Month;

extern Month month;

// Calendar and reminder management
void initialize_month(void);
void insert_to_calendar(int day, const char* reminder);
void print_calendar(void);
void handle_signal(int sig);

#endif
