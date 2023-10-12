#ifndef SPISOK
#define SPISOK

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    double value;
    struct node* next;
} node;

typedef struct list {
    int size;
    struct node* root;
} list;

// Инициализация пустого списка
list* create_list();

// Добавление элемента в конец списка
void append(list* l, double value);

// Удаление элемента по индексу
void remove_node(list* l, int idx);

// Длина списка
int length(const list* l);

// Вывод содержимого списка
void print_list(list* l);

// Освобождение памяти, выделенной под список
void free_list(list* l);

// Перестановка списка в обратном порядке
void reverse_list(list* l);

#endif
