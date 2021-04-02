#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "../utils/colors.h"
#include "../utils/stack/number_stack.h"
#include "../symboltable/symboltable.h"

#include "macros.h"
#include "structs.h"

int yyerror(char *message);
int yylex(void);

extern int yylineno;
extern char *yytext;
extern FILE *yyin;

unsigned int scope = 0;

SymbolTable *symTab;
ScopeTable *scopeTab;

number_stack_t *funcdefStack;

unsigned int unamed_functions = 0;

char noname_prefix[12];

FILE *ost;

#define TRACE_PRINT 1

/* Yacc code */

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
        else if ((entry->value).varVal->scope > 0 && (entry->value).varVal->scope < scope)
        {
            /* elegxoume an exoume prosvasi (an eimaste mesa se synarthsh) */
            if (!number_stack_is_empty(funcdefStack))
            {
                if (number_stack_top(funcdefStack) >= (entry->value).varVal->scope)
                {
                    fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Used not accessible variable \"%s\" at line %u\n", (entry->value).varVal->name, yylineno);
                }
            }
            else{
                //assign
            }
        }
        else{
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
        if ((entry->type < 3) && (entry->value).varVal->scope > 0 && (entry->value).varVal->scope < scope)
        {
            if (!number_stack_is_empty(funcdefStack))
            {
                if (number_stack_top(funcdefStack) >= (entry->value).varVal->scope)
                {
                    fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Used not accessible variable \"%s\" at line %u\n", (entry->value).varVal->name, yylineno);
                }
            }
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
 * @brief Code for lvalue <- global
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
    SymbolTableEntry *entry;

    /*if ((entry = SymbolTable_lookup_general(symTab, id, scope)) != NULL)
    {
        if (entry->type == 3)
        {
            fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Formal argument \"%s\" shadows user defined function \"%s\" at line %lu\n", id, (entry->value).funcVal->name, yylineno);
            return NULL;
        }

        if (entry->type == 4)
        {
            fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Formal argument \"%s\" shadows library function \"%s\" at line %lu\n", id, (entry->value).funcVal->name, yylineno);
            return NULL;
        }
    }*/

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

    return entry;
}

SymbolTableEntry *ManageIDFunctionDefinition(char *id)
{
    SymbolTableEntry *entry = NULL;
    SymbolTableEntry *insertEntry;

    if (checkForLibFunc(id))
    {
        fprintf_red(stdout, "[Syntax Analysis] -- ERROR: Library function \"%s\" shadowed at line %lu\n", id, yylineno);
        return NULL;
    }

    entry = SymbolTable_lookup(symTab, id, scope);
    if (entry != NULL)
    {
        if (entry->type < 3)
            fprintf_red(stdout, "[Syntax Analysis] -- ERROR: Variable \"%s\" redeclaration as function at line %lu\n", (entry->value).varVal->name, yylineno);
        else if (entry->type == 3)
        {
            fprintf_red(stdout, "[Syntax Analysis] -- ERROR: User function \"%s\" redeclaration at line %lu\n", (entry->value).funcVal->name, yylineno);
        }

        return NULL;
    }
    else
    {
        insertEntry = SymbolTable_insert(symTab, id, scope, yylineno, USERFUNC_ID);
        ScopeTable_insert(scopeTab, insertEntry, scope);
        entry = insertEntry;
    }

    return entry;
}

void ManagePrimaryFunction(SymbolTableEntry *entry)
{
    if (entry != NULL)
    {
        if (entry->type < 3)
        {
            if ((entry->value).varVal->scope > 0 && (entry->value).varVal->scope < scope)
            {
                if (!number_stack_is_empty(funcdefStack))
                {
                    if (number_stack_top(funcdefStack) >= (entry->value).varVal->scope)
                    {
                        fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Used not accessible variable \"%s\" at line %u\n", (entry->value).varVal->name, yylineno);
                    }
                }
            }
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