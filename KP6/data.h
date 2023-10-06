#ifndef DATA
#define DATA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#define MAX_LEN 256
#define STAT_LEN 64

#define MAX_STUDENTS 50


typedef struct student {
    char* name;
    int cpu_num;
    char* cpu_type;
    int mem;
    char* gpu;
    int gpu_mem;
    int hdd_num;
    char* hdds;
    int devices;
    char* os;
} student;

student* create_student();

void free_student(student* s);

int student_read_txt(student* s, FILE* fd);

int student_write_txt(student* s, FILE* fd);

int student_read_bin(student* s, FILE* fd);

int student_write_bin(student* s, FILE* fd);

void print_student(student* s);

void print_studlist(student** sl, int len);

// Function to find students with a given name in a list
student** find_student(char* name, student** list, int list_len);

// Function to compare two CPU types and return 0 if the first is better, 1 otherwise
int cmp_cpu(char* a, char* b);

// Function to compare two GPU types and return 0 if the first is better, 1 otherwise
int cmp_gpu(char* a, char* b);

// Function to compare two HDD types and return 0 if the first is better, 1 otherwise
int cmp_hdd(char* a, char* b);

// Function to compare two operating systems and return 0 if the first is better, 1 otherwise
int cmp_os(char* a, char* b);

// Function to compare computers based on their components and return the best one
student* cmp_computers(student* list[]);


#endif