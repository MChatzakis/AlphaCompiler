#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define BUCKETS 2
#define HASH_MULTIPLIER 65599

typedef struct symboltable_variable
{
    const char *name;
    unsigned int scope;
    unsigned int line;

    enum var_type
    {
        INTEGER_V,
        REAL_V,
        STRING_V
    } type;

    int int_val;
    double real_val;
    char *string_val;

} symboltable_variable;

typedef struct symboltable_function
{
    const char *name;
    //List of arguments
    unsigned int scope;
    unsigned int line;
} symboltable_function;

enum SymbolType
{
    GLOBAL,
    LOCAL,
    FORMAL,
    USERFUNC,
    LIBFUNC
};

typedef struct symboltable_entry
{
    int isActive;
    union
    {
        symboltable_variable *varVal;
        symboltable_function *funcVal;
    } value;
    enum SymbolType t;

    struct symboltable_entry *next;
} symboltable_entry;

typedef struct symboltable_t
{
    symboltable_entry *hashtable[BUCKETS];
} symboltable_t;

unsigned int symboltable_hash(const char *pcKey)
{

    size_t ui;

    unsigned int uiHash = 0U;

    for (ui = 0U; pcKey[ui] != '\0'; ui++)
    {
        uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui];
    }

    return uiHash % BUCKETS;
}

symboltable_t *symboltable_init()
{
    symboltable_t *s;
    unsigned int i;
    s = (symboltable_t *)malloc(sizeof(symboltable_t));
    if (!s)
    {
        perror("Could not allocate memory for symboltable");
        exit(EXIT_FAILURE);
    }

    //memset(s->hashtable, 0, BUCKETS * sizeof(symboltable_entry));
    //init
    for (i = 0; i < BUCKETS; i++)
    {
        s->hashtable[i] = NULL;
    }

    return s;
}

symboltable_entry *symboltable_insert(symboltable_t *s, const char *id, unsigned int scope, unsigned int line, enum SymbolType type)
{
    unsigned int index;
    symboltable_entry *curr, *prev, *entry;

    assert(s && id);

    index = symboltable_hash(id);

    curr = s->hashtable[index];
    prev = NULL;

    while (curr)
    {
        prev = curr;
        curr = curr->next;
    }

    entry = (symboltable_entry *)malloc(sizeof(symboltable_entry));
    entry->isActive = 1;
    entry->next = NULL;
    entry->t = type;

    if (type < 3)
    {
        (entry->value).varVal = (symboltable_variable *)malloc(sizeof(symboltable_variable));
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
        (entry->value).funcVal = (symboltable_function *)malloc(sizeof(symboltable_function));
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

    return entry;
}

void symboltable_print(symboltable_t *s)
{
    unsigned int i;
    symboltable_entry *curr;
    char *arr[5] = {"GLOBAL", "LOCAL", "FORMAL", "USERFUNC", "LIBFUNC"};
    assert(s);

    for (i = 0; i < BUCKETS; i++)
    {
        curr = s->hashtable[i];

        if (curr != NULL)
            printf("List %u:\n", i);

        while (curr != NULL)
        {
            if (curr->t < 3)
            {
                printf("\tName: %s\n", (curr->value).varVal->name);
                printf("\t\tLine: %u\n", (curr->value).varVal->line);
                printf("\t\tScore %u\n", (curr->value).varVal->scope);
            }
            else
            {
                printf("\tName: %s\n", (curr->value).funcVal->name);
                printf("\t\tLine: %u\n", (curr->value).funcVal->line);
                printf("\t\tScore %u\n", (curr->value).funcVal->scope);
            }
            printf("\t\tType: %s\n", arr[curr->t]);
            printf("\t\tActive: %d\n", curr->isActive);

            curr = curr->next;
        }

        //printf("}\n");
    }
}