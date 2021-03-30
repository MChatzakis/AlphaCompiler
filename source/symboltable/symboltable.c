#include "symboltable.h"

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

    s->max_scope = 0;

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
        s->max_scope = scope;
    }

    return entry;
}

void SymbolTable_print(SymbolTable *s)
{
    unsigned int i;
    char *arr[5] = {"GLOBAL", "LOCAL", "FORMAL", "USERFUNC", "LIBFUNC"};
    SymbolTableEntry *curr;

    assert(s);

    for (i = 0; i < BUCKETS; i++)
    {
        curr = s->hashtable[i];

        if (curr != NULL)
            printf("List %u:\n", i);

        while (curr != NULL)
        {
            if (curr->type < 3)
            {
                printf("\tName: %s\n", (curr->value).varVal->name);
                printf("\tLine: %u\n", (curr->value).varVal->line);
                printf("\tScope: %u\n", (curr->value).varVal->scope);
            }
            else
            {
                printf("\tName: %s\n", (curr->value).funcVal->name);
                printf("\tLine: %u\n", (curr->value).funcVal->line);
                printf("\tScope: %u\n", (curr->value).funcVal->scope);
            }
            printf("\tType: %s\n", arr[curr->type]);
            printf("\tActive: %d\n", curr->isActive);
            if (curr->next != NULL)
            {
                printf("\t-----------\n");
            }
            curr = curr->next;
        }
    }
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
    //printf("SS: %u\n", scope);
    for (i = 0; i <= scope; i++)
    {
        curr = SymbolTable_lookup(s, id, scope - i);
        if (curr != NULL)
        {
            break;
        }
        //printf("!\n");
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

void SymbolTable_add_libfun(SymbolTable *s)
{

    char *arr[12] = {"print", "input", "objectmemberkeys", "objecttotalmembers", "objectcopy", "totalarguments", "argument", "typeof", "strtonum", "sqrt", "cos", "sin"};
    int i;

    for (i = 0; i < 12; i++)
        SymbolTable_insert(s, arr[i], 0, 0, LIBFUNC_ID);

    return;
}

ScopeTable *ScopeTable_init()
{
    ScopeTable *st;
    unsigned int i = 0;

    st = (ScopeTable *)malloc(sizeof(st));
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

    if (scope > st->max_scope)
    {
        //realoc
    }

    curr = st->table[scope];
    while (curr)
    {
        prev = curr;
        curr = curr->next;
    }

    slentry = (ScopeList *)malloc(sizeof(ScopeList));
    if (!slentry)
    {
        perror("Could not allocate memory gor sl entry");
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

void ScopeTable_print(ScopeTable *st)
{
    unsigned int i;
    ScopeList *curr;
    SymbolTableEntry *entry;
    char *arr[5] = {"GLOBAL", "LOCAL", "FORMAL", "USERFUNC", "LIBFUNC"};

    assert(st);

    for (i = 0; i < st->max_scope; i++)
    {
        curr = st->table[i];

        if (curr != NULL)
        {
            printf("-------- Scope #%d --------\n", i);
        }

        while (curr)
        {
            entry = curr->entry;

            if (entry->type < 3)
            {
                printf("\"%s\" [%s] (line %u) (scope %u) (isActive %d)", (entry->value).varVal->name, arr[entry->type], (entry->value).varVal->line, (entry->value).varVal->scope, entry->isActive);
            }
            else
            {
                printf("\"%s\" [%s] (line %u) (scope %u) (isActive %d)", (entry->value).funcVal->name, arr[entry->type], (entry->value).funcVal->line, (entry->value).funcVal->scope, entry->isActive);
            }

            curr = curr->next;
        }
    }
}
