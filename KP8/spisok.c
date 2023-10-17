#include "spisok.h"

#include <stdio.h>
#include <stdlib.h>

// Инициализация пустого списка
list* create_list() {
    list* new_list = (list*)malloc(sizeof(list));
    if (new_list == NULL) {
        perror("Ошибка выделения памяти");
        exit(1);
    }
    new_list->size = 0;
    new_list->root = NULL;
    return new_list;
}

// Добавление элемента в конец списка
void append(list* l, double value) {
    node* n = (node*)malloc(sizeof(node));
    if (n == NULL) {
        perror("Ошибка выделения памяти");
        exit(1);
    }
    n->value = value;
    n->next = NULL;

    if (l->root == NULL) {
        l->root = n;
    } else {
        node* current = l->root;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = n;
    }
    l->size++;
    return;
}

// Вставка элемента по индексу
void insert(list* l, int index, double value) {
    if (index < 0 || index >= l->size) {
        printf("Индекс за пределами допустимого диапазона\n");
        return;
    }
    node* n = (node*)malloc(sizeof(node));
    if (n == NULL) {
        perror("Ошибка выделения памяти");
        exit(1);
    }
    n->value = value;
    if (index == 0) {
        n->next = l->root;
        l->root = n;
    } else {
        node* current = l->root;
        node* prev = current;
        for (int i = 0; i < index; i++) {
            prev = current;
            current = current->next;
        }
        n->next = current;
        prev->next = n;
    }
    l->size++;
    return;
}

void remove_node(list* l, int index) {
    if (index < 0 || index >= l->size) {
        printf("Индекс за пределами допустимого диапазона\n");
        return;
    }

    if (index == 0) {
        // Удаляем первый элемент
        node* temp = l->root;
        l->root = l->root->next;
        free(temp);
    } else {
        // Удаляем элемент, не являющийся первым
        node* cur = l->root;
        for (int i = 0; i < index - 1; i++) {
            cur = cur->next;
        }
        node* temp = cur->next;
        cur->next = temp->next;
        free(temp);
    }

    l->size--;
    return;
}

// Узнать длину списка
int length(const list* l) {
    return l->size;
}

// Вывод содержимого списка
void print_list(list* l) {
    node* current = l->root;
    while (current != NULL) {
        printf("[%.2lf] ", current->value);
        current = current->next;
    }
    printf("\n");
    return;
}

// Освобождение памяти, выделенной под список
void free_list(list* l) {
    node* cur = l->root;
    while (cur != NULL) {
        node* next = cur->next;
        free(cur);
        cur = next;
    }
    free(l);
    return;
}

// Перестановка списка в обратном порядке
void reverse_list(list* l) {
    node* prev = NULL;
    node* cur = l->root;
    node* next = NULL;

    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    l->root = prev;
    return;
}

