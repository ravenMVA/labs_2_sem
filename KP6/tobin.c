#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        perror("Использование: tobin.out <*.txt> <*.bin>\n");
        exit(1);
    }

    FILE* txt = fopen(argv[1], "r");
    if (txt == NULL) {
        perror("Файл не найден");
        return 1;
    }

    FILE* bin = fopen(argv[2], "wb");
    if (bin == NULL) {
        perror("Ошибка открытия файла");
        fclose(txt);
        return 1;
    }

    student* s = create_student();

    while (student_read_txt(s, txt)) { 
        printf("|");
        if (student_write_bin(s, bin) == 0) {
            perror("Ошибка записи");
            break;
        }
    }

    free_student(s);

    fclose(txt);
    fclose(bin);

    printf("\nФайл конвертирован.\n");
    return 0;
}
