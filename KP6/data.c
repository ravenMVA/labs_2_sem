#include "data.h"

student* create_student() {
    student* s = (student*)malloc(sizeof(student));
    if (s == NULL) {
        perror("Ошибка создания студента");
        exit(1);
    }
    s->name = calloc(STAT_LEN, sizeof(char));
    s->cpu_type = calloc(STAT_LEN, sizeof(char));
    s->gpu = calloc(STAT_LEN, sizeof(char));
    s->hdds = calloc(STAT_LEN, sizeof(char));
    s->os = calloc(STAT_LEN, sizeof(char));
    // Initialize fields to default values or NULL
    s->cpu_num = 0;
    s->mem = 0;
    s->gpu_mem = 0;
    s->hdd_num = 0;
    s->devices = 0;

    return s;
}

void free_student(student* s) {
    if (s == NULL) {
        return; // Nothing to delete if the student is NULL
    }

    // Free dynamically allocated fields
    free(s->name);
    free(s->cpu_type);
    free(s->gpu);
    free(s->hdds);
    free(s->os);
    // Free the student structure itself
    free(s);
}

// Function to read a student record from a text file
int student_read_txt(student* s, FILE* fd) {
    char buffer[MAX_LEN]; // A buffer for reading lines from the file
    // Read data from the CSV file
    if (fgets(buffer, MAX_LEN, fd) == NULL) {
        return 0; // End of file or error
    }
    // Parse the CSV line into the student struct members
    char* token = strtok(buffer, ",");
    s->name = strndup(token, STAT_LEN);
    token = strtok(NULL, ",");
    s->cpu_num = atoi(token);
    token = strtok(NULL, ",");
    s->cpu_type = strndup(token, STAT_LEN);
    token = strtok(NULL, ",");
    s->mem = atoi(token);
    token = strtok(NULL, ",");
    s->gpu = strndup(token, STAT_LEN);
    token = strtok(NULL, ",");
    s->gpu_mem = atoi(token);
    token = strtok(NULL, ",");
    s->hdd_num = atoi(token);
    token = strtok(NULL, ",");
    s->hdds = strndup(token, STAT_LEN);
    token = strtok(NULL, ",");
    s->devices = atoi(token);
    token = strtok(NULL, ",");
    s->os = strndup(token, STAT_LEN);
    return 1; // Successfully read a student record
}

// Function to write a student record to a text file
int student_write_txt(student* s, FILE* fd) {
    char* template = "%s,%d,%s,%d,%s,%d,%d,%s,%d,%s";
    if (s->os[strlen(s->os) - 1] != '\n') {
        template = "%s,%d,%s,%d,%s,%d,%d,%s,%d,%s\n";
    }
    if (fprintf(fd, template,
                s->name, s->cpu_num, s->cpu_type, s->mem, s->gpu,
                s->gpu_mem, s->hdd_num, s->hdds, s->devices, s->os) < 0) {
        return 0; // Error writing to the file
    }
    return 1; // Successfully wrote a student record
}

int student_read_bin(student *s, FILE* fd)
{
    if (fread(s->name, sizeof(char), STAT_LEN, fd) == 0) {
        return 0;
    };
    fread(&(s->cpu_num), sizeof(int), 1, fd);
    fread(s->cpu_type, sizeof(char), STAT_LEN, fd);
    fread(&(s->mem), sizeof(int), 1, fd);
    fread(s->gpu, sizeof(char), STAT_LEN, fd);
    fread(&(s->gpu_mem), sizeof(int), 1, fd);
    fread(&(s->hdd_num), sizeof(int), 1, fd);
    fread(s->hdds, sizeof(char), STAT_LEN, fd);
    fread(&(s->devices), sizeof(int), 1, fd);
    fread(s->os, sizeof(char), STAT_LEN, fd)  ;

    return 1;
}

int student_write_bin(student *s, FILE* fd)
{
    if (fwrite(s->name, sizeof(char), STAT_LEN, fd) == 0) {
        return 0;
    };
    fwrite(&(s->cpu_num), sizeof(int), 1, fd);
    fwrite(s->cpu_type, sizeof(char), STAT_LEN, fd);
    fwrite(&(s->mem), sizeof(int), 1, fd);
    fwrite(s->gpu, sizeof(char), STAT_LEN, fd);
    fwrite(&(s->gpu_mem), sizeof(int), 1, fd);
    fwrite(&(s->hdd_num), sizeof(int), 1, fd);
    fwrite(s->hdds, sizeof(char), STAT_LEN, fd);
    fwrite(&(s->devices), sizeof(int), 1, fd);
    fwrite(s->os, sizeof(char), STAT_LEN, fd); 

    return 1;
}

// Function to print a student record
void print_student(student* s) {
    printf("    Name: %s\n", s->name);
    printf("    CPU Number: %d\n", s->cpu_num);
    printf("    CPU Type: %s\n", s->cpu_type);
    printf("    Memory [MB]: %d MB\n", s->mem);
    printf("    GPU: %s\n", s->gpu);
    printf("    GPU Memory [MB]: %d MB\n", s->gpu_mem);
    printf("    Number of HDDs: %d\n", s->hdd_num);
    printf("    HDD sizes [TB]: %s\n", s->hdds);
    printf("    Number of Devices: %d\n", s->devices);
    printf("    Operating System: %s\n", s->os);
}

void print_studlist(student** sl, int len) {
    for (int i = 0; i < len; i++) {
        printf("===\n");
        print_student(sl[i]);
    }
}

student** find_student(char* name, student** list, int list_len) {
    student** result = (student**)malloc(MAX_STUDENTS * sizeof(student*));
    int top = 0;

    for (int i = 0; i < list_len; i++) {
        if (list[i] == NULL) {
            break;
        }
        if (strncmp(list[i]->name, name, MAX_LEN) == 0) {
            result[top] = list[i];
            top++;
        }
    }

    result[top] = NULL;
    return top == 0 ? NULL : result;
}

int cmp_cpu(char* a, char* b) {
    int res1, res2;
    char* c = a;
    while (c < a + strlen(a)) {
        if (!isdigit(*c)) {
            c++;
            continue;
        }
        res1 += *c - '0';
        c++;
    }
    c = b;
    while (c < b + strlen(b)) {
        if (!isdigit(*c)) {
            c++;
            continue;
        }
        res2 += *c - '0';
        c++;
    }
    return res1 > res2 ? 0 : 1;
}

int cmp_gpu(char* a, char* b) {
    int res1, res2;
    char* c = a;
    while (c < a + strlen(a)) {
        if (!isdigit(*c)) {
            c++;
            continue;
        }
        res1 += *c - '0';
        c++;
    }
    c = b;
    while (c < b + strlen(b)) {
        if (!isdigit(*c)) {
            c++;
            continue;
        }
        res2 += *c - '0';
        c++;
    }
    return res1 > res2 ? 0 : 1;
}

int cmp_hdd(char* a, char* b) {
    int res1, res2;
    char* c = a;
    while (c < a + strlen(a)) {
        if (!isdigit(*c)) {
            c++;
            continue;
        }
        res1 += *c - '0';
        c++;
    }
    c = b;
    while (c < b + strlen(b)) {
        if (!isdigit(*c)) {
            c++;
            continue;
        }
        res2 += *c - '0';
        c++;
    }
    return res1 > res2 ? 0 : 1;
}

int cmp_os(char* a, char* b) {
    int res1, res2;
    if (strcmp(a, "Windows 7") == 0) {
        res1 = 1;
    } 
    else if (strcmp(a, "Windows 8") == 0) {
        res1 = 2;
    }
    else if (strcmp(a, "Windows 10") == 0) {
        res1 = 3;
    }
    else if (strcmp(a, "Ubuntu") == 0) {
        res1 = 4;
    }
    else {
        return -1; 
    }

    if (strcmp(a, "Windows 7") == 0) {
        res2 = 1;
    } 
    else if (strcmp(a, "Windows 8") == 0) {
        res2 = 2;
    }
    else if (strcmp(a, "Windows 10") == 0) {
        res2 = 3;
    }
    else if (strcmp(a, "Ubuntu") == 0) {
        res2 = 4;
    }
    else {
        return -1; 
    }

    return res1 > res2 ? 0 : 1;
}

student* cmp_computers(student* list[]) {
    if (list[0] == NULL) {
        return NULL;
    }
    student* best = list[0];
    for (int i = 1; list[i] != NULL; i++) {
        student* pc1 = best;
        student* pc2 = list[i];
        if (pc2 == NULL) {
            break;
        }
        int c1 = 0, c2 = 0;
        
        cmp_cpu(pc1->cpu_type, pc2->cpu_type) == 0 ? c1++ : c2++;
        pc1->mem > pc2->mem ? c1++ : c2++;
        cmp_gpu(pc1->cpu_type, pc2->cpu_type) == 0 ? c1++ : c2++;
        pc1->gpu_mem > pc2->gpu_mem ? c1++ : c2++;
        cmp_hdd(pc1->cpu_type, pc2->cpu_type) == 0 ? c1++ : c2++;
        pc1->devices > pc2->devices ? c1++ : c2++;
        cmp_os(pc1->cpu_type, pc2->cpu_type) == 0 ? c1++ : c2++;

        if (c1 < c2) {
            best = pc2;
        }
    }

    return best;
}