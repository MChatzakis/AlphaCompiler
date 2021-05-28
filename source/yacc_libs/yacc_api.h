/**
 * @file yacc_api.h
 * @author Manos Chatzakis (4238) Nikos Fanourakis (4237)
 * 
 * @brief Functions to be used for yacc
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#include "../utils/utils.h"
#include "../avm/avm.h"
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

/* ------------------------------------- ICG -------------------------------------*/
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
void ManageReturnStatement(expr *ex);
void ManageForStatement(forPrefixJumps *forPref, unsigned N1, unsigned N2, unsigned N3, stmt_t *st);
void printQuads(int verbosePrint, FILE *stream);
void printQuadVerbose(unsigned int i, FILE *stream);
void printQuadFormally(unsigned int i, FILE *stream);
void printExprVal(expr *ex, FILE *stream);
void printSymTabEntry(SymbolTableEntry *entry, FILE *stream);
void check_arith(expr *e);
void make_stmt(stmt_t *s);
void patchlist(int list, int label);
void partEvaluation(expr *rval);
void printToFile();
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
indexedPair *reverseIndexedPairList(indexedPair *plist);
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
void printToFile();

/* ------------------------------------- TCG -------------------------------------*/
unsigned consts_newstring(char *s);
unsigned consts_newnumber(double n);
unsigned libfuncs_newused(const char *s);
unsigned userfuncs_newfunc(SymbolTableEntry *sym);

void make_operand(expr *e, vmarg *arg);

/**
 * @brief Allocates and expands the quad array
 * 
 */
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

/**
 * @brief Creates a new quad with the corresponding attributes
 * 
 * @param op     Operation code
 * @param arg1   First operand
 * @param arg2   Second operand
 * @param result Variable which stores the result
 * @param label  Quad jump-to address (only for quads that change the flow)
 * @param line   The line of the file that the quad corresponds
 */
void emit(iopcode op, expr *arg1, expr *arg2, expr *result, unsigned label, unsigned line)
{
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
 * The new names follow the form "_f[curr function count]"
 */
void GenerateFuncName()
{
    sprintf(anonymous_func_prefix + 2, "%u", unamed_functions);
    unamed_functions++;
}

/**
 * @brief Initializes the function name array
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

/**
 * @brief Generates names for every anonymous variable
 * The new names follow the form "_t[curr variable count]"
 */
void newtempname()
{
    sprintf(temp_var_prefix + 2, "%u", tempcounter);
    tempcounter++;
}

/**
 * @brief Initializes the variable name array
 * It is invoked upon the beggining of compilation and after every statement
 */
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

/**
 * @brief Returns the current scope space
 * 
 * @return enum scopespace_t The current scope space
 */
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

/**
 * @brief Returns the current scope offset
 * 
 * @return unsigned The current offset count
 */
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

/**
 * @brief Increases the corresponding offset
 * 
 */
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

/**
 * @brief Increases scope space counter
 * 
 */
void enterscopespace()
{
    ++scopeSpaceCounter;
}

/**
 * @brief Decreases scope space counter
 * 
 */
void exitscopespace()
{
    assert(scopeSpaceCounter > 1);
    --scopeSpaceCounter;
}

/**
 * @brief Resets the formal argument offset
 * 
 */
void resetformalargsoffset()
{
    formalArgOffset = 0;
}

/**
 * @brief Resets the function local offset
 * 
 */
void resetfunctionlocalsoffset()
{
    functionLocalOffset = 0;
}

/**
 * @brief Restores the current scope offset, mainly upon exiting a function definition
 * 
 */
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

/**
 * @brief Returns the next quad label
 * 
 * @return unsigned The index of the next (current) quad label
 */
unsigned nextquadlabel()
{
    return currQuad;
}

/**
 * @brief Sets the label field of quadNo to label
 * 
 * @param quadNo Number of quad
 * @param label  The quad address to jump
 */
void patchlabel(unsigned quadNo, unsigned label)
{
    assert(quadNo < currQuad);
    quads[quadNo].label = label;
}

/**
 * @brief Generates a new expression containing the symbol sym
 * 
 * @param sym The symboltable entry
 * @return expr* The new expression containing the entry
 */
expr *lvalue_expr(SymbolTableEntry *sym)
{
    assert(sym);

    expr *e = (expr *)malloc(sizeof(expr));
    memset(e, 0, sizeof(expr));

    e->next = NULL;
    e->sym = sym; /*We shall never put NULL symbol to valid expressions*/

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

/**
 * @brief Returns an entry of a temporary variable. This variable could be an already allocated variable (optimization)
 * or a new symboltable entry.
 * @return SymbolTableEntry* The entry pointer to the tmp variable
 */
SymbolTableEntry *newtemp()
{
    char *name;
    SymbolTableEntry *sym;

    newtempname();
    name = temp_var_prefix;

    sym = SymbolTable_lookup(symTab, name, scope);
    if (sym == NULL)
    {
        /*A tmp variable could also be global*/
        if (scope > 0)
        {
            sym = SymbolTable_insert(symTab, name, scope, yylineno, LOCAL_ID);
        }
        else
        {
            sym = SymbolTable_insert(symTab, name, scope, yylineno, GLOBAL_ID);
        }

        /*Temporary variables participate in offset as regular variables*/
        sym->space = currscopespace();
        sym->offset = currscopeoffset();
        incurrscopeoffset();

        ScopeTable_insert(scopeTab, sym, scope);
    }

    return sym;
}

/**
 * @brief Creates a new statement
 * 
 * @return stmt_t* The pointer to the memory allocated for the statement
 */
stmt_t *newstmt()
{
    stmt_t *s = (stmt_t *)malloc(sizeof(stmt_t));
    memset((void *)s, 0, sizeof(stmt_t));

    s->breakList = 0;
    s->contList = 0;

    return s;
}

/**
 * @brief Creates a new expression
 * 
 * @param t      Expression type
 * @return expr* The pointer to the memory allocated for the expression
 */
expr *newexpr(expr_t t)
{
    expr *e = (expr *)malloc(sizeof(expr));
    memset(e, 0, sizeof(expr));

    e->type = t;
    return e;
}

/**
 * @brief Creates a new call object
 * 
 * @return call* The pointer to the memory allocated for the call object
 */
call *newcall()
{
    call *c = (call *)malloc(sizeof(call));
    memset(c, 0, sizeof(call));
    return c;
}

/**
 * @brief Creates a new indexed pair (key,value)
 * 
 * @param key The key expression of the pair
 * @param value The value expression of the pair
 * @return indexedPair* The memory allocated for the new pair
 */
indexedPair *newIndexPair(expr *key, expr *value)
{
    indexedPair *pair = (indexedPair *)malloc(sizeof(indexedPair));
    memset(pair, 0, sizeof(indexedPair));

    pair->key = key;
    pair->val = value;
    pair->next = NULL;

    return pair;
}

/**
 * @brief Creates a new forPrefixJumps object (test,enter)
 * 
 * @param test  The address of the condition
 * @param enter The address of the body
 * @return forPrefixJumps* 
 */
forPrefixJumps *newForPrefixJump(unsigned test, unsigned enter)
{
    forPrefixJumps *jmp = (forPrefixJumps *)malloc(sizeof(forPrefixJumps));
    memset(jmp, 0, sizeof(forPrefixJumps));

    jmp->enter = enter;
    jmp->test = test;

    return jmp;
}

/**
 * @brief Creates a new constnum expression, with the value i
 * 
 * @param i      The double value of the expression
 * @return expr* The pointer to the memory allocated for this expression
 */
expr *newexpr_constnum(double i)
{
    expr *e;
    e = newexpr(constnum_e);
    e->numConst = i;
    return e;
}

/**
 * @brief Creates a new conststring expression, with value s
 * 
 * @param s      The string value of the expression
 * @return expr* The pointer to the memory allocated for this expression
 */
expr *newexpr_conststring(char *s)
{
    expr *e = newexpr(conststring_e);
    e->strConst = strdup(s);
    return e;
}

/**
 * @brief Creates a new nil expression
 * 
 * @return expr* The pointer to the memory allocated for this expression
 */
expr *newexpr_nil()
{
    expr *e = newexpr(nil_e);
    return e;
}

/**
 * @brief Creates a new constbool expression, with value boolConst
 * 
 * @param boolConst The boolean value of the expression
 * @return expr* The pointer to the memory allocated for this expression
 */
expr *newexpr_constbool(unsigned char boolConst)
{
    expr *e = newexpr(constbool_e);
    e->boolConst = !!boolConst;
    return e;
}

/**
 * @brief If the e is tableitem, creates the emits for getelement, and returns the result of the getelement expression
 * else it returns the expression e without any change
 * This function is invoked every time a tableitem is used as an rvalue.
 * 
 * @param e      The expression to be checked
 * @return expr* The result if e is tableitem, else returns e without any change
 */
expr *emit_iftableitem(expr *e)
{
    if (e->type != tableitem_e)
    {
        return e;
    }
    else
    {
        expr *result = newexpr(var_e);
        result->sym = newtemp(); // = e[e->index]
        emit(tablegetelem_op, e, e->index, result, 0, yylineno);
        return result;
    }
}

/**
 * @brief Creates a new tableitem expression lv["name"] or lv.name
 * 
 * @param lv The table expression
 * @param name The index name
 * @return expr* The pointer to the memory allocated for the new tableitem expression
 */
expr *member_item(expr *lv, char *name)
{
    lv = emit_iftableitem(lv);       // Emit code if r-value use of table item
    expr *ti = newexpr(tableitem_e); // Make a new expression

    ti->sym = lv->sym;
    ti->index = newexpr_conststring(name); // Const string index

    return ti;
}

/**
 * @brief Creates a function call and returns the variable containing the result of the call
 * 
 * @param lv The function call expression
 * @param reversed_elist The argument list, reversed
 * @return expr* The pointer to the memory allocated for the expression that holds the return result
 */
expr *make_call(expr *lv, expr *reversed_elist)
{
    assert(lv); //reversed list could be NULL

    expr *func = emit_iftableitem(lv);

    /*Access Error Check*/
    if (lv->sym == NULL || !CheckPrimaryForAccess(lv->sym, scope))
    {
        compileError = 1;
    }

    while (reversed_elist)
    {
        emit(param_op, reversed_elist, NULL, NULL, 0, yylineno);
        reversed_elist = reversed_elist->next;
    }

    emit(call_op, func, NULL, NULL, 0, yylineno);
    //emit(call_op, NULL, NULL, func, 0, yylineno);

    expr *result = newexpr(var_e);
    result->sym = newtemp();

    emit(getretval_op, NULL, NULL, result, 0, yylineno);

    return result;
}

/**
 * @brief Manages a classic function call
 * 
 * @param lvalue The name of the function
 * @param callsuffix The call parameters
 * @return expr* The result of the call
 */
expr *ManageLvalueCallsuffix(expr *lvalue, call *callsuffix)
{
    expr *callFunc;
    expr *t;
    expr *curr, *prev;

    assert(lvalue && callsuffix);
    lvalue = emit_iftableitem(lvalue);

    /*If the function is a method, the lvalue should be added as the last parameter, representing "this"*/
    if (callsuffix->method)
    {
        t = lvalue;
        lvalue = emit_iftableitem(member_item(t, callsuffix->name));

        curr = callsuffix->elist;
        prev = NULL;
        while (curr)
        {
            prev = curr;
            curr = curr->next;
        }

        if (prev == NULL)
        {
            callsuffix->elist = t;
        }
        else
        {
            prev->next = t;
        }
    }

    callFunc = make_call(lvalue, callsuffix->elist);
    return callFunc;
}

/**
 * @brief   Creates the quads for the new table and its elements.
            Returns the table.
 * 
 * @param elist  Table's elements
 * @return expr* New table
 */
expr *ManageObjectDef(expr *elist)
{
    expr *t;
    int i;

    t = newexpr(newtable_e);
    t->sym = newtemp();

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

/**
 * @brief Prints the error message when a wrong assignment is made.
 * 
 * @param entry The lvalue entry
 * @return int Returns 1 for error, 0 for no-error
 */
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

/**
 * @brief Manages a method call
 * 
 * @param elist The parameter list
 * @param id The name of the method
 * @return call* The pointer for the memory allocated for the data of this call
 */
call *ManageMethodCall(expr *elist, char *id)
{
    call *newCall = newcall();

    newCall->elist = elist;
    newCall->method = 1;
    newCall->name = strdup(id);

    return newCall;
}

/**
 * @brief Manages a normal call
 * 
 * @param elist  The parameter list
 * @return call* The pointer for the memory allocated for the data of this call
 */
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
 * @param lval The lvalue expression
 * @param rval The rvalue expression
 * 
 * @return The assign expression
 */
expr *ManageAssignValue(expr *lval, expr *rval)
{
    expr *newExpr;
    SymbolTableEntry *entry;

    assert(lval && rval);

    partEvaluation(rval); /*Patches the true/false lists if a boolean expression is encountered*/

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
            return newexpr(undef_e); //dummy expression for not using null expression
        }

        emit(assign_op, rval, NULL, lval, 0, yylineno);

        newExpr = newexpr(assignexpr_e);
        newExpr->sym = newtemp();

        emit(assign_op, lval, NULL, newExpr, 0, yylineno);

        return newExpr;
    }
}

/**
 * @brief For every boolean expression encountered, it fixes its true/false lists with current quad
 * 
 * @param rval The input expression
 */
void partEvaluation(expr *rval)
{
    assert(rval);
    if (rval->type == boolexpr_e)
    {
        patchlist(rval->truelist, nextquadlabel());
        emit(assign_op, newexpr_constbool(1), NULL, rval, 0, yylineno);
        emit(jump_op, NULL, NULL, NULL, nextquadlabel() + 2, yylineno);

        patchlist(rval->falselist, nextquadlabel());
        emit(assign_op, newexpr_constbool(0), NULL, rval, 0, yylineno);
    }
}

/**
 * @brief Checks if the rvalue entry has proper access for the current scope
 * 
 * @param entry The rvalue expression symbol
 * @param scope The current scope
 * @return int Return 0 for error, 1 for non-error
 */
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
 * @param exVal The expression containing the symboltable entry of the identifier
 * 
 * @return The expression result
 */
expr *ManagePrimaryLValue(expr *exVal)
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
 * @brief Checks if an identifier exists in symboltable and if not, it inserts it in every case.
 * Corresponds to rule expr: lvalue: ID
 * 
 * @param id The name of the variable
 * @return expr* Pointer to the memory allocated containing the symboltable entry
 */
expr *EvaluateLValue(char *id)
{
    SymbolTableEntry *entry, *insertEntry;
    expr *exVal;

    /*Lookup, starting from current scope and going backwards till global scope*/
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
 * @return expr* The expression entry of the variable if no error occurs, otherwise undef expression
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
            exVal = newexpr(undef_e);
            return exVal;
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
 * @return expr * The expression entry of the variable if no error occurs, otherwise throws error and returns dummy expr 
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
        exVal = newexpr(undef_e);
        return exVal;
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
 * 
 * @param exVal The result of the function call
 * 
 * @return The result or the table item
 */
expr *ManagePrimaryFunction(expr *exVal)
{
    expr *newExp;

    assert(exVal);
    newExp = emit_iftableitem(exVal);

    return newExp;
}

/**
 * @brief Check if the use of return statement is valid
          and create the ret quad
 * 
 * @param ex The expression to return
 */
void ManageReturnStatement(expr *ex)
{
    if (ex != NULL)
    {
        partEvaluation(ex);
    }

    if (FuncStack_isEmpty(functionStack))
    {
        fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Used \"return\" statement outside of function at line %lu\n", yylineno);
        compileError = 1;
    }

    emit(ret_op, NULL, NULL, ex, 0, yylineno);
}

/**
 * @brief Creates a new break statement with unpatched break list
 * Throws error if this stmt is not inside a loop
 * 
 * @return stmt_t* The pointer to the memory allocated for this stmt
 */
stmt_t *ManageBreak()
{
    stmt_t *breakStmt;

    breakStmt = newstmt();
    make_stmt(breakStmt);

    if (loopcounter == 0)
    {
        fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Used \"break\" statement outside of loop at line %lu\n", yylineno);
        compileError = 1;
    }

    emit(jump_op, NULL, NULL, NULL, 0, yylineno);
    breakStmt->breakList = newlist(nextquadlabel() - 1);

    return breakStmt;
}

/**
 * @brief Creates a new continue statement with unpatched continue list
 * Throws error if this stmt is not inside a loop
 * 
 * @return stmt_t* The pointer to the memory allocated for this stmt
 */
stmt_t *ManageContinue()
{
    stmt_t *continueStmt;

    continueStmt = newstmt();
    make_stmt(continueStmt);
    if (loopcounter == 0)
    {
        fprintf_red(stderr, "[Syntax Analysis] -- ERROR: Used \"continue\" statement outside of loop at line %lu\n", yylineno);
        compileError = 1;
    }

    emit(jump_op, NULL, NULL, NULL, 0, yylineno);
    continueStmt->contList = newlist(nextquadlabel() - 1);

    return continueStmt;
}

/**
 * @brief Prints the entry to stream
 * 
 * @param entry 
 * @param stream 
 */
void printSymTabEntry(SymbolTableEntry *entry, FILE *stream)
{
    assert(entry);
    if (entry->type < 3)
    {
        fprintf(stream, "%s", (entry->value).varVal->name);
    }
    else
    {
        fprintf(stream, "%s", (entry->value).funcVal->name);
    }
}

/**
 * @brief Prints the expression to stream
 * 
 * @param expr 
 * @param stream 
 */
void printExprVal(expr *expr, FILE *stream)
{
    assert(expr);

    switch (expr->type)
    {
    case var_e:
        printSymTabEntry(expr->sym, stream);
        break;
    case tableitem_e:
        printSymTabEntry(expr->sym, stream);
        break;
    case programfunc_e:
        printSymTabEntry(expr->sym, stream);
        break;
    case libraryfunc_e:
        printSymTabEntry(expr->sym, stream);
        break;
    case arithexpr_e:
        printSymTabEntry(expr->sym, stream);
        break;
    case boolexpr_e:
        printSymTabEntry(expr->sym, stream);
        break;
    case assignexpr_e:
        printSymTabEntry(expr->sym, stream);
        break;
    case newtable_e:
        printSymTabEntry(expr->sym, stream);
        break;
    case constnum_e:
        if (is_int(expr->numConst))
        {
            fprintf(stream, "%d", (int)expr->numConst);
        }
        else
        {
            fprintf(stream, "%f", expr->numConst);
        }
        break;
    case constbool_e:
        //fprintf(ost, "%u", expr->boolConst);
        if (expr->boolConst == 1)
        {
            fprintf(stream, "TRUE");
        }
        else
        {
            fprintf(stream, "FALSE");
        }
        break;
    case conststring_e:
        fprintf(stream, "\"%s\"", expr->strConst);
        break;
    case nil_e:
        fprintf(stream, "NIL");
        break;
    default:
        assert(0);
    }
}

/**
 * @brief Prints the quads with analytical field description
 * 
 * @param i 
 * @param stream 
 */
void printQuadVerbose(unsigned int i, FILE *stream)
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

    fprintf(stream, "#%u: %s ", i, names[quads[i].op]);
    expr *ex;
    if (quads[i].result != NULL)
    {
        fprintf(stream, "[result: ");
        ex = quads[i].result;
        printExprVal(ex, stream);
        fprintf(stream, "] ");
    }

    if (quads[i].arg1 != NULL)
    {
        fprintf(stream, "[arg1: ");
        ex = quads[i].arg1;
        printExprVal(ex, stream);
        fprintf(stream, "] ");
    }

    if (quads[i].arg2 != NULL)
    {
        fprintf(stream, "[arg2: ");
        ex = quads[i].arg2;
        printExprVal(ex, stream);
        fprintf(stream, "] ");
    }

    fprintf(stream, "(label: %u) ", quads[i].label);

    fprintf(stream, "(line: %u)", quads[i].line);
    fprintf(stream, "\n");
}

/**
 * @brief Prints the quads in a simplified way
 * 
 * @param i 
 * @param stream 
 */
void printQuadFormally(unsigned int i, FILE *stream)
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

    fprintf(stream, "%u: %s ", i, names[quads[i].op]);
    expr *ex;
    if (quads[i].result != NULL)
    {
        ex = quads[i].result;
        printExprVal(ex, stream);
        fprintf(stream, " ");
    }

    if (quads[i].arg1 != NULL)
    {
        ex = quads[i].arg1;
        printExprVal(ex, stream);
        fprintf(stream, " ");
    }

    if (quads[i].arg2 != NULL)
    {
        ex = quads[i].arg2;
        printExprVal(ex, stream);
        fprintf(stream, " ");
    }

    if (isJumpCode(i))
        fprintf(stream, "%u ", quads[i].label);

    //fprintf(ost, "[%u]", quads[i].line);
    fprintf(stream, "\n");
}

/**
 * @brief Prints the quads to the stream
 * 
 * @param verbosePrint 
 * @param stream 
 */
void printQuads(int verbosePrint, FILE *stream)
{
    unsigned int i;

    fprintf(stream, "----------------------- QUADS -----------------------\n");

    for (i = 1; i < currQuad; i++)
    {
        if (verbosePrint)
            printQuadVerbose(i, stream);
        else
        {
            printQuadFormally(i, stream);
        }
    }

    fprintf(stream, "-----------------------------------------------------\n");
}

/**
 * @brief Checks whether or not a number is an int
 * 
 * @param d Number d
 * @return int 0 if the number is double, 1 if its int
 */
int is_int(double d)
{
    return (int)d == d;
}

/**
 * @brief Checks if the expression e is valid for arithmetic expressions
 * 
 * @param e The input expression
 */
void check_arith(expr *e)
{
    if (e->type == constbool_e ||
        e->type == conststring_e ||
        e->type == nil_e ||
        e->type == newtable_e ||
        e->type == programfunc_e ||
        e->type == libraryfunc_e ||
        e->type == boolexpr_e) /*Should we include undef_expr?*/
    {
        fprintf_red(stderr, "[Alpha Compiler] -- ERROR: Illegal (non arithmetic) expression used in line %u\n", yylineno);
        compileError = 1;
    }
}

/**
 * @brief Manages uminus expressions
 * 
 * @param exVal The input expression
 * @return expr* The pointer to the arithmetic expression created
 */
expr *ManageUminus(expr *exVal)
{
    expr *ex;

    check_arith(exVal);

    ex = newexpr(arithexpr_e);
    ex->sym = newtemp();

    emit(uminus_op, exVal, NULL, ex, 0, yylineno);

    return ex;
}

/**
 * @brief Manages not expressions
 * 
 * @param exVal  The input expression
 * @return expr* The pointer to the boolean expression created
 */
expr *ManageNot(expr *exVal)
{
    expr *ex;

    exVal = valToBool(exVal, nextquadlabel(), nextquadlabel() + 1);
    ex = newexpr(boolexpr_e);

    ex->sym = exVal->sym;

    ex->truelist = exVal->falselist;
    ex->falselist = exVal->truelist;

    return ex;
}

/**
 * @brief Manages lval++ expressions
 * 
 * @param exVal  The input expression
 * @return expr* The pointer to the expression created
 */
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
        emit(tablesetelem_op, exVal->index, val, exVal, 0, yylineno);
    }
    else
    {
        emit(assign_op, exVal, NULL, ex, 0, yylineno);
        emit(add_op, exVal, newexpr_constnum(1), exVal, 0, yylineno);
    }

    return ex;
}

/**
 * @brief Manages ++lvalue expressions
 * 
 * @param exVal The input expression
 * @return expr* The new expression created
 */
expr *ManagePlusPlusLvalue(expr *exVal) //++lvalue
{
    expr *ex;

    check_arith(exVal);
    if (exVal->type == tableitem_e)
    {
        ex = emit_iftableitem(exVal);
        emit(add_op, ex, newexpr_constnum(1), ex, 0, yylineno);
        emit(tablesetelem_op, exVal->index, ex, exVal, 0, yylineno);
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

/**
 * @brief Manages lvalue-- expressions
 * 
 * @param exVal  The input expression
 * @return expr* The new expression
 */
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
        emit(tablesetelem_op, exVal->index, val, exVal, 0, yylineno);
    }
    else
    {
        emit(assign_op, exVal, NULL, ex, 0, yylineno);
        emit(sub_op, exVal, newexpr_constnum(1), exVal, 0, yylineno);
    }

    return ex;
}

/**
 * @brief Manages --lvalue expressions
 * 
 * @param exVal  The input expression
 * @return expr* The new expression created
 */
expr *ManageMinusMinusLvalue(expr *exVal) //--val
{
    expr *ex;

    check_arith(exVal);
    if (exVal->type == tableitem_e)
    {
        ex = emit_iftableitem(exVal);
        emit(sub_op, ex, newexpr_constnum(1), ex, 0, yylineno);
        emit(tablesetelem_op, exVal->index, ex, exVal, 0, yylineno);
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

/**
 * @brief Checks if id matches to a temporary variable
 * 
 * @param s Id
 * @return unsigned int 1 if matches a temporary variable else 0
 */
unsigned int istempname(const char *s)
{
    return s[0] == '_' && s[1] == 'v';
}

/**
 * @brief Checks if an expression is a tmp expression
 * 
 * @param e The input expression
 * @return unsigned int 1 on success 0 on failure
 */
unsigned int istempexpr(expr *e)
{
    return e->sym && istempname((e->sym->value).varVal->name);
}

/**
 * @brief Manages arithmetic expressions
 * 
 * @param expr1 First operand
 * @param op    Operation code
 * @param expr2 Second operand
 * @return expr* Result expression
 */
expr *ManageArithmeticExpression(expr *expr1, iopcode op, expr *expr2)
{
    //expr *constExpr;
    expr *expr;

    assert(expr1 && expr2);

    check_arith(expr1);
    check_arith(expr2);

    /*Const arithmetic expression optimization*/
    /*if (expr1->type == constnum_e && expr2->type == constnum_e)
    {
        double arRes;
        expr = newexpr(assignexpr_e);
        expr->sym = newtemp();

        switch (op)
        {
        case add_op:
            arRes = expr1->numConst + expr2->numConst;
            break;
        case sub_op:
            arRes = expr1->numConst - expr2->numConst;
            break;
        case mul_op:
            arRes = expr1->numConst * expr2->numConst;
            break;
        case div_op:
            arRes = expr1->numConst / expr2->numConst;
            break;
        case mod_op:
            arRes = (double)((int)expr1->numConst % (int)expr2->numConst);
            break;
        default:
            assert(0);
        }

        constExpr = newexpr_constnum(arRes);
        emit(assign_op, constExpr, NULL, expr, 0, yylineno);
    }
    else
    {*/
    expr = newexpr(arithexpr_e);
    expr->sym = newtemp();

    emit(op, expr1, expr2, expr, 0, yylineno);
    //}

    return expr;
}

/**
 * @brief Manages relation expressions
 * 
 * @param ex1 First operand
 * @param op    Operation code
 * @param ex2 Second operand
 * @return expr* Result expression
 */
expr *ManageRelationExpression(expr *ex1, iopcode op, expr *ex2)
{
    expr *ex;

    assert(ex1 && ex2);

    if (op != if_eq_op && op != if_noteq_op)
    {
        check_arith(ex1);
        check_arith(ex2);
    }

    ex = newexpr(boolexpr_e);
    ex->sym = newtemp(); /*An auto to vgaloyme, doylevei akrivws opws to tool me ligoteres krifes metavlites. O savidis deixnei oti prepei na bei..*/
    ex->truelist = newlist(nextquadlabel());
    ex->falselist = newlist(nextquadlabel() + 1);

    emit(op, ex1, ex2, NULL, 0, yylineno);
    emit(jump_op, NULL, NULL, NULL, 0, yylineno);
    return ex;
}

/**
 * @brief Manages the actions to be done for if prefix
 * 
 * @param ex The prefix expression
 * @return int The quadlabel of the unfinished jump (fail jump)
 */
int ManageIfPrefix(expr *ex)
{
    int ifprefix;

    partEvaluation(ex);
    emit(if_eq_op, ex, newexpr_constbool(1), NULL, nextquadlabel() + 2, yylineno);

    ifprefix = nextquadlabel();

    emit(jump_op, NULL, NULL, NULL, 0, yylineno);

    return ifprefix;
}

/**
 * @brief Manages the actions to be done after a for stmt is complete
 * 
 * @param forPref For prefix labels for the jumps
 * @param N1 Before Elist label
 * @param N2 Before Body label 
 * @param N3 After Body label
 * @param st The loopstmt
 */
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

/**
 * @brief Manages for prefix actions
 * 
 * @param expr The input expression
 * @param M The elist label
 * @return forPrefixJumps* The test and enter labels 
 */
forPrefixJumps *ManageForPrefix(expr *expr, unsigned M)
{
    forPrefixJumps *forprefix;

    partEvaluation(expr);

    forprefix = newForPrefixJump(M, nextquadlabel());

    emit(if_eq_op, expr, newexpr_constbool(1), NULL, 0, yylineno);

    return forprefix;
}

/**
 * @brief Initializes stmt lists
 * 
 * @param s The input statement
 */
void make_stmt(stmt_t *s)
{
    s->breakList = 0;
    s->contList = 0;
}

/**
 * @brief Initializes a new quad list
 * 
 * @param i The quad index
 * @return int The quad index
 */
int newlist(int i)
{
    quads[i].label = 0;
    return i;
}

/**
 * @brief Merges two quad lists, by attaching the second to the first one
 * 
 * @param l1 The first list
 * @param l2 The second list
 * @return int The head quad index of the list
 */
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

/**
 * @brief Traverses a quad list and patches the labels
 * 
 * @param list The head quad index
 * @param label The label to patch the quads of the list
 */
void patchlist(int list, int label)
{
    while (list)
    {
        int next = quads[list].label;
        quads[list].label = label;
        list = next;
    }
}

/**
 * @brief Reverses the expression list
 * 
 * @param elist  The expression list
 * @return expr* The reversed expression list
 */
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

/**
 * @brief Reverses an indexed pair list
 * 
 * @param plist The list head
 * @return indexedPair* The reversed list head
 */
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

/**
 * @brief Manages indexed object definition
 *        with elements with the format {key : value}
 * 
 * @param list The pairs list
 * @return expr* The result of the definition
 */
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

/**
 * @brief Returns whether or not an opcode is jumpcode for the prints
 * 
 * @param i 
 * @return int 
 */
int isJumpCode(int i)
{
    quad q = quads[i];
    if ((q.op >= 10 && q.op <= 15) || q.op == 25)
    {
        return 1;
    }
    return 0;
}

/**
 * @brief Manages AND expressions using partial evaluation
 * 
 * @param ex1 The first operand
 * @param ex2 The second operant
 * @param qd The patch label
 * @return expr* The result of the AND expression
 */
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

/**
 * @brief Manages OR expressions using partial evaluation
 * 
 * @param ex1 The first operand
 * @param ex2 The second operant
 * @param qd The patch label
 * @return expr* The result of the OR expression
 */
expr *ManageORexpression(expr *ex1, expr *ex2, int qd)
{
    expr *e;
    e = newexpr(boolexpr_e);
    e->sym = newtemp();

    patchlist(ex1->falselist, qd);

    e->truelist = mergelist(ex1->truelist, ex2->truelist);
    e->falselist = ex2->falselist;

    return e;
}

/**
 * @brief Converts every non boolean expression to boolean.
          It is used only for logical operations.
 * 
 * @param ex1       Expression operand
 * @param truejump  Truelist of the expression
 * @param falsejump Falselist of the expression
 * @return expr*    The boolean expression
 */
expr *valToBool(expr *ex1, int truejump, int falsejump)
{
    expr *ex;

    if (ex1->type != boolexpr_e)
    {
        ex = newexpr(boolexpr_e);
        ex->sym = newtemp();

        ex->truelist = newlist(truejump);
        ex->falselist = newlist(falsejump);

        emit(if_eq_op, ex1, newexpr_constbool(1), NULL, 0, yylineno);
        emit(jump_op, NULL, NULL, NULL, 0, yylineno);

        return ex;
    }
    else
        return ex1;
}

/**
 * @brief Prints the quads to "quads.txt file"
 * 
 */
void printToFile()
{
    FILE *fp;

    fp = fopen("quads.txt", "w+");

    if (fp == NULL)
    {
        fprintf(stderr, "Couldn't open quads.txt\n");
        return;
    }

    //printQuads(0, fp);
    printQuads(1, fp);

    fclose(fp);
}

/* ------------------------------------- TCG -------------------------------------*/
unsigned consts_newstring(char *s)
{
    return 0;
}

unsigned consts_newnumber(double n)
{
    return 0;
}

unsigned libfuncs_newused(const char *s)
{
    return 0;
}

unsigned userfuncs_newfunc(SymbolTableEntry *sym)
{
    return 0;
}

void make_operand(expr *e, vmarg *arg)
{
    switch (e->type)
    {
    case var_e:
    case tableitem_e:
    case arithexpr_e:
    case boolexpr_e:
    case newtable_e:
    {
        assert(e->sym);
        arg->val = e->sym->offset;
        switch (e->sym->space)
        {
        case programvar:
        {
            arg->type = global_a;
            break;
        }
        case functionlocal:
        {
            arg->type = local_a;
            break;
        }
        case formalarg:
        {
            arg->type = formal_a;
            break;
        }
        default:
            assert(0);
        }

        break;
    }
    case constbool_e:
    {
        arg->val = e->boolConst;
        arg->type = bool_a;
        break;
    }
    case conststring_e:
    {
        arg->val = consts_newstring(e->strConst);
        arg->type = string_a;
        break;
    }
    case constnum_e:
    {
        arg->val = consts_newnumber(e->numConst);
        arg->type = number_a;
        break;
    }
    case nil_e:
    {
        arg->type = nil_a;
        break;
    }
    case programfunc_e:
    {
        arg->type = userfunc_a;
        //arg->val = e->sym->taddress;
        arg->val = userfuncs_newfunc(e->sym);
        break;
    }
    case libraryfunc_e:
    {
        arg->type = libfunc_a;
        arg->val = libfuncs_newused((e->sym->value).funcVal->name);//e->sym->name);
        break;
    }
    default:
        assert(0);
    }
}

void make_numberoperand(vmarg *arg, double val)
{
    arg->val = consts_newnumber(val);
    arg->type = number_a;
}

void make_booloperand(vmarg *arg, unsigned val)
{
    arg->val = val;
    arg->type = bool_a;
}

void make_retvaloperand(vmarg *arg)
{
    arg->type = retval_a;
}
/* Prepei na ftiaksoume tis akolouthes */
void reset_operand(vmarg *arg)
{
}

void emitInstruction(instruction i)
{
}

unsigned nextinstructionlabel()
{
    return 0;
}

unsigned currprocessedquad()
{
    return 0;
}

void generate(enum vmopcode op, quad *q)
{
    /*instruction t;
    t.opcode = op;
    make_operand(q->arg1, &t.arg1);
    make_operand(q->arg2, &t.arg2);
    make_operand(q->result, &t.result);

    q->label*/
}

void generate_relational(enum vmopcode op, quad *q)
{
    /*instruction t;
    t.opcode = op;
    make_operand(q.arg1, &t.arg1);
    make_operand(q.arg2, &t.arg2);
    t.result.type = label_a;
    if (quad.label jump target < currprocessedquad())
        t.result.value = quads[quad.label].taddress;
    else
        add_incomplete_jump(nextinstructionlabel(), quad.label);
    quad.taddress = nextinstructionlabel();
    emitInstruction(t);*/
}

void generate_ADD(quad *q) { generate(add_v, q); }
void generate_SUB(quad *q) { generate(sub_v, q); }
void generate_MUL(quad *q) { generate(mul_v, q); }
void generate_DIV(quad *q) { generate(div_v, q); }
void generate_MOD(quad *q) { generate(mod_v, q); }

void generate_NEWTABLE(quad *q) { generate(newtable_v, q); }
void generate_TABLEGETELEM(quad *q) { generate(tablegetelem_v, q); }
void generate_TABLESETELEM(quad *q) { generate(tablesetelem_v, q); }
void generate_ASSIGN(quad *q) { generate(assign_v, q); }
void generate_NOP()
{
    instruction t;
    t.opcode = nop_v;
    emitInstruction(t);
}

void generate_JUMP(quad *q) { generate_relational(jump_v, q); }
void generate_IF_EQ(quad *q) { generate_relational(jeq_v, q); }
void generate_IF_NOTEQ(quad *q) { generate_relational(jne_v, q); }
void generate_IF_GREATER(quad *q) { generate_relational(jgt_v, q); }
void generate_IF_GREATEREQ(quad *q) { generate_relational(jge_v, q); }
void generate_IF_LESS(quad *q) { generate_relational(jlt_v, q); }
void generate_IF_LESSEQ(quad *q) { generate_relational(jle_v, q); }

void generate_NOT(quad *q)
{
    q->label = nextinstructionlabel();
    instruction t;
    t.opcode = jeq_v;
    make_operand(q->arg1, &t.arg1);
    make_booloperand(&t.arg2, 0);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel() + 3;
    emitInstruction(t);
    t.opcode = assign_v;
    make_booloperand(&t.arg1, 0);
    reset_operand(&t.arg2);
    make_operand(q->result, &t.result);
    emitInstruction(t);

    t.opcode = jump_v;
    reset_operand(&t.arg1);
    reset_operand(&t.arg2);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel() + 2;
    emitInstruction(t);
    t.opcode = assign_v;
    make_booloperand(&t.arg1, 1);
    reset_operand(&t.arg2);
    make_operand(q->result, &t.result);
    emitInstruction(t);
}

void generate_OR(quad *q)
{
    q->label = nextinstructionlabel();
    instruction t;

    t.opcode = jeq_v;

    make_operand(q->arg1, &t.arg1);
    make_booloperand(&t.arg2, 1);

    t.result.type = label_a;
    t.result.val = nextinstructionlabel() + 4;

    emitInstruction(t);

    make_operand(q->arg2, &t.arg1);

    t.result.val = nextinstructionlabel() + 3;

    emitInstruction(t);

    t.opcode = assign_v;

    make_booloperand(&t.arg1, 0);
    reset_operand(&t.arg2);
    make_operand(q->result, &t.result);
    emitInstruction(t);

    t.opcode = jump_v;

    reset_operand(&t.arg1);
    reset_operand(&t.arg2);

    t.result.type = label_a;
    t.result.val = nextinstructionlabel() + 2;

    emitInstruction(t);

    t.opcode = assign_v;
    make_booloperand(&t.arg1, 1);
    reset_operand(&t.arg2);
    make_operand(q->result, &t.result);
    emitInstruction(t);
}

void generate_PARAM(quad *q)
{
    q->label = nextinstructionlabel();
    instruction t;
    t.opcode = pusharg_v;
    make_operand(q->arg1, &t.arg1);
    emitInstruction(t);
}

void generate_CALL(quad *q)
{
    q->label = nextinstructionlabel();
    instruction t;
    t.opcode = call_v;
    make_operand(q->arg1, &t.arg1);
    emitInstruction(t);
}

void generate_GETRETVAL(quad *q)
{
    q->label = nextinstructionlabel();
    instruction t;
    t.opcode = assign_v;
    make_operand(q->result, &t.result);
    make_retvaloperand(&t.arg1);
    emitInstruction(t);
}

void generate_FUNCSTART(quad *q){
    SymbolTableEntry *f;
    f = q->result->sym;
    (f->value).funcVal->address = nextinstructionlabel();

    //userfunctions.add(f->id, f->taddress, f->totallocals);
    //!gia activation record: push(funcstack,f);
    instruction t;
    t.opcode = funcenter_v;
    make_operand(q->result, &t.result);
    emitInstruction(t);
}


void generate_RETURN(quad *q){
    q->label = nextinstructionlabel();
    instruction t;
    t.opcode = assign_v;
    make_retvaloperand(&t.result);
    make_operand(q->arg1, &t.arg1);
    emitInstruction(t);

    
    // !SymbolTableEntry *f = top(funcstack);
    // !append(f.returnList, nextinstructionlabel());

    t.opcode = jump_v;
    reset_operand(&t.arg1);
    reset_operand(&t.arg2);
    t.result.type = label_a;
    emitInstruction(t);
}

void generate_FUNCEND(quad *q){
    SymbolTableEntry *f;
    // !f = pop(funcstack);
    //backpatch(f.returnList, nextinstuctionlabel());
    q->label = nextinstructionlabel();

    instruction t;
    t.opcode = funcexit_v;
    make_operand(q->result, &t.result);
    emitInstruction(t);
}

void generate_UMINUS(quad *q){

}

void generate_AND(quad *q){

}

typedef void (*generator_func_t)(quad *);

generator_func_t generators[] = {
    generate_ASSIGN,
    generate_ADD,
    generate_SUB,
    generate_MUL,
    generate_DIV,
    generate_MOD,
    generate_UMINUS,
    generate_AND,
    generate_OR,
    generate_NOT,
    generate_IF_EQ,
    generate_IF_NOTEQ,
    generate_IF_LESSEQ,
    generate_IF_GREATEREQ,
    generate_IF_LESS,
    generate_IF_GREATER,
    generate_CALL,
    generate_PARAM,
    generate_RETURN,
    generate_GETRETVAL,
    generate_FUNCSTART,
    generate_FUNCEND,
    generate_NEWTABLE,
    generate_TABLEGETELEM,
    generate_TABLESETELEM,
    generate_JUMP
};

void generateInstructions(){
    for(unsigned i = 0; i < total; ++i)
        (*generators[quads[i].op])(quads+i);
}


