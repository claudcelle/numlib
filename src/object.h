typedef enum ObjectKind{
    STRING = 0,
    INT = 1,
    FLOAT = 2,
    ARRAY = 3
}  object_kind_t;

typedef union ObjectData{
    char *string;
    int integer;
    float real;
    object_t *array;
} object_data_t;

typedef struct Object{
    object_kind_t kind;
    object_data_t data;
} object_t;