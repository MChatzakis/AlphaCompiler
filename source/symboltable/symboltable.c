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
                printf("\tScore: %u\n", (curr->value).varVal->scope);
            }
            else
            {
                printf("\tName: %s\n", (curr->value).funcVal->name);
                printf("\tLine: %u\n", (curr->value).funcVal->line);
                printf("\tScore: %u\n", (curr->value).funcVal->scope);
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