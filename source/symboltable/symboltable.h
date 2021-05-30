#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define BUCKETS 255
#define INIT_SCOPE_SIZE 50
#define HASH_MULTIPLIER 65599

/* ---- Symbol Types ---- */
enum SymbolType
{
    GLOBAL_ID,
    LOCAL_ID,
    FORMAL_ID,
    USERFUNC_ID,
    LIBFUNC_ID
};

enum scopespace_t
{
    programvar,
    functionlocal,
    formalarg
};

/* ------------------------------------ SymbolTable Structures ------------------------------------ */
typedef struct Variable
{
    const char *name;
    unsigned int scope;
    unsigned int line;
} Variable;

typedef struct returnList
{
    unsigned label;
    struct returnList *next;
}returnList;

struct FuncArg;
typedef struct Function
{
    const char *name;
    struct FuncArg *args;
    unsigned int scope;
    unsigned int line;
    unsigned int address;
    unsigned int totalLocals;

    returnList *retList;

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
    enum scopespace_t space;
    unsigned offset;
    //unsigned scope;
    //char *name;
    //unsigned line;
    struct SymbolTableEntry *next;

} SymbolTableEntry;

typedef struct FuncArg
{
    SymbolTableEntry *arg;
    struct FuncArg *next;
} FuncArg;

typedef struct SymbolTable
{
    unsigned int max_scope;
    SymbolTableEntry *hashtable[BUCKETS];
} SymbolTable;

/* ------------------------------------ ScopeList Structures ------------------------------------ */
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

/* ------------------------------------ Function Stack Structures ------------------------------------ */
typedef struct FuncStackNode
{
    unsigned int scope;
    SymbolTableEntry *entry; /*If this is null, it means that the function insertion was not valid*/
    struct FuncStackNode *next;
} FuncStackNode;

typedef struct FuncStack
{
    unsigned int size;
    struct FuncStackNode *top;
} FuncStack;

/* ------------------------------------ Hashing ------------------------------------ */
unsigned int hash_function(const char *pcKey);

/* ------------------------------------ SymbolTable Functions ------------------------------------ */
SymbolTable *SymbolTable_init();
SymbolTableEntry *SymbolTable_insert(SymbolTable *s, const char *id, unsigned int scope, unsigned int line, enum SymbolType type);
SymbolTableEntry *SymbolTable_lookup(SymbolTable *s, const char *id, unsigned int scope);
SymbolTableEntry *SymbolTable_lookup_general(SymbolTable *s, const char *id, unsigned int scope);
void SymbolTable_print(SymbolTable *s, FILE *stream);
void SymbolTable_scope_print(SymbolTable *s);
void SymbolTable_hide(SymbolTable *s, const char *id, unsigned int scope);
void SymbolTable_add_libfun(SymbolTable *s, ScopeTable *t);

/* ------------------------------------ ScopeTable Functions ------------------------------------ */
ScopeTable *ScopeTable_init();
ScopeList *ScopeTable_insert(ScopeTable *st, SymbolTableEntry *entry, unsigned int scope);
ScopeList *ScopeTable_hide_scope(ScopeTable *st, unsigned int scope);
void ScopeTable_print(ScopeTable *st, FILE *stream);

/* ------------------------------------ FuncArg Functions ------------------------------------ */
FuncArg *FuncArg_insert(SymbolTableEntry *function, SymbolTableEntry *arg);
void FuncArg_print(SymbolTableEntry *function, FILE *stream);

/* ------------------------------------ Function Stack ------------------------------------ */
FuncStack *FuncStack_init();
int FuncStack_isEmpty(FuncStack *fs);
FuncStackNode *FuncStack_push(FuncStack *fs, SymbolTableEntry *entry, unsigned int scope);
FuncStackNode *FuncStack_top(FuncStack *fs);
SymbolTableEntry *FuncStack_topEntry(FuncStack *fs);
unsigned int FuncStack_topScope(FuncStack *fs);
unsigned int FuncStack_pop(FuncStack *fs);
void FuncStack_print(FuncStack *fs);

/* ------------------------------------ ReturnList Functions ------------------------------------ */
void RetList_append(SymbolTableEntry *f, unsigned label);