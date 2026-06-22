#include <stdio.h>

#include "lib.h"

int main(void)
{
    IntVector iv = int_arange(0, 10, 2);
    FloatVector fv = float_linspace(0.0f, 1.0f, 5);

    printf("int_arange: ");
    for (size_t i = 0; i < iv.size; i++) {
        printf("%d ", iv.data[i]);
    }
    printf("\n");

    printf("float_linspace: ");
    for (size_t i = 0; i < fv.size; i++) {
        printf("%.2f ", fv.data[i]);
    }
    printf("\n");

    int_vector_free(&iv);
    float_vector_free(&fv);

    return 0;
}
