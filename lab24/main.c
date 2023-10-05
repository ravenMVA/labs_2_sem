// Вариант 18
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "parse.h"

#define MAX_LEN 250

int main() {
    char str[MAX_LEN];
    printf("Enter the expression:\n");
    fgets(str, MAX_LEN, stdin);
    int len;
    for(len = 0; str[len] != '\0'; ++len);
    queue* q = parse(str, len);

    printf("\n=== the tree of the original expression ===\n");
    tree* t = create_tree(q);
    print_tree(t->root, 0);

    printf("\n=== tree of the transformed expression ===\n");
    reduce_minuses(t->root);
    print_tree(t->root, 0);

    printf("\n=== infix entry ===\n");
    char* infix_str = infix(t->root);
    printf("%s\n", infix_str);

    free(infix_str);
    delete_tree(t);
    free(q);

    return 0;
}
