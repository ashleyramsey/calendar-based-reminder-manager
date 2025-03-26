#ifndef INTERACT_H
#define INTERACT_H

#include "reminder.h"

// Functions for interacting with the user and managing input/output
int read_reminder(char* str, int n);
void load_reminders_from_file(const char* filename);
void save_reminders_to_file(const char* filename);

#endif
