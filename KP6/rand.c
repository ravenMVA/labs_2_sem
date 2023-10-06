#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "data.h"

#define BUF_SIZE 64
#define MAX_STUD 30

char* random_student() {
    char* cpus[] = { "i3", "i5", "i7", "i9" };
    char* oss[] = { "Windows7", "Windows8", "Windows10", "Ubuntu" };
    char* gpus[] = { "1080", "1070", "1060", "1050" };
    char* names[] = { "Masha", "Petya", "Sergei", "Vitaly", "Fedor", "Ibragim", "Nikita", "Maksim", "Diana" };
    int hdds[] = { 1, 2, 3, 4, 8, 16, 32 };

    // Randomly select values
    char* name = names[rand() % 8];
    int cpu_num = 1 + rand() % 4; // Random number of CPUs (1 to 4)
    char cpu_types[MAX_LEN] = "";
    for (int i = 0; i < cpu_num; i++) {
        strcat(cpu_types, cpus[rand() % 4]);
        if (i < cpu_num - 1) {
            strcat(cpu_types, "+");
        }
    }
    int mem = (1 + rand() % 8) * 1024; // Random memory size in multiples of 1024MB
    char* gpu = gpus[rand() % 4];
    int gpu_mem = (1 + rand() % 6) * 1024; // Random GPU memory size in multiples of 1024MB
    int hdd_num = 1 + rand() % 3;
    char hdd_sizes[MAX_LEN] = "";
    for (int i = 0; i < hdd_num; i++) {
        char hdd_size[BUF_SIZE];
        sprintf(hdd_size, "%d", hdds[rand() % 7]);
        strcat(hdd_sizes, hdd_size);
        if (i < hdd_num - 1) {
            strcat(hdd_sizes, "+");
        }
    }
    int devices = 2 + rand() % 5;
    char* os = oss[rand() % 4];

    // Create a formatted string in CSV format
    char* str = (char*)malloc(MAX_LEN);
    snprintf(str, MAX_LEN, "%s,%d,%s,%d,%s,%d,%d,%s,%d,%s\n", name, cpu_num, cpu_types, mem, gpu, gpu_mem, hdd_num, hdd_sizes, devices, os);

    return str;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        perror("Использование: rand.out <имя_файла>\n");
        exit(1);
    }
    FILE* fp;
    fp = fopen(argv[1], "w");
    if (fp == NULL) {
        perror("Файл не найден\n");
        exit(1);
    }

    // Seed the random number generator
    srand(time(NULL));

    int n = 1 + rand() % MAX_STUD;
    for (int i = 0; i < n; i++) {
        char* student_data = random_student();
        fprintf(fp, "%s", student_data);
        free(student_data);
    }

    fclose(fp);
    return 0;
}
