#ifndef TREE
#define TREE

#include <stdlib.h>

typedef struct Tree {
    int value;
    struct Tree* left;
    struct Tree* right;
} Tree;

Tree* create_tree(int value);

Tree* add_node(Tree* root, int value);

Tree* delete_tree(Tree* root, int key);

Tree* min_node(Tree* root);

void print_tree(Tree* root, int n);

void free_node(Tree* root);

int height(Tree* node);

int level_width(Tree* tree, int level);

int tree_max_width(Tree* root);

#endif
