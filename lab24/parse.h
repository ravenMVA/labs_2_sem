#ifndef PARSE
#define PARSE

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 250

typedef enum {
    OPERATOR,
    NUMBER,
    VARIABLE
} token;

typedef struct node {
    struct node* parent;
    struct node* l_ch;
    struct node* r_ch;
    token type;
    char oper;
    bool minus;
    int val;
    char var;
    struct node* next; // Для очереди
} node;

typedef struct tree {
    node* root;
} tree;

typedef struct {
    node* back;
    node* front;
} queue;

node* create_node(token type, char op, int val, char var, bool minus);

//===== ОЧЕРЕДЬ ======
queue* create_queue();

void enqueue(queue* q, node* n);

node* dequeue(queue* q);

void delete_queue(queue* q);
//=====================

queue* parse(char* str, int l);

node* add_to_tree(node* n, queue* q);

tree* create_tree(queue* q);

void print_tree(node* root, int n);

void print_node(node* n);

bool reduce_minuses(node* root);

char* infix(node* root);

void free_node(node* n);

void delete_tree(tree* t);

#endif
