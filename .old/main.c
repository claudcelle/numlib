#include <stdio.h>

#include "lib.h"

int main(void)
{
    Vector iv = make_int_vector(4);
    Vector fv = make_float_vector(4);
    int i_value = 0;
    float f_value = 0.0f;

    vector_push_int(&iv, 2);
    vector_push_int(&iv, 4);
    vector_push_int(&iv, 6);
    vector_push_int(&iv, 8);

    vector_push_float(&fv, 1.5f);
    vector_push_float(&fv, 2.5f);
    vector_push_float(&fv, 3.5f);
    vector_push_float(&fv, 4.5f);

    printf("int vector: ");
    for (size_t i = 0; i < iv.size; i++) {
        vector_get_int(&iv, i, &i_value);
        printf("%d ", i_value);
    }
    printf("\n");

    printf("float vector: ");
    for (size_t i = 0; i < fv.size; i++) {
        vector_get_float(&fv, i, &f_value);
        printf("%.2f ", f_value);
    }
    printf("\n");

    vector_free(&iv);
    vector_free(&fv);

    return 0;
}
