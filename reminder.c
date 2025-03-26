#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "reminder.h"
#include "interact.h"

// Global variable for the month structure
Month month;

/*
Purpose: Initializes the current month's details, including start day and total days in the month
Parameters: None
Return Value: None (void)
*/
void initialize_month(void) {
    time_t now = time(NULL);
    struct tm t = *localtime(&now);

    month.month_idx = t.tm_mon;

    t.tm_mday = 1;
    mktime(&t);
    month.start_day = t.tm_wday + 1;

    month.month_days = 0;
    while (t.tm_mon == month.month_idx) {
        month.month_days++;
        t.tm_mday++;
        mktime(&t);
    }
}

/*
Purpose: Adds a reminder to the calendar for a specified day if the day is within the valid range
Parameters: The day of the month for the reminder (day), and the text of the reminder (reminder)
Return Value: None (void)
*/
void insert_to_calendar(int day, const char* reminder) {
    // Add the reminder if the day is valid
    if (day >= 1 && day <= month.month_days) {
        add_node(&month.reminders[day - 1], reminder);  // Add a node to the linked list for the day
    // Print an error message if user input not within range
    } else {
        printf("Invalid day: The day must be >= 1 and <= %d days\n", month.month_days);
    }
}

/*
Purpose: Prints the calendar for the month, marking days with reminders in parentheses and listing reminders at the end
Parameters: None
Return Value: None (void)
*/
void print_calendar() {
    // Define the names of weekdays and months
    const char* WEEK_DAYS[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    const char* MONTH_NAMES[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    // Print the weekday header
    printf("\n Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

    // Print initial spaces for the first week
    int day = month.start_day;
    for (int i = 1; i < day; i++) {
        printf("     ");
    }

    // Print days of the month
    for (int i = 1; i <= month.month_days; i++) {
        if (month.reminders[i - 1]) {
            printf("(%2d) ", i);   // Print the day with parentheses if it contains a reminder
        } else {
            printf(" %2d  ", i);   // Otherwise just print the number if contains no reminder
        }

        // Move to the next line after
        if ((i + day - 1) % 7 == 0) {
            printf("\n");
        }
    }

    // Print reminders for each day
    printf("\n\n%s reminders:\n", MONTH_NAMES[month.month_idx]);
    for (int i = 0; i < month.month_days; i++) {
        if (month.reminders[i]) {
            int weekday = (month.start_day + i - 1) % 7;
            printf("%s %d: ", WEEK_DAYS[weekday], i + 1);

            Node* reversed = NULL;
            Node* current = month.reminders[i];

            // Reverse the linked list for display
            while (current) {
                Node* next = current->next;
                current->next = reversed;
                reversed = current;
                current = next;
            }

            // Print the reversed list
            int count = 1;
            Node* temp = reversed;
            while (temp) {
                printf("\n(%d) %s", count++, temp->reminder);
                temp = temp->next;
            }

            // Restore the original order
            current = reversed;
            reversed = NULL;
            while (current) {
                Node* next = current->next;
                current->next = reversed;
                reversed = current;
                current = next;
            }

            printf("\n");
        }
    }

    printf("\n------------------------\n");
}

/*
Purpose: Handles termination signals (SIGINT and SIGTERM), saves reminders to a file, and exits the program gracefully
Parameters: sig: The signal received (sig)
Return Value: None (void)
*/
void handle_signal(int sig) {
    save_reminders_to_file("reminders.txt");    // Save all reminders to a file

    // Print an appropriate message based on the signal received
    if (sig == SIGINT) {
        printf("\nProgram interrupted...");
    } else {
        printf("\nProgram terminated...");
    }

    printf("\nWriting to file...\n");
    exit(0);
}
