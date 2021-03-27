#define print_expression($x)         \
    switch ($x.type)                 \
    {                                \
    case INT_T:                      \
        printf("%d", $x.int_val);    \
        break;                       \
    case REAL_T:                     \
        printf("%f", $x.real_val);   \
        break;                       \
    case STRING_T:                   \
        printf("%s", $x.string_val); \
        break;                       \
    }
