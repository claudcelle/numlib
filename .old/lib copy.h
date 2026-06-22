#ifndef LIB_H
#define LIB_H

#include <stddef.h>

typedef struct {
    int *data;
    size_t size;
} IntVector;

typedef struct {
    float *data;
    size_t size;
} FloatVector;

IntVector int_arange(int start, int stop, int step);
IntVector int_linspace(int start, int stop, size_t count);
FloatVector float_arange(float start, float stop, float step);
FloatVector float_linspace(float start, float stop, size_t count);

void int_vector_free(IntVector *v);
void float_vector_free(FloatVector *v);

#endif
