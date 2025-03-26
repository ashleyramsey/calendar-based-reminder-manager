#include "interact.h"

int read_reminder(char* str, int n) {
    int day;

    while (1) { // Loop until valid input is provided
        printf("Enter day and reminder (0 to quit): ");

        if (scanf("%d", &day) != 1 || day == 0) return 0;

        if (day >= 1 && day <= month.month_days) {
            getchar(); // Consume newline character left by scanf
            fgets(str, n, stdin);
            str[strcspn(str, "\n")] = '\0'; // Remove the newline character
            return day;
        }

        // If input is invalid, notify the user and prompt again
        printf("Invalid day: The day must be >= 1 and <= %d days\n", month.month_days);
        while (getchar() != '\n'); // Clear the input buffer
    }
}

void load_reminders_from_file(const char* filename) {
    FILE* file = fopen(filename, "r"); 
    if (!file) {
        return;
    }

    int day;
    char reminder[MAX_STR_LEN];
    while (fscanf(file, "%d|%[^\n]", &day, reminder) == 2) {
        insert_to_calendar(day, reminder);
    }
    fclose(file);
    // printf("Reminders loaded from %s.\n", filename);
}

void save_reminders_to_file(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Error saving reminders");
        return;
    }

    for (int i = 0; i < month.month_days; i++) {
        if (month.reminders[i]) {
            Node* temp = month.reminders[i];
            while (temp) {
                fprintf(file, "%d|%s\n", i + 1, temp->reminder);
                temp = temp->next;
            }
        }
    }
    fclose(file);
}
