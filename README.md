# NUMERICAL LIBRARY FOR STOCHASTIC DIFFERENTIAL EQUATIONS (SDE) INTEGRATION


### STATE OF ART
src/vector.c contains a numerical library to be used as a base for the implementation for methodologies for the integration of stochastic differential equations 

tests/test_vector.c implements munit tests for all functions in the vector.c library
to test execute 

``` bash
gcc tests/test_vector.c src/vector.c external/munit.c -lm -o test_vector && ./test_vector
```
