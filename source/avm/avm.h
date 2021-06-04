#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../yacc_libs/tcode.h"

#define AVM_STACKSIZE 4096 //is this N?
#define AVM_WIPEOUT(m) memset(&(m), 0, sizeof(m))
#define AVM_TABLE_HASHSIZE 211

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

typedef struct avm_table_bucket
{
    avm_memcell key;
    avm_memcell value;
    struct avm_table_bucket *next;
} avm_table_bucket;

typedef struct avm_table
{
    unsigned refCounter;

    avm_table_bucket *strIndexed[AVM_TABLE_HASHSIZE]; //x["string"]
    avm_table_bucket *numIndexed[AVM_TABLE_HASHSIZE]; //x[1]
    avm_table_bucket *boolIndexed[AVM_TABLE_HASHSIZE]; //x[TRUE]
    avm_table_bucket *userfuncIndexed[AVM_TABLE_HASHSIZE]; //x[func]
    avm_table_bucket *libFuncIndexed[AVM_TABLE_HASHSIZE]; //x[print]

    unsigned total;
} avm_table;

avm_memcell stack[AVM_STACKSIZE];
