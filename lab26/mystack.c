#include "mystack.h"
#include <limits.h>

StackNode* create_node(int value) {
    StackNode* new_node = (StackNode*)malloc(sizeof(StackNode));
    if (new_node == NULL) {
        printf("ОШИБКА ИНИЦИАЛИЗАЦИИ УЗЛА СТЕКА\n");
        exit(1);
    }
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

Stack* create_stack() {
    Stack* new_stack = (Stack*)malloc(sizeof(Stack));
    if (new_stack == NULL) {
        printf("ОШИБКА ИНИЦИАЛИЗАЦИИ СТЕКА\n");
        exit(1);
    }
    new_stack->top = NULL;
    return new_stack;
}

int is_empty(Stack* stack) {
    if (stack == NULL) {
        return 1;
    }
    return stack->top == NULL;
}

void push(Stack* stack, int value) {
    if (stack == NULL) {
        return;
    }
    StackNode* new_node = create_node(value);
    new_node->next = stack->top;
    stack->top = new_node;
    return;
}

int pop(Stack* stack) {
    if (is_empty(stack)) {
        printf("СТЕК ПУСТ\n");
        exit(1);
    }
    StackNode* temp = stack->top;
    int value = temp->data;
    stack->top = temp->next;
    free(temp);
    return value;
}

int check_top(Stack* stack) {
    if (is_empty(stack)) {
        printf("СТЕК ПУСТ\n");
        exit(1);
    }
    int value = pop(stack);
    push(stack, value);
    return value;
}

void delete_stack(Stack* stack) {
    while (!is_empty(stack)) {
        pop(stack);
    }
    return;
}

void print_stack(StackNode* top) {
    if (top == NULL) {
        return;
    }
    printf("[ %d ]\n", top->data);
    print_stack(top->next);
    return;
}

// --- ГЛАВНОЕ --- 

int delete_max_elem(Stack* stack, int* max) {
    if (is_empty(stack)) {
        return INT_MIN;
    }
    int data = pop(stack);
    if (data > *max) {
        *max = data;
    }
    int result = delete_max_elem(stack, max);
    if (data == *max && result != 1) {
        return 1;
    }
    push(stack, data);
    return result;
}

void sort_stack(Stack* stack) {
    if (is_empty(stack)) {
        printf("Стек пуст\n");
        return;
    }
    Stack* sorted_stack = create_stack();

    while (!is_empty(stack)) {
        int max_value = INT_MIN;
        delete_max_elem(stack, &max_value);
        push(sorted_stack, max_value);
    }
    
    while (!is_empty(sorted_stack)) {
        int top = pop(sorted_stack);
        push(stack, top);
    }

    delete_stack(sorted_stack);
    return;
}
