// [2,2,11]
#include "spisok.h"
#include <stdio.h>

int main() {

    list* l = create_list();

    while (1) {
        double value;
        int choice = 0;
    	printf("    1. Добавить элемент\n");
        printf("    2. Удалить элемент\n");
        printf("    3. Вывести список\n");
        printf("    4. Найти длину списка\n");
        printf("    5. Переставить список в обратном порядке\n");
        printf("    6. Выйти\n");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Введите значение добавляемого элемента: ");
        		scanf("%lf", &value);
       	 		append(l, value);
                printf("Элемент добавлен\n");
                break;
            case 2:
                printf("Введите номер элемента: ");
                int num;
        		scanf("%d", &num);
        		remove_node(l, num - 1);
                printf("Элемент удален\n");
                break;
            case 3:
                printf("Список: ");
                print_list(l);
                break;
            case 4:
                printf("Длина списка: %d\n", length(l));
                break;
            case 5:
                reverse_list(l);
                printf("Список развернут\n");
                break;
            case 6:
                free_list(l);
    			return 0;
                break;
            default:
                printf("Некорректный ввод\n");
                break;
        }
    }
    return 0;
}
