#include "reminder.h"
#include "interact.h"
#include <signal.h>

int main() {
    // Set up signal handling
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);
    signal(SIGSEGV, handle_signal);

    // Initialize the month structure
    initialize_month();

    // Load reminders from file
    load_reminders_from_file("reminders.txt");

    char reminder[MAX_STR_LEN];
    // Initialize an infinite loop
    while (1) {
        // Call the read_reminder function to get the day number and the reminder
        int day = read_reminder(reminder, MAX_STR_LEN);     // Prompt is handled inside `read_reminder`
        
        if (day == 0) break;    // End program once user inputs 0
        if (day > 0) {
            // Add valid reminders to calendar
            insert_to_calendar(day, reminder);
            print_calendar();
        }
    }

    // Save reminders to file
    save_reminders_to_file("reminders.txt");
    return 0;
}
