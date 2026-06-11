#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct Vector {
    size_t size;
    double *data;
} vector_t;

vector_t vector_create(size_t);
void vector_free(vector_t*);
void vector_print(const vector_t*);
int vector_set(vector_t*, size_t, double);
double vector_get(const vector_t*, size_t);
int vector_add(const vector_t*,const vector_t*,vector_t*);
int vector_fill_from_array(vector_t *v,const double *array, size_t size);
size_t vector_size(const vector_t*);


int main(){

    vector_t a = vector_create(3);
    vector_t b = vector_create(3);
    vector_t out = vector_create(3);

    if (!vector_fill_from_array(&a, (double[]){1., 2., 3.}, 3)) {
        printf("FAIL: fill a\n");
    }

    if (!vector_fill_from_array(&b, (double[]){4., 5., 6.}, 3)) {
        printf("FAIL: fill b\n");
    }

    if (!vector_add(&a, &b, &out)) {
        printf("FAIL: vector_add valid input\n");
    }

    printf("Expected: [ 5.000000, 7.000000, 9.000000 ]\n");
    printf("Got:      ");
    vector_print(&out);

    if (vector_fill_from_array(&b, (double[]){4., 5.}, 2)) {
        printf("FAIL: fill should reject wrong size\n");
    }

    vector_t bad = {0};

    if (vector_add(&a, &bad, &out)) {
        printf("FAIL: vector_add should reject null data\n");
    }

    if (vector_add(NULL, &b, &out)) {
        printf("FAIL: vector_add should reject NULL vector\n");
    }

    vector_free(&a);
    vector_free(&b);
    vector_free(&out);

    return 0;
}
vector_t vector_create(size_t size){
    vector_t v = {0};
    if (size==0){
        return v;
    }
    double *data = malloc(size*sizeof(double));
    if (data==NULL){
        return v;
    }
    v.size = size;
    v.data = data;
    return v;
}
void vector_free(vector_t *v){
    if (v == NULL){
        return;
    }
    free(v->data);
    v->data = NULL;
    v->size = 0;
}

void vector_print(const vector_t *v){
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

int vector_set(vector_t* v, size_t index, double element){
    if (v == NULL||v->data == NULL){
        return 0;
    }
    if (index>=v->size){
        return 0;
    }
    v->data[index] = element;
    return 1;
}
double vector_get(const vector_t* v, size_t index){
    if (v == NULL||v->data == NULL){
        return NAN;
    }
    if (index>=v->size){
        return NAN;
    }
    return v->data[index];
}

size_t vector_size(const vector_t* v){
    if (v == NULL||v->data == NULL){
        return 0;
    }
    return v->size;
}

int vector_fill_from_array(vector_t *v,const double *array,size_t size){
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

int vector_add(const vector_t *a, const vector_t *b, vector_t *out){

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