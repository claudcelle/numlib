#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>



int double_vector_scale(const double_vector_t *v, double scalar, double_vector_t *out){
    if(v==NULL||out==NULL||v->data==NULL||out->data==NULL||v->size!=out->size){
        return 0;
    }
    for (size_t i=0;i<v->size;i++){
        out->data[i] = scalar * v->data[i];
    }
    return 1;
}



double_vector_t double_vector_create(size_t size){
    double_vector_t v = {0};
    if (size==0){
        return v;
    }
    double *data = calloc(size,sizeof(double));
    if (data==NULL){
        return v;
    }
    v.size = size;
    v.data = data;
    return v;
}
void double_vector_free(double_vector_t *v){
    if (v == NULL){
        return;
    }
    free(v->data);
    v->data = NULL;
    v->size = 0;
}

void double_vector_print(const double_vector_t *v){
    if (v == NULL||v->data == NULL){
        printf("[ ]\n");
        return;
    }
    printf("[ ");
    size_t cap = v->size;
    for (size_t i=0; i<cap; i++){
        if (i==cap-1){
            printf("%f",v->data[i]); 
        }else{
        printf("%f, ",v->data[i]); 
        }
    }
    printf(" ]\n");
}

int double_vector_set(double_vector_t* v, size_t index, double element){
    if (v == NULL||v->data == NULL){
        return 0;
    }
    if (index>=v->size){
        return 0;
    }
    v->data[index] = element;
    return 1;
}
double double_vector_get(const double_vector_t* v, size_t index){
    if (v == NULL||v->data == NULL){
        return NAN;
    }
    if (index>=v->size){
        return NAN;
    }
    return v->data[index];
}

size_t double_vector_size(const double_vector_t* v){
    if (v == NULL||v->data == NULL){
        return 0;
    }
    return v->size;
}

int double_vector_fill_from_array(double_vector_t *v,const double *array,size_t size){
    if (v == NULL || 
        v->data == NULL || 
        array == NULL|| 
        v->size!=size){

        return 0;
    }
    
    for (size_t i=0;i<size;i++){
        v->data[i]=array[i];
    }
    return 1;
}

int double_vector_add(const double_vector_t *a, const double_vector_t *b, double_vector_t *out){

    if (a == NULL || b == NULL || out==NULL){
        return 0;
    }
    if (a->data == NULL || b->data == NULL || out->data==NULL){
        return 0;
    }
    if (a->size != b->size || 
        b->size != out->size ){
            return 0;
        }
    
    for (size_t i=0; i<out->size;i++){

       out->data[i] = a->data[i]+b->data[i];
    }
    return 1;

}

int double_vector_axpy(double a, double_vector_t *x, double_vector_t *y, double_vector_t *out){
    if (x == NULL || y == NULL || out==NULL){
        return 0;
    }
    if (x->data == NULL || y->data == NULL || out->data==NULL){
        return 0;
    }
    if (x->size != y->size || 
        y->size != out->size ){
            return 0;
        }
    
    for (size_t i=0; i<out->size;i++){

       out->data[i] = (a*x->data[i])+y->data[i];
    }
    return 1;
}