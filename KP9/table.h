#ifndef TABLE
#define TABLE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 250
#define LIST_SIZE 20

typedef struct elem {
    long long key;
    char* line;
} elem;

typedef enum {
    NOT,
    UP,
    DOWN,
} sorting;

typedef struct table {
    int size;
    elem** list;
    sorting sorting;
} table;

table* read_table(FILE* fd);

elem* create_elem(long long key, char* line);

elem* search(table* t, long long key);

void swap(elem** a, elem** b);

void sort(table* t);

void print_table(table* t);

void free_elem(elem* e);

void free_table(table* t);

#endif
