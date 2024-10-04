/* MINI CALENDAR */
//TYNIP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EVENTS 100

// Structure to hold events
typedef struct {
    int day;
    int month;
    int year;
    char description[50];
    char time[6]; // format: HH:MM
} Event;

Event events[MAX_EVENTS];
int event_count = 0;

// Check if a year is a leap year
int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Get the number of days in a month
int get_days_in_month(int month, int year) {
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && is_leap_year(year)) return 29;
    return days_in_month[month - 1];
}

// Add days to a date
void add_days_to_date(int *day, int *month, int *year, int days_to_add) {
    while (days_to_add > 0) {
        int days_in_month = get_days_in_month(*month, *year);
        if (*day + days_to_add <= days_in_month) {
            *day += days_to_add;
            days_to_add = 0;
        } else {
            days_to_add -= (days_in_month - *day + 1);
            *day = 1;
            (*month)++;
            if (*month > 12) {
                *month = 1;
                (*year)++;
            }
        }
    }
}

// Add an event
void add_event() {
    if (event_count >= MAX_EVENTS) {
        printf("Event limit reached.\n");
        return;
    }
    int day, month, year;
    printf("Enter event date (dd mm yyyy): ");
    scanf("%d %d %d", &day, &month, &year);
    if (day < 1 || day > get_days_in_month(month, year) || month < 1 || month > 12) {
        printf("Invalid date.\n");
        return;
    }
    printf("Enter event description: ");
    scanf(" %[^\n]", events[event_count].description);
    printf("Enter event time (HH:MM): ");
    scanf("%s", events[event_count].time);

    events[event_count].day = day;
    events[event_count].month = month;
    events[event_count].year = year;
    event_count++;
    printf("Event added successfully!\n");
}

// Modify an event
void modify_event() {
    int day, month, year;
    char description[50];
    printf("Enter event date to modify (dd mm yyyy): ");
    scanf("%d %d %d", &day, &month, &year);
    for (int i = 0; i < event_count; i++) {
        if (events[i].day == day && events[i].month == month && events[i].year == year) {
            printf("Enter new description: ");
            scanf(" %[^\n]", events[i].description);
            printf("Enter new time (HH:MM): ");
            scanf("%s", events[i].time);
            printf("Event modified successfully!\n");
            return;
        }
    }
    printf("Event not found.\n");
}

// View the calendar and events
void view_calendar(int year) {
    int days_in_month;
    printf("\nCalendar for Year %d\n", year);
    for (int month = 1; month <= 12; month++) {
        days_in_month = get_days_in_month(month, year);
        printf("\nMonth %d:\n", month);
        for (int day = 1; day <= days_in_month; day++) {
            printf("%02d-%02d-%d", day, month, year);
            for (int i = 0; i < event_count; i++) {
                if (events[i].day == day && events[i].month == month && events[i].year == year) {
                    printf(" - %s at %s", events[i].description, events[i].time);
                }
            }
            printf("\n");
        }
    }
}

// Main menu function
void main_menu() {
    char choice;
    int year;
    while (1) {
        printf("\n--- Menu ---\n");
        printf("a) Check if a year is a leap year\n");
        printf("b) Add days to a date\n");
        printf("c) Add an event\n");
        printf("d) Modify an event\n");
        printf("e) View calendar with events\n");
        printf("x) Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case 'a': {
                printf("Enter a year: ");
                scanf("%d", &year);
                if (is_leap_year(year)) printf("%d is a leap year.\n", year);
                else printf("%d is not a leap year.\n", year);
                break;
            }
            case 'b': {
                int day, month, year, days_to_add;
                printf("Enter the start date (dd mm yyyy): ");
                scanf("%d %d %d", &day, &month, &year);
                printf("Enter the number of days to add: ");
                scanf("%d", &days_to_add);
                add_days_to_date(&day, &month, &year, days_to_add);
                printf("New date: %02d-%02d-%d\n", day, month, year);
                break;
            }
            case 'c': 
                add_event();
                break;
            case 'd': 
                modify_event();
                break;
            case 'e': 
                printf("Enter the year to view: ");
                scanf("%d", &year);
                view_calendar(year);
                break;
            case 'x': 
                printf("Thank you for using the mini Calendar! Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

int main() {
    main_menu();
    return 0;
}
