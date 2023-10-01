#ifndef MYSTACK
#define MYSTACK

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 512

typedef struct StackNode {
    int data;
    struct StackNode *next;
} StackNode;

typedef struct Stack {
    StackNode *top;
} Stack;

StackNode* create_node(int value);

Stack* create_stack();

int is_empty(Stack* stack);

void push(Stack* stack, int value);

int pop(Stack* stack);

int check_top(Stack* stack);

void delete_stack(Stack* stack);

void print_stack(StackNode* top);

int delete_max_elem(Stack* stack, int* max);

void sort_stack(Stack* stack);

#endif
