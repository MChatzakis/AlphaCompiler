#include "symboltable.h"

/* ------------------------------------ Hashing ------------------------------------ */
unsigned int hash_function(const char *pcKey)
{
    size_t ui;

    unsigned int uiHash = 0U;

    for (ui = 0U; pcKey[ui] != '\0'; ui++)
    {
        uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui];
    }

    return uiHash % BUCKETS;
}

/* ------------------------------------ SymbolTable Functions ------------------------------------ */
SymbolTable *SymbolTable_init()
{
    SymbolTable *s;
    unsigned int i;

    s = (SymbolTable *)malloc(sizeof(SymbolTable));
    if (!s)
    {
        perror("Could not allocate memory for Symbol Table");
        exit(EXIT_FAILURE);
    }

    s->max_scope = 0; //check to remove

    for (i = 0; i < BUCKETS; i++)
    {
        s->hashtable[i] = NULL;
    }

    return s;
}

SymbolTableEntry *SymbolTable_insert(SymbolTable *s, const char *id, unsigned int scope, unsigned int line, enum SymbolType type)
{
    unsigned int index;
    SymbolTableEntry *curr, *prev, *entry;

    assert(s && id);

    index = hash_function(id);

    curr = s->hashtable[index];
    prev = NULL;
    while (curr)
    {
        prev = curr;
        curr = curr->next;
    }

    entry = (SymbolTableEntry *)malloc(sizeof(SymbolTableEntry));
    if (!entry)
    {
        perror("Could not allocate memory for symtab entry");
        exit(EXIT_FAILURE);
    }
    entry->isActive = 1;
    entry->next = NULL;
    entry->type = type;

    if (type < 3)
    {
        (entry->value).varVal = (Variable *)malloc(sizeof(Variable));
        if (!((entry->value).varVal))
        {
            perror("Could not allocate memory for sym variable");
            exit(EXIT_FAILURE);
        }

        (entry->value).varVal->name = strdup(id);
        (entry->value).varVal->line = line;
        (entry->value).varVal->scope = scope;
    }
    else
    {
        (entry->value).funcVal = (Function *)malloc(sizeof(Function));
        if (!((entry->value).funcVal))
        {
            perror("Could not allocate memory for sym function");
            exit(EXIT_FAILURE);
        }
        (entry->value).funcVal->name = strdup(id);
        (entry->value).funcVal->line = line;
        (entry->value).funcVal->scope = scope;
        (entry->value).funcVal->args = NULL;
    }

    if (prev == NULL)
    {
        s->hashtable[index] = entry;
    }
    else
    {
        prev->next = entry;
    }

    if (scope > s->max_scope)
    {
        s->max_scope = scope; //chck
    }

    return entry;
}

void SymbolTable_print(SymbolTable *s, FILE *stream)
{
    unsigned int i;
    char *arr[5] = {"GLOBAL", "LOCAL", "FORMAL", "USERFUNC", "LIBFUNC"};
    SymbolTableEntry *curr;

    assert(s);

    for (i = 0; i < BUCKETS; i++)
    {
        curr = s->hashtable[i];

        if (curr != NULL)
            fprintf(stream, "------------- Bucket %u: -------------\n", i);

        while (curr != NULL)
        {
            if (curr->type < 3)
            {
                fprintf(stream, "\"%s\" [%s] (line %u) (scope %u) (isActive %d)\n", (curr->value).varVal->name, arr[curr->type], (curr->value).varVal->line, (curr->value).varVal->scope, curr->isActive);
            }
            else
            {
                fprintf(stream, "\"%s\" [%s] (line %u) (scope %u) (isActive %d)\n", (curr->value).funcVal->name, arr[curr->type], (curr->value).funcVal->line, (curr->value).funcVal->scope, curr->isActive);
                if (curr->type == 3)
                {
                    FuncArg_print(curr, stream);
                }
            }
            curr = curr->next;
        }
    }

    fprintf(stream, "--------------------------\n\"name\" [type] (line) (scope) (status)\n");
}

SymbolTableEntry *SymbolTable_lookup(SymbolTable *s, const char *id, unsigned int scope)
{
    unsigned int index;
    SymbolTableEntry *curr;

    assert(s && id);

    index = hash_function(id);
    curr = s->hashtable[index];

    while (curr)
    {
        if (curr->type < 3)
        {
            if (curr->isActive && !strcmp((curr->value).varVal->name, id) && (curr->value).varVal->scope == scope)
            {
                return curr;
            }
        }
        else
        {
            if (curr->isActive && !strcmp(id, (curr->value).funcVal->name) && (curr->value).funcVal->scope == scope)
            {
                return curr;
            }
        }

        curr = curr->next;
    }

    return curr;
}

SymbolTableEntry *SymbolTable_lookup_general(SymbolTable *s, const char *id, unsigned int scope)
{
    unsigned int i;
    SymbolTableEntry *curr;

    curr = NULL;
    for (i = 0; i <= scope; i++)
    {
        curr = SymbolTable_lookup(s, id, scope - i);
        if (curr != NULL)
        {
            break;
        }
    }

    return curr;
}

void SymbolTable_hide(SymbolTable *s, const char *id, unsigned int scope)
{
    SymbolTableEntry *curr;
    curr = SymbolTable_lookup(s, id, scope);

    assert(curr);

    curr->isActive = 0;
}

/* -------------------------- Function for library functions insertion ---------------------------- */

void SymbolTable_add_libfun(SymbolTable *s, ScopeTable *t)
{
    SymbolTableEntry *entry;
    char *arr[12] = {"print", "input", "objectmemberkeys", "objecttotalmembers", "objectcopy", "totalarguments", "argument", "typeof", "strtonum", "sqrt", "cos", "sin"};
    int i;

    assert(s && t);

    for (i = 0; i < 12; i++)
    {
        entry = SymbolTable_insert(s, arr[i], 0, 0, LIBFUNC_ID);
        ScopeTable_insert(t, entry, 0);
    }

    return;
}

/* ------------------------------------ ScopeTable Functions ------------------------------------ */
ScopeTable *ScopeTable_init()
{
    ScopeTable *st;
    unsigned int i = 0;

    st = (ScopeTable *)malloc(sizeof(ScopeTable));
    if (!st)
    {
        perror("Could not allocate memory for the scope list\n");
        exit(EXIT_FAILURE);
    }

    st->max_scope = INIT_SCOPE_SIZE;
    st->table = (ScopeList **)malloc(INIT_SCOPE_SIZE * sizeof(ScopeList));

    for (i = 0; i < INIT_SCOPE_SIZE; i++)
    {
        st->table[i] = NULL;
    }

    return st;
}

ScopeList *ScopeTable_insert(ScopeTable *st, SymbolTableEntry *entry, unsigned int scope)
{
    ScopeList *curr, *prev, *slentry;

    assert(st && entry);

    if (scope >= st->max_scope)
    {
        st->max_scope = 2 * (st->max_scope);
        st->table = realloc(st->table, st->max_scope * sizeof(ScopeList));
    }

    curr = st->table[scope];
    prev = NULL;
    while (curr != NULL)
    {
        prev = curr;
        curr = curr->next;
    }

    slentry = (ScopeList *)malloc(sizeof(ScopeList));
    if (!slentry)
    {
        perror("Could not allocate memory for sl entry");
        exit(EXIT_FAILURE);
    }

    slentry->entry = entry;
    slentry->next = NULL;

    if (prev == NULL)
    {
        st->table[scope] = slentry;
    }
    else
    {
        prev->next = slentry;
    }

    return slentry;
}

ScopeList *ScopeTable_hide_scope(ScopeTable *st, unsigned int scope)
{
    ScopeList *curr;
    SymbolTableEntry *entry;

    assert(st);

    curr = st->table[scope];
    while (curr)
    {
        entry = curr->entry;

        if (entry->isActive == 1)
            entry->isActive = 0;

        curr = curr->next;
    }

    return st->table[scope];
}

void ScopeTable_print(ScopeTable *st, FILE *stream)
{
    unsigned int i;
    ScopeList *curr;
    SymbolTableEntry *entry;
    char *arr[5] = {"global variabe", "local variable", "formal argument", "user function", "library function"};

    assert(st);

    for (i = 0; i < st->max_scope; i++)
    {
        curr = st->table[i];

        if (curr != NULL)
        {
            fprintf(stream, "---------------- Scope #%d ----------------\n", i);
        }

        while (curr)
        {
            entry = curr->entry;

            if (entry->type < 3)
            {
                fprintf(stream, "\"%s\" [%s] (line %u) (scope %u) (isActive %d)\n", (entry->value).varVal->name, arr[entry->type], (entry->value).varVal->line, (entry->value).varVal->scope, entry->isActive);
            }
            else
            {
                fprintf(stream, "\"%s\" [%s] (line %u) (scope %u) (isActive %d) ", (entry->value).funcVal->name, arr[entry->type], (entry->value).funcVal->line, (entry->value).funcVal->scope, entry->isActive);
                if (entry->type == 3)
                {
                    FuncArg_print(entry, stream);
                }
                else
                {
                    printf("\n");
                }
            }

            curr = curr->next;
        }

        if (st->table[i] != NULL)
        {
            fprintf(stream, "\n");
        }
    }

    fprintf(stream, "--------------------------\n\"name\" [type] (line) (scope) (status)\n");
}

/* ------------------------------------ FuncArg Functions ------------------------------------ */
FuncArg *FuncArg_insert(SymbolTableEntry *function, SymbolTableEntry *arg)
{
    FuncArg *curr, *prev, *funcarg;

    assert(function && function->type == 3 && arg && arg->type == 2);

    curr = (function->value).funcVal->args;
    prev = NULL;
    while (curr != NULL)
    {
        prev = curr;
        curr = curr->next;
    }

    funcarg = (FuncArg *)malloc(sizeof(FuncArg));
    if (!funcarg)
    {
        perror("Could not allocate memory for arguments");
        exit(EXIT_FAILURE);
    }

    funcarg->arg = arg;
    funcarg->next = NULL;

    if (prev == NULL)
    {
        (function->value).funcVal->args = funcarg;
    }
    else
    {
        prev->next = funcarg;
    }

    return funcarg;
}

void FuncArg_print(SymbolTableEntry *function, FILE *stream)
{
    FuncArg *curr;
    SymbolTableEntry *entry;

    assert(function && function->type == 3);

    curr = (function->value).funcVal->args;
    fprintf(stream, "Args: [ ");
    while (curr)
    {
        entry = curr->arg;
        fprintf(stream, "%s ", (entry->value).varVal->name);
        curr = curr->next;
    }
    fprintf(stream, "]\n");
}

/* ------------------------------------ Function Stack ------------------------------------ */
FuncStack *FuncStack_init()
{
    FuncStack *fs;
    fs = (FuncStack *)malloc(sizeof(FuncStack));
    if (!fs)
    {
        perror("Could not allocate memory for Function Stack");
        exit(EXIT_FAILURE);
    }
    fs->size = 0;
    fs->top = NULL;

    return fs;
}

int FuncStack_isEmpty(FuncStack *fs)
{
    assert(fs);
    return (fs->size == 0);
}

FuncStackNode *FuncStack_push(FuncStack *fs, SymbolTableEntry *entry, unsigned int scope)
{
    FuncStackNode *node;

    assert(fs);

    node = (FuncStackNode *)malloc(sizeof(FuncStackNode));
    if (!node)
    {
        perror("Could not allocate memory for function stack node");
        exit(EXIT_FAILURE);
    }

    node->next = fs->top;
    node->scope = scope;
    node->entry = entry;

    fs->top = node;
    fs->size++;

    return node;
}

FuncStackNode *FuncStack_top(FuncStack *fs)
{
    assert(fs && fs->top);
    return fs->top;
}

unsigned int FuncStack_topScope(FuncStack *fs)
{
    assert(fs && fs->top);
    return fs->top->scope;
}

SymbolTableEntry *FuncStack_topEntry(FuncStack *fs)
{
    assert(fs && fs->top);
    return fs->top->entry;
}

unsigned int FuncStack_pop(FuncStack *fs)
{
    FuncStackNode *del;
    unsigned int tmp;

    assert(fs && fs->top);

    tmp = fs->top->scope;
    del = fs->top;

    fs->top = fs->top->next;
    fs->size--;

    del->next = NULL;
    free(del);

    return tmp;
}

void FuncStack_print(FuncStack *fs)
{
    FuncStackNode *curr;
    assert(fs);

    if (FuncStack_isEmpty(fs))
    {
        return;
    }

    printf("FuncStack:\n");
    curr = fs->top;
    while (curr)
    {
        printf("Func Scope: %u\n", curr->scope);
        curr = curr->next;
    }
}
