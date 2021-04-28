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
/**
 * @brief Initializes the symbol table
 * 
 * @return SymbolTable* Returns the symbol table
 */
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

/**
 * @brief Inserts an entry in symbol table
 * 
 * @param s Symbol table
 * @param id Name of entry
 * @param scope Scope of entry
 * @param line Line of entry
 * @param type Type of entry
 * @return SymbolTableEntry* Returns the inserted symbol table entry
 */
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
        (entry->value).funcVal->address = 0;
        (entry->value).funcVal->totalLocals = 0;
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

/**
 * @brief Prints the symbol table at the file stream
 * 
 * @param s SymbolTable
 * @param stream Output file stream
 */
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

/**
 * @brief Look up an entry with name id at this single scope
 * 
 * @param s SymbolTable
 * @param id Name of entry
 * @param scope Scope of entry
 * @return SymbolTableEntry* If found returns the entry, else returns NULL
 */
SymbolTableEntry *SymbolTable_lookup(SymbolTable *s, const char *id, unsigned int scope)
{
    unsigned int index;
    SymbolTableEntry *curr;

    assert(s && id);

    index = hash_function(id);
    curr = s->hashtable[index];

    /*Searching identifier ID in the given scope*/
    while (curr)
    {
        /*Variable Case*/
        if (curr->type < 3)
        {
            if (curr->isActive && !strcmp((curr->value).varVal->name, id) && (curr->value).varVal->scope == scope)
            {
                return curr;
            }
        }
        /*Function Case*/
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

/**
 * @brief Look up an entry with name id from this scope since scope 0.
 * 
 * @param s SymbolTable
 * @param id Name of entry
 * @param scope Scope of entry 
 * @return SymbolTableEntry* If found returns the entry, else returns NULL
 */
SymbolTableEntry *SymbolTable_lookup_general(SymbolTable *s, const char *id, unsigned int scope)
{
    unsigned int i;
    SymbolTableEntry *curr;

    curr = NULL;
    /*Searching the identifier id from scope to 0*/
    for (i = 0; i <= scope; i++)
    {
        curr = SymbolTable_lookup(s, id, scope - i); /*Scope -> Scope-1 -> ... -> 0*/
        if (curr != NULL)
        {
            /*If something is found, the search ends and the entry is returned*/
            break;
        }
    }

    return curr;
}

/**
 * @brief Inactivate the entry with this name and scope
 * 
 * @param s SymbolTable
 * @param id Name of entry
 * @param scope Scope of entry 
 */
void SymbolTable_hide(SymbolTable *s, const char *id, unsigned int scope)
{
    SymbolTableEntry *curr;
    curr = SymbolTable_lookup(s, id, scope);

    assert(curr);

    curr->isActive = 0;
}

/* -------------------------- Function for library functions insertion ---------------------------- */
/**
 * @brief Initializes symbol table with the library functions
 * 
 * @param s SymbolTable
 * @param t ScopeTable
 */
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
/**
 * @brief Initializes the scope table
 * 
 * @return ScopeTable* ScopeTable
 */
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

/**
 * @brief Inserts an entry in scope list
 * 
 * @param st ScopeTable
 * @param entry Symbol table entry
 * @param scope Scope of entry
 * @return ScopeList* Scopelist
 */
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

/**
 * @brief Hide all the entries of scope list with this scope
 * 
 * @param st ScopeTable
 * @param scope Scope of scopelist
 * @return ScopeList* ScopeList
 */
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

/**
 * @brief Prints the scope table
 * 
 * @param st ScopeTable
 * @param stream Output file stream
 */
void ScopeTable_print(ScopeTable *st, FILE *stream)
{
    unsigned int i;
    ScopeList *curr;
    SymbolTableEntry *entry;
    char *arr[5] = {"global variabe", "local variable", "formal argument", "user function", "library function"};
    char *scopeArr[3] = {"program var", "function local", "formal arg"};

    assert(st);

     fprintf(stream, "----------------------- SCOPE LIST -----------------------\n");

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
                fprintf(stream, "\"%s\" [%s] (line %u) (scope %u) (isActive %d) (offset %u) (space %s)\n", (entry->value).varVal->name, arr[entry->type], (entry->value).varVal->line, (entry->value).varVal->scope, entry->isActive, entry->offset, scopeArr[entry->space]);
            }
            else
            {
                fprintf(stream, "\"%s\" [%s] (line %u) (scope %u) (isActive %d) (total locals %u) (iaddress %u) ",
                        (entry->value).funcVal->name, arr[entry->type], (entry->value).funcVal->line, (entry->value).funcVal->scope, entry->isActive, (entry->value).funcVal->totalLocals, (entry->value).funcVal->address);
                if (entry->type == 3)
                {
                    FuncArg_print(entry, stream);
                }
                else
                {
                    fprintf(stream, "\n");
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
/**
 * @brief Insert an argument in a function argument list
 * 
 * @param function The function
 * @param arg The argument of the function
 * @return FuncArg* The node of the argument in argument list of this function
 */
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

/**
 * @brief Prints the arguments of the function at stream
 * 
 * @param function The function
 * @param stream Output file stream
 */
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

/**
 * @brief Initializes a new Function stack 
 * 
 * @return FuncStack * The pointer to the memory allocated for the stack
 */
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

/**
 * @brief Checks whether or not the function stack is empty
 * 
 * @param fs The stack pointer
 * @return int 0 if the stack is not empty, 1 if it is empty
 */
int FuncStack_isEmpty(FuncStack *fs)
{
    assert(fs);
    return (fs->size == 0);
}

/**
 * @brief Pushes an item to the function stack 
 * 
 * @param fs The stack pointer
 * @param entry The entry of the item, that can also be NULL
 * @param scope The scope of the item
 * @return FuncStackNode * The pointer to the newly added element
 */
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

/**
 * @brief Gets the top item 
 * 
 * @param fs The stack pointer
 * @return FuncStackNode * The top element
 */
FuncStackNode *FuncStack_top(FuncStack *fs)
{
    assert(fs && fs->top);
    return fs->top;
}

/**
 * @brief Gets the top item scope value
 * 
 * @param fs The stack pointer
 * @return unsigned int The scope of the top element
 */
unsigned int FuncStack_topScope(FuncStack *fs)
{
    assert(fs && fs->top);
    return fs->top->scope;
}

/**
 * @brief Gets the top item entry value
 * 
 * @param fs The stack pointer
 * @return SymbolTableEntry * The entry of the top element
 */
SymbolTableEntry *FuncStack_topEntry(FuncStack *fs)
{
    assert(fs && fs->top);
    return fs->top->entry;
}

/**
 * @brief Pop the last entry the funcstack
 * 
 * @param fs The stack pointer
 * @return The scope of the popped entry
 */
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

/**
 * @brief Prints the function stack
 * 
 * @param fs The stack pointer
 */
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
