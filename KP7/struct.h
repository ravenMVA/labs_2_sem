#ifndef MATRIX
#define MATRIX

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX_SIZE 100



// Define the vector data structure
typedef struct {
    double* data;     // Array to store elements
    int size;   // Current size of the vector
    int volume;
} vector;

typedef struct matrix {
    int rows, cols;
    vector* cip;
    vector* pi;
    vector* ye;
} sparse;

vector* create_vector(int volume);

void print_vector(vector* v);

void add(vector* v, double value);

void free_vector(vector* v);

sparse* read_matrix(FILE* fd);

void print_sparse(sparse* v);

// === Задание по варианту 2 ===
void transform(sparse* sp);
// =============================

void print_as_regular(sparse* sp);

void free_sparse(sparse* v);



#endif
