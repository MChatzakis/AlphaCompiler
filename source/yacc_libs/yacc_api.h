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
unsigned int loop_stack = 0;

char noname_prefix[12];

SymbolTable *symTab;
ScopeTable *scopeTab;
FuncStack *functionStack;

FILE *ost; /*Output stream*/

#define TRACE_PRINT 0 /*Set this flag to print the rule evaluation messages*/

/**
 * @brief Checks if id refers to some library function name.
 * 
 */
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

/**
 * @brief Checks if the entry is accesible.
 * 
 * @param entry The symbol table entry to be checked
 * @param scope The current scope
 */
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
 * @brief Manages the actions to be done at an assignment expression.
 * It corresponds to rule expr: lvalue ASSIGN expr.
 * 
 * @param entry The symboltable entry of the identifier
 */
void ManageAssignValue(SymbolTableEntry *entry)
{
    if (entry != NULL)
    {
        /* an vrei function error */
        if (entry->type == 3)
        {
            fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Assigned value to User defined function \"%s\" at line %u\n", (entry->value).funcVal->name, yylineno);
            fprintf_cyan(stderr, "[Syntax Analysis] -- NOTE: Function \"%s\" defined at line %lu\n", (entry->value).funcVal->name, (entry->value).funcVal->line);
        }
        else if (entry->type == 4)
        {
            fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Assigned value to Library function \"%s\" at line %u\n", (entry->value).funcVal->name, yylineno);
        }
        else if (!CheckForAccess(entry, scope))
        {
            fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Assigned value to not accessible variable \"%s\" at line %u\n", (entry->value).varVal->name, yylineno);
            fprintf_cyan(stderr, "[Syntax Analysis] -- NOTE: Variable \"%s\" is declared at line %lu\n", (entry->value).varVal->name, (entry->value).varVal->line);
        }
        else
        {
            //assign val
        }
    }
}

/**
 * @brief Manages the actions to be done when the value of a symbol table entry is asked.
 * It corresponds to rule primary:   lvalue
 *                                  |call
 * 
 * @param entry The symboltable entry of the identifier
 */
void ManagePrimaryLValue(SymbolTableEntry *entry)
{
    if (entry != NULL)
    {
        if (!CheckForAccess(entry, scope))
        {
            fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Used not accessible variable \"%s\" as primary value at line %u\n", (entry->value).varVal->name, yylineno);
            fprintf_cyan(stderr, "[Syntax Analysis] -- NOTE: Variable \"%s\" is declared at line %lu\n", (entry->value).varVal->name, (entry->value).varVal->line);
        }
        else
        {
            //assign value to expression
        }
    }
}

/**
 * @brief Checks if an identifier exists in symboltable and if not, it inserts it in every case.
 * Corresponds to rule expr: lvalue: ID
 * 
 * @param id The name of the variable
 * @return SymbolTableEntry * The entry of the identifier
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
 * @brief Checks if the local variable exists. If not, it is inserted in the symbol table.
 * It corresponds to yacc rule lvalue: local id
 * 
 * @param id The name of the local variable 
 * @return SymbolTableEntry* The entry of the variable if no error occurs, otherwise NULL
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
 * @brief Checks if the global variable exists. If not, prints error.
 * It corresponds to yacc rule lvalue: global id
 * 
 * @param id The name of the global variable 
 * @return SymbolTableEntry* The entry of the variable if no error occurs, otherwise NULL 
 */
SymbolTableEntry *EvaluateGlobalLValue(char *id)
{
    SymbolTableEntry *entry;

    entry = SymbolTable_lookup(symTab, id, 0);
    if (entry == NULL)
    {
        fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Undefined global symbol \"%s\" at line %u\n", id, yylineno);
    }

    return entry;
}

/**
 * @brief Checks if the id of the formal argument is valid and adds it to the symboltable.
 * It corresponds to yacc rule idlist:    ID
 *                                      | idlist,ID
 * 
 * @param id The name of the formal argument
 * @return SymbolTableEntry* The entry of the argument if no error occurs, otherwise NULL
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

/**
 * @brief Manages the actions to be done when a function is defined (rule funcdef: *)
 * It checks if the name is valid by comparing it to the default library names, and then checks the current scope
 * to find if another ID has already the same name. In that case it throws an error message.
 * Otherwise, it adds the entry to the symboltable.
 * 
 * @param id The name of the function to be defined
 * @return NULL if an error occurs, otherwise returns the entry instance of the function
 */
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
        {
            fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Redefinition of Variable \"%s\" as a function at line %lu\n", (entry->value).varVal->name, yylineno);
            fprintf_cyan(stderr, "[Syntax Analysis] -- NOTE: Variable \"%s\" declared at line %lu\n", (entry->value).varVal->name, (entry->value).varVal->line);
        }
        else if (entry->type == 3)
        {
            fprintf_red(stdout, "[Syntax Analysis] -- ERROR: Redefinition of User function \"%s\" at line %lu\n", (entry->value).funcVal->name, yylineno);
            fprintf_cyan(stderr, "[Syntax Analysis] -- NOTE: Function \"%s\" defined at line %lu\n", (entry->value).funcVal->name, (entry->value).funcVal->line);
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

/**
 * @brief Manages the actions to be done when a function is called (rule primary: call)
 * If the id called is a variable it checks the accessibility and throws an error message.
 * 
 * @param entry The ID's entry on symboltable
 */
void ManagePrimaryFunction(SymbolTableEntry *entry)
{
    if (entry != NULL)
    {
        if (!CheckForAccess(entry, scope))
        {
            fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Used not accessible variable \"%s\" at line %u\n", (entry->value).varVal->name, yylineno);
            fprintf_cyan(stderr, "[Syntax Analysis] -- NOTE: Variable \"%s\" declared at line %lu\n", (entry->value).varVal->name, (entry->value).varVal->line);
        }
    }
}

/**
 * @brief Check is the use of return statement is valid
 * 
 */
void ManageReturnStatement()
{
    if (FuncStack_isEmpty(functionStack))
    {
        fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Used \"return\" statement outside of function at line %lu\n", yylineno);
    }
}

/**
 * @brief Check is the use of break and continue keyword is valid
 * 
 * @param keyword "Break" or "Else"
 */
void ManageLoopKeywords(char *keyword)
{
    if (loop_stack == 0)
    {
        fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Used \"%s\" statement outside of loop at line %lu\n", keyword, yylineno);
    }
}

/**
 * @brief Generates names for every anonymous function
 * 
 */
void GenerateName()
{
    sprintf(noname_prefix + 1, "%u", unamed_functions);
}

/**
 * @brief Initializes the name array
 * 
 */
void InitNames()
{
    int i;

    noname_prefix[0] = '_';
    for (i = 1; i < 12; i++)
    {
        noname_prefix[i] = '\0';
    }
}
