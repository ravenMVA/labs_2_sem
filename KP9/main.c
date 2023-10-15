#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "table.h"

int main(int argc, char** argv) {
    if (argc != 2 || argv[1] == NULL) {
        printf("Использование: lab <файл>\n");
        exit(1);
    }

    FILE* fd = fopen(argv[1], "r");
    if (fd == NULL) {
        perror("Ошибка открытия файла");
        exit(1);
    }

    table* t = read_table(fd);
    table* t_sorted = NULL;

    // Если стих неотсортирован
    if (t->sorting == NOT) {
        // Создаем отсортированную копию стиха
        t_sorted = (table*)malloc(sizeof(table));
        t_sorted->size = t->size;
        t_sorted->list = (elem**)malloc(sizeof(elem*) * t->size);
        for (int i = 0; i < t->size; i++) {
            t_sorted->list[i] = create_elem(t->list[i]->key, strdup(t->list[i]->line));
        }
        
        sort(t_sorted);
    } else {
        t_sorted = t;
    }

    while (1) {
        long long key;
        int choice = 0;
    	printf("\n    1. Вывести изначальный стих\n");
        printf("    2. Вывести отсортированный стих\n");
        printf("    3. Поиск по ключу\n");
        printf("    4. Выйти\n");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Стих:\n");
                print_table(t);
                break;
            case 2:
                printf("Отсортированный стих:\n");
                print_table(t_sorted);
                break;
            case 3:
                printf("Введите ключ: ");
                scanf("%lld", &key);
                elem* e = search(t_sorted, key);
                if (e != NULL) {
                    printf("Строка: %s", e->line);
                } else {
                    printf("Ключа не существует");
                }
                break;
            case 4:
                if (t->sorting == NOT) {
                    free(t_sorted);
                }
                free_table(t);
    			return 0;
                break;
            default:
                printf("Некорректный ввод\n");
                break;
        }
    }
    
    return 0;
}
