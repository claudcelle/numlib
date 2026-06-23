#include "../external/munit.h"
#include "../src/vector.h"
#include <math.h>
#include <stdio.h>

#define ARRAY_LEN(a) (sizeof(a) / sizeof((a)[0]))

static MunitResult test_double_vector_create(const MunitParameter params[], void* user_data);
static MunitResult test_double_vector_create_size_zero(const MunitParameter params[], void* user_data);
static MunitResult test_double_vector_free(const MunitParameter params[], void* user_data);
static MunitResult test_double_vector_set(const MunitParameter params[], void* user_data);
static MunitResult test_double_vector_get(const MunitParameter params[], void* user_data);
static MunitResult test_double_vector_fill_from_array(const MunitParameter params[], void* user_data);
static MunitResult test_double_vector_add(const MunitParameter params[], void* user_data);
static MunitResult test_double_vector_scale(const MunitParameter params[], void* user_data);
static MunitResult test_double_vector_size(const MunitParameter params[], void* user_data);
static MunitResult test_double_vector_axpy(const MunitParameter params[], void* user_data);
static MunitResult test_double_vector_dotproduct(const MunitParameter params[], void* user_data);
static MunitResult test_double_vector_norm2(const MunitParameter params[], void* user_data);
static MunitResult test_double_vector_weird_size_zero(const MunitParameter params[], void* user_data);
static MunitResult test_double_vector_dist2(const MunitParameter params[], void* user_data);
static MunitResult test_double_vector_copy(const MunitParameter params[], void* user_data);
static MunitResult test_double_vector_fill_const(const MunitParameter params[], void* user_data);
static MunitResult test_double_vector_sum(const MunitParameter params[], void* user_data);


static MunitTest tests[] = {
    // { "/empty", test_empty, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/double_vector_create",test_double_vector_create, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/double_vector_create_size_zero",test_double_vector_create_size_zero, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/double_vector_free",test_double_vector_free, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/double_vector_set",test_double_vector_set, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/double_vector_get",test_double_vector_get, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/double_vector_fill_from_array",test_double_vector_fill_from_array, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/double_vector_add",test_double_vector_add, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/double_vector_scale",test_double_vector_scale, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/double_vector_size",test_double_vector_size, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/double_vector_axpy",test_double_vector_axpy, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/double_vector_dotproduct",test_double_vector_dotproduct, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/double_vector_norm2",test_double_vector_norm2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/double_vector_weird_size_zero",test_double_vector_weird_size_zero, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/double_vector_dist2",test_double_vector_dist2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/double_vector_copy",test_double_vector_copy, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/double_vector_fill_const",test_double_vector_fill_const, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/double_vector_sum",test_double_vector_sum, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/double_vector",
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
static MunitResult test_double_vector_sum(const MunitParameter params[], void* user_data){
    (void) params;
    (void) user_data;

    size_t size = 3;
    double_vector_t v = double_vector_create(size);
    double_vector_t empty = {0};
    double result;

    double v_vals[3] = {1.0,2.0,3.0};
    double_vector_fill_from_array(&v,v_vals,size);

    munit_assert_int(double_vector_sum(&v,&result), ==, 1);
    munit_assert_double_equal(result, 6.0, 6);

    munit_assert_int(double_vector_sum(&v,NULL), ==, 0);
    munit_assert_int(double_vector_sum(NULL,&result), ==, 0);
    munit_assert_int(double_vector_sum(&empty,&result), ==, 0);
    
    double_vector_free(&v);
    return MUNIT_OK;
}
static MunitResult test_double_vector_fill_const(const MunitParameter params[], void* user_data){
    (void) params;
    (void) user_data;

    size_t size = 3;
    double_vector_t v = double_vector_create(size);
    double_vector_t empty = {0};

    munit_assert_int(double_vector_fill_const(&v,1.0), ==, 1);
    for (size_t i=0;i<size;i++){
        munit_assert_double(v.data[i], ==, 1.0);
    }

    munit_assert_int(double_vector_fill_const(NULL,1.0), ==, 0);
    munit_assert_int(double_vector_fill_const(&empty,1.0), ==, 0);
    
    double_vector_free(&v);
    return MUNIT_OK;
}

static MunitResult test_double_vector_copy(const MunitParameter params[], void* user_data){
    (void) params;
    (void) user_data;

    size_t size = 3;
    size_t bad_size = 4;
    double_vector_t v = double_vector_create(size);
    double_vector_t w = double_vector_create(size); 
    double_vector_t empty = {0};
    double_vector_t wrong_size = double_vector_create(bad_size);

    double v_vals[] = {1.0,2.0,3.0};
    double_vector_fill_from_array(&v,v_vals,size); 

    munit_assert_int(double_vector_copy(&v,&w), ==, 1);
    munit_assert_not_null(w.data);
    munit_assert_size(w.size, ==, v.size);
    for (size_t i=0;i<w.size;i++){
        munit_assert_double(w.data[i], ==, v.data[i]);
    }

    munit_assert_int(double_vector_copy(NULL,&w), ==, 0);
    munit_assert_int(double_vector_copy(&v,NULL), ==, 0);

    munit_assert_int(double_vector_copy(&empty,&w), ==, 0);
    munit_assert_int(double_vector_copy(&v,&empty), ==, 0);
    munit_assert_int(double_vector_copy(&v,&wrong_size), ==, 0);
    munit_assert_int(double_vector_copy(&wrong_size,&w), ==, 0);


    double_vector_free(&w);
    double_vector_free(&v);
    double_vector_free(&empty);
    double_vector_free(&wrong_size);
    
    return MUNIT_OK;
}


static MunitResult test_double_vector_create(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    
    double_vector_t v = double_vector_create(3);

    munit_assert_size(v.size, ==, 3);
    munit_assert_not_null(v.data);
    for (size_t i=0;i<v.size;i++){
        munit_assert_double(v.data[i], ==, 0.0);      
    }

    double_vector_free(&v);
    return MUNIT_OK;
}
static MunitResult test_double_vector_create_size_zero(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    
    double_vector_t w = double_vector_create(0);
    munit_assert_null(w.data);
    munit_assert_size(w.size, ==, 0);

    return MUNIT_OK;
}
static MunitResult test_double_vector_free(const MunitParameter params[], void* user_data){
    (void) params;
    (void) user_data;
    double_vector_t v = double_vector_create(3);
    double_vector_free(&v);
    munit_assert_null(v.data);
    munit_assert_size(v.size, ==, 0);
    return MUNIT_OK;
}
static MunitResult test_double_vector_set(const MunitParameter params[], void* user_data){
    (void) params;
    (void) user_data;
    double_vector_t v = double_vector_create(3);
    munit_assert_int(double_vector_set(&v,0,1.0), ==, 1);
    munit_assert_double(v.data[0], ==, 1.0);
    munit_assert_int(double_vector_set(&v,v.size,1.0), ==, 0);
    double_vector_free(&v);
    return MUNIT_OK;
    
}
static MunitResult test_double_vector_get(const MunitParameter params[], void* user_data){
    (void) params;
    (void) user_data;
    double_vector_t v = double_vector_create(3);
    double_vector_set(&v,0,1.0);
    double value = double_vector_get(&v,0);

    munit_assert_double(value, ==, 1.0);
    munit_assert(isnan(double_vector_get(&v,v.size)));
    double_vector_free(&v);
    munit_assert(isnan(double_vector_get(&v,0)));
    munit_assert(isnan(double_vector_get(NULL,0)));

    return MUNIT_OK;
    
}
static MunitResult test_double_vector_fill_from_array(const MunitParameter params[], void* user_data){
    (void) params;
    (void) user_data;
    double_vector_t v = double_vector_create(3);
    double values[] = {1.0,2.0,3.0};
    munit_assert_int(double_vector_fill_from_array(&v,values,3), ==, 1);
    munit_assert_double(v.data[0], ==, 1.0);
    munit_assert_double(v.data[1], ==, 2.0);
    munit_assert_double(v.data[2], ==, 3.0);
    munit_assert_int(double_vector_fill_from_array(&v,values,2), ==, 0);
    munit_assert_int(double_vector_fill_from_array(NULL,values,3), ==, 0);
    munit_assert_int(double_vector_fill_from_array(&v,NULL,3), ==, 0);

    
    double new_values[] = {4.0,5.0,6.0};
    munit_assert_int(double_vector_fill_from_array(&v,new_values,3), ==, 1);
    munit_assert_double(v.data[0], ==, 4.0);
    munit_assert_double(v.data[1], ==, 5.0);
    munit_assert_double(v.data[2], ==, 6.0);
    double_vector_free(&v);
    munit_assert_int(double_vector_fill_from_array(&v,values,3), ==, 0);

    return MUNIT_OK;    
}
static MunitResult test_double_vector_add(const MunitParameter params[], void* user_data){
    (void) params;
    (void) user_data;

    double_vector_t v = double_vector_create(3);
    double_vector_t w = double_vector_create(3);
    double_vector_t k = double_vector_create(4);
    double_vector_t empty = {0};
    double_vector_t result = double_vector_create(3);

    double v_vals[] = {1.0,2.0,3.0};
    double w_vals[] = {4.0,5.0,6.0};
    double_vector_fill_from_array(&v,v_vals,3);
    double_vector_fill_from_array(&w,w_vals,3);

    munit_assert_int(double_vector_add(&v,&w,&result), ==, 1);
    munit_assert_double(result.data[0], ==, 5.0);
    munit_assert_double(result.data[1], ==, 7.0);
    munit_assert_double(result.data[2], ==, 9.0);
    munit_assert_int(double_vector_add(&v,&w,&k), ==, 0);
    munit_assert_int(double_vector_add(&v,&k,&result), ==, 0);
    munit_assert_int(double_vector_add(&k,&w,&result), ==, 0);
    munit_assert_int(double_vector_add(NULL,&w,&result), ==, 0);
    munit_assert_int(double_vector_add(&v,NULL,&result), ==, 0);
    munit_assert_int(double_vector_add(&v,&w,NULL), ==, 0);

    munit_assert_int(double_vector_add(&empty,&w,&result), ==, 0);
    munit_assert_int(double_vector_add(&v,&empty,&result), ==, 0);
    munit_assert_int(double_vector_add(&v,&w,&empty), ==, 0);



    double_vector_free(&v);
    double_vector_free(&w);
    double_vector_free(&k);
    double_vector_free(&empty);
    double_vector_free(&result);
    return MUNIT_OK;

}
static MunitResult test_double_vector_scale(const MunitParameter params[], void* user_data){
    (void) params;
    (void) user_data;

    double v_vals[] = {1.0,2.0,3.0};
    double_vector_t v = double_vector_create(3);
    double_vector_t result = double_vector_create(3);
    double_vector_t empty = {0};
    double_vector_t wrong_size = double_vector_create(4);

    double_vector_fill_from_array(&v,v_vals,3);
    
    munit_assert_int(double_vector_scale(&v,2.0,&result), ==, 1);
    munit_assert_double(result.data[0], ==, 2.0);
    munit_assert_double(result.data[1], ==, 4.0);
    munit_assert_double(result.data[2], ==, 6.0);

    munit_assert_int(double_vector_scale(&v,2.0,NULL), ==, 0);
    munit_assert_int(double_vector_scale(NULL,2.0,&result), ==, 0);
    munit_assert_int(double_vector_scale(&v,2.0,&empty), ==, 0);
    munit_assert_int(double_vector_scale(&empty,2.0,&result), ==, 0);

    munit_assert_int(double_vector_scale(&wrong_size,2.0,&result), ==, 0);
    munit_assert_int(double_vector_scale(&v,2.0,&wrong_size), ==, 0);


    double_vector_free(&v);
    double_vector_free(&empty);
    double_vector_free(&result);
    double_vector_free(&wrong_size);


    return MUNIT_OK;
}
static MunitResult test_double_vector_size(const MunitParameter params[], void* user_data){
    (void) params;
    (void) user_data;

    double_vector_t v = double_vector_create(3);
    double_vector_t empty = {0};

    munit_assert_size(double_vector_size(&v), ==, 3);
    munit_assert_size(double_vector_size(NULL), ==, 0);
    munit_assert_size(double_vector_size(&empty), ==, 0);
    
    double_vector_free(&v);
    munit_assert_size(double_vector_size(&v), ==, 0);


    return MUNIT_OK;
}
static MunitResult test_double_vector_axpy(const MunitParameter params[], void* user_data){
    (void) params;
    (void) user_data;

    double a = 2.;
    double_vector_t x = double_vector_create(3);
    double_vector_t y = double_vector_create(3);
    double_vector_t out = double_vector_create(3);
    double_vector_t empty = {0};
    double_vector_t wrong_size = double_vector_create(4);

    double x_vals[] = {1.0,2.0,3.0};
    double y_vals[] = {4.0,5.0,6.0};
    double_vector_fill_from_array(&x,x_vals,3);
    double_vector_fill_from_array(&y,y_vals,3);

    munit_assert_int(double_vector_axpy(a,&x,&y,&out), ==, 1);
    munit_assert_double(out.data[0], ==, 6.0);
    munit_assert_double(out.data[1], ==, 9.0);
    munit_assert_double(out.data[2], ==, 12.0);

    munit_assert_int(double_vector_axpy(a,&x,&y,&x), ==, 1);
    munit_assert_double(x.data[0], ==, 6.0);
    munit_assert_double(x.data[1], ==, 9.0);
    munit_assert_double(x.data[2], ==, 12.0);

    double_vector_fill_from_array(&x,x_vals,3);
    double_vector_fill_from_array(&y,y_vals,3);


    munit_assert_int(double_vector_axpy(a,&x,&y,&y), ==, 1);
    munit_assert_double(y.data[0], ==, 6.0);
    munit_assert_double(y.data[1], ==, 9.0);
    munit_assert_double(y.data[2], ==, 12.0);

    munit_assert_int(double_vector_axpy(a,&x,&y,NULL), ==, 0);
    munit_assert_int(double_vector_axpy(a,NULL,&y,&out), ==, 0);
    munit_assert_int(double_vector_axpy(a,&x,NULL,&out), ==, 0);
    munit_assert_int(double_vector_axpy(a,&x,&y,&empty), ==, 0);
    munit_assert_int(double_vector_axpy(a,&empty,&y,&out), ==, 0);
    munit_assert_int(double_vector_axpy(a,&x,&empty,&out), ==, 0);

    munit_assert_int(double_vector_axpy(a,&x,&wrong_size,&out), ==, 0);
    munit_assert_int(double_vector_axpy(a,&wrong_size,&y,&out), ==, 0);
    munit_assert_int(double_vector_axpy(a,&x,&y,&wrong_size), ==, 0);


    double_vector_free(&x);
    double_vector_free(&y);
    double_vector_free(&out);
    double_vector_free(&empty);
    double_vector_free(&wrong_size);



    return MUNIT_OK;
}

static MunitResult test_double_vector_dotproduct(const MunitParameter params[], void* user_data){
    (void) params;
    (void) user_data;

    double_vector_t x = double_vector_create(3);
    double_vector_t y = double_vector_create(3);
    double_vector_t empty = {0};
    double_vector_t wrong_size = double_vector_create(4);
    double result;

    double x_vals[] = {1.0,2.0,3.0};
    double y_vals[] = {4.0,5.0,6.0};
    double_vector_fill_from_array(&x,x_vals,3);
    double_vector_fill_from_array(&y,y_vals,3);

    munit_assert_int(double_vector_dotproduct(&x,&y,&result), ==, 1);
    munit_assert_double(result, ==, 32.0);

    munit_assert_int(double_vector_dotproduct(&x,&y,NULL), ==, 0);
    munit_assert_int(double_vector_dotproduct(NULL,&y,&result), ==, 0);
    munit_assert_int(double_vector_dotproduct(&x,NULL,&result), ==, 0);

    munit_assert_int(double_vector_dotproduct(&empty,&y,&result), ==, 0);
    munit_assert_int(double_vector_dotproduct(&x,&empty,&result), ==, 0);

    munit_assert_int(double_vector_dotproduct(&x,&wrong_size,&result), ==, 0);
    munit_assert_int(double_vector_dotproduct(&wrong_size,&y,&result), ==, 0);


    double_vector_free(&x);
    double_vector_free(&y);
    double_vector_free(&empty);
    double_vector_free(&wrong_size);

    return MUNIT_OK;

}

static MunitResult test_double_vector_norm2(const MunitParameter params[], void* user_data){
    (void) params;
    (void) user_data;

    double_vector_t x = double_vector_create(3);
    double_vector_t empty = {0};
    double result;

    double x_vals[] = {1.0,2.0,3.0};
    double_vector_fill_from_array(&x,x_vals,3);

    munit_assert_int(double_vector_norm2(&x,&result), ==, 1);
    munit_assert_double_equal(result, sqrt(14.0), 6);

    munit_assert_int(double_vector_norm2(&x,NULL), ==, 0);
    munit_assert_int(double_vector_norm2(NULL,&result), ==, 0);

    munit_assert_int(double_vector_norm2(&empty,&result), ==, 0);

    double_vector_free(&x);
    double_vector_free(&empty);

    return MUNIT_OK;
}

static MunitResult test_double_vector_weird_size_zero(const MunitParameter params[], void* user_data){
    (void) params;
    (void) user_data;

    double raw[] = {1.0};
    double values[] = {2.0};
    double_vector_t weird = {0, raw};
    double_vector_t valid = double_vector_create(1);
    double result;

    double_vector_fill_from_array(&valid,values,1);

    munit_assert_int(double_vector_scale(&weird,2.0,&valid), ==, 0);
    munit_assert_int(double_vector_add(&weird,&valid,&valid), ==, 0);
    munit_assert_int(double_vector_fill_from_array(&weird,values,0), ==, 0);
    munit_assert_int(double_vector_axpy(2.0,&weird,&valid,&valid), ==, 0);
    munit_assert_int(double_vector_dotproduct(&weird,&valid,&result), ==, 0);
    munit_assert_int(double_vector_norm2(&weird,&result), ==, 0);

    double_vector_free(&valid);

    return MUNIT_OK;
}

static MunitResult test_double_vector_dist2(const MunitParameter params[], void* user_data){
    (void) params;
    (void) user_data;

    size_t size = 2;
    size_t bad_size = 4;
    double_vector_t x = double_vector_create(size);
    double_vector_t y = double_vector_create(size);
    double_vector_t empty = {0};
    double_vector_t wrong_size = double_vector_create(bad_size);
    double result;

    double x_vals[] = {1.0,2.0};
    double y_vals[] = {4.0,6.0};
    double_vector_fill_from_array(&x,x_vals,ARRAY_LEN(x_vals));
    double_vector_fill_from_array(&y,y_vals,ARRAY_LEN(y_vals));

    munit_assert_int(double_vector_distance2(&x,&y,&result), ==, 1);
    munit_assert_double_equal(result, 5., 6);

    munit_assert_int(double_vector_distance2(&x,&y,NULL), ==, 0);
    munit_assert_int(double_vector_distance2(NULL,&y,&result), ==, 0);
    munit_assert_int(double_vector_distance2(&x,NULL,&result), ==, 0);

    munit_assert_int(double_vector_distance2(&empty,&y,&result), ==, 0);
    munit_assert_int(double_vector_distance2(&x,&empty,&result), ==, 0);

    munit_assert_int(double_vector_distance2(&x,&wrong_size,&result), ==, 0);
    munit_assert_int(double_vector_distance2(&wrong_size,&y,&result), ==, 0);

    double_vector_free(&x);
    double_vector_free(&y);
    double_vector_free(&empty);
    double_vector_free(&wrong_size);

    return MUNIT_OK;


}