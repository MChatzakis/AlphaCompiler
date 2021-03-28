typedef enum VAL_TYPES
{
    NIL_VAL,
    INT_VAL,
    REAL_VAL,
    STRING_VAL,
    BOOL_VAL
} VAL_TYPES;

typedef struct gen_value
{
    VAL_TYPES type;

    short bool_val;
    int int_val;

    double real_val;
    char *string_val;

} gen_value;