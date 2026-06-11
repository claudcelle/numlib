#include "lib.h"

#include <stdlib.h>

#define DEFINE_VECTOR_FUNCTIONS(TYPE, VTYPE, PREFIX)                                   \
    static size_t PREFIX##_length_range(TYPE start, TYPE stop, TYPE step)             \
    {                                                                                  \
        size_t n = 0;                                                                  \
                                                                                       \
        if (step == 0) {                                                               \
            return 0;                                                                  \
        }                                                                              \
        if ((step > 0 && start >= stop) || (step < 0 && start <= stop)) {             \
            return 0;                                                                  \
        }                                                                              \
        for (TYPE value = start;                                                      \
             (step > 0) ? (value < stop) : (value > stop);                             \
             value += step) {                                                          \
            n++;                                                                       \
        }                                                                              \
        return n;                                                                      \
    }                                                                                  \
                                                                                       \
    static VTYPE##Vector PREFIX##_make_vector(size_t size)                             \
    {                                                                                  \
        VTYPE##Vector v;                                                               \
                                                                                       \
        v.data = size == 0 ? NULL : malloc(size * sizeof(TYPE));                      \
        v.size = v.data == NULL ? 0 : size;                                            \
        return v;                                                                      \
    }                                                                                  \
                                                                                       \
    void PREFIX##_vector_free(VTYPE##Vector *v)                                        \
    {                                                                                  \
        if (v == NULL) {                                                               \
            return;                                                                    \
        }                                                                              \
        free(v->data);                                                                 \
        v->data = NULL;                                                                \
        v->size = 0;                                                                   \
    }

#define DEFINE_LINSPACE_ARANGE(TYPE, VTYPE, PREFIX)                                    \
    VTYPE##Vector PREFIX##_arange(TYPE start, TYPE stop, TYPE step)                    \
    {                                                                                  \
        VTYPE##Vector v = PREFIX##_make_vector(PREFIX##_length_range(start, stop, step)); \
        size_t i = 0;                                                                  \
                                                                                       \
        for (TYPE value = start; v.data != NULL && i < v.size; value += step) {        \
            v.data[i++] = value;                                                       \
        }                                                                              \
        return v;                                                                      \
    }                                                                                  \
                                                                                       \
    VTYPE##Vector PREFIX##_linspace(TYPE start, TYPE stop, size_t count)               \
    {                                                                                  \
        VTYPE##Vector v = PREFIX##_make_vector(count);                                 \
                                                                                       \
        if (v.data == NULL || count == 0) {                                            \
            return v;                                                                  \
        }                                                                              \
        if (count == 1) {                                                              \
            v.data[0] = start;                                                         \
            return v;                                                                  \
        }                                                                              \
        for (size_t i = 0; i < count; i++) {                                           \
            float t = (float)i / (float)(count - 1);                                   \
            v.data[i] = (TYPE)(start + (stop - start) * t);                            \
        }                                                                              \
        return v;                                                                      \
    }

DEFINE_VECTOR_FUNCTIONS(int, Int, int)
DEFINE_VECTOR_FUNCTIONS(float, Float, float)
DEFINE_LINSPACE_ARANGE(int, Int, int)
DEFINE_LINSPACE_ARANGE(float, Float, float)
