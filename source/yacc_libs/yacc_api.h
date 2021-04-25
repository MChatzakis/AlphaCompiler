/**
 * @file yacc_api.h
 * @author Manos Chatzakis (4238) Nikos Fanourakis (4237)
 * @brief Functions to be used for yacc
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#include "../utils/utils.h"
//#include "../symboltable/symboltable.h"
#include "structs.h"

int yyerror(char *message);
int yylex(void);

extern int yylineno;
extern char *yytext;
extern FILE *yyin;

unsigned int scope = 0;
unsigned int unamed_functions = 0;
unsigned int tempcounter = 0;
unsigned int loop_stack = 0;

unsigned compileError = 0;
unsigned programVarOffset = 0;
unsigned functionLocalOffset = 0;
unsigned formalArgOffset = 0;
unsigned scopeSpaceCounter = 1;

char anonymous_func_prefix[13];
char temp_var_prefix[13];

SymbolTable *symTab;
ScopeTable *scopeTab;
FuncStack *functionStack;
NumberStack *loopStack;
NumberStack *scopeoffsetstack;

FILE *ost; /*Output stream*/

quad *quads = NULL;
unsigned total = 0;
unsigned int currQuad = 0;

#define EXPAND_SIZE 1024
#define CURR_SIZE (total * sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE * sizeof(quad) + CURR_SIZE)

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

void expand();
void emit(iopcode op, expr *arg1, expr *arg2, expr *result, unsigned label, unsigned line);
void GenerateFuncName();
void InitFuncNames();
void newtempname();
void resettemp();
void patchlabel(unsigned quadNo, unsigned label);
void incurrscopeoffset();
void enterscopespace();
void exitscopespace();
void resetformalargsoffset();
void resetfunctionlocalsoffset();
void restorecurrscopeoffset(unsigned n);
void ManageLoopKeywords(char *keyword);
void ManageReturnStatement();
void printQuads();
void printQuad(unsigned int i);
void printExprVal(expr *ex);
void printSymTabEntry(SymbolTableEntry *entry);
enum scopespace_t currscopespace();
unsigned currscopeoffset();
unsigned nextquadlabel();
int CheckForAccess(SymbolTableEntry *entry, unsigned int scope);
int CheckForAssignError(SymbolTableEntry *entry);
int CheckPrimaryForAccess(SymbolTableEntry *entry, unsigned int scope);
int is_int(double d);
SymbolTableEntry *newtemp();
SymbolTableEntry *CheckAddFormal(char *id);
SymbolTableEntry *ManageIDFunctionDefinition(char *id);
call *newcall();
call *ManageMethodCall(expr *elist, char *id);
call *ManageNormalCall(expr *elist);
expr *newexpr(expr_t t);
expr *lvalue_expr(SymbolTableEntry *sym);
expr *newexpr_constnum(double i);
expr *newexpr_conststring(char *s);
expr *newexpr_constbool(unsigned char boolConst);
expr *newexpr_nil();
expr *emit_iftableitem(expr *e);
expr *member_item(expr *lv, char *name);
expr *make_call(expr *lv, expr *reversed_elist);
expr *ManageLvalueCallsuffix(expr *lvalue, call *callsuffix);
expr *ManageObjectDef(expr *elist);
expr *ManageAssignValue(expr *lval, expr *rval);
expr *ManagePrimaryFunction(expr *exVal);
expr *ManagePrimaryLValue(expr *exVal);
expr *EvaluateLValue(char *id);
expr *EvaluateGlobalLValue(char *id);
expr *EvaluateLocalLValue(char *id);

void expand()
{
    assert(total == currQuad);
    quad *p = (quad *)malloc(NEW_SIZE);
    if (quads)
    {
        memcpy(p, quads, CURR_SIZE);
        free(quads);
    }
    quads = p;
    total += EXPAND_SIZE;
}

void emit(iopcode op, expr *arg1, expr *arg2, expr *result, unsigned label, unsigned line)
{

    if (compileError)
    {
        return;
    }

    if (currQuad == total)
    {
        expand();
    }

    quad *p = quads + currQuad++;
    p->op = op;
    p->arg1 = arg1;
    p->arg2 = arg2;
    p->result = result;
    p->label = label;
    p->line = line;
}

/**
 * @brief Generates names for every anonymous function
 * 
 */
void GenerateFuncName()
{
    sprintf(anonymous_func_prefix + 2, "%u", unamed_functions);
    unamed_functions++;
}

/**
 * @brief Initializes the name array
 * 
 */
void InitFuncNames()
{
    int i;

    anonymous_func_prefix[0] = '_';
    anonymous_func_prefix[1] = 'f';
    for (i = 2; i < 13; i++)
    {
        anonymous_func_prefix[i] = '\0';
    }
}

void newtempname()
{
    sprintf(temp_var_prefix + 2, "%u", tempcounter);
    tempcounter++;
}

void resettemp()
{
    int i;

    tempcounter = 0;

    temp_var_prefix[0] = '_';
    temp_var_prefix[1] = 'v';

    for (i = 2; i < 13; i++)
    {
        temp_var_prefix[i] = '\0';
    }
}

enum scopespace_t currscopespace()
{
    if (scopeSpaceCounter == 1)
    {
        return programvar;
    }
    else if (scopeSpaceCounter % 2 == 0)
    {
        return formalarg;
    }

    return functionlocal;
}

unsigned currscopeoffset()
{
    switch (currscopespace())
    {
    case programvar:
        return programVarOffset;
    case functionlocal:
        return functionLocalOffset;
    case formalarg:
        return formalArgOffset;
    default:
        assert(0);
    }
}

void incurrscopeoffset()
{
    switch (currscopespace())
    {
    case programvar:
        ++programVarOffset;
        break;
    case functionlocal:
        ++functionLocalOffset;
        break;
    case formalarg:
        ++formalArgOffset;
        break;
    default:
        assert(0);
    }
}

void enterscopespace()
{
    ++scopeSpaceCounter;
}

void exitscopespace()
{
    assert(scopeSpaceCounter > 1);
    --scopeSpaceCounter;
}

void resetformalargsoffset()
{
    formalArgOffset = 0;
}

void resetfunctionlocalsoffset()
{
    functionLocalOffset = 0;
}

void restorecurrscopeoffset(unsigned n)
{
    switch (currscopespace())
    {
    case programvar:
        programVarOffset = n;
        break;
    case functionlocal:
        functionLocalOffset = n;
        break;
    case formalarg:
        formalArgOffset = n;
        break;
    default:
        assert(0);
    }
}

unsigned nextquadlabel()
{
    return currQuad;
}

void patchlabel(unsigned quadNo, unsigned label)
{
    assert(quadNo < currQuad);
    quads[quadNo].label = label;
}

expr *lvalue_expr(SymbolTableEntry *sym)
{
    assert(sym);
    expr *e = (expr *)malloc(sizeof(expr));
    memset(e, 0, sizeof(expr));

    e->next = NULL;
    e->sym = sym;

    switch (sym->type)
    {
    case LOCAL_ID:
        e->type = var_e;
        break;
    case GLOBAL_ID:
        e->type = var_e;
        break;
    case FORMAL_ID:
        e->type = var_e;
        break;
    case USERFUNC_ID:
        e->type = programfunc_e;
        break;
    case LIBFUNC_ID:
        e->type = libraryfunc_e;
        break;
    default:
        assert(0);
    }
    return e;
}

SymbolTableEntry *newtemp()
{
    char *name;
    SymbolTableEntry *sym;

    newtempname();

    name = temp_var_prefix;

    sym = SymbolTable_lookup(symTab, name, scope);
    if (sym == NULL)
    {
        if (scope > 0)
        {
            sym = SymbolTable_insert(symTab, name, scope, yylineno, LOCAL_ID);
        }
        else
        {
            sym = SymbolTable_insert(symTab, name, scope, yylineno, GLOBAL_ID);
        }

        sym->space = currscopespace();
        sym->offset = currscopeoffset();
        incurrscopeoffset();

        ScopeTable_insert(scopeTab, sym, scope);

        //printf("Added new symtab entry\n");
    }

    return sym;
}

expr *newexpr(expr_t t)
{
    expr *e = (expr *)malloc(sizeof(expr));
    memset(e, 0, sizeof(expr));
    e->type = t;
    return e;
}

call *newcall()
{
    call *c = (call *)malloc(sizeof(call));
    memset(c, 0, sizeof(call));
    return c;
}

indexedPair *newIndexPair(expr *key, expr *value)
{
    indexedPair *pair = (indexedPair *)malloc(sizeof(indexedPair));
    memset(pair, 0, sizeof(indexedPair));
    pair->key = key;
    pair->val = value;
    pair->next = NULL;
    return pair;
}

expr *newexpr_constnum(double i)
{
    expr *e;
    e = newexpr(constnum_e);
    e->numConst = i;
    return e;
}

expr *newexpr_conststring(char *s)
{
    expr *e = newexpr(conststring_e);
    e->strConst = strdup(s);
    return e;
}

expr *newexpr_nil()
{
    expr *e = newexpr(nil_e);
    return e;
}

expr *newexpr_constbool(unsigned char boolConst)
{
    expr *e = newexpr(boolexpr_e);
    e->boolConst = boolConst;
    return e;
}

expr *emit_iftableitem(expr *e)
{
    if (e->type != tableitem_e)
    {
        return e;
    }
    else
    {
        expr *result = newexpr(var_e);
        result->sym = newtemp();
        emit(tablegetelem_op, e, e->index, result, 0, yylineno);
        return result;
    }
}

expr *member_item(expr *lv, char *name)
{
    lv = emit_iftableitem(lv);       // Emit code if r-value use of table item
    expr *ti = newexpr(tableitem_e); // Make a new expression
    ti->sym = lv->sym;
    ti->index = newexpr_conststring(name); // Const string index
    return ti;
}

expr *make_call(expr *lv, expr *reversed_elist)
{
    assert(lv && reversed_elist);
    expr *func = emit_iftableitem(lv);
    while (reversed_elist)
    {
        emit(param_op, reversed_elist, NULL, NULL, 0, yylineno);
        reversed_elist = reversed_elist->next;
    }
    emit(call_op, func, NULL, NULL, 0, yylineno);
    expr *result = newexpr(var_e);
    result->sym = newtemp();
    emit(getretval_op, NULL, NULL, result, 0, yylineno);
    return result;
}

expr *ManageLvalueCallsuffix(expr *lvalue, call *callsuffix)
{
    expr *callFunc;
    expr *t;

    assert(lvalue && callsuffix);
    lvalue = emit_iftableitem(lvalue);
    if (callsuffix->method)
    {
        t = lvalue;
        lvalue = emit_iftableitem(member_item(t, callsuffix->name));
        callsuffix->elist->next = t; //vazei to onoma sto elist?
    }
    callFunc = make_call(lvalue, callsuffix->elist);
    return callFunc;
}

expr *ManageObjectDef(expr *elist)
{
    expr *t;
    int i;
    t = newexpr(newtable_e);
    t->sym = newtemp();
    emit(tablecreate_op, t, NULL, NULL, 0, yylineno);
    for (i = 0; elist; elist = elist->next)
        emit(tablesetelem_op, t, newexpr_constnum(i++), elist, 0, yylineno);

    return t;
}

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

int CheckForAssignError(SymbolTableEntry *entry)
{
    assert(entry);
    /*If the lvalue refers to a function (eg. print = 5;) an error is thrown*/
    if (entry->type == 3)
    {
        fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Assigned value to User defined function \"%s\" at line %u\n", (entry->value).funcVal->name, yylineno);
        fprintf_cyan(stderr, "[Syntax Analysis] -- NOTE: Function \"%s\" defined at line %lu\n", (entry->value).funcVal->name, (entry->value).funcVal->line);
        return 1;
    }
    else if (entry->type == 4)
    {
        fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Assigned value to Library function \"%s\" at line %u\n", (entry->value).funcVal->name, yylineno);
        return 1;
    }
    /*If the lvalue is not a function, we only need to check for the accessibility.*/
    else if (!CheckForAccess(entry, scope))
    {
        fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Assigned value to not accessible variable \"%s\" at line %u\n", (entry->value).varVal->name, yylineno);
        fprintf_cyan(stderr, "[Syntax Analysis] -- NOTE: Variable \"%s\" is declared at line %lu\n", (entry->value).varVal->name, (entry->value).varVal->line);
        return 1;
    }

    return 0;
}

call *ManageMethodCall(expr *elist, char *id)
{
    call *newCall = newcall();

    newCall->elist = elist;
    newCall->method = 1;
    newCall->name = strdup(id);

    return newCall;
}

call *ManageNormalCall(expr *elist)
{
    call *newCall = newcall();

    newCall->elist = elist;
    newCall->method = 0;
    newCall->name = NULL;

    return newCall;
}

/**
 * @brief Manages the actions to be done at an assignment expression.
 * It corresponds to rule expr: lvalue ASSIGN expr.
 * 
 * @param entry The symboltable entry of the identifier
 */
expr *ManageAssignValue(expr *lval, expr *rval)
{
    expr *newExpr;
    SymbolTableEntry *entry;

    assert(lval && rval);

    if (lval->type == tableitem_e)
    {
        emit(tablesetelem_op, lval, lval->index, rval, 0, yylineno);
        newExpr = emit_iftableitem(lval);
        newExpr->type = assignexpr_e;
        return newExpr;
    }
    else
    {
        //printf("IM IN\n");
        entry = lval->sym;

        if (entry == NULL || CheckForAssignError(entry))
        {
            compileError = 1;
            return newexpr(undef_e);
        }

        //okay
        emit(assign_op, rval, NULL, lval, 0, yylineno);

        newExpr = newexpr(assignexpr_e);
        newExpr->sym = newtemp();

        emit(assign_op, lval, NULL, newExpr, 0, yylineno);

        return newExpr;
    }
}

int CheckPrimaryForAccess(SymbolTableEntry *entry, unsigned int scope)
{
    if (!CheckForAccess(entry, scope))
    {
        fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Used not accessible variable \"%s\" as primary value at line %u\n", (entry->value).varVal->name, yylineno);
        fprintf_cyan(stderr, "[Syntax Analysis] -- NOTE: Variable \"%s\" is declared at line %lu\n", (entry->value).varVal->name, (entry->value).varVal->line);
        return 0;
    }

    return 1;
}

/**
 * @brief Manages the actions to be done when the value of a symbol table entry is asked.
 * It corresponds to rule primary:   lvalue x
 *                                  |call
 * 
 * @param entry The symboltable entry of the identifier
 */
expr *ManagePrimaryLValue(expr *exVal)
{
    expr *newExp;
    assert(exVal);

    newExp = emit_iftableitem(exVal);

    if (newExp->sym == NULL || !CheckPrimaryForAccess(newExp->sym, scope))
    {
        compileError = 1;
        //return newexpr(undef_e);
    }

    return newExp;
}

/**
 * @brief Checks if an identifier exists in symboltable and if not, it inserts it in every case.
 * Corresponds to rule expr: lvalue: ID
 * 
 * @param id The name of the variable
 * @return SymbolTableEntry * The entry of the identifier
 */
expr *EvaluateLValue(char *id)
{
    SymbolTableEntry *entry, *insertEntry;
    expr *exVal;
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
        entry->space = currscopespace();
        entry->offset = currscopeoffset();
        incurrscopeoffset();
    }
    /*Else the id found somewhere in the symtab and its returned right after the lookup*/
    exVal = lvalue_expr(entry);

    return exVal;
}

/**
 * @brief Checks if the local variable exists. If not, it is inserted in the symbol table.
 * It corresponds to yacc rule lvalue: local id
 * 
 * @param id The name of the local variable 
 * @return SymbolTableEntry* The entry of the variable if no error occurs, otherwise NULL
 */
expr *EvaluateLocalLValue(char *id)
{
    SymbolTableEntry *entry, *insertEntry;
    expr *exVal;
    /*Look up on current scope*/
    if ((entry = SymbolTable_lookup(symTab, id, scope)) == NULL)
    {

        /*We get here only if nothing was found in the current scope*/

        /*Using lib name is forbidden when scope > 0*/
        if (checkForLibFunc(id))
        {
            fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Library Function \"%s\" redefined as local variable at line %u\n", id, yylineno);
            compileError = 1;
            return newexpr(undef_e);
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
        entry->space = currscopespace();
        entry->offset = currscopeoffset();
        incurrscopeoffset();
    }
    //else it means that the lookup to the current scope found the corresponding symbol, so no actions needed here.
    exVal = lvalue_expr(entry);
    return exVal;
}

/**
 * @brief Checks if the global variable exists. If not, prints error.
 * It corresponds to yacc rule lvalue: global id
 * 
 * @param id The name of the global variable 
 * @return SymbolTableEntry* The entry of the variable if no error occurs, otherwise NULL 
 */
expr *EvaluateGlobalLValue(char *id)
{
    SymbolTableEntry *entry;
    expr *exVal;

    /*Lookup in the global scope*/
    entry = SymbolTable_lookup(symTab, id, 0);
    if (entry == NULL)
    {
        /*If nothing is found, error is thrown and NULL is returned*/
        fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Undefined global symbol \"%s\" at line %u\n", id, yylineno);
        compileError = 1;
        return newexpr(undef_e);
    }

    exVal = lvalue_expr(entry);
    return exVal;
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
        compileError = 1;
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
        compileError = 1;
        return NULL;
    }
    else
    {
        /*If nothing is found, the function definition is okay so the function id is added to the structures*/
        insertEntry = SymbolTable_insert(symTab, id, scope, yylineno, USERFUNC_ID);
        ScopeTable_insert(scopeTab, insertEntry, scope);

        entry = insertEntry;
        FuncStack_push(functionStack, entry, scope);

        (entry->value).funcVal->address = nextquadlabel();
    }

    return entry;
}

/**
 * @brief Manages the actions to be done when a function is called (rule primary: call)
 * If the id called is a variable it checks the accessibility and throws an error message.
 * 
 * @param entry The ID's entry on symboltable
 */
expr *ManagePrimaryFunction(expr *exVal)
{
    expr *newExp;
    assert(exVal);

    newExp = emit_iftableitem(exVal);

    if (newExp->sym == NULL || !CheckPrimaryForAccess(newExp->sym, scope))
    {
        compileError = 1;
    }

    return newExp;
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

void printSymTabEntry(SymbolTableEntry *entry)
{
    assert(entry);
    if (entry->type < 3)
    {
        fprintf(ost, "%s", (entry->value).varVal->name);
    }
    else
    {
        fprintf(ost, "%s", (entry->value).funcVal->name);
    }
}

void printExprVal(expr *expr)
{
    assert(expr);

    switch (expr->type)
    {
    case var_e:
        printSymTabEntry(expr->sym);
        break;
    case tableitem_e:
        printSymTabEntry(expr->sym);
        break;
    case programfunc_e:
        printSymTabEntry(expr->sym);
        break;
    case libraryfunc_e:
        printSymTabEntry(expr->sym);
        break;
    case arithexpr_e:
        printSymTabEntry(expr->sym);
        break;
    case boolexpr_e:
        printSymTabEntry(expr->sym);
        break;
    case assignexpr_e:
        printSymTabEntry(expr->sym);
        break;
    case newtable_e:
        printSymTabEntry(expr->sym);
        break;
    case constnum_e:
        if (is_int(expr->numConst))
        {
            fprintf(ost, "%d", (int)expr->numConst);
        }
        else
        {
            fprintf(ost, "%f", expr->numConst);
        }
        break;
    case constbool_e:
        fprintf(ost, "%u", expr->boolConst);
        break;
    case conststring_e:
        fprintf(ost, "%s", expr->strConst);
        break;
    case nil_e:
        fprintf(ost, "NIL");
        break;
    default:
        assert(0);
    }
}

void printQuad(unsigned int i)
{
    char *names[26] = {
        "assign",
        "add",
        "sub",
        "mul",
        "div",
        "mod",
        "uminus",
        "and",
        "or",
        "not",
        "if_eq",
        "if_noteq",
        "if_lesseq",
        "if_greatereq",
        "if_less",
        "if_greater",
        "call",
        "param",
        "ret",
        "getretval",
        "funcstart",
        "funcend",
        "tablecreate",
        "tablegetelem",
        "tablesetelem",
        "jump"};

    fprintf(ost, "#%u: [%s] ", i, names[quads[i].op]);
    expr *ex;
    if (quads[i].result != NULL)
    {
        fprintf(ost, "[result: ");
        ex = quads[i].result;
        printExprVal(ex);
        fprintf(ost, "] ");
    }
    /*else
    {
        fprintf(ost, "-");
    }
    fprintf(ost, ",");*/
    if (quads[i].arg1 != NULL)
    {
        fprintf(ost, "[arg1: ");
        ex = quads[i].arg1;
        printExprVal(ex);
        fprintf(ost, "] ");
    }
    /*else
    {
        fprintf(ost, "-");
    }
    fprintf(ost, ",");*/
    if (quads[i].arg2 != NULL)
    {
        fprintf(ost, "[arg2: ");
        ex = quads[i].arg2;
        printExprVal(ex);
        fprintf(ost, "] ");
    }
    /*else
    {
        fprintf(ost, "-");
    }*/

    if (quads[i].label != 0)
    {
        fprintf(ost, "(label: %u) ", quads[i].label);
    }

    fprintf(ost, "(line: %u)", quads[i].line);
    fprintf(ost, "\n");
}

void printQuads()
{
    unsigned int i;

    fprintf(ost, "\n----------------------- QUADS -----------------------\n");
    //fprintf(ost, "#quad,opcode,result,arg1,arg2,label,line\n");

    for (i = 0; i < currQuad; i++)
    {
        printQuad(i);
    }

    fprintf(ost, "-----------------------------------------------------\n");
    //fprintf(ost, "#quad opcode result arg1 arg2 label line\n");
}

int is_int(double d)
{
    double absolute = abs(d);
    return absolute == floor(absolute);
}