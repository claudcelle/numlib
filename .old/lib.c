#include "lib.h"

#include <stdlib.h>

static size_t element_size(VecType type)
{
    if (type == VEC_INT) {
        return sizeof(int);
    }
    if (type == VEC_FLOAT) {
        return sizeof(float);
    }
    return 0;
}

static Vector make_vector(size_t capacity, VecType type)
{
    Vector v;
    size_t bytes = capacity * element_size(type);

    v.data = bytes == 0 ? NULL : malloc(bytes);
    v.size = 0;
    v.capacity = v.data == NULL ? 0 : capacity;
    v.type = type;
    return v;
}

Vector make_int_vector(size_t capacity)
{
    return make_vector(capacity, VEC_INT);
}

Vector make_float_vector(size_t capacity)
{
    return make_vector(capacity, VEC_FLOAT);
}

static int resize_vector(Vector *v, size_t new_capacity)
{
    void *new_data;
    size_t bytes;

    if (v == NULL) {
        return 0;
    }
    bytes = new_capacity * element_size(v->type);
    new_data = realloc(v->data, bytes);
    if (new_data == NULL && bytes != 0) {
        return 0;
    }
    v->data = new_data;
    v->capacity = new_data == NULL ? 0 : new_capacity;
    if (v->size > v->capacity) {
        v->size = v->capacity;
    }
    return 1;
}

int vector_push_int(Vector *v, int value)
{
    if (v == NULL || v->type != VEC_INT) {
        return 0;
    }
    if (v->size == v->capacity) {
        size_t new_capacity = v->capacity == 0 ? 1 : v->capacity * 2;

        if (!resize_vector(v, new_capacity)) {
            return 0;
        }
    }
    ((int *)v->data)[v->size] = value;
    v->size++;
    return 1;
}

int vector_push_float(Vector *v, float value)
{
    if (v == NULL || v->type != VEC_FLOAT) {
        return 0;
    }
    if (v->size == v->capacity) {
        size_t new_capacity = v->capacity == 0 ? 1 : v->capacity * 2;

        if (!resize_vector(v, new_capacity)) {
            return 0;
        }
    }
    ((float *)v->data)[v->size] = value;
    v->size++;
    return 1;
}

void vector_free(Vector *v)
{
    if (v == NULL) {
        return;
    }
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
    v->type = VEC_INT;
}

int vector_get_int(const Vector *v, size_t index, int *out)
{
    if (v == NULL || out == NULL || v->type != VEC_INT || index >= v->size) {
        return 0;
    }
    *out = ((int *)v->data)[index];
    return 1;
}

int vector_get_float(const Vector *v, size_t index, float *out)
{
    if (v == NULL || out == NULL || v->type != VEC_FLOAT || index >= v->size) {
        return 0;
    }
    *out = ((float *)v->data)[index];
    return 1;
}


