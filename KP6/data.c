#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "data.h"

// Function to delete a student from the array
bool delete_student(char* name, student* s_list[], int* list_size) {
    int i, j;
    for (i = 0; i < *list_size; i++) {
        if (s_list[i] != NULL && strcmp(s_list[i]->name, name) == 0) {

            free_student(s_list[i]);

            for (j = i; j < *list_size - 1; j++) {
                s_list[j] = s_list[j + 1];
            }
            // Decrement the list size
            (*list_size)--;
            // Set the last element to NULL (optional)
            s_list[*list_size] = NULL;
            return true; // Student found and deleted, exit the function
        }
    }
    return false;
}

int main(int argc, char **argv) {
    if (argc != 2 || argv[1] == NULL) {
        printf("Using: lab <file>\n");
        exit(1);
    }

    bool bin = false;
    
    char* ext = strrchr(argv[1], '.');
    if (ext == NULL || strcmp(ext, ".txt") == 0) {
        printf("Working with .txt file.\n");
    } 
    else if (ext != NULL && strcmp(ext, ".bin") == 0) {
        bin = true;
        printf("Working with .bin file.\n");
    }
    else {
        perror("Incorrect file extension\n");
        exit(1);
    }

    FILE* fd;
    
    student* s_list[MAX_STUDENTS];
    int list_size;

    if (bin) {
        fd = fopen(argv[1], "rb");
        if (fd == NULL) {
            perror("Error opening file\n");
            exit(1);
        }
        for (list_size = 0; true; list_size++) {
            student* s = create_student();
            if (student_read_bin(s, fd) == 0) {
                break;
            }
            s_list[list_size] = s;
        }
    } else {
        fd = fopen(argv[1], "r");
        if (fd == NULL) {
            perror("Error opening file\n");
            exit(1);
        }
        for (list_size = 0; true; list_size++) {
            student* s = create_student();
            if (student_read_txt(s, fd) == 0) {
                break;
            }
            s_list[list_size] = s;
        }
    }

    int value;
    int choice = 0;

    while (choice != 5) {
        
    	printf("1. Add student\n");
        printf("2. Delete student\n");
        printf("3. Print the list\n");
        printf("4. Find the best student's computer\n");
        printf("5. Exit\n");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
            {
                student* s = create_student();
                printf("Enter the name: ");
                scanf("%s", s->name);
                printf("Enter the number of proccesors: ");
                scanf("%d", &(s->cpu_num));
                printf("Enter proccesors (e.g.: 'i5+i7'): ");
                scanf("%s", s->cpu_type);
                printf("Add the number of memory (Mb): ");
                scanf("%d", &(s->mem));
                printf("Enter the graphic card name (e.g.: 1080): ");
                scanf("%s", s->gpu);
                printf("Enter the number of graphic memory: ");
                scanf("%d", &(s->gpu_mem));
                printf("Enter the number HDD: ");
                scanf("%d", &(s->hdd_num));
                printf("Enter the sizes of HDD (e.g.: 2+4): ");
                scanf("%s", s->hdds);
                printf("Enter the number of periperal devices: ");
                scanf("%d", &(s->devices));
                printf("Enter the OS name (w/out space): ");
                scanf("%s", s->os);
                printf("\n");
                s_list[list_size++] = s;
                fclose(fd);
                if (bin) {
                    fd = fopen(argv[1], "ab");
                    student_write_bin(s, fd);
                } else {
                    fd = fopen(argv[1], "a");
                    student_write_txt(s, fd);
                }
                fclose(fd);
                if (bin) {
                    fd = fopen(argv[1], "rb");
                    student_write_bin(s, fd);
                } else {
                    fd = fopen(argv[1], "r");
                    student_write_txt(s, fd);
                }
                break;
            }
            case 2:
            {
                char name[STAT_LEN];
                printf("Enter the name: ");
                scanf("%s", name);
                while (delete_student(name, s_list, &list_size)) {}
                
                FILE* tmp = fopen("temp", "w");
                for (int i = 0; i < list_size; i++) {
                    if (bin) {
                        student_write_bin(s_list[i], tmp);
                    } else {
                        student_write_txt(s_list[i], tmp);
                    }
                }
                fclose(tmp);
                fclose(fd);
                remove(argv[1]);
                rename("temp", argv[1]);
                if (bin) {
                    fd = fopen(argv[1], "rb");
                } else {
                    fd = fopen(argv[1], "r");
                }
                printf("Student deleted from the list\n");
                break;
            }
            case 3:
                print_studlist(s_list, list_size);
                break;
            case 4:
            {
                char name[STAT_LEN];
                printf("Enter the name: ");
                scanf("%s", name);
                student** found = find_student(name, s_list, list_size);
                if (found == NULL) {
                    printf("Student not found\n");
                    break;
                }
                student* best = cmp_computers(found);
                printf("Best computer %s:\n", name);
                print_student(best);
                free(found);
                break;
            }
            case 5: 
                // Просто выходим
                break;

        }
    }

    // Удаляем студентов из памяти
    for (int i = 0; i < list_size; i++) { 
        if (s_list[i] == NULL) {
            continue;
        }
        free_student(s_list[i]);
    }

    return 0;
}
