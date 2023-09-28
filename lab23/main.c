
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

int main() {
    Tree* root = NULL;
    
    while (1) {
        int value;
        int choice = 0;
    	printf("1. Добавить узел\n");
        printf("2. Удалить узел\n");
        printf("3. Вывести дерево на экран\n");
        printf("4. Найти ширину двоичного дерева\n");
        printf("5. Выйти\n");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Введите значение добавляемого узла: ");
        		scanf("%d", &value);
       	 		root = add_node(root, value);
                break;
            case 2:
                printf("Введите значение узла для удаления: ");
        		scanf("%d", &value);
        		root = delete_tree(root, value);
                break;
            case 3:
                printf("Дерево:\n");
    			print_tree(root, 1);
                break;
            case 4:
                printf("Ширина дерева: %d\n", tree_max_width(root));
                break;
            case 5:
                free_node(root);
    			return 0;
                break;
            default:
                printf("НЕКОРРЕКТНЫЙ ВВОД\n");
                break;
        }
    }
    delete_tree(root, root->value);
    
    return 0;
}
