// Вариант 18
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "parse.h"

#define MAX_LEN 250

int main() {
    char str[MAX_LEN];
    printf("Введите выражение:\n");
    fgets(str, MAX_LEN, stdin);
    int len;
    for(len = 0; str[len] != '\0'; ++len);
    queue* q = parse(str, len);

    printf("\n=== Дерево исходного выражения ===\n");
    tree* t = create_tree(q);
    print_tree(t->root, 0);

    printf("\n=== Дерево преобразованного выражения ===\n");
    reduce_minuses(t->root);
    print_tree(t->root, 0);

    printf("\n=== Инфиксная запись ===\n");
    char* infix_str = infix(t->root);
    printf("%s\n", infix_str);

    free(infix_str);
    delete_tree(t);
    free(q);

    return 0;
}
