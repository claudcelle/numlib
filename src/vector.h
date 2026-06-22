#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

// typedef enum DoubleVectorKind{
//     INT = 0,
//     DOUBLE = 1
// }

typedef struct DoubleVector {
    size_t size;
    double *data;
} double_vector_t;

double_vector_t double_vector_create(size_t);
void double_vector_free(double_vector_t*);
void double_vector_print(const double_vector_t*);
int double_vector_set(double_vector_t*, size_t, double);
double double_vector_get(const double_vector_t*, size_t);
int double_vector_add(const double_vector_t*,const double_vector_t*,double_vector_t*);
int double_vector_fill_from_array(double_vector_t *v,const double *array, size_t size);
size_t double_vector_size(const double_vector_t*);

int double_vector_scale(const double_vector_t*, double, double_vector_t*);
int double_vector_axpy(double a, double_vector_t*, double_vector_t*, double_vector_t*);

#endif