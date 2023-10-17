#include "struct.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc != 2 || argv[1] == NULL) {
        printf("Использование: lab <файл>\n");
        exit(1);
    }

    FILE* fd = fopen(argv[1], "r");
    if (fd == NULL) {
        perror("Ошибка открытия файла");
        exit(1);
    }

    sparse* sp;
    int n = 1;

    while (true) {
        sp = read_matrix(fd);
        if (sp == NULL) {
            break;
        }
        
        printf(">>===================================================\n");
        printf("Матрица №%d в разреженном виде:\n", n);
        print_sparse(sp);

        transform(sp);

        printf("После преобразования:\n");
        print_sparse(sp);

        printf("В обычном виде (преобразованная):\n");
        print_as_regular(sp);

        printf(">>===================================================\n\n");

        free_sparse(sp);
        n++;
        fclose(fd);
    }

    

    return 0;
}
