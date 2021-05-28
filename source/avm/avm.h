#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef enum vmopcode
{
    assign_v,
    add_v,
    sub_v,
    mul_v,
    div_v,
    mod_v,
    uminus_v,
    and_v,
    or_v,
    not_v,
    jump_v,
    jeq_v,
    jne_v,
    jle_v,
    jge_v,
    jlt_v,
    jgt_v,
    call_v,
    pusharg_v,
    ret_v,
    funcenter_v,
    funcexit_v,
    newtable_v,
    tablegetelem_v,
    tablesetelem_v,
    nop_v
} vmopcode;

typedef enum vmarg_t
{
    label_a = 0,
    global_a = 1,
    formal_a = 2,
    local_a = 3,
    number_a = 4,
    string_a = 5,
    bool_a = 6,
    nil_a = 7,
    userfunc_a = 8,
    libfunc_a = 9,
    retval_a = 10
} vmarg_t;

typedef struct vmarg
{
    vmarg_t type;
    unsigned val;
} vmarg;

typedef struct instruction
{
    vmopcode opcode;
    vmarg result;
    vmarg arg1;
    vmarg arg2;
    unsigned srcLine;
} instruction;

typedef struct userfunc
{
    unsigned address;
    unsigned localSize;
    char *id;
} userfunc;

double *numConsts;
unsigned totalNumConsts;
char **stringConsts;
unsigned totalStringConsts;
char **namedLibfuncs;
unsigned totalNamedLibfuncs;
userfunc *userFuncs;
unsigned totalUserFuncs;

typedef enum avm_memcell_t
{
    number_m = 0,
    string_m = 1,
    bool_m = 2,
    table_m = 3,
    userfunc_m = 4,
    libfunc_m = 5,
    nil_m = 6,
    undef_m = 7
} avm_memcell_t;

struct avm_table;
typedef struct avm_memcell
{
    avm_memcell_t type;
    union
    {
        double numVal;
        char *strVal;
        unsigned char boolVal;
        struct avm_table *tableVal;
        unsigned funcVal;
        char *libfuncVal;
    } data;
} avm_memcell;

#define AVM_STACKSIZE 4096
#define AVM_WIPEOUT(m) memset(&(m), 0, sizeof(m))

avm_memcell stack[AVM_STACKSIZE];
static void avm_initstack()
{
    for (unsigned i = 0; i < AVM_STACKSIZE; ++i)
    {
        AVM_WIPEOUT(stack[i]);
        stack[i].type = undef_m;
    }
}
struct avm_table;
struct avm_table *avm_tablenew();
void avm_tabledestroy(struct avm_table *t);
//avm_memcell *avm_tablegetelem(avm_memcell *key);
//void avm_tablesetelem(avm_memcell *key, avm_memcell *value);

#define AVM_TABLE_HASHSIZE 211

typedef struct avm_table_bucket
{

    avm_memcell key;
    avm_memcell value;
    struct avm_table_bucket *next;
} avm_table_bucket;

typedef struct avm_table
{
    unsigned refCounter;

    avm_table_bucket *strIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket *numIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket *boolIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket *userfuncIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket *libFuncIndexed[AVM_TABLE_HASHSIZE];

    unsigned total;
} avm_table;

void avm_tableincrefcounter(avm_table *t)
{
    ++t->refCounter;
}

void avm_tabledecrefcounter(avm_table *t)
{
    assert(t->refCounter > 0);
    if (!--t->refCounter)
        avm_tabledestroy(t);
}

void avm_tablebucketsinit(avm_table_bucket **p)
{
    for (unsigned i = 0; i < AVM_TABLE_HASHSIZE; ++i)
        p[i] = (avm_table_bucket *)0;
}

avm_table *avm_tablenew(void)
{
    avm_table *t = (avm_table *)malloc(sizeof(avm_table));
    AVM_WIPEOUT(*t);
    t->refCounter = t->total = 0;
    avm_tablebucketsinit(t->numIndexed);
    avm_tablebucketsinit(t->strIndexed);

    avm_tablebucketsinit(t->userfuncIndexed);
    avm_tablebucketsinit(t->libFuncIndexed);
    avm_tablebucketsinit(t->boolIndexed);

    return t;
}

void avm_memcellclear(avm_memcell *m);
typedef void (*memclear_func_t)(avm_memcell *);

extern void memclear_string(avm_memcell *m)
{
    assert(m->data.strVal);
    free(m->data.strVal);
}

extern void memclear_table(avm_memcell *m)
{
    assert(m->data.tableVal);
    avm_tabledecrefcounter(m->data.tableVal);
}

memclear_func_t memclearFuncs[] = {
    0, //number
    memclear_string,
    0, //bool
    memclear_table,
    0, //userfunc
    0, //libfunc
    0, //nil
    0  //undef
};

void avm_memcellclear(avm_memcell *m)
{
    if (m->type != undef_m)
    {
        memclear_func_t f = memclearFuncs[m->type];
        if (f)
            (*f)(m);
        m->type = undef_m;
    }
}

void avm_tablebucketsdestroy(avm_table_bucket **p)
{
    for (unsigned i = 0; i < AVM_TABLE_HASHSIZE; ++i, ++p)
    {
        for (avm_table_bucket *b = *p; b;)
        {
            avm_table_bucket *del = b;
            b = b->next;
            avm_memcellclear(&del->key);
            avm_memcellclear(&del->value);
            free(del);
        }
        p[i] = (avm_table_bucket *)0;
    }
}

void avm_tabledestroy(avm_table *t)
{
    avm_tablebucketsdestroy(t->strIndexed);
    avm_tablebucketsdestroy(t->numIndexed);
    free(t);
}

typedef struct incomplete_jump
{
    unsigned instrNo;
    unsigned iaddress;
    struct incomplete_jump *next;
} incomplete_jump;

incomplete_jump *ij_head = (incomplete_jump *)0;
unsigned ij_total = 0;

void add_incomplete_jump(unsigned instrNo, unsigned iaddress)
{
}

/*
patch_incomplete_jumps() {
    for each incomplete jump x do {
        if x.iaddress = intermediate code size then
            instructions[x.instrNo].result = target code size;
        else
            instructions[x.instrNo].result = quads[x.iaddress].taddress;
    }
}
*/