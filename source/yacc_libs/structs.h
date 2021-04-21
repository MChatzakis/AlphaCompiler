#include "../symboltable/symboltable.h"

typedef enum iopcode
{
    assign_op,
    add_op,
    sub_op,
    mul_op,
    div_op,
    mod_op,
    uminus_op,
    and_op,
    or_op,
    not_op,
    if_eq_op,
    if_noteq_op,
    if_lesseq_op,
    if_greatereq_op,
    if_less_op,
    if_greater_op,
    call_op,
    param_op,
    ret_op,
    getretval_op,
    funcstart_op,
    funcend_op,
    tablecreate_op,
    tablegetelem_op,
    tablesetelem_op,
    jump_op
} iopcode;

typedef enum expr_t
{
    var_e,
    tableitem_e,

    programfunc_e,
    libraryfunc_e,

    arithexpr_e,
    boolexpr_e,
    assignexpr_e,
    newtable_e,

    constnum_e,
    constbool_e,
    conststring_e,

    nil_e
} expr_t;


typedef struct expr
{
    expr_t type;
    SymbolTableEntry *sym;
    struct expr *index;
    double numConst;
    char *srtConst;
    unsigned char boolConst;
    struct expr *next;
} expr;

typedef struct quad
{
    iopcode op;
    expr *result;
    expr *arg1;
    expr *arg2;
    unsigned label;
    unsigned line;
} quad;