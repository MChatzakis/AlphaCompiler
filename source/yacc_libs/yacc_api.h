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
#include "structs.h"

int yyerror(char *message);
int yylex(void);

extern unsigned compileError;
extern int yylineno;
extern char *yytext;
extern FILE *yyin;

unsigned int scope = 0;
unsigned int loopcounter = 0;
unsigned int unamed_functions = 0;
unsigned int tempcounter = 0;

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
void ManageReturnStatement();
void ManageForStatement(forPrefixJumps *forPref, unsigned N1, unsigned N2, unsigned N3, stmt_t *st);
void printQuads(int verbosePrint);
void printQuadVerbose(unsigned int i);
void printQuadFormally(unsigned int i);
void printExprVal(expr *ex);
void printSymTabEntry(SymbolTableEntry *entry);
void check_arith(expr *e);
void make_stmt(stmt_t *s);
void patchlist(int list, int label);
void partEvaluation(expr *rval);
enum scopespace_t currscopespace();
unsigned currscopeoffset();
unsigned nextquadlabel();
unsigned int istempname(const char *s);
unsigned int istempexpr(expr *e);
int CheckForAccess(SymbolTableEntry *entry, unsigned int scope);
int CheckForAssignError(SymbolTableEntry *entry);
int CheckPrimaryForAccess(SymbolTableEntry *entry, unsigned int scope);
int ManageIfPrefix(expr *ex);
int is_int(double d);
int isJumpCode(int i);
int newlist(int i);
int mergelist(int l1, int l2);
SymbolTableEntry *newtemp();
SymbolTableEntry *CheckAddFormal(char *id);
SymbolTableEntry *ManageIDFunctionDefinition(char *id);
forPrefixJumps *newForPrefixJump(unsigned test, unsigned enter);
forPrefixJumps *ManageForPrefix(expr *expr, unsigned M);
stmt_t *newstmt();
stmt_t *ManageBreak();
stmt_t *ManageContinue();
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
expr *ManageUminus(expr *exVal);
expr *ManageNot(expr *exVal);
expr *ManageLvaluePlusPlus(expr *exVal);
expr *ManagePlusPlusLvalue(expr *exVal);
expr *ManageLvalueMinusMinus(expr *exVal);
expr *ManageMinusMinusLvalue(expr *exVal);
expr *ManageRelationExpression(expr *ex1, iopcode op, expr *ex2);
expr *ManageArithmeticExpression(expr *expr1, iopcode op, expr *expr2);
expr *reverseExprList(expr *elist);
expr *ManageIndexedObjectDef(indexedPair *list);
expr *ManageANDexpression(expr *ex1, expr *ex2, int qd);
expr *ManageORexpression(expr *ex1, expr *ex2, int qd);
expr *valToBool(expr *ex, int truej, int falsej);
indexedPair *reverseIndexedPairList(indexedPair *plist);

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

stmt_t *newstmt()
{
    stmt_t *s = (stmt_t *)malloc(sizeof(stmt_t));
    memset((void *)s, 0, sizeof(stmt_t));
    s->breakList = 0;
    s->contList = 0;
    return s;
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

forPrefixJumps *newForPrefixJump(unsigned test, unsigned enter)
{
    forPrefixJumps *jmp = (forPrefixJumps *)malloc(sizeof(forPrefixJumps));
    memset(jmp, 0, sizeof(forPrefixJumps));

    jmp->enter = enter;
    jmp->test = test;

    return jmp;
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
    //expr *e = newexpr(boolexpr_e);expr *e = newexpr(boolexpr_e);
    expr *e = newexpr(constbool_e);
    e->boolConst = !!boolConst;
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
        emit(tablegetelem_op, e->index, e, result, 0, yylineno);
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
    assert(lv); //reversed list could be NULL
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

        if (callsuffix->elist != NULL) /* ! fix gia to seg sta palia test Grammar kai tree! */
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
    /*Elist needs to be reversed here*/
    emit(tablecreate_op, NULL, NULL, t, 0, yylineno);
    for (i = 0; elist; elist = elist->next)
        emit(tablesetelem_op, newexpr_constnum(i++), elist, t, 0, yylineno);

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

    partEvaluation(rval);

    if (lval->type == tableitem_e)
    {
        emit(tablesetelem_op, lval->index, rval, lval, 0, yylineno);
        newExpr = emit_iftableitem(lval);
        newExpr->type = assignexpr_e;
        return newExpr;
    }
    else
    {
        entry = lval->sym;

        if (entry == NULL || CheckForAssignError(entry))
        {
            compileError = 1;
            return newexpr(undef_e);
        }

        emit(assign_op, rval, NULL, lval, 0, yylineno);

        newExpr = newexpr(assignexpr_e);
        newExpr->sym = newtemp();

        emit(assign_op, lval, NULL, newExpr, 0, yylineno);

        return newExpr;
    }
}

void partEvaluation(expr *rval)
{
    assert(rval);
    if (rval->type == boolexpr_e)
    {
        //printf("patching putch\n");
        patchlist(rval->truelist, nextquadlabel());
        emit(assign_op, newexpr_constbool(1), NULL, rval, 0, yylineno);
        emit(jump_op, NULL, NULL, NULL, nextquadlabel() + 2, yylineno);
        patchlist(rval->falselist, nextquadlabel());
        emit(assign_op, newexpr_constbool(0), NULL, rval, 0, yylineno);
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
        compileError = 1;
        return NULL;
    }

    /*Look up on the current scope*/
    if ((entry = SymbolTable_lookup(symTab, id, scope)) != NULL)
    {
        /*Getting hear means that the current id refers to an already added formal argument*/
        fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Formal argument already used in function \"%s\" at line %u\n", id, yylineno);
        compileError = 1;
        return NULL;
    }

    /*Getting hear means that the argument name is valid, thus it is added to the scope list and symboltable*/
    entry = SymbolTable_insert(symTab, id, scope, yylineno, FORMAL_ID);
    ScopeTable_insert(scopeTab, entry, scope);

    entry->space = currscopespace();
    entry->offset = currscopeoffset();
    incurrscopeoffset();

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
void ManageReturnStatement(expr *ex)
{
    //assert(ex);

    if (FuncStack_isEmpty(functionStack))
    {
        fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Used \"return\" statement outside of function at line %lu\n", yylineno);
        compileError = 1;
        //return;
    }

    emit(ret_op, NULL, NULL, ex, 0, yylineno);
}

stmt_t *ManageBreak()
{
    stmt_t *breakStmt;

    breakStmt = newstmt();
    make_stmt(breakStmt); //auto gia kapoio logo to deinxei by reference
    if (loopcounter == 0)
    {
        fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Used \"break\" statement outside of loop at line %lu\n", yylineno);
        compileError = 1;
        return breakStmt;
    }

    emit(jump_op, NULL, NULL, NULL, 0, yylineno);
    breakStmt->breakList = newlist(nextquadlabel() - 1);

    return breakStmt;
}

stmt_t *ManageContinue()
{
    stmt_t *continueStmt;

    continueStmt = newstmt();

    make_stmt(continueStmt); //auto gia kapoio logo to deinxei by reference
    if (loopcounter == 0)
    {
        fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Used \"continue\" statement outside of loop at line %lu\n", yylineno);
        compileError = 1;
    }

    emit(jump_op, NULL, NULL, NULL, 0, yylineno);
    continueStmt->contList = newlist(nextquadlabel() - 1);

    return continueStmt;
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
        //fprintf(ost, "%u", expr->boolConst);
        if (expr->boolConst == 1)
        {
            fprintf(ost, "TRUE");
        }
        else
        {
            fprintf(ost, "FALSE");
        }
        break;
    case conststring_e:
        fprintf(ost, "\"%s\"", expr->strConst);
        break;
    case nil_e:
        fprintf(ost, "NIL");
        break;
    default:
        assert(0);
    }
}

void printQuadVerbose(unsigned int i)
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

    fprintf(ost, "#%u: %s ", i, names[quads[i].op]);
    expr *ex;
    if (quads[i].result != NULL)
    {
        fprintf(ost, "[result: ");
        ex = quads[i].result;
        printExprVal(ex);
        fprintf(ost, "] ");
    }

    if (quads[i].arg1 != NULL)
    {
        fprintf(ost, "[arg1: ");
        ex = quads[i].arg1;
        printExprVal(ex);
        fprintf(ost, "] ");
    }

    if (quads[i].arg2 != NULL)
    {
        fprintf(ost, "[arg2: ");
        ex = quads[i].arg2;
        printExprVal(ex);
        fprintf(ost, "] ");
    }

    fprintf(ost, "(label: %u) ", quads[i].label);

    fprintf(ost, "(line: %u)", quads[i].line);
    fprintf(ost, "\n");
}

void printQuadFormally(unsigned int i)
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

    fprintf(ost, "%u: %s ", i, names[quads[i].op]);
    expr *ex;
    if (quads[i].result != NULL)
    {
        ex = quads[i].result;
        printExprVal(ex);
        fprintf(ost, " ");
    }

    if (quads[i].arg1 != NULL)
    {
        ex = quads[i].arg1;
        printExprVal(ex);
        fprintf(ost, " ");
    }

    if (quads[i].arg2 != NULL)
    {
        ex = quads[i].arg2;
        printExprVal(ex);
        fprintf(ost, " ");
    }

    if (isJumpCode(i))
        fprintf(ost, "%u ", quads[i].label);

    //fprintf(ost, "[%u]", quads[i].line);
    fprintf(ost, "\n");
}

void printQuads(int verbosePrint)
{
    unsigned int i;

    fprintf(ost, "\n----------------------- QUADS -----------------------\n");
    //fprintf(ost, "#quad,opcode,result,arg1,arg2,label,line\n");

    for (i = 1; i < currQuad; i++)
    {
        if (verbosePrint)
            printQuadVerbose(i);
        else
        {
            printQuadFormally(i);
        }
    }

    fprintf(ost, "-----------------------------------------------------\n");
    //fprintf(ost, "#quad opcode result arg1 arg2 label line\n");
}

int is_int(double d)
{
    double absolute = abs(d);
    return absolute == floor(absolute);
}

void check_arith(expr *e)
{
    if (e->type == constbool_e ||
        e->type == conststring_e ||
        e->type == nil_e ||
        e->type == newtable_e ||
        e->type == programfunc_e ||
        e->type == libraryfunc_e ||
        e->type == boolexpr_e)
    {
        fprintf_red(stderr, "[Alpha Compiler] -- ERROR: Illegal (non arithmetic) expression used in line %u\n", yylineno);
        compileError = 1;
    }
}

expr *ManageUminus(expr *exVal)
{
    expr *ex;

    check_arith(exVal);
    ex = newexpr(arithexpr_e);
    ex->sym = newtemp();
    emit(uminus_op, exVal, NULL, ex, 0, yylineno);

    return ex;
}

expr *ManageNot(expr *exVal)
{
    expr *ex;
    exVal = valToBool(exVal, nextquadlabel(), nextquadlabel() + 1);
    ex = newexpr(boolexpr_e);
    //if(exVal->sym)
    ex->sym = exVal->sym;
    //emit(not_op, exVal, NULL, ex, 0, 0);
    ex->truelist = exVal->falselist;
    ex->falselist = exVal->truelist;

    return ex;
}

expr *ManageLvaluePlusPlus(expr *exVal) //lvalue ++
{
    expr *ex;
    check_arith(exVal);
    ex = newexpr(var_e);
    ex->sym = newtemp();

    if (exVal->type == tableitem_e)
    {
        expr *val = emit_iftableitem(exVal);
        emit(assign_op, val, NULL, ex, 0, yylineno);
        emit(add_op, val, newexpr_constnum(1), val, 0, yylineno);
        emit(tablesetelem_op, exVal->index, exVal, val, 0, yylineno);
    }
    else
    {
        emit(assign_op, exVal, NULL, ex, 0, yylineno);
        emit(add_op, exVal, newexpr_constnum(1), exVal, 0, yylineno);
    }

    return ex;
}

expr *ManagePlusPlusLvalue(expr *exVal) //++lvalue
{
    expr *ex;

    check_arith(exVal);
    if (exVal->type == tableitem_e)
    {
        ex = emit_iftableitem(exVal);
        emit(add_op, ex, newexpr_constnum(1), ex, 0, yylineno);
        emit(tablesetelem_op, exVal->index, exVal, ex, 0, yylineno);
    }
    else
    {
        emit(add_op, exVal, newexpr_constnum(1), exVal, 0, yylineno);
        ex = newexpr(arithexpr_e);
        ex->sym = newtemp();
        emit(assign_op, exVal, NULL, ex, 0, yylineno);
    }

    return ex;
}

expr *ManageLvalueMinusMinus(expr *exVal) //val--
{
    expr *ex;
    check_arith(exVal);
    ex = newexpr(var_e);
    ex->sym = newtemp();

    if (exVal->type == tableitem_e)
    {
        expr *val = emit_iftableitem(exVal);
        emit(assign_op, val, NULL, ex, 0, yylineno);
        emit(sub_op, val, newexpr_constnum(1), val, 0, yylineno);
        emit(tablesetelem_op, exVal->index, exVal, val, 0, yylineno);
    }
    else
    {
        emit(assign_op, exVal, NULL, ex, 0, yylineno);
        emit(sub_op, exVal, newexpr_constnum(1), exVal, 0, yylineno);
    }

    return ex;
}

expr *ManageMinusMinusLvalue(expr *exVal) //--val
{
    expr *ex;

    check_arith(exVal);
    if (exVal->type == tableitem_e)
    {
        ex = emit_iftableitem(exVal);
        emit(sub_op, ex, newexpr_constnum(1), ex, 0, yylineno);
        emit(tablesetelem_op, exVal->index, exVal, ex, 0, yylineno);
    }
    else
    {
        emit(sub_op, exVal, newexpr_constnum(1), exVal, 0, yylineno);
        ex = newexpr(arithexpr_e);
        ex->sym = newtemp();
        emit(assign_op, exVal, NULL, ex, 0, yylineno);
    }

    return ex;
}

unsigned int istempname(const char *s)
{
    return s[0] == '_' && s[1] == 'v';
}

unsigned int istempexpr(expr *e)
{
    return e->sym && istempname((e->sym->value).varVal->name);
}

expr *ManageArithmeticExpression(expr *expr1, iopcode op, expr *expr2)
{
    expr *expr;
    assert(expr1 && expr2);

    check_arith(expr1);
    check_arith(expr2);

    /*if (expr1->type == constnum_e && expr2->type == constnum_e)
    {
        expr = newexpr(constnum_e);
        switch (op)
        {
        case add_op:
            expr->numConst = expr1->numConst + expr2->numConst;
            break;
        case sub_op:
            expr->numConst = expr1->numConst - expr2->numConst;
            break;
        case mul_op:
            expr->numConst = expr1->numConst * expr2->numConst;
            break;
        case div_op:
            expr->numConst = expr1->numConst / expr2->numConst;
            break;
        case mod_op:
            expr->numConst = (int)expr1->numConst % (int)expr2->numConst;
            break;
        default:
            assert(0);
        }
    }
    else
    {
        expr = newexpr(arithexpr_e);
        expr->sym = newtemp();
    }*/

    expr = newexpr(arithexpr_e);
    expr->sym = newtemp();

    emit(op, expr1, expr2, expr, 0, yylineno);
    return expr;
}

expr *ManageRelationExpression(expr *ex1, iopcode op, expr *ex2)
{
    expr *ex;

    assert(ex1 && ex2);

    //check_arith(ex1);
    //check_arith(ex2);

    ex = newexpr(boolexpr_e);
    ex->sym = newtemp(); /*An auto to vgaloyme, doylevei akrivws opws to tool me ligoteres krifes metavlites. O savidis deixnei oti prepei na bei..*/

    //ex->sym = istempexpr(ex1) ? ex1->sym : newtemp();
    ex->truelist = newlist(nextquadlabel());      //exei thema giati den exei ginei akoma to prwto emit an einai stin arxi.
    ex->falselist = newlist(nextquadlabel() + 1); //to idio thema (mipws na kanoume ena arxiko allocation?)

    emit(op, ex1, ex2, NULL, 0, yylineno); //???
    emit(jump_op, NULL, NULL, NULL, 0, yylineno);
    return ex;
}

int ManageIfPrefix(expr *ex)
{
    int ifprefix;
    partEvaluation(ex);
    emit(if_eq_op, ex, newexpr_constbool(1), NULL, nextquadlabel() + 2, yylineno);
    ifprefix = nextquadlabel();
    emit(jump_op, NULL, NULL, NULL, 0, yylineno);
    return ifprefix;
}

void ManageForStatement(forPrefixJumps *forPref, unsigned N1, unsigned N2, unsigned N3, stmt_t *st)
{

    int bl = 0, cl = 0;

    patchlabel(forPref->enter, N2 + 1);
    patchlabel(N1, nextquadlabel());
    patchlabel(N2, forPref->test);
    patchlabel(N3, N1 + 1);

    if (st != NULL)
    {
        bl = st->breakList;
        cl = st->contList;
    }

    patchlist(bl, nextquadlabel());
    patchlist(cl, N1 + 1);
}

forPrefixJumps *ManageForPrefix(expr *expr, unsigned M)
{
    forPrefixJumps *forprefix;

    partEvaluation(expr);
    forprefix = newForPrefixJump(M, nextquadlabel());
    emit(if_eq_op, expr, newexpr_constbool(1), NULL, 0, yylineno);
    return forprefix;
}

void make_stmt(stmt_t *s)
{
    s->breakList = 0;
    s->contList = 0;
}

int newlist(int i)
{
    quads[i].label = 0;
    return i;
}

int mergelist(int l1, int l2)
{
    if (!l1)
        return l2;
    else if (!l2)
        return l1;
    else
    {
        int i = l1;
        while (quads[i].label)
            i = quads[i].label;
        quads[i].label = l2;
        return l1;
    }
}

void patchlist(int list, int label)
{
    while (list)
    {
        printf("quad[%d].label == %d\n", list, label);
        int next = quads[list].label;
        quads[list].label = label;
        list = next;
    }
}

expr *reverseExprList(expr *elist)
{
    expr *tmp = NULL, *curr = elist, *prev = NULL;

    while (curr)
    {
        tmp = curr->next;

        curr->next = prev;
        prev = curr;

        curr = tmp;
    }

    return prev;
}

indexedPair *reverseIndexedPairList(indexedPair *plist)
{
    indexedPair *tmp = NULL, *curr = plist, *prev = NULL;

    while (curr)
    {
        tmp = curr->next;

        curr->next = prev;
        prev = curr;

        curr = tmp;
    }

    return prev;
}

expr *ManageIndexedObjectDef(indexedPair *list)
{
    expr *t = newexpr(newtable_e);
    indexedPair *ptr;

    t->sym = newtemp();
    emit(tablecreate_op, NULL, NULL, t, 0, yylineno);
    ptr = list;

    while (ptr)
    {
        emit(tablesetelem_op, ptr->key, ptr->val, t, 0, yylineno);
        ptr = ptr->next;
    }

    return t;
}

int isJumpCode(int i)
{
    quad q = quads[i];
    if ((q.op >= 10 && q.op <= 15) || q.op == 25)
    {
        return 1;
    }
    return 0;
}

expr *ManageANDexpression(expr *ex1, expr *ex2, int qd)
{
    expr *e;
    e = newexpr(boolexpr_e);
    e->sym = newtemp();

    patchlist(ex1->truelist, qd);

    e->truelist = ex2->truelist;
    e->falselist = mergelist(ex1->falselist, ex2->falselist);
    return e;
}

expr *ManageORexpression(expr *ex1, expr *ex2, int qd)
{
    expr *e;
    e = newexpr(boolexpr_e);
    //e->sym = istempexpr(ex2) ? ex2->sym : newtemp();
    e->sym = newtemp();
    patchlist(ex1->falselist, qd);
    //printf("after patch list!\n");
    e->truelist = mergelist(ex1->truelist, ex2->truelist);
    e->falselist = ex2->falselist;

    return e;
}

expr *valToBool(expr *ex1, int truejump, int falsejump)
{
    expr *ex;
    if (ex1->type != boolexpr_e)
    {
        ex = newexpr(boolexpr_e);
        ex->sym = newtemp();

        ex->truelist = newlist(truejump);   //exei thema giati den exei ginei akoma to prwto emit an einai stin arxi.
        ex->falselist = newlist(falsejump); //to idio thema (mipws na kanoume ena arxiko allocation?)
        emit(if_eq_op, ex1, newexpr_constbool(1), NULL, 0, yylineno);
        emit(jump_op, NULL, NULL, NULL, 0, yylineno);
        //printf("Ex truelist... %d\n", ex->truelist);
        //printf("Ex falselist... %d\n", ex->falselist);

        return ex;
    }
    else
        return ex1;
}