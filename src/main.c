/**
 * Date:       20 November 2024
 * File:       main.c
 * Authors:    Samra Abdullayeva, Fidan Alizada, Martian 
 * Purpose:    Implement the main menu for the application. 
 */

#include <stdlib.h>
#include "../include/dsaproject.h"


// Clear screen function
void clear_screen() {
    #ifdef _WIN32
        system("cls"); 
    #else
        system("clear"); 
    #endif
}

void menu_mode(T_Student** list);
void command_line_mode(T_Student** list);

int main() {
    T_Student* list = NULL;
    int choice;
    clear_screen();
    print_intro();

    while (1) {
        printf(BLUE "\nMain Menu:\n" RESET);
        printf(GREEN "1. Use menu interface\n" RESET);
        printf(GREEN "2. Use command-line interface\n" RESET);
        printf(GREEN "3. Clear Screen\n" RESET);
        printf(GREEN "4. Exit\n" RESET);
        printf(YELLOW "Enter your choice: " RESET);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                clear_screen();
                menu_mode(&list);
                break;
            case 2:
                command_line_mode(&list);
                break;
            case 3:
                clear_screen();
                break;
            case 4:
                printf(BOLD MAGENTA "Exiting the program...\n" RESET);
                free_list(list);
                return 0;
            default:
                printf(RED "Invalid choice! Please try again.\n" RESET);
        }
    }
    return 0;
}

/**
 * Menu interface.
 * Provides options as a menu for users to select actions.
 */
void menu_mode(T_Student** list) {
    int option;
    long id;
    char name[50];
    float grade;

    while (1) {
        printf(BLUE "\nMenu Interface:\n" RESET);
        printf(GREEN "1. Enter students\n" RESET);
        printf(GREEN "2. Add a new student\n" RESET);
        printf(GREEN "3. Search for a student\n" RESET);
        printf(GREEN "4. Display student list\n" RESET);
        printf(GREEN "5. Sort the list by grade\n" RESET);
        printf(GREEN "6. Split and merge lists by grade\n" RESET);
        printf(GREEN "7. Calculate exam average\n" RESET);
        printf(GREEN "8. Clear screen\n" RESET);
        printf(GREEN "9. Free list\n" RESET);
        printf(GREEN "10. Go back to main menu\n" RESET);
        printf(YELLOW "Enter your option: " RESET);
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf(CYAN "How many students would you like to add? " RESET);
                int count;
                scanf("%d", &count);
                for (int i = 0; i < count; i++) {
                    T_Student* new_student = create_student();
                    if (new_student) *list = add_student(*list, new_student->name, new_student->id_num, new_student->grade);
                    free(new_student);
                }
                break;

            case 2:
                printf(CYAN "Enter student details:\n" RESET);
                printf(YELLOW "Name: " RESET);
                scanf(" %49[^\n]", name);
                printf(YELLOW "Student ID: " RESET);
                scanf("%ld", &id);
                printf(YELLOW "Grade: " RESET);
                scanf("%f", &grade);
                *list = add_student(*list, name, id, grade);
                break;

            case 3:
                printf(CYAN "Enter student ID to search: " RESET);
                scanf("%ld", &id);
                find_student(*list, id);
                break;

            case 4:
                display_list(*list);
                break;

            case 5:
                sort_list(list);
                printf(GREEN "List sorted by grades.\n" RESET);
                break;

            case 6: {
                T_Student* high = NULL;
                T_Student* low = NULL;
                split_list(*list, &high, &low);

                printf(BOLD BLUE "High-Level List:\n" RESET);
                display_list(high);
                printf(BOLD BLUE "Low-Level List:\n" RESET);
                display_list(low);

                printf(CYAN "Merging sorted lists...\n" RESET);
                sort_list(&high);
                sort_list(&low);
                *list = merge_lists(high, low);

                printf(GREEN "Merged Sorted List:\n" RESET);
                display_list(*list);
                break;
            }

            case 7:
                average_exam(*list);
                break;

            case 8:
                clear_screen();
                break;

            case 9:
                free_list(*list);
                *list = NULL;
                printf(MAGENTA "List has been freed.\n" RESET);
                break;

            case 10:
            clear_screen();
                return;

            default:
                printf(RED "Invalid option! Please try again.\n" RESET);
        }
    }
}

/**
 * Command-line interface.
 * Allows to interact with the program by typing commands.
 */
void command_line_mode(T_Student** list) {
    char command[50];
    long id;
    char name[50];
    float grade;
    char filename[100];

    printf(BOLD CYAN "\nEntering Command-Line Input Mode:\n" RESET);
    printf(MAGENTA "Type 'help' to see available commands or 'exit' to return to the main menu.\n" RESET);

    while (1) {
        printf(YELLOW "\n>> " RESET);
        scanf("%s", command);

        if (strcmp(command, "help") == 0) {
            printf(BOLD "Available Commands:\n\n" RESET);
            printf(GREEN "  add         -   Add a new student (Usage: add name id grade)\n" RESET);
            printf(GREEN "  find        -   Find a student by ID (Usage: find id)\n" RESET);
            printf(GREEN "  display     -   Display all students\n" RESET);
            printf(GREEN "  sort        -   Sort students by grade\n" RESET);
            printf(GREEN "  average     -   Calculate and display exam average\n" RESET);
            printf(GREEN "  delete_last -   Remove the last student from the list\n" RESET);
            printf(GREEN "  split_merge -   Split and merge students by grades\n" RESET);
            printf(GREEN "  save        -   Save the current list to a file(Usage: save filename.txt)\n" RESET);
            printf(GREEN "  load        -   Load a list from a file(Usage: load filename.txt)\n" RESET);
            printf(GREEN "  free        -   Free the entire list\n" RESET);
            printf(GREEN "  delete      -   Delete a student by ID\n" RESET);
            printf(GREEN "  update      -   Update a student by ID\n" RESET);
            printf(GREEN "  clear       -   Clear the screen\n" RESET);
            printf(GREEN "  exit        -   Return to the main menu\n" RESET);
            printf(GREEN "  fun         -   Display fun animation :)\n" RESET);

        } else if (strcmp(command, "clear") == 0) {
            clear_screen();
        } else if (strcmp(command, "add") == 0) {
            scanf("%s %ld %f", name, &id, &grade);
            *list = add_student(*list, name, id, grade);
            printf(GREEN "Student added successfully.\n" RESET);
        } else if (strcmp(command, "find") == 0) {
            scanf("%ld", &id);
            find_student(*list, id);
        } else if (strcmp(command, "display") == 0) {
            display_list(*list);
        } else if (strcmp(command, "sort") == 0) {
            sort_list(list);
            printf(GREEN "List sorted by grades.\n" RESET);
        } else if (strcmp(command, "average") == 0) {
            average_exam(*list);
        } else if (strcmp(command, "delete_last") == 0) {
            delete_last_student(list);
            printf(MAGENTA "Last student removed.\n" RESET);
        } else if (strcmp(command, "delete") == 0) {
            scanf("%ld", &id);
            delete_student(list, id);
        } else if (strcmp(command, "update") == 0) {
            scanf("%ld", &id);
            update_student(*list, id);
        } else if (strcmp(command, "split_merge") == 0) {
            T_Student* high = NULL;
            T_Student* low = NULL;
            split_list(*list, &high, &low);

            printf(BLUE "High-Level List:\n" RESET);
            display_list(high);
            printf(BLUE "Low-Level List:\n" RESET);
            display_list(low);

            *list = merge_lists(high, low);
            printf(GREEN "Lists merged successfully.\n" RESET);
        } else if (strcmp(command, "free") == 0) {
            free_list(*list);
            *list = NULL;
            printf(MAGENTA "List has been freed.\n" RESET);
        } else if (strcmp(command, "fun") == 0) {
            system("python3 test/rick.py");
        } else if (strcmp(command, "ls") == 0) {
            printf("%s", "This is not a terminal broo -_-\n");

        } else if (strcmp(command, "save") == 0) {
            scanf("%s", filename);
            save_list(*list, filename);
        } else if (strcmp(command, "load") == 0) {
            scanf("%s", filename);
            load_list(list, filename);
        } else if (strcmp(command, "exit") == 0) {
            printf(BOLD CYAN "Exiting Command-Line Input Mode...\n" RESET);
            break;
        } else {
            printf(RED "Invalid command. Type 'help' for a list of commands.\n" RESET);
        }
    }
}
