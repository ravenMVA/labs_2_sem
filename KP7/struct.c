#include "struct.h"

#include "struct.h"

// Function to create a vector
vector* create_vector(int volume) {
    vector* v = (vector*)malloc(sizeof(vector));
    v->size = 0;
    v->volume = volume;
    v->data = calloc(volume, sizeof(double));
    return v;
}

// Function to print the values of a vector
void print_vector(vector* v) {
    if (v == NULL) {
        return;
    }
    for (int i = 0; i < v->size; i++) {
        printf("[%.1lf] ", v->data[i]);
    }
    printf("\n");
    return;
}

// Function to add a value to a vector
void add(vector* v, double value) {
    if (v->size >= v->volume) {
        v->volume++;
        v->data = (double*)realloc(v->data, v->volume * sizeof(double));
    }
    v->data[v->size++] = value;
    return;
}

// Function to free the memory allocated for a vector
void free_vector(vector* v) {
    free(v->data);
    v->data = NULL;
    free(v);
    return;
}

// Function to read a matrix from a file and convert it to a sparse representation
sparse* read_matrix(FILE* fd) {
    int rows, cols;
    if (fscanf(fd, "%d %d", &rows, &cols) != 2) {
        return NULL; // Failed to read matrix size, so assume end of file
    }
    double matrix[cols][rows];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fscanf(fd, "%lf", &matrix[i][j]);
        }
    }
    sparse* sp = (sparse*)malloc(sizeof(sparse));
    sp->rows = rows;
    sp->cols = cols;
    sp->cip = create_vector(rows);
    sp->pi = create_vector(cols * rows + 1);
    sp->ye = create_vector(cols * rows);
    for (int i = 0; i < rows; i++) {
        bool has_values = false;
        int col_start = sp->pi->size;
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0.0) {
                continue;
            }
            has_values = true;
            add(sp->ye, matrix[i][j]);
            add(sp->pi, j + 1);
        }
        if (has_values) {
            add(sp->cip, col_start);
        } else {
            add(sp->cip, -1); // If no values in the row
        }
    }
    add(sp->pi, 0.0);
    return sp;
}

// Function to print the sparse representation of a matrix
void print_sparse(sparse* sp) {
    printf("CIP: ");
    print_vector(sp->cip);
    printf("PI:  ");
    print_vector(sp->pi);
    printf("YE:  ");
    print_vector(sp->ye);
}

// Function to transform the sparse representation of a matrix
void transform(sparse* sp) {
    double max = 0;
    int max_col = 0;
    int col = 0;
    int prev_col = 0;
    for (int i = 0; i < sp->ye->size; i++) {
        double value = fabs(sp->ye->data[i]);
        if (value > max) {
            max_col = 0;
        }
        if (value >= max) {
            max = value;
            col = (int)sp->pi->data[i];
            if (col > max_col) {
                if (max_col == 0) {
                    prev_col = col;
                } else {
                    prev_col = max_col;
                }
                max_col = col;
            }
        }
    }
    for (int i = 0; sp->pi->data[i] != 0.0; i++) {
        col = (int)sp->pi->data[i];
        if (col == prev_col) {
            sp->ye->data[i] /= max;
        }
    }
    return;
}

// Function to print the sparse representation of a matrix as a regular matrix
void print_as_regular(sparse* sp) {
    for (int i = 0; i < sp->rows; i++) {
        double row[sp->cols];
        for (int r = 0; r < sp->cols; r++) {
            row[r] = 0.0;
        }
        // Set the lower bound in PI for the current row
        int l_bound = sp->cip->data[i];
        if (l_bound != -1) {
            int up_idx = i + 1;
            int r_bound;
            // Handle the condition for the last row
            if (up_idx >= sp->rows) {
                r_bound = sp->pi->size - 1;
            } else {
                r_bound = sp->cip->data[up_idx];
            }
            // Shift the right index bound if -1
            while (r_bound == -1) {
                up_idx++;
                r_bound = sp->cip->data[up_idx];
            }
            for (int p = l_bound; p < r_bound; p++) {
                int col = sp->pi->data[p];
                row[col - 1] = sp->ye->data[p];
            }
        }
        for (int r = 0; r < sp->cols; r++) {
            printf("|%.1lf| ", row[r]);
        }
        printf("\n");
    }
    return;
}

// Function to free the memory allocated for a sparse matrix
void free_sparse(sparse* v) {
    if (v == NULL) {
        return;
    }
    free_vector(v->cip);
    free_vector(v->pi);
    free_vector(v->ye);
    free(v);
    return;
}
