// Var S1
#include "stdio.h"
#include "stdlib.h"
#include "mystack.h"
#include <limits.h>

int main() {
    Stack* stack = create_stack();

    while (1) {
        int value;
        int choice = 0;
    	printf("1. Push (add)\n");
        printf("2. Pop (extract)\n");
        printf("3. Print stack\n");
        printf("4. Sort stack\n");
        printf("5. Delete largest element\n");
        printf("6. Exit\n");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter a value: ");
        		scanf("%d", &value);
       	 		push(stack, value);
                printf("Element is added.\n");
                break;
            case 2:
                if (is_empty(stack)) {
                    printf("Stack is empty\n");
                    break;
                }
                printf("Highest element [ %d ] extracted.\n", pop(stack));
                break;
            case 3:
                printf("Stack:\n");
    			print_stack(stack->top);
                printf("===\n");
                break;
            case 4:
                sort_stack(stack);
                printf("Stack is sorted\n");
                break;
            case 5: {
                int max = INT_MIN;
                delete_max_elem(stack, &max);
                printf("Largest element deleted\n");
                break;
            }
            case 6:
                delete_stack(stack);
                return 0;
            default:
                printf("INCORRECT INPUT\n");
                break;
        }
    }

    return 0;
}
