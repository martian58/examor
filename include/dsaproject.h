#ifndef DSAPROJECT_H
#define DSAPROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ANSI color codes for colorful prints.
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"

// Version
#define VERSION  "1.3"

// Structure for student
typedef struct student {
    char name[50];
    long id_num;
    float grade;
    struct student *next;
} T_Student;

// Function prototypes
T_Student* create_student(void);
void display_list(T_Student*);
T_Student* add_student(T_Student*, char[], long, float);
int student_count(T_Student*);
int find_student(T_Student*, long);
void delete_last_student(T_Student**);
void sort_list(T_Student**);
float average_exam(T_Student*);
void free_list(T_Student*);
void split_list(T_Student*, T_Student**, T_Student**);
T_Student* merge_lists(T_Student*, T_Student*);
void split_linked_list(T_Student* head, T_Student** front_ref, T_Student** back_ref);
T_Student* merge_sorted_lists(T_Student* a, T_Student* b);
void print_intro();
void save_list(T_Student* head, const char* filename);
void load_list(T_Student** head_ref, const char* filename);
void delete_student(T_Student** head_ref, long id);
void update_student(T_Student* head, long id);
#endif
