#include "tree.h"
#include "tree.h"
#include <stdio.h>

// Функция для создания нового узла дерева
Tree* create_tree(int value) {
    Tree* new_tree = (Tree*)malloc(sizeof(Tree));
    new_tree->value = value;
    new_tree->left = NULL;
    new_tree->right = NULL;
    return new_tree;
}

// Функция для добавления нового узла: если элемент меньше корня, добавляем слева, если больше - справа.
Tree* add_node(Tree* root, int value) {
    if(root == NULL) {
        return create_tree(value);
    }
    if(value < root->value) {
        root->left = add_node(root->left, value);
    }
    else if(value > root->value) {
        root->right = add_node(root->right, value);
    }
    return root;
}

// Функция для нахождения минимального значения в дереве
Tree* min_node(Tree* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Функция для удаления узла из дерева
Tree* delete_tree(Tree* root, int value) {
    if (root == NULL) { // дерево пусто
        return root;
    }
    if (value < root->value) {
        root->left = delete_tree(root->left, value);
    } else if (value > root->value) {   
        root->right = delete_tree(root->right, value);
    } else {
        // узел имеет только правого потомка
        if (root->left == NULL) { 
            Tree* temp = root->right;
            free(root);
            return temp;
        // узел имеет только левого потомка
        } else if (root->right == NULL) { 
            Tree* temp = root->left;
            free(root);
            return temp;
        }
        // узел имеет и левого, и правого потомка
        Tree* temp = min_node(root->right); // находим минимальное значение в правом поддереве
        root->value = temp->value;
        root->right = delete_tree(root->right, temp->value);
    }
    return root;    
}

// Функция для вывода дерева в форматированном виде
void print_tree(Tree* root, int n) {
    if (root == NULL) {
        return;
    }
    print_tree(root->right, n + 1);
    for (int i = 0; i < n; i++) printf("\t");
    printf("%d\n", root->value);
    print_tree(root->left, n + 1);
}

// Функция для освобождения памяти, выделенной для узлов дерева
void free_node(Tree* root) {
    if (root == NULL) {
        return;
    }
    free_node(root->left);
    free_node(root->right);
    free(root);
}

// ---- Главное ------

// Функция для определения высоты бинарного дерева
int height(Tree* node) {
    if (node == NULL)
        return 0;

    int l_height = height(node->left);
    int r_height = height(node->right);
    
    if (l_height > r_height) {
        return l_height + 1;
    } else {
        return r_height + 1;
    }
}

// Функция для подсчета ширины уровня
int level_width(Tree* tree, int level) {
    if (tree == NULL)
        return 0;
    if (level == 1)
        return 1;
    
    // Рекурсивно считаем ширину уровня для левого и правого поддеревьев
    return level_width(tree->left, level - 1) + level_width(tree->right, level - 1);
}

// Функция для подсчета максимальной ширины бинарного дерева
int tree_max_width(Tree* root) {
    int max_width = 0;
    if (root == NULL) {
        return max_width;
    }
    for (int i = 1; i <= height(root); i++) {
        int width = level_width(root, i);
        if (width > max_width) {
            max_width = width;
        }
    }
    return max_width;
}
