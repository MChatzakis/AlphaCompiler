#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "../utils/utils.h"
#include "../symboltable/symboltable.h"

int yyerror(char *message);
int yylex(void);

extern int yylineno;
extern char *yytext;
extern FILE *yyin;

unsigned int scope = 0;
unsigned int unamed_functions = 0;

SymbolTable *symTab;
ScopeTable *scopeTab;

FuncStack *functionStack;

char noname_prefix[12];

FILE *ost;

#define TRACE_PRINT 0

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

/* Yacc code */

int CheckForAccess(SymbolTableEntry *entry, unsigned int scope)
{
    assert(entry);

    if ((entry->type < 3) && (entry->value).varVal->scope > 0 && (entry->value).varVal->scope < scope)
    {
        if (!FuncStack_isEmpty(functionStack))
        {
            if (FuncStack_topScope(functionStack) >= (entry->value).varVal->scope)
            {
                return 0;
            }
        }
    }

    return 1;
}

/**
 * @brief Code for lvalue assign expr
 * 
 * @param entry 
 */
void ManageAssignValue(SymbolTableEntry *entry)
{
    if (entry != NULL)
    {
        /* an vrei function error */
        if (entry->type == 3)
        {
            fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Assigned value to User defined function \"%s\" at line %u\n", (entry->value).funcVal->name, yylineno);
        }
        else if (entry->type == 4)
        {
            fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Assigned value to Library function \"%s\" at line %u\n", (entry->value).funcVal->name, yylineno);
        }
        else if (!CheckForAccess(entry, scope))
        {
            fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Assigned value to not accessible variable \"%s\" at line %u\n", (entry->value).varVal->name, yylineno);
        }
        else
        {
            //assgin val
        }
    }
}

/**
 * @brief Code for Primary <- lvalue
 * 
 * @param entry 
 */
void ManagePrimaryLValue(SymbolTableEntry *entry)
{
    if (entry != NULL)
    {
        if (!CheckForAccess(entry, scope))
        {
            fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Used not accessible variable \"%s\" as primary value at line %u\n", (entry->value).varVal->name, yylineno);
        }
        else
        {
            //assign value to expression
        }
    }
}

/**
 * @brief Code for lvalue -> ID
 * 
 * @param id 
 * @return SymbolTableEntry* 
 */
SymbolTableEntry *EvaluateLValue(char *id)
{
    SymbolTableEntry *entry, *insertEntry;

    if (!(entry = SymbolTable_lookup_general(symTab, id, scope)))
    {
        if (scope > 0)
        {
            insertEntry = SymbolTable_insert(symTab, id, scope, yylineno, LOCAL_ID);
            ScopeTable_insert(scopeTab, insertEntry, scope);
        }
        else
        {
            insertEntry = SymbolTable_insert(symTab, id, scope, yylineno, GLOBAL_ID);
            ScopeTable_insert(scopeTab, insertEntry, scope);
        }

        entry = insertEntry;
    }

    return entry;
}

/**
 * @brief Code for lvalue <- local
 * 
 * @param id 
 * @return SymbolTableEntry* 
 */
SymbolTableEntry *EvaluateLocalLValue(char *id)
{
    SymbolTableEntry *entry, *insertEntry;

    if ((entry = SymbolTable_lookup(symTab, id, scope)) == NULL)
    {

        if (checkForLibFunc(id))
        {
            fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Library Function \"%s\" redefined as local variable at line %u\n", id, yylineno);
            return NULL;
        }

        if (scope > 0)
        {
            insertEntry = SymbolTable_insert(symTab, id, scope, yylineno, LOCAL_ID);
            ScopeTable_insert(scopeTab, insertEntry, scope);
        }
        else
        {
            insertEntry = SymbolTable_insert(symTab, id, scope, yylineno, GLOBAL_ID);
            ScopeTable_insert(scopeTab, insertEntry, scope);
        }

        entry = insertEntry;
    }

    return entry;
}

/**
 * @brief Code for lvalue -> global ID
 * 
 * @param id 
 * @return SymbolTableEntry* 
 */
SymbolTableEntry *EvaluateGlobalLValue(char *id)
{
    SymbolTableEntry *entry;

    entry = SymbolTable_lookup(symTab, id, 0);
    if (entry == NULL)
    {
        fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Undefined symbol \"%s\" at line %u\n", id, yylineno);
    }

    return entry;
}

/**
 * @brief Checks if the id of the formal argument is valid
 * 
 * @param id 
 * @return SymbolTableEntry* 
 */
SymbolTableEntry *CheckAddFormal(char *id)
{
    SymbolTableEntry *entry, *corrFunc;

    if (checkForLibFunc(id))
    {
        fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Formal argument \"%s\" shadows library function at line %lu\n", id, yylineno);
        return NULL;
    }

    if ((entry = SymbolTable_lookup(symTab, id, scope)) != NULL)
    {
        fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Formal argument already used in function \"%s\" at line %u\n", id, yylineno);
        return NULL;
    }

    entry = SymbolTable_insert(symTab, id, scope, yylineno, FORMAL_ID);
    ScopeTable_insert(scopeTab, entry, scope);
    //insert format to funcstack top
    if (!FuncStack_isEmpty(functionStack)) /* kanonika, pote den prepei to funcstack na einai adeio se auto to simeio */
    {
        if (FuncStack_topEntry(functionStack) != NULL)
        {
            corrFunc = FuncStack_topEntry(functionStack);
            FuncArg_insert(corrFunc, entry);
        }
    }

    return entry;
}

SymbolTableEntry *ManageIDFunctionDefinition(char *id)
{
    SymbolTableEntry *entry = NULL;
    SymbolTableEntry *insertEntry;

    if (checkForLibFunc(id))
    {
        fprintf_red(stdout, "[Syntax Analysis] -- ERROR: Library function \"%s\" shadowed at line %lu\n", id, yylineno);
        FuncStack_push(functionStack, NULL, scope);
        return NULL;
    }

    entry = SymbolTable_lookup(symTab, id, scope);
    if (entry != NULL)
    {
        if (entry->type < 3)
            fprintf_red(stdout, "[Syntax Analysis] -- ERROR: Redeclaration of Variable \"%s\" as function at line %lu\n", (entry->value).varVal->name, yylineno);
        else if (entry->type == 3)
        {
            fprintf_red(stdout, "[Syntax Analysis] -- ERROR: Redefinition of User function \"%s\" at line %lu\n", (entry->value).funcVal->name, yylineno);
        }

        FuncStack_push(functionStack, NULL, scope);
        return NULL;
    }
    else
    {
        insertEntry = SymbolTable_insert(symTab, id, scope, yylineno, USERFUNC_ID);
        ScopeTable_insert(scopeTab, insertEntry, scope);
        entry = insertEntry;
        FuncStack_push(functionStack, entry, scope);
    }

    return entry;
}

void ManagePrimaryFunction(SymbolTableEntry *entry)
{
    if (entry != NULL)
    {
        if (!CheckForAccess(entry, scope))
        {
            fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Used not accessible variable \"%s\" at line %u\n", (entry->value).varVal->name, yylineno);
        }
    }
}

void GenerateName()
{
    sprintf(noname_prefix + 1, "%u", unamed_functions);
}

void InitNames()
{
    int i;

    noname_prefix[0] = '_';
    for (i = 1; i < 12; i++)
    {
        noname_prefix[i] = '\0';
    }
}
