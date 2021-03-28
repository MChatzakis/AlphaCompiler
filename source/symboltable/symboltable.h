#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define BUCKETS 20
#define HASH_MULTIPLIER 65599

enum SymbolType
{
    GLOBAL_ID,
    LOCAL_ID,
    FORMAL_ID,
    USERFUNC_ID,
    LIBFUNC_ID
};

typedef struct Variable
{
    const char *name;
    unsigned int scope;
    unsigned int line;
} Variable;

typedef struct Function
{
    const char *name;
    //List of arguments
    unsigned int scope;
    unsigned int line;
} Function;

typedef struct SymbolTableEntry
{
    int isActive;
    union
    {
        Variable *varVal;
        Function *funcVal;
    } value;

    enum SymbolType type;
    struct SymbolTableEntry *next;

} SymbolTableEntry;

typedef struct SymbolTable
{
    SymbolTableEntry *hashtable[BUCKETS];
} SymbolTable;

unsigned int hash_function(const char *pcKey);

SymbolTable *SymbolTable_init();
SymbolTableEntry *SymbolTable_insert(SymbolTable *s, const char *id, unsigned int scope, unsigned int line, enum SymbolType type);
void SymbolTable_print(SymbolTable *s);
void SymbolTable_add_libfun(SymbolTable *s);
