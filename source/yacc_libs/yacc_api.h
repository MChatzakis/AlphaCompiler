/**
 * @file yacc_api.h
 * @author Manos Chatzakis (4238) Nikos Fanourakis (4237)
 * @brief Functions to be used for yacc
 */

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
NumberStack *loopStack;

FILE *ost; /*Output stream*/

#define TRACE_PRINT 1 /*Set this flag to print the rule evaluation messages*/

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

    /*
        If the refferred entry is a variable with scope between 0 and 
        current scope the accessibility might not be allowed.
        If entry is a function, access is allowed no matter the scopes etc.
    */
    if ((entry->type < 3) && (entry->value).varVal->scope > 0 && (entry->value).varVal->scope < scope)
    {
        /*If there is a function definition currently*/
        if (!FuncStack_isEmpty(functionStack))
        {
            /*
                If the function is between the entry first appearance 
                and the current scope, access is not allowed, eg:
                {
                    x = 5; //scope 1
                    function t(){ //scope 1, funcstack.size = 1
                        x = 3;  //scope 2
                    }
                }    
            */
            if (FuncStack_topScope(functionStack) >= (entry->value).varVal->scope)
            {
                return 0; /*Error*/
            }
        }
    }

    return 1; /*Access Allowed*/
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
        /*If the lvalue refers to a function (eg. print = 5;) an error is thrown*/
        if (entry->type == 3)
        {
            fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Assigned value to User defined function \"%s\" at line %u\n", (entry->value).funcVal->name, yylineno);
            fprintf_cyan(stderr, "[Syntax Analysis] -- NOTE: Function \"%s\" defined at line %lu\n", (entry->value).funcVal->name, (entry->value).funcVal->line);
        }
        else if (entry->type == 4)
        {
            fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Assigned value to Library function \"%s\" at line %u\n", (entry->value).funcVal->name, yylineno);
        }
        /*If the lvalue is not a function, we only need to check for the accessibility.*/
        else if (!CheckForAccess(entry, scope))
        {
            fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Assigned value to not accessible variable \"%s\" at line %u\n", (entry->value).varVal->name, yylineno);
            fprintf_cyan(stderr, "[Syntax Analysis] -- NOTE: Variable \"%s\" is declared at line %lu\n", (entry->value).varVal->name, (entry->value).varVal->line);
        }
        else
        {
            /*Getting here means that the assignment is valid*/
        }
    }
}

/**
 * @brief Manages the actions to be done when the value of a symbol table entry is asked.
 * It corresponds to rule primary:   lvalue x
 *                                  |call
 * 
 * @param entry The symboltable entry of the identifier
 */
void ManagePrimaryLValue(SymbolTableEntry *entry)
{
    if (entry != NULL)
    {
        /*As calling a function as a variable (etc x = print;) is allowed on alpha, we only need to check for access*/
        if (!CheckForAccess(entry, scope))
        {
            fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Used not accessible variable \"%s\" as primary value at line %u\n", (entry->value).varVal->name, yylineno);
            fprintf_cyan(stderr, "[Syntax Analysis] -- NOTE: Variable \"%s\" is declared at line %lu\n", (entry->value).varVal->name, (entry->value).varVal->line);
        }
        else
        {
            /*Getting here means that the expression is valid*/
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

    /*Lookup, starting from current scope and goind backwards till global scope*/
    if (!(entry = SymbolTable_lookup_general(symTab, id, scope)))
    {
        /*If we get here, it means lookup failed so the identifier ID is inserted to the symtab*/
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
    /*Else the id found somewhere in the symtab and its returned right after the lookup*/

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

    /*Look up on current scope*/
    if ((entry = SymbolTable_lookup(symTab, id, scope)) == NULL)
    {

        /*We get here only if nothing was found in the current scope*/

        /*Using lib name is forbidden when scope > 0*/
        if (checkForLibFunc(id))
        {
            fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Library Function \"%s\" redefined as local variable at line %u\n", id, yylineno);
            return NULL;
        }

        /*At this point, insertion is valid*/
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
    //else it means that the lookup to the current scope found the corresponding symbol, so no actions needed here.

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

    /*Lookup in the global scope*/
    entry = SymbolTable_lookup(symTab, id, 0);
    if (entry == NULL)
    {
        /*If nothing is found, error is thrown and NULL is returned*/
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

    /*Arguments with lib func names are not allowed*/
    if (checkForLibFunc(id))
    {
        fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Formal argument \"%s\" shadows library function at line %lu\n", id, yylineno);
        return NULL;
    }

    /*Look up on the current scope*/
    if ((entry = SymbolTable_lookup(symTab, id, scope)) != NULL)
    {
        /*Getting hear means that the current id refers to an already added formal argument*/
        fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Formal argument already used in function \"%s\" at line %u\n", id, yylineno);
        return NULL;
    }

    /*Getting hear means that the argument name is valid, thus it is added to the scope list and symboltable*/
    entry = SymbolTable_insert(symTab, id, scope, yylineno, FORMAL_ID);
    ScopeTable_insert(scopeTab, entry, scope);

    if (!FuncStack_isEmpty(functionStack)) /*At this point funcStack is never empty: Extra Safety*/
    {
        if (FuncStack_topEntry(functionStack) != NULL)
        {
            /*
                In case that the current function name is valid, the argument is matched with its
                corresponding function using the FuncArg list.
            */
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

    /*Shadowing of library functions is not allowed*/
    if (checkForLibFunc(id))
    {
        fprintf_red(stdout, "[Syntax Analysis] -- ERROR: Library function \"%s\" shadowed at line %lu\n", id, yylineno);
        FuncStack_push(functionStack, NULL, scope);
        return NULL;
    }

    /*Looking up on the current scope*/
    entry = SymbolTable_lookup(symTab, id, scope);
    if (entry != NULL)
    {
        /*If something is found, definition is wrong*/

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
        /*If nothing is found, the function definition is okay so the function id is added to the structures*/
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
        /*As calling a variable is allowed on alpha, we only need to check if we have access to the entry returned to this rule*/
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
    if (NumberStack_isEmpty(loopStack))
    {
        fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Used \"%s\" statement outside of loop at line %lu\n", keyword, yylineno);
    }
    else if (!FuncStack_isEmpty(functionStack))
    {
        if (FuncStack_topScope(functionStack) >= NumberStack_top(loopStack))
        {
            fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Used \"%s\" statement outside of loop at line %lu\n", keyword, yylineno);
        }
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
