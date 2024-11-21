/**
 * Date:       20 November 2024
 * File:       dsaproject.c
 * Authors:    Samra Abdullayeva, Fidan Allahverdiyeva, Martian
 * Purpose:    Implement the functions given in the final project 
 *             instructions.
 */


#include "../include/dsaproject.h"

/**
 * Exercise 1: Create a student for the exam.
 * Allocates memory for a new student, takes input for their details, and creates the student structure.
 * @return Pointer to the created student.
 */
T_Student* create_student() {
    T_Student* new_student = (T_Student*)malloc(sizeof(T_Student));
    if (!new_student) {
        // Print error message
        perror("Memory allocation failed");
        return NULL;
    }
    printf("Enter name: ");
    scanf(" %49[^\n]", new_student->name);
    printf("Enter student ID: ");
    scanf("%ld", &new_student->id_num);
    printf("Enter grade: ");
    scanf("%f", &new_student->grade);
    new_student->next = NULL;
    return new_student;
}

/**
 * Exercise 2: Display the list of students.
 * Traverses the linked list and prints each student's details.
 * @param head Pointer to the first student in the list.
 */
void display_list(T_Student* head) {
    if (!head) {
        printf(RED "The list is empty.\n" RESET);
        return;
    }

    // Header
    printf(CYAN "\nStudent List:\n" RESET);
    printf(BOLD "+-------------------------+---------------------+--------+\n" RESET);
    printf(BOLD "| %-23s | %-19s | %-6s |\n" RESET, "Name", "ID", "Grade");
    printf(BOLD "+-------------------------+---------------------+--------+\n" RESET);

    // Rows
    while (head) {
        // Print grades with conditional coloring
        char* grade_color = head->grade >= 65 ? GREEN : (head->grade >= 50 ? YELLOW : RED);

        printf("| %-23s | %-19ld | %s%6.2f%s |\n",
               head->name,
               head->id_num,
               grade_color,
               head->grade,
               RESET);

        head = head->next;
    }

    // Footer
    printf(BOLD "+-------------------------+---------------------+--------+\n" RESET);
    
}


/**
 * Exercise 3: Add a new student to the list.
 * Appends a student to the end of the list.
 * @param head Pointer to the head of the list.
 * @param name Name of the student.
 * @param id_num Student ID.
 * @param grade Grade of the student.
 * @return Updated head of the list.
 */
T_Student* add_student(T_Student* head, char name[], long id_num, float grade) {
    T_Student* new_student = (T_Student*)malloc(sizeof(T_Student));
    if (!new_student) {
        // Print error message
        perror("Memory allocation failed");
        return head;
    }
    strcpy(new_student->name, name);
    new_student->id_num = id_num;
    new_student->grade = grade;
    new_student->next = NULL;

    if (!head) return new_student;

    T_Student* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = new_student;
    return head;
}

/**
 * Exercise 4: Count the number of students in the list.
 * @param head Pointer to the head of the list.
 * @return Number of students.
 */
int student_count(T_Student* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

/**
 * Exercise 5: Find a student by their ID.
 * Searches the list for a student and displays their details.
 * @param head Pointer to the head of the list.
 * @param id_num Student ID to search for.
 * @return 1 if found, 0 otherwise.
 */
int find_student(T_Student* head, long id_num) {
    while (head) {
        if (head->id_num == id_num) {
            printf("%sStudent Found:\nName: %s, ID: %ld, Grade: %.2f%s\n",
                   GREEN,head->name, head->id_num, head->grade, RESET);
            return 1;
        }
        head = head->next;
    }
    printf("Student with ID %ld %snot found.%s\n", id_num, RED, RESET);
    return 0;
}

/**
 * Exercise 6: Delete the last student from the list.
 * Removes the last node of the list.
 * @param head Double pointer to the head of the list.
 */
void delete_last_student(T_Student** head) {
    if (!*head) {
        printf("The list is empty.\n");
        return;
    }
    if (!(*head)->next) {
        free(*head);
        *head = NULL;
        return;
    }
    T_Student* temp = *head;
    while (temp->next->next) temp = temp->next;
    free(temp->next);
    temp->next = NULL;
}


/////////////////////
/**
 * Exercise 7: Sort the list by grade.
 * Splits a linked list into two halves.
 * @param head Pointer to the head of the list.
 * @param front_ref Pointer to store the first half.
 * @param back_ref Pointer to store the second half.
 */
void split_linked_list(T_Student* head, T_Student** front_ref, T_Student** back_ref) {
    T_Student* slow = head;
    T_Student* fast = head->next;

    // Use the fast/slow pointer strategy to find the middle of the list
    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // Split the list into two halves
    *front_ref = head;
    *back_ref = slow->next;
    slow->next = NULL;
}

/**
 * Merges two sorted linked lists into one sorted list.
 * @param a Pointer to the first sorted list.
 * @param b Pointer to the second sorted list.
 * @return Pointer to the merged sorted list.
 */
T_Student* merge_sorted_lists(T_Student* a, T_Student* b) {
    if (!a) return b;
    if (!b) return a;

    T_Student* result = NULL;

    if (a->grade <= b->grade) {
        result = a;
        result->next = merge_sorted_lists(a->next, b);
    } else {
        result = b;
        result->next = merge_sorted_lists(a, b->next);
    }
    return result;
}

/**
 * Sorts a linked list using merge sort.
 * @param head_ref Pointer to the head of the list.
 */
void sort_list(T_Student** head_ref) {
    T_Student* head = *head_ref;
    if (!head || !head->next) return; // Base case: list is empty or has one element

    T_Student* a;
    T_Student* b;

    // Split the list into two halves
    split_linked_list(head, &a, &b);

    // Recursively sort the two halves
    sort_list(&a);
    sort_list(&b);

    // Merge the sorted halves
    *head_ref = merge_sorted_lists(a, b);
}
////////////////////////////////////////

/**
 * Exercise 8: Calculate the exam average.
 * Also prints an interpretation of the average.
 * @param head Pointer to the head of the list.
 * @return Average grade.
 */
float average_exam(T_Student* head) {
    if (!head) {
        printf(RED "No students in the list.\n" RESET);
        return 0.0;
    }

    float sum = 0.0;
    int count = 0;

    // Traverse the list to calculate the sum and count
    while (head) {
        sum += head->grade;
        count++;
        head = head->next;
    }

    // Calculate the average
    float avg = sum / count;

    // Print the average with colored performance interpretation
    printf(CYAN "Exam Average: %.2f - " RESET, avg);

    if (avg > 65)
        printf(GREEN "High performance.\n" RESET);
    else if (avg >= 50)
        printf(YELLOW "Moderate performance.\n" RESET);
    else
        printf(RED "Low performance.\n" RESET);

    return avg;
}

/**
 * Exercise 9: Free the entire list.
 * @param head Pointer to the head of the list.
 */
void free_list(T_Student* head) {
    T_Student* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

/**
 * Exercise 10: Split the list into two sub-lists.
 * Divides the list into high-level and low-level lists based on grades.
 * @param head Original list.
 * @param high Pointer to the high-level list.
 * @param low Pointer to the low-level list.
 */
void split_list(T_Student* head, T_Student** high, T_Student** low) {
    while (head) {
        if (head->grade >= 65)
            *high = add_student(*high, head->name, head->id_num, head->grade);
        else
            *low = add_student(*low, head->name, head->id_num, head->grade);
        head = head->next;
    }
}

/**
 * Exercise 11: Merge two lists.
 * Combines high-level and low-level lists into one list.
 * @param high High-level list.
 * @param low Low-level list.
 * @return Merged list.
 */
T_Student* merge_lists(T_Student* high, T_Student* low) {
    T_Student temp = {.next = NULL};
    T_Student* current = &temp;

    while (high && low) {
        if (high->grade < low->grade) {
            current->next = high;
            high = high->next;
        } else {
            current->next = low;
            low = low->next;
        }
        current = current->next;
    }
    current->next = high ? high : low;
    return temp.next;
}




// Extras


void print_intro(){
    printf("%s","\n\n");
    printf("%s  ███████╗██╗  ██╗ █████╗ ███╗   ███╗ ██████╗ ██████╗  %s\n",BOLD GREEN,RESET);
    printf("%s  ██╔════╝╚██╗██╔╝██╔══██╗████╗ ████║██╔═══██╗██╔══██╗ %s\n",BOLD GREEN,RESET);
    printf("%s  █████╗   ╚███╔╝ ███████║██╔████╔██║██║   ██║██████╔╝ %s\n",BOLD GREEN,RESET);
    printf("%s  ██╔══╝   ██╔██╗ ██╔══██║██║╚██╔╝██║██║   ██║██╔══██╗ %s\n",BOLD GREEN,RESET);
    printf("%s  ███████╗██╔╝ ██╗██║  ██║██║ ╚═╝ ██║╚██████╔╝██║  ██║ %s\n",BOLD GREEN,RESET);
    printf("%s  ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝     ╚═╝ ╚═════╝ ╚═╝  ╚═╝ %s\n",BOLD GREEN,RESET);
    printf(BOLD "      =========================================\n" RESET);
    printf("      %s=%s Welcome to the Exam Management System %s%s=%s\n",BOLD,BOLD CYAN,RESET, BOLD,RESET);
    printf(BOLD "      =========================================\n" RESET);
    printf("            %sVersion: %s%s\n", CYAN, VERSION, RESET);
}


/**
 * Saves the linked list to a file.
 * @param head Pointer to the head of the list.
 * @param filename Name of the file to save the list to.
 */
void save_list(T_Student* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file for saving");
        return;
    }

    while (head) {
        fprintf(file, "%s %ld %.2f\n", head->name, head->id_num, head->grade);
        head = head->next;
    }

    fclose(file);
    printf(GREEN "List successfully saved to '%s'.\n" RESET, filename);
}

/**
 * Loads a linked list from a file.
 * @param head_ref Pointer to the head of the list (modified to reflect the loaded list).
 * @param filename Name of the file to load the list from.
 */
void load_list(T_Student** head_ref, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file.");
        return;
    }

    // Free the current list if it exists
    free_list(*head_ref);
    *head_ref = NULL;

    char name[50];
    long id_num;
    float grade;

    // Read the file and add students to the list
    while (fscanf(file, "%49s %ld %f", name, &id_num, &grade) == 3) {
        *head_ref = add_student(*head_ref, name, id_num, grade);
    }

    fclose(file);
    printf(GREEN "List successfully loaded from '%s'.\n" RESET, filename);
}

/**
 * Deletes a student from the list by their ID.
 * @param head_ref Pointer to the head of the list.
 * @param id Student ID to delete.
 */
void delete_student(T_Student** head_ref, long id) {
    if (!*head_ref) {
        printf(RED "The list is empty.\n" RESET);
        return;
    }

    T_Student* temp = *head_ref;
    T_Student* prev = NULL;

    // Check if the head node is the one to delete
    if (temp && temp->id_num == id) {
        *head_ref = temp->next;
        free(temp);
        printf(GREEN "Student with ID %ld has been deleted.\n" RESET, id);
        return;
    }

    // Traverse the list to find the node to delete
    while (temp && temp->id_num != id) {
        prev = temp;
        temp = temp->next;
    }

    // If the student was not found
    if (!temp) {
        printf(RED "Student with ID %ld not found.\n" RESET, id);
        return;
    }

    // Unlink the node and free memory
    prev->next = temp->next;
    free(temp);
    printf(GREEN "Student with ID %ld has been deleted.\n" RESET, id);
}


/**
 * Updates a student's details by their ID.
 * @param head Pointer to the head of the list.
 * @param id Student ID to update.
 */
void update_student(T_Student* head, long id) {
    if (!head) {
        printf(RED "The list is empty. Cannot update.\n" RESET);
        return;
    }

    T_Student* current = head;

    // Search for the student by ID
    while (current) {
        if (current->id_num == id) {
            printf(GREEN "Student found:\n" RESET);
            printf("Name: %s, ID: %ld, Grade: %.2f\n", current->name, current->id_num, current->grade);

            int choice;
            printf("\nWhat would you like to update?\n");
            printf("1. Name\n");
            printf("2. ID\n");
            printf("3. Grade\n");
            printf("4. All fields\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Enter new name: ");
                    scanf(" %49[^\n]", current->name);
                    printf(GREEN "Name updated successfully.\n" RESET);
                    break;
                case 2:
                    printf("Enter new ID: ");
                    scanf("%ld", &current->id_num);
                    printf(GREEN "ID updated successfully.\n" RESET);
                    break;
                case 3:
                    printf("Enter new grade: ");
                    scanf("%f", &current->grade);
                    printf(GREEN "Grade updated successfully.\n" RESET);
                    break;
                case 4:
                    printf("Enter new name: ");
                    scanf(" %49[^\n]", current->name);
                    printf("Enter new ID: ");
                    scanf("%ld", &current->id_num);
                    printf("Enter new grade: ");
                    scanf("%f", &current->grade);
                    printf(GREEN "All fields updated successfully.\n" RESET);
                    break;
                default:
                    printf(RED "Invalid choice. No updates made.\n" RESET);
            }
            return;
        }
        current = current->next;
    }

    printf(RED "Student with ID %ld not found.\n" RESET, id);
}
