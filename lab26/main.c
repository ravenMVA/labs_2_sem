#include "stdio.h"
#include "stdlib.h"
#include "mystack.h"

int main() {
    Stack* stack = create_stack();

    while (1) {
        int value;
        int choice = 0;
    	printf("1. Push (добавить)\n");
        printf("2. Pop (извлечь)\n");
        printf("3. Вывести стек\n");
        printf("4. Отсортировать стек\n");
        printf("5. Удалить наибольший элемент\n");
        printf("6. Выйти\n");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Введите значение: ");
        		scanf("%d", &value);
       	 		push(stack, value);
                printf("Элемент добавлен.\n");
                break;
            case 2:
                if (is_empty(stack)) {
                    printf("Стек пуст\n");
                    break;
                }
                printf("Верхний элемент [ %d ] извлечен.\n", pop(stack));
                break;
            case 3:
                printf("Стек:\n");
    			print_stack(stack->top);
                printf("===\n");
                break;
            case 4:
                sort_stack(stack);
                printf("Стэк отсортирован\n");
                break;
            case 5: {
                int max = INT32_MIN;
                delete_max_elem(stack, &max);
                printf("Наибольший элемент удален\n");
                break;
            }
            case 6:
                delete_stack(stack);
                return 0;
            default:
                printf("НЕКОРРЕКТНЫЙ ВВОД\n");
                break;
        }
    }

    delete_stack(stack);
    return 0;
}
