#ifndef LIB_H
#define LIB_H

#include <stddef.h>

typedef enum {
    VEC_INT,
    VEC_FLOAT
} VecType;

typedef struct {
    void *data;
    size_t size;
    size_t capacity;
    VecType type;
} Vector;

Vector make_int_vector(size_t capacity);
Vector make_float_vector(size_t capacity);

int vector_push_int(Vector *v, int value);
int vector_push_float(Vector *v, float value);
void vector_free(Vector *v);

int vector_get_int(const Vector *v, size_t index, int *out);
int vector_get_float(const Vector *v, size_t index, float *out);

#endif
