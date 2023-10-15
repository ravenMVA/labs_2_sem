#include "table.h"
#include <limits.h>

table* read_table(FILE* fd) {
    table* t = (table*)malloc(sizeof(table));
    t->size = 0;
    t->list = (elem**)malloc(sizeof(elem*) * LIST_SIZE);
    t->sorting = NOT;
    
    bool unsorted = false;
    long long key;
    long long prev_key = INT_MIN;
    char buffer[MAX_LEN];
    while (fscanf(fd, "%lld", &key) && fgets(buffer, MAX_LEN, fd) != NULL) {
        char* line = malloc(MAX_LEN * sizeof(char));
        strncpy(line, buffer, MAX_LEN);
        t->list[t->size] = create_elem(key, line);
        t->size++;

        // В первую итерацию не проверяем тип сортировки
        if (prev_key == INT_MIN) {
            prev_key = key;
            continue; // Пропускаем дальше
        }
        // Проверяем тип отсортированности
        if (key > prev_key && t->sorting != DOWN && !unsorted) {
            t->sorting = UP;
        } else if (key < prev_key && t->sorting != UP && !unsorted) {
            t->sorting = DOWN;
        } else {
            t->sorting = NOT;
            unsorted = true;
        }
        
        prev_key = key;
    }
    return t;
}

elem* create_elem(long long key, char* line) {
    elem* e = (elem*)malloc(sizeof(elem));
    e->key = key;
    e->line = line;
    return e;
}

// Бинарный поиск в зависимости от типа отсортированности
elem* search(table* t, long long key) {
    int left = 0;
    int right = t->size - 1;
    sorting type = t->sorting;

    while (left <= right) {
        int middle = left + (right - left) / 2;

        if (t->list[middle]->key == key) {
            return t->list[middle];
        }
        if ((type == UP && t->list[middle]->key < key) 
        || (type == DOWN && t->list[middle]->key > key)) 
        {
            left = middle + 1;
        } 
        else {
            right = middle - 1;
        }
    }

    return NULL; // Key not found
}

// Функция для обмена элементов
void swap(elem** a, elem** b) {
    elem* temp = *a;
    *a = *b;
    *b = temp;
}

// Функция для чётно-нечётной сортировки по ключу
void sort(table* t) {
    int n = t->size;
    int sorted = 0; // Флаг, указывающий на то, был ли произведен обмен на последней итерации

    while (!sorted) {
        sorted = 1;
        
        // Проход по четным элементам и сравнение соседних ключей
        for (int i = 0; i < n - 1; i += 2) {
            if (t->list[i]->key > t->list[i + 1]->key) {
                swap(&(t->list[i]), &(t->list[i + 1]));
                sorted = 0; // Обмен произведен, таблица может быть не отсортированной
            }
        }

        // Проход по нечетным элементам и сравнение соседних ключей
        for (int i = 1; i < n - 1; i += 2) {
            if (t->list[i]->key > t->list[i + 1]->key) {
                swap(&(t->list[i]), &(t->list[i + 1]));
                sorted = 0; // Обмен произведен, таблица может быть не отсортированной
            }
        }
    }
    t->sorting = UP;
}

void print_table(table* t) {
    if (t == NULL) {
        return;
    }
    for (int i = 0; i < t->size; i++) {
        printf("%lld %s", t->list[i]->key, t->list[i]->line);
    }
}

void free_elem(elem* e) {
    if (e == NULL) {
        return;
    }
    free(e->line);
    free(e);
    return;
}

void free_table(table* t) {
    for (int i = 0; i < t->size; i++) {
        free_elem(t->list[i]);
    }
    free(t->list);
    free(t);
}
