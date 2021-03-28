#define print_gen($x)                 \
    switch ($x.type)                  \
    {                                 \
    case INT_VAL:                     \
        printf("%d\n", $x.int_val);     \
        break;                        \
    case REAL_VAL:                    \
        printf("%f\n", $x.real_val);    \
        break;                        \
    case STRING_VAL:                  \
        printf("%s\n", $x.string_val);  \
        break;                        \
    case NIL_VAL:                     \
        printf("NUL\n");                \
        break;                        \
    case BOOL_VAL:                    \
        if ($x.bool_val)              \
            printf("TRUE\n");         \
        else                          \
            printf("FALSE\n");        \
        break;                        \
    default:                          \
        printf("Wrong value type\n"); \
    }
