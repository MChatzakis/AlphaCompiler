#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define BUCKETS 20
#define INIT_SCOPE_SIZE 50
#define HASH_MULTIPLIER 65599

#define checkForLibFunc(id)               \
    (!strcmp(id, "print") ||              \
     !strcmp(id, "input") ||              \
     !strcmp(id, "objectmemberkeys") ||   \
     !strcmp(id, "objecttotalmembers") || \
     !strcmp(id, "objectcopy") ||         \
     !strcmp(id, "totalarguments") ||     \
     !strcmp(id, "argument") ||           \
     !strcmp(id, "typeof") ||             \
     !strcmp(id, "strtonum") ||           \
     !strcmp(id, "sqrt") ||               \
     !strcmp(id, "cos") ||                \
     !strcmp(id, "sin"))

/* Symbol Types */
enum SymbolType
{
    GLOBAL_ID,
    LOCAL_ID,
    FORMAL_ID,
    USERFUNC_ID,
    LIBFUNC_ID
};

/* Symbol Table Structures*/
typedef struct Variable
{
    const char *name;
    unsigned int scope;
    unsigned int line;
} Variable;

typedef struct Function
{
    const char *name;
    //list
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
    unsigned int max_scope;
    SymbolTableEntry *hashtable[BUCKETS];
} SymbolTable;


/* Scope Structures */
typedef struct ScopeList
{
    SymbolTableEntry *entry;
    struct ScopeList *next;
} ScopeList;

typedef struct ScopeTable
{
    unsigned int max_scope;
    ScopeList **table;
} ScopeTable;



/* ------------------------------------ Hashing ------------------------------------ */
unsigned int hash_function(const char *pcKey);



/* ------------------------------------ SymbolTable Functions ------------------------------------ */
SymbolTable *SymbolTable_init();
SymbolTableEntry *SymbolTable_insert(SymbolTable *s, const char *id, unsigned int scope, unsigned int line, enum SymbolType type);
SymbolTableEntry *SymbolTable_lookup(SymbolTable *s, const char *id, unsigned int scope);
SymbolTableEntry *SymbolTable_lookup_general(SymbolTable *s, const char *id, unsigned int scope);

void SymbolTable_print(SymbolTable *s);
void SymbolTable_scope_print(SymbolTable *s);
void SymbolTable_hide(SymbolTable *s, const char *id, unsigned int scope);
void SymbolTable_add_libfun(SymbolTable *s);



/* ------------------------------------ ScopeTable Functions ------------------------------------ */
ScopeTable *ScopeTable_init();
ScopeList *ScopeTable_insert(ScopeTable *st, SymbolTableEntry *entry, unsigned int scope);
ScopeList *ScopeTable_hide_scope(ScopeTable *st, unsigned int scope);
void ScopeTable_print(ScopeTable *st);
