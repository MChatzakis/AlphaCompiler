#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#include "avm.h"
#include "../utils/utils.h"

#define MAGIC_NUMBER 12345678
#define HASH_MULTIPLIER 65599
#define DEFAULT_STR_SIZE 128

#define AVM_STACKENV_SIZE 4
#define N AVM_STACKSIZE

#define AVM_MAX_INSTRUCTIONS (unsigned)nop_v
#define AVM_NUMACTUALS_OFFSET +4
#define AVM_SAVEDPC_OFFSET +3
#define AVM_SAVEDTOP_OFFSET +2
#define AVM_SAVEDTOPSP_OFFSET +1

#define AVM_ENDING_PC codeSize

#define avm_error fprintf_avm_red
#define avm_warning fprintf_avm_yellow

#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic

avm_memcell ax, bx, cx;
avm_memcell retval;

unsigned char executionFinished = 0;

unsigned top, topsp;
unsigned pc = 0;
unsigned currLine = 0;
unsigned codeSize = 0;

instruction *code = (instruction *)0;

unsigned totalActuals = 0;

unsigned totalNumConsts = 0;
double *numConsts = NULL;

unsigned totalStringConsts = 0;
char **stringConsts = NULL;

unsigned totalNamedLibfuncs = 0;
char **namedLibfuncs = NULL;

unsigned totalUserFuncs = 0;
userfunc *userFuncs = NULL;

typedef void (*library_func_t)();

typedef char *(*tostring_func_t)(avm_memcell *);
char *typeStrings[8] = {
    "number",
    "string",
    "bool",
    "table",
    "userfunc",
    "libfunc",
    "nil",
    "undef"};

/* ---------------------- Executors ---------------------- */
void execute_assign(instruction *instr);
void execute_add(instruction *instr);
void execute_sub(instruction *instr);
void execute_mul(instruction *instr);
void execute_div(instruction *instr);
void execute_mod(instruction *instr);
void execute_uminus(instruction *instr);
void execute_and(instruction *instr);
void execute_or(instruction *instr);
void execute_not(instruction *instr);
void execute_jump(instruction *instr);
void execute_jeq(instruction *instr);
void execute_jne(instruction *instr);
void execute_jle(instruction *instr);
void execute_jge(instruction *instr);
void execute_jlt(instruction *instr);
void execute_jgt(instruction *instr);
void execute_call(instruction *instr);
void execute_pusharg(instruction *instr);
void execute_funcenter(instruction *instr);
void execute_funcexit(instruction *instr);
void execute_newtable(instruction *instr);
void execute_tablegetelem(instruction *instr);
void execute_tablesetelem(instruction *instr);
void execute_assign(instruction *instr);
void execute_nop(instruction *instr);
void execute_arithmetic(instruction *instr);

typedef void (*execute_func_t)(instruction *);

execute_func_t executeFuncs[] = {
    execute_assign,
    execute_add,
    execute_sub,
    execute_mul,
    execute_div,
    execute_mod,
    execute_uminus,
    execute_and,
    execute_or,
    execute_not,
    execute_jump,
    execute_jeq,
    execute_jne,
    execute_jle,
    execute_jge,
    execute_jlt,
    execute_jgt,
    execute_call,
    execute_pusharg,
    NULL, //!
    execute_funcenter,
    execute_funcexit,
    execute_newtable,
    execute_tablegetelem,
    execute_tablesetelem,
    execute_nop};
/* ---------------------- ------- ---------------------- */

/* ---------------------- AVM Functions ---------------------- */
avm_memcell *avm_translate_operand(vmarg *arg, avm_memcell *reg);
avm_memcell *avm_getactual(unsigned i);
avm_memcell *avm_tablegetelem(avm_table *table, avm_memcell *index);
userfunc *avm_getfuncinfo(unsigned address);
library_func_t avm_getlibraryfunc(char *id);
avm_table *avm_tablenew(void);
avm_table *avm_copyTable(avm_table *src);
avm_table *avm_getTableKeys(avm_table *src);
static void avm_initstack();
void avm_calllibfunc(char *id);
void avm_assign(avm_memcell *lv, avm_memcell *rv);
void avm_callsaveenvironment(void);
void avm_dec_top();
void avm_push_envvalue(unsigned val);
void avm_callsaveenvironment();
void avm_registerlibfunc(char *id, library_func_t addr);
void avm_tablesetelem(avm_table *table, avm_memcell *index, avm_memcell *content);
void avm_tableincrefcounter(avm_table *t);
void avm_tabledecrefcounter(avm_table *t);
void avm_tablebucketsinit(avm_table_bucket **p);
void avm_tabledelelem(avm_table *table, avm_memcell *index);
void avm_tablebucketsinit_customSize(avm_table_bucket **p, unsigned size);
void avm_tablebucketsdestroy_CustomSize(avm_table_bucket **p, unsigned size);
void avm_memcellclear(avm_memcell *m);
void avm_tablebucketsdestroy(avm_table_bucket **p);
void avm_tabledestroy(avm_table *t);
void avm_calllibfunc(char *id);
char *avm_tostring(avm_memcell *);
unsigned avm_get_envvalue(unsigned i);
unsigned avm_totalactuals();
unsigned char avm_tobool(avm_memcell *m);
/* ---------------------- ------- ---------------------- */

/* ---------------------- Getter Functions ---------------------- */
double consts_getnumber(unsigned index);
char *consts_getstring(unsigned index);
char *libfuncs_getused(unsigned index);
/* ---------------------- ------- ---------------------- */

/* ---------------------- toString Functions ---------------------- */
char *number_tostring(avm_memcell *);
char *string_tostring(avm_memcell *);
char *bool_tostring(avm_memcell *);
char *table_tostring(avm_memcell *);
char *userfunc_tostring(avm_memcell *);
char *libfunc_tostring(avm_memcell *m);
char *nil_tostring(avm_memcell *);
char *undef_tostring(avm_memcell *);

tostring_func_t tostringFuncs[] = {
    number_tostring,
    string_tostring,
    bool_tostring,
    table_tostring,
    userfunc_tostring,
    libfunc_tostring,
    nil_tostring,
    undef_tostring};
/* ---------------------- ------- ---------------------- */

/* ---------------------- Arithm Functions ---------------------- */
double add_impl(double x, double y);
double sub_impl(double x, double y);
double mul_impl(double x, double y);
double div_impl(double x, double y);
double mod_impl(double x, double y);

typedef double (*arithmetic_func_t)(double x, double y);
arithmetic_func_t arithmeticFuncs[] = {
    add_impl,
    sub_impl,
    mul_impl,
    div_impl,
    mod_impl};

/* ---------------------- toBool Functions ---------------------- */
unsigned char number_tobool(avm_memcell *m);
unsigned char string_tobool(avm_memcell *m);
unsigned char bool_tobool(avm_memcell *m);
unsigned char table_tobool(avm_memcell *m);
unsigned char userfunc_tobool(avm_memcell *m);
unsigned char libfunc_tobool(avm_memcell *m);
unsigned char nil_tobool(avm_memcell *m);
unsigned char undef_tobool(avm_memcell *m);

typedef unsigned char (*tobool_func_t)(avm_memcell *);

tobool_func_t toboolFuncs[] = {
    number_tobool,
    string_tobool,
    bool_tobool,
    table_tobool,
    userfunc_tobool,
    libfunc_tobool,
    nil_tobool,
    undef_tobool};
/* ---------------------- ------- ---------------------- */

/* ---------------------- Lib Funcs ---------------------- */
void libfunc_print();
void libfunc_input();
void libfunc_objectmemberkeys();
void libfunc_objecttotalmembers();
void libfunc_objectcopy();
void libfunc_argument();
void libfunc_strtonum();
void libfunc_sqrt();
void libfunc_cos();
void libfunc_sin();
void libfunc_typeof();

typedef struct libFuncPair
{
    char *id;
    library_func_t addr;
    struct libFuncPair *next;
} libFuncPair;

libFuncPair *libFuncPairs = NULL;
/* ---------------------- ------- ---------------------- */

/* ---------------------- MemClear Functions ---------------------- */
void memclear_string(avm_memcell *m);
void memclear_table(avm_memcell *m);

typedef void (*memclear_func_t)(avm_memcell *);

memclear_func_t memclearFuncs[] = {
    0, //number
    memclear_string,
    0, //bool
    memclear_table,
    0, //userfunc
    0, //libfunc
    0, //nil
    0  //undef
};
/* ---------------------- ------- ---------------------- */
void execute_cycle(void);

/* ---------------------- Utils ---------------------- */
void decoder(char *filename); //decodes the binary file created by compiler
void print_log(int printInstr);
unsigned int hashNum(unsigned int x);
unsigned int customHashNum(double x);
unsigned int hashString(const char *pcKey);
unsigned char isNumber(char *str);
unsigned char isTrue(char *str);
unsigned char isFalse(char *str);
unsigned char isNil(char *nil);
unsigned char isDigit(char c);
unsigned char isMinus(char c);
unsigned char isDot(char c);
unsigned char isInt(double d);
long hashPtr(void *ptr);
double DegreeToRadians(double degree);

/* ---------------------- Equality Functions ---------------------- */
unsigned char numEqual(avm_memcell *m1, avm_memcell *m2);
unsigned char stringEqual(avm_memcell *m1, avm_memcell *m2);
unsigned char tableEqual(avm_memcell *m1, avm_memcell *m2);
unsigned char userFuncEqual(avm_memcell *m1, avm_memcell *m2);

typedef unsigned char (*equalityFuncDisp)(avm_memcell *m1, avm_memcell *m2);
equalityFuncDisp equalArr[] = {
    numEqual,
    stringEqual,
    NULL,
    tableEqual,
    userFuncEqual,
    stringEqual,
    NULL,
    NULL};

/* ---------------------- Code ---------------------- */
avm_memcell *avm_translate_operand(vmarg *arg, avm_memcell *reg)
{
    if (arg->type == unused_a)
    {
        reg->type = nil_m;
        return reg;
    }

    switch (arg->type)
    {
    case global_a:
        return &stack[AVM_STACKSIZE - 1 - arg->val];
    case local_a:
        return &stack[topsp - arg->val];
    case formal_a:
        return &stack[topsp + AVM_STACKENV_SIZE + 1 + arg->val];
    case retval_a:
        return &retval;
    case number_a:
    {
        reg->type = number_m;
        reg->data.numVal = consts_getnumber(arg->val);
        return reg;
    }
    case string_a:
    {
        reg->type = string_m;
        reg->data.strVal = strdup(consts_getstring(arg->val));
        return reg;
    }
    case bool_a:
    {
        reg->type = bool_m;
        reg->data.boolVal = arg->val;
        return reg;
    }
    case nil_a:
    {
        reg->type = nil_m;
        return reg;
    }
    case userfunc_a:
    {
        reg->type = userfunc_m;
        reg->data.funcVal = arg->val;
        return reg;
    }
    case libfunc_a:
    {
        reg->type = libfunc_m;
        reg->data.libfuncVal = libfuncs_getused(arg->val);
        return reg;
    }
    default:
        assert(0);
    }
}

void execute_cycle(void)
{
    if (executionFinished)
    {
        return;
    }
    else if (pc == AVM_ENDING_PC)
    {
        executionFinished = 1;
        return;
    }
    else
    {
        assert(pc < AVM_ENDING_PC);
        instruction *instr = code + pc;
        assert(instr->opcode >= 0 && instr->opcode <= AVM_MAX_INSTRUCTIONS);

        if (instr->srcLine)
            currLine = instr->srcLine;

        unsigned oldPC = pc;
        //printf("going to %d, %d = \n", instr->opcode, pc);
        (*executeFuncs[instr->opcode])(instr);
        //printf("PC in cycle: %d\n", pc);
        if (pc == oldPC)
            pc++;
    }
}

void execute_assign(instruction *instr)
{
    avm_memcell *lv = avm_translate_operand(&instr->result, (avm_memcell *)0);
    avm_memcell *rv = avm_translate_operand(&instr->arg1, &ax);

    assert(lv && (&stack[N - 1] >= lv && lv > &stack[top] || lv == &retval));
    assert(rv);

    avm_assign(lv, rv);
}

void avm_assign(avm_memcell *lv, avm_memcell *rv)
{
    if (lv == rv)
        return;

    if (lv->type == table_m && rv->type == table_m && lv->data.tableVal == rv->data.tableVal)
        return;

    if (rv->type == undef_m)
        avm_warning("[AVM] -- Warning: Assigning fron undefined rvalue.\n");

    avm_memcellclear(lv);
    memcpy(lv, rv, sizeof(avm_memcell));

    if (lv->type == string_m)
        lv->data.strVal = strdup(rv->data.strVal);
    else if (lv->type == table_m)
    {
        //printf("AVMTOBOOL: Increasing ref counter of table %s\n", avm_tostring(lv));
        avm_tableincrefcounter(lv->data.tableVal);
    }
}

void avm_functorCall(avm_memcell *table)
{
    assert(table->type == table_m);
    char *fs = "()";
    unsigned int ix = 0, functorFound = 0;
    avm_table_bucket *curr, *prev = NULL;
    avm_memcell *function;

    ix = hashString(fs);
    curr = (table->data.tableVal)->strIndexed[ix];
    while (curr)
    {
        prev = curr;
        if (!strcmp((curr->key).data.strVal, fs))
        {
            function = &(curr->value);
            functorFound = 1;
            break;
        }
        curr = curr->next;
    }

    if (!functorFound)
    {
        avm_error("[AVM] -- Error: Functor call made on table without \"()\" key.\n");
    }

    ++totalActuals;
    avm_assign(&stack[top], table);
    avm_dec_top();

    avm_callsaveenvironment();

    assert(function); // && function->type == userfunc_m); //should throw error
    if (function->type != userfunc_m)
    {
        avm_error("[AVM] -- Error: Functor calls must contain user function as values.\n");
    }

    pc = userFuncs[function->data.funcVal].address;

    assert(pc < AVM_ENDING_PC);

    assert(code[pc].opcode == funcenter_v);
    assert(pc == userFuncs[function->data.funcVal].address);
}

void execute_call(instruction *instr)
{
    avm_memcell *table;
    avm_memcell *func = avm_translate_operand(&(instr->arg1), &ax);
    assert(func);

    //avm_callsaveenvironment();
    switch (func->type)
    {
    case userfunc_m:
    {
        avm_callsaveenvironment();
        pc = userFuncs[func->data.funcVal].address;
        assert(pc < AVM_ENDING_PC);
        assert(code[pc].opcode == funcenter_v);
        break;
    }
    case string_m:
        avm_callsaveenvironment();
        avm_calllibfunc((func->data).strVal);
        break;
    case libfunc_m:
        avm_callsaveenvironment();
        avm_calllibfunc((func->data).libfuncVal);
        break;
    case table_m:
        avm_functorCall(func);
        break;
    default:
    {
        avm_callsaveenvironment();
        char *s = avm_tostring(func);
        avm_error("[AVM] -- Error: Cannot use \"%s\" as a function.\n", s);
        free(s);
        executionFinished = 1;
    }
    }
}

void avm_dec_top()
{
    if (!top)
    {
        avm_error("[AVM] -- Error: Stack Overflow\n");
        executionFinished = 1;
    }
    else
        --top;
}

void avm_push_envvalue(unsigned val)
{
    stack[top].type = number_m;
    stack[top].data.numVal = val;
    avm_dec_top();
}

void avm_callsaveenvironment()
{
    avm_push_envvalue(totalActuals);
    avm_push_envvalue(pc + 1);
    avm_push_envvalue(top + totalActuals + 2);
    avm_push_envvalue(topsp);
}

void execute_funcenter(instruction *instr)
{
    //printf("funcenter entering\n");

    avm_memcell *func = avm_translate_operand(&instr->result, &ax);
    assert(func);
    assert(pc == userFuncs[func->data.funcVal].address);

    totalActuals = 0;
    userfunc *funcInfo = avm_getfuncinfo(func->data.funcVal);

    topsp = top;
    top = top - funcInfo->localSize;
}

unsigned avm_get_envvalue(unsigned i)
{
    assert(stack[i].type == number_m);
    unsigned val = (unsigned)stack[i].data.numVal;
    assert(stack[i].data.numVal == ((double)val));
    return val;
}

void execute_funcexit(instruction *unused)
{
    unsigned oldTop = top;
    top = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
    pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
    topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);

    while (++oldTop <= top)
    {
        avm_memcellclear(&stack[oldTop]);
    }
}

void avm_calllibfunc(char *id)
{
    library_func_t f = avm_getlibraryfunc(id);
    if (!f)
    {
        avm_error("[AVM] -- Error: Function \"%s\" not supported.\n", id);
        executionFinished = 1;
    }
    else
    {
        topsp = top;
        totalActuals = 0;
        (*f)();
        if (!executionFinished)
            execute_funcexit((instruction *)0);
    }
}

unsigned avm_totalactuals()
{
    return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

avm_memcell *avm_getactual(unsigned i)
{
    assert(i < avm_totalactuals());
    return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}

void execute_pusharg(instruction *instr)
{
    avm_memcell *arg = avm_translate_operand(&instr->arg1, &ax);
    assert(arg);

    avm_assign(&stack[top], arg);
    ++totalActuals;
    avm_dec_top();
}

char *avm_tostring(avm_memcell *m)
{
    assert(m->type >= 0 && m->type <= undef_m);
    return (*tostringFuncs[m->type])(m);
}

double add_impl(double x, double y)
{
    return x + y;
}

double sub_impl(double x, double y)
{
    return x - y;
}

double mul_impl(double x, double y)
{
    return x * y;
}

double div_impl(double x, double y)
{
    return x / y;
}

double mod_impl(double x, double y)
{
    return ((unsigned)x) % ((unsigned)y);
}

void execute_arithmetic(instruction *instr)
{
    avm_memcell *lv = avm_translate_operand(&instr->result, (avm_memcell *)0);
    avm_memcell *rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell *rv2 = avm_translate_operand(&instr->arg2, &bx);

    assert(lv && (&stack[N - 1] >= lv && lv > &stack[top] || lv == &retval));
    assert(rv1 && rv2);

    if (rv1->type != number_m || rv2->type != number_m)
    {
        avm_error("[AVM] -- Error: Non-number operands used in arithmetic expression.\n");
        executionFinished = 1;
    }
    else
    {
        arithmetic_func_t op = arithmeticFuncs[instr->opcode - add_v];
        avm_memcellclear(lv);

        lv->type = number_m;
        lv->data.numVal = (*op)(rv1->data.numVal, rv2->data.numVal);
    }
}

unsigned char number_tobool(avm_memcell *m)
{
    assert(m);
    return m->data.numVal != 0;
}

unsigned char string_tobool(avm_memcell *m)
{
    assert(m);
    return m->data.strVal[0] != 0;
}

unsigned char bool_tobool(avm_memcell *m)
{
    assert(m);
    return m->data.boolVal;
}

unsigned char table_tobool(avm_memcell *m)
{
    //assert(m);
    return 1;
}

unsigned char userfunc_tobool(avm_memcell *m)
{
    //assert(m);
    return 1;
}

unsigned char libfunc_tobool(avm_memcell *m)
{
    //assert(m);
    return 1;
}

unsigned char nil_tobool(avm_memcell *m)
{
    //assert(m);
    return 0;
}

unsigned char undef_tobool(avm_memcell *m)
{
    assert(0);
    return 0;
}

unsigned char stringEqual(avm_memcell *m1, avm_memcell *m2)
{
    unsigned char result;

    assert(m1 && m2);
    assert(m1->type == string_m || m1->type == libfunc_m);
    assert(m2->type == string_m || m2->type == libfunc_m);
    assert(m1->type == m2->type);

    if (m1->type == string_m)
    {
        result = !(strcmp(m1->data.strVal, m2->data.strVal));
    }
    else
    {
        result = !(strcmp(m1->data.libfuncVal, m2->data.libfuncVal));
    }

    return result;
}

unsigned char numEqual(avm_memcell *m1, avm_memcell *m2)
{
    assert(m1 && m2 && m1->type == number_m && m2->type == number_m);
    return (unsigned char)(fabs(m1->data.numVal - m2->data.numVal) < 0.00001);
}

unsigned char userFuncEqual(avm_memcell *m1, avm_memcell *m2)
{
    assert(m1 && m2 && m1->type == userfunc_m && m2->type == userfunc_m);
    unsigned char res1, res2;
    res1 = (unsigned char)(userFuncs[m1->data.funcVal].address == userFuncs[m2->data.funcVal].address);
    res2 = (unsigned char)(!strcmp(userFuncs[m1->data.funcVal].id, userFuncs[m2->data.funcVal].id));
    return (unsigned char)(res1 && res2);
}

unsigned char tableEqual(avm_memcell *m1, avm_memcell *m2)
{
    assert(m1 && m2 && m1->type == table_m && m2->type == table_m);
    return (unsigned char)(m1->data.tableVal == m2->data.tableVal);
}

unsigned char avm_tobool(avm_memcell *m)
{
    assert(m->type >= 0 && m->type < undef_m);
    return (*toboolFuncs[m->type])(m);
}

void execute_jeq(instruction *instr)
{
    assert(instr->result.type == label_a);

    avm_memcell *rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell *rv2 = avm_translate_operand(&instr->arg2, &bx);

    unsigned char result = 0;

    if (rv1->type == undef_m || rv2->type == undef_m)
        avm_error("[AVM] -- Error: undef used in comparison.\n");
    else if (rv1->type == nil_m || rv2->type == nil_m)
        result = rv1->type == nil_m && rv2->type == nil_m;
    else if (rv1->type == bool_m || rv2->type == bool_m)
        result = (avm_tobool(rv1) == avm_tobool(rv2));
    else if (rv1->type != rv2->type)
        avm_error("[AVM] -- Error: %s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
    else
    {
        unsigned int index = rv1->type;
        result = (*equalArr[index])(rv1, rv2);
    }

    if (!executionFinished && result)
        pc = instr->result.val;
}

void execute_newtable(instruction *instr)
{
    avm_memcell *lv = avm_translate_operand(&instr->result, (avm_memcell *)0);

    assert(lv && (&stack[N - 1] >= lv && lv > &stack[top] || lv == &retval));

    avm_memcellclear(lv);
    lv->type = table_m;
    lv->data.tableVal = avm_tablenew();

    avm_tableincrefcounter(lv->data.tableVal);
}

void execute_tablegetelem(instruction *instr)
{
    avm_memcell *lv = avm_translate_operand(&instr->result, (avm_memcell *)0);
    avm_memcell *t = avm_translate_operand(&instr->arg1, (avm_memcell *)0);
    avm_memcell *i = avm_translate_operand(&instr->arg2, &ax);

    assert(lv && &stack[N - 1] >= lv && lv > &stack[top] || lv == &retval);
    assert(t && &stack[N - 1] >= t && t > &stack[top]);
    assert(i);

    avm_memcellclear(lv);
    lv->type = nil_m;

    if (t->type != table_m)
    {
        avm_warning("[AVM] -- Warning: Illegal use of type %s as table!", typeStrings[t->type]);
    }
    else
    {
        if (i->type == nil_m)
        {
            avm_warning("[AVM] -- Warning: Addressing tables with nil indexes is not allowed!");
            return;
        }

        avm_memcell *content = avm_tablegetelem(t->data.tableVal, i);
        if (content)
            avm_assign(lv, content);
        else
        /*Returning null means that the content was not found*/
        {
            /*char *ts = avm_tostring(t);
            char *is = avm_tostring(i);
            avm_warning("%s[%s] not found! (Ignore if this after deleting..)\n", ts, is);
            free(ts);
            free(is);*/

            avm_memcell nilCont;
            nilCont.type = nil_m;
            avm_assign(lv, &nilCont);
        }
    }
}

void execute_tablesetelem(instruction *instr)
{
    avm_memcell *t = avm_translate_operand(&instr->result, (avm_memcell *)0);
    avm_memcell *i = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell *c = avm_translate_operand(&instr->arg2, &bx);

    assert(t && &stack[N - 1] >= t && t > &stack[top]);
    assert(i && c);

    if (t->type != table_m)
        avm_error("[AVM] -- Error: Illegal use of type %s as table.\n", typeStrings[t->type]);
    else if (i->type == nil_m)
        avm_warning("[AVM] -- Warning: Nil indexes are not allowed on table addressing.\n");
    else if (i->type == undef_m)
        avm_warning("[AVM] -- Warning: Undefined indexes are not allowed on table addressing.\n");
    else
    {
        if (c->type == nil_m)
        {
            avm_tabledelelem(t->data.tableVal, i);
        }
        else
        {
            //printf("Indexing %s[%s] = [%s]\n", avm_tostring(t),avm_tostring(i),avm_tostring(c));
            avm_tablesetelem(t->data.tableVal, i, c);
        }
    }
}

double consts_getnumber(unsigned index)
{
    return numConsts[index];
}

char *consts_getstring(unsigned index)
{
    return stringConsts[index]; //TABLESET t "string" 1
}

char *libfuncs_getused(unsigned index)
{
    return namedLibfuncs[index];
}

userfunc *avm_getfuncinfo(unsigned address)
{
    return &userFuncs[address];
}

void execute_uminus(instruction *instr)
{
    assert(0);
    return;
}

void execute_and(instruction *instr)
{
    assert(0);
    return;
}

void execute_or(instruction *instr)
{
    assert(0);
    return;
}

void execute_not(instruction *instr)
{
    assert(0);
    return;
}

void execute_jump(instruction *instr)
{
    unsigned int jumpTo;
    assert(instr->result.type == label_a);

    jumpTo = instr->result.val;

    if (!executionFinished)
        pc = jumpTo;
}

void execute_jne(instruction *instr)
{
    assert(instr->result.type == label_a);

    avm_memcell *rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell *rv2 = avm_translate_operand(&instr->arg2, &bx);

    unsigned char result = 0;

    if (rv1->type == undef_m || rv2->type == undef_m)
        avm_error("[AVM] -- Error: undef used in comparison.\n");
    else if (rv1->type == nil_m || rv2->type == nil_m)
        result = rv1->type == nil_m && rv2->type == nil_m;
    else if (rv1->type == bool_m || rv2->type == bool_m)
        result = (avm_tobool(rv1) == avm_tobool(rv2));
    else if (rv1->type != rv2->type)
        avm_error("[AVM] -- Error: %s == %s is illegal.\n", typeStrings[rv1->type], typeStrings[rv2->type]);
    else
    {
        unsigned int index = rv1->type;
        result = (*equalArr[index])(rv1, rv2);
    }

    if (!executionFinished && !result)
        pc = instr->result.val;
}

void execute_jle(instruction *instr)
{
    assert(instr->result.type == label_a);

    avm_memcell *rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell *rv2 = avm_translate_operand(&instr->arg2, &bx);

    unsigned char result = 0;

    if (rv1->type != number_m || rv2->type != number_m)
    {
        avm_warning("[AVM] -- Error: Relational operation using non arithmetic operands.\n");
        return;
    }

    double x1 = rv1->data.numVal;
    double x2 = rv2->data.numVal;

    result = (x1 <= x2);

    if (!executionFinished && result)
        pc = instr->result.val;
}

void execute_jge(instruction *instr)
{
    assert(instr->result.type == label_a);

    avm_memcell *rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell *rv2 = avm_translate_operand(&instr->arg2, &bx);

    unsigned char result = 0;

    if (rv1->type != number_m || rv2->type != number_m)
    {
        avm_warning("[AVM] -- Warning: Relational operation using non arithmetic operands!\n");
        return;
    }

    double x1 = rv1->data.numVal;
    double x2 = rv2->data.numVal;

    result = (x1 >= x2);

    if (!executionFinished && result)
        pc = instr->result.val;
}

void execute_jlt(instruction *instr)
{
    assert(instr->result.type == label_a);

    avm_memcell *rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell *rv2 = avm_translate_operand(&instr->arg2, &bx);

    unsigned char result = 0;

    if (rv1->type != number_m || rv2->type != number_m)
    {
        avm_warning("[AVM] -- Warning: Relational operation using non arithmetic operands!\n");
        return;
    }

    double x1 = rv1->data.numVal;
    double x2 = rv2->data.numVal;

    result = (x1 < x2);

    if (!executionFinished && result)
        pc = instr->result.val;
}

void execute_jgt(instruction *instr)
{
    assert(instr->result.type == label_a);

    avm_memcell *rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell *rv2 = avm_translate_operand(&instr->arg2, &bx);

    unsigned char result = 0;

    if (rv1->type != number_m || rv2->type != number_m)
    {
        avm_error("[AVM] -- Warning: Relational operation using non arithmetic operands!\n");
        return; //if we change the exit on avm_error!
    }

    double x1 = rv1->data.numVal;
    double x2 = rv2->data.numVal;

    result = (x1 > x2);

    if (!executionFinished && result)
        pc = instr->result.val;
}

void execute_nop(instruction *instr)
{
}

char *number_tostring(avm_memcell *m)
{
    assert(m->type == number_m);

    double num = m->data.numVal;
    int intNum;
    char strNum[60] = {0};

    if (isInt(num))
    {
        intNum = (int)num;
        snprintf(strNum, 60, "%d", intNum);
    }
    else
    {
        snprintf(strNum, 60, "%.3f", num); //.2
    }

    return strdup(strNum);
}

char *string_tostring(avm_memcell *m)
{
    assert(m->type == string_m);
    return strdup(m->data.strVal);
}

char *bool_tostring(avm_memcell *m)
{
    assert(m && m->type == bool_m);
    if (m->data.boolVal == 1)
    {
        return strdup("true");
    }

    return strdup("false");
}

char *libfunc_tostring(avm_memcell *m)
{
    assert(m && m->type == libfunc_m);
    char funcToStr[60] = {0};
    strcpy(funcToStr, "Lib Function: ");
    strcat(funcToStr, m->data.libfuncVal);
    return strdup(funcToStr);
}

void pair_tostring(avm_table_bucket *curr, avm_table *t, char **str, int *size_change, int *counter) //(char *str, char *key, char *val)
{
    char *key, *val;
    char addr[21] = {0};
    while (curr)
    {
        if (curr->key.data.tableVal == t) //avoiding self loop
        {
            snprintf(addr, 20, "%p", t); // snprintf(strNum, 60, "%d", intNum);
            key = strdup(addr);
        }
        else
        {
            key = avm_tostring(&curr->key);
        }

        if (curr->value.data.tableVal == t) //avoiding self loop
        {
            snprintf(addr, 20, "%p", t); // snprintf(strNum, 60, "%d", intNum);
            val = strdup(addr);
        }
        else
        {
            val = avm_tostring(&curr->value);
        }

        *counter += strlen(key) + strlen(val) + 5;

        while (*counter >= DEFAULT_STR_SIZE * (*size_change))
        {
            (*size_change)++;
            *str = (char *)realloc((void *)(*str), (*size_change) * DEFAULT_STR_SIZE * sizeof(char));
        }

        strcat(*str, " {");
        strcat(*str, key);
        strcat(*str, ":");
        strcat(*str, val);
        strcat(*str, "} ");

        free(key);
        free(val);

        curr = curr->next;
    }
}

char *table_tostring(avm_memcell *m)
{
    assert(m->type == table_m);

    int size_change = 1, counter = 0;
    char c;

    char *str = (char *)malloc(sizeof(char) * DEFAULT_STR_SIZE);
    memset((void *)str, 0, DEFAULT_STR_SIZE);

    str[counter++] = '[';

    avm_table *t = m->data.tableVal;
    int i;

    avm_table_bucket *curr;

    for (i = 0; i < AVM_TABLE_HASHSIZE; i++)
    {
        curr = t->numIndexed[i];
        pair_tostring(curr, t, &str, &size_change, &counter);
    }

    for (i = 0; i < AVM_TABLE_HASHSIZE; i++)
    {
        curr = t->strIndexed[i];
        pair_tostring(curr, t, &str, &size_change, &counter);
    }

    for (i = 0; i < 2; i++)
    {
        curr = t->boolIndexed[i];
        pair_tostring(curr, t, &str, &size_change, &counter);
    }

    for (i = 0; i < AVM_TABLE_HASHSIZE; i++)
    {
        curr = t->libFuncIndexed[i];
        pair_tostring(curr, t, &str, &size_change, &counter);
    }

    for (i = 0; i < AVM_TABLE_HASHSIZE; i++)
    {
        curr = t->userfuncIndexed[i];
        pair_tostring(curr, t, &str, &size_change, &counter);
    }

    for (i = 0; i < AVM_TABLE_HASHSIZE; i++)
    {
        curr = t->tableIndexed[i];
        pair_tostring(curr, t, &str, &size_change, &counter);
    }

    counter += 2;

    if (counter >= DEFAULT_STR_SIZE * (size_change))
    {
        str = (char *)realloc((void *)(str), ((size_change * DEFAULT_STR_SIZE) + 2) * sizeof(char));
    }

    str[counter - 2] = ']';
    str[counter - 1] = '\0';

    return str;
}

char *userfunc_tostring(avm_memcell *m)
{
    assert(m->type == userfunc_m);

    unsigned index = m->data.funcVal;
    char funcToStr[60] = {0};

    strcpy(funcToStr, "User Function: ");

    char addressToStr[60] = {0};
    snprintf(addressToStr, 59, "%d", index);

    //addressToStr[59] = '\0';

    strcat(funcToStr, addressToStr);
    return strdup(funcToStr);
}

char *nil_tostring(avm_memcell *m)
{
    assert(m->type == nil_m);
    return strdup("nil");
}

char *undef_tostring(avm_memcell *m)
{
    assert(m->type == undef_m);
    return strdup("undefined");
}

void avm_registerlibfunc(char *id, library_func_t addr)
{
    libFuncPair *pair = NULL;

    pair = (libFuncPair *)malloc(sizeof(libFuncPair));
    if (!pair)
    {
        perror("Malloc for library function pairs failed!\n");
        exit(EXIT_FAILURE);
    }
    pair->id = strdup(id);
    pair->addr = addr;
    pair->next = libFuncPairs;

    libFuncPairs = pair;

    return;
}

library_func_t avm_getlibraryfunc(char *id)
{
    libFuncPair *curr = libFuncPairs;

    while (curr)
    {
        if (!strcmp(curr->id, id))
        {
            return curr->addr;
        }
        curr = curr->next;
    }

    return NULL;
}

avm_memcell *avm_tablegetelem(avm_table *table, avm_memcell *index)
{
    unsigned int ix = 0;
    avm_table_bucket *curr, *prev = NULL, *pair;

    /*if (index->type == table_m)
    {
        avm_tableincrefcounter(index->data.tableVal);
    }*/

    assert(table && index);

    switch (index->type)
    {
    case string_m:
        ix = hashString(index->data.strVal);
        curr = table->strIndexed[ix];
        //printf("Looking for %s of table\n", index->data.strVal);
        while (curr)
        {
            prev = curr;
            if (!strcmp((curr->key).data.strVal, index->data.strVal))
            {
                /*if (curr->value.type == table_m)
                {
                    avm_tableincrefcounter(curr->value.data.tableVal);
                }*/
                return &(curr->value);
            }
            curr = curr->next;
        }
        break;
    case number_m:
        ix = customHashNum(index->data.numVal);
        curr = table->numIndexed[ix];
        while (curr)
        {
            prev = curr;
            if ((curr->key).data.numVal == index->data.numVal)
            {
                /*if (curr->value.type == table_m)
                {
                    avm_tableincrefcounter(curr->value.data.tableVal);
                }*/
                return &(curr->value);
            }
            curr = curr->next;
        }
        break;
    case bool_m:
        ix = index->data.boolVal;
        curr = table->boolIndexed[ix];
        if (curr != NULL)
        {
            //avm_tableincrefcounter(curr->value.data.tableVal);
            return &(curr->value);
        }
        break;
    case userfunc_m:
        ix = hashString(userFuncs[index->data.funcVal].id);
        curr = table->userfuncIndexed[ix];
        while (curr)
        {
            prev = curr;
            if (!strcmp(userFuncs[index->data.funcVal].id, userFuncs[curr->key.data.funcVal].id) && userFuncs[index->data.funcVal].address == userFuncs[curr->key.data.funcVal].address) //address needless?
            {
                /*if (curr->value.type == table_m)
                {
                    avm_tableincrefcounter(curr->value.data.tableVal);
                }*/
                return &(curr->value);
            }
            curr = curr->next;
        }
        break;
    case libfunc_m:
        ix = hashString(index->data.libfuncVal);
        curr = table->libFuncIndexed[ix];
        while (curr)
        {
            prev = curr;
            if (!strcmp(index->data.libfuncVal, (curr->key).data.libfuncVal))
            {
                /*if (curr->value.type == table_m)
                {
                    avm_tableincrefcounter(curr->value.data.tableVal);
                }*/
                return &(curr->value);
            }
            curr = curr->next;
        }
        break;
    case table_m:
        ix = hashPtr(index->data.tableVal);
        //printf("HERE!");
        curr = table->tableIndexed[ix];
        while (curr)
        {
            prev = curr;
            //printf("Comparing %p with %p\n", index->data.tableVal, curr->key.data.tableVal);

            if (index->data.tableVal, (curr->key).data.tableVal)
            {
                /*if (curr->value.type == table_m)
                {
                    avm_tableincrefcounter(curr->value.data.tableVal);
                }*/
                return &(curr->value);
            }
            curr = curr->next;
        }
        break;
    }

    return NULL;
}

void avm_tabledelelem(avm_table *table, avm_memcell *index)
{
    unsigned int ix = 0, foundItemToDelete = 0;
    avm_table_bucket *curr, *prev = NULL;

    assert(table && index);

    switch (index->type)
    {
    case string_m:
        ix = hashString(index->data.strVal);
        curr = table->strIndexed[ix];
        while (curr)
        {
            if (!strcmp((curr->key).data.strVal, index->data.strVal))
            {
                if (prev == NULL)
                {
                    table->strIndexed[ix] = curr->next;
                }
                else
                {
                    prev->next = curr->next;
                }

                free(curr);
                table->total--;
                return;
            }

            prev = curr;
            curr = curr->next;
        }
        break;
    case number_m:
        ix = customHashNum(index->data.numVal);
        curr = table->numIndexed[ix];
        while (curr)
        {
            if ((curr->key).data.numVal == index->data.numVal)
            {
                if (prev == NULL)
                {
                    table->numIndexed[ix] = curr->next;
                }
                else
                {
                    prev->next = curr->next;
                }

                free(curr);
                table->total--;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        break;
    case bool_m:
        ix = index->data.boolVal;
        curr = table->boolIndexed[ix];
        if (curr != NULL)
        {
            table->boolIndexed[ix] = NULL;
            free(curr);
            table->total--;
            return;
        }
        break;
    case userfunc_m:
        ix = hashString(userFuncs[index->data.funcVal].id);
        curr = table->userfuncIndexed[ix];
        while (curr)
        {
            if (index->data.funcVal == curr->key.data.funcVal)
            {
                if (prev == NULL)
                {
                    table->userfuncIndexed[ix] = curr->next;
                }
                else
                {
                    prev->next = curr->next;
                }

                free(curr);
                table->total--;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        break;
    case libfunc_m:
        ix = hashString(index->data.libfuncVal);
        curr = table->libFuncIndexed[ix];
        while (curr)
        {

            if (!strcmp(index->data.libfuncVal, (curr->key).data.libfuncVal))
            {
                if (prev == NULL)
                {
                    table->libFuncIndexed[ix] = curr->next;
                }
                else
                {
                    prev->next = curr->next;
                }

                free(curr);
                table->total--;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        break;
    case table_m:
        ix = hashPtr(index->data.tableVal);
        curr = table->tableIndexed[ix];
        while (curr)
        {
            if (index->data.tableVal, (curr->key).data.tableVal)
            {
                if (prev == NULL)
                {
                    table->tableIndexed[ix] = curr->next;
                }
                else
                {
                    prev->next = curr->next;
                }

                free(curr);
                table->total--;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        break;
    default:
        assert(0);
    }

    avm_warning("Could not find the table item to delete!\n");
}

void avm_deepCopy(avm_memcell *dst, avm_memcell *src)
{
    dst->type = src->type;
    if (dst->type == string_m)
    {
        dst->data.strVal = strdup(src->data.strVal);
    }
    else
    {
        dst->data = src->data;
    }
}

void avm_tablesetelem(avm_table *table, avm_memcell *index, avm_memcell *content)
{
    unsigned int ix = 0, simple;
    avm_table_bucket *curr, *prev = NULL, *pair;

    assert(table && index && content);

    if (content->type == table_m)
    {
        //printf("Indexing inside set elem with table %s\n",avm_tostring(content));
        avm_tableincrefcounter(content->data.tableVal);
    }

    if (index->type == table_m)
    {
        avm_tableincrefcounter(index->data.tableVal);
        //(index->data.tableVal->refCounter)++;
    }

    switch (index->type)
    {
    case string_m:
        ix = hashString(index->data.strVal);
        curr = table->strIndexed[ix];
        while (curr)
        {
            prev = curr;
            if (!strcmp((curr->key).data.strVal, index->data.strVal))
            {
                curr->value = *content; //type, ptr->string
                if (content->type == string_m)
                {
                    curr->value.data.strVal = strdup(content->data.strVal);
                }

                return;
            }
            curr = curr->next;
        }

        pair = (avm_table_bucket *)malloc(sizeof(avm_table_bucket));
        pair->next = NULL;
        pair->key = *index;
        pair->value = *content;

        if (content->type == string_m)
        {
            pair->value.data.strVal = strdup(content->data.strVal);
        }

        if (index->type == string_m)
        {
            pair->key.data.strVal = strdup(index->data.strVal);
        }

        if (prev == NULL)
        {
            table->strIndexed[ix] = pair;
        }
        else
        {
            prev->next = pair;
        }

        table->isSimple = 0;
        break;
    case number_m:
        ix = customHashNum(index->data.numVal);
        curr = table->numIndexed[ix];
        while (curr)
        {
            prev = curr;
            if ((curr->key).data.numVal == index->data.numVal)
            {
                curr->value = *content;
                if (content->type == string_m)
                {
                    curr->value.data.strVal = strdup(content->data.strVal);
                }
                return;
            }
            curr = curr->next;
        }

        pair = (avm_table_bucket *)malloc(sizeof(avm_table_bucket));
        pair->next = NULL;
        pair->key = *index;
        pair->value = *content;

        if (content->type == string_m)
        {
            pair->value.data.strVal = strdup(content->data.strVal);
        }

        if (prev == NULL)
        {
            table->numIndexed[ix] = pair;
        }
        else
        {
            prev->next = pair;
        }

        if (pair->key.data.numVal < 0 || !isInt(pair->key.data.numVal))
        {
            table->isSimple = 0;
        }
        break;
    case bool_m:
        ix = index->data.boolVal;
        curr = table->boolIndexed[ix];
        if (curr == NULL)
        {
            pair = (avm_table_bucket *)malloc(sizeof(avm_table_bucket));
            pair->next = NULL;
            pair->key = *index;
            pair->value = *content;
            if (content->type == string_m)
            {
                pair->value.data.strVal = strdup(content->data.strVal);
            }
            table->boolIndexed[ix] = pair;
        }
        else
        {
            curr->value = *content;
            if (content->type == string_m)
            {
                curr->value.data.strVal = strdup(content->data.strVal);
            }
            return;
        }
        table->isSimple = 0;
        break;
    case userfunc_m:
        ix = hashString(userFuncs[index->data.funcVal].id);
        curr = table->userfuncIndexed[ix];
        while (curr)
        {
            prev = curr;
            if (index->data.funcVal == curr->key.data.funcVal) //!strcmp(userFuncs[index->data.funcVal].id, userFuncs[curr->key.data.funcVal].id))
            {
                curr->value = *content;
                if (content->type == string_m)
                {
                    curr->value.data.strVal = strdup(content->data.strVal);
                }
                return;
            }
            curr = curr->next;
        }

        pair = (avm_table_bucket *)malloc(sizeof(avm_table_bucket));
        pair->next = NULL;
        pair->key = *index;
        pair->value = *content;

        if (content->type == string_m)
        {
            pair->value.data.strVal = strdup(content->data.strVal);
        }

        if (prev == NULL)
        {
            table->userfuncIndexed[ix] = pair;
        }
        else
        {
            prev->next = pair;
        }
        table->isSimple = 0;
        break;
    case libfunc_m:
        ix = hashString(index->data.libfuncVal);
        curr = table->libFuncIndexed[ix];
        while (curr)
        {
            prev = curr;
            if (!strcmp(index->data.libfuncVal, (curr->key).data.libfuncVal))
            {
                curr->value = *content;
                if (content->type == string_m)
                {
                    curr->value.data.strVal = strdup(content->data.strVal);
                }
                return;
            }
            curr = curr->next;
        }

        pair = (avm_table_bucket *)malloc(sizeof(avm_table_bucket));
        pair->next = NULL;
        pair->key = *index;
        pair->value = *content;

        if (content->type == string_m)
        {
            pair->value.data.strVal = strdup(content->data.strVal);
        }

        if (index->type == string_m)
        {
            pair->key.data.strVal = strdup(index->data.strVal);
        }

        if (prev == NULL)
        {
            table->libFuncIndexed[ix] = pair;
        }
        else
        {
            prev->next = pair;
        }
        table->isSimple = 0;
        break;
    case table_m:
        ix = (unsigned)hashPtr(index->data.tableVal);
        printf("Going to index %u\n", ix);

        curr = table->tableIndexed[ix];
        while (curr)
        {
            prev = curr;
            printf("Inserting table. Comparing %p with %p\n", index->data.tableVal, curr->key.data.tableVal);
            if (index->data.tableVal == curr->key.data.tableVal)
            {
                curr->value = *content;
                if (content->type == string_m)
                {
                    curr->value.data.strVal = strdup(content->data.strVal);
                }
                return;
            }
            curr = curr->next;
        }

        pair = (avm_table_bucket *)malloc(sizeof(avm_table_bucket));
        pair->next = NULL;
        pair->key = *index;
        pair->value = *content;

        if (content->type == string_m)
        {
            pair->value.data.strVal = strdup(content->data.strVal);
        }

        if (prev == NULL)
        {
            table->tableIndexed[ix] = pair;
        }
        else
        {
            prev->next = pair;
        }
        table->isSimple = 0;
        break;
    default:
        assert(0);
    }

    table->total++;
}

//ok
void libfunc_input()
{
    int counter = 0, size_change = 1;
    char *str, c;
    unsigned n = avm_totalactuals();

    if (n != 0)
        avm_error("[AVM] -- Error: Input does not support arguments!!\n");
    else
    {
        str = (char *)malloc(sizeof(char) * DEFAULT_STR_SIZE);
        memset((void *)str, 0, DEFAULT_STR_SIZE);

        while ((c = getchar()) != '\n')
        {
            *(str + counter) = c;

            counter++;
            if (counter >= size_change * DEFAULT_STR_SIZE)
            {
                size_change++;
                str = (char *)realloc((void *)str, size_change * DEFAULT_STR_SIZE * sizeof(char));
            }
        }
        *(str + counter) = '\0';

        avm_memcellclear(&retval);

        if (isNumber(str))
        {
            double num = atof(str);
            retval.type = number_m;
            retval.data.numVal = num;
        }
        else if (isNil(str))
        {
            retval.type = nil_m;
        }
        else if (isTrue(str))
        {
            retval.type = bool_m;
            retval.data.boolVal = 1;
        }
        else if (isFalse(str))
        {
            retval.type = bool_m;
            retval.data.boolVal = 0;
        }
        else
        {
            retval.type = string_m;
            retval.data.strVal = str;
        }
    }
}

avm_table *avm_copyTable(avm_table *src)
{
    avm_table *newT = avm_tablenew();
    avm_table_bucket *curr;
    int i;

    //copy str
    for (i = 0; i < AVM_TABLE_HASHSIZE; i++)
    {
        curr = src->strIndexed[i];
        while (curr)
        {
            avm_tablesetelem(newT, &curr->key, &curr->value);
            curr = curr->next;
        }
    }

    //copy nums
    for (i = 0; i < AVM_TABLE_HASHSIZE; i++)
    {
        curr = src->numIndexed[i];
        while (curr)
        {
            avm_tablesetelem(newT, &curr->key, &curr->value);
            curr = curr->next;
        }
    }

    //copy bools
    for (i = 0; i < 2; i++)
    {
        curr = src->boolIndexed[i];
        while (curr)
        {
            avm_tablesetelem(newT, &curr->key, &curr->value);
            curr = curr->next;
        }
    }

    //copy func
    for (i = 0; i < AVM_TABLE_HASHSIZE; i++)
    {
        curr = src->userfuncIndexed[i];
        while (curr)
        {
            avm_tablesetelem(newT, &curr->key, &curr->value);
            curr = curr->next;
        }
    }

    //copy libfunc
    for (i = 0; i < AVM_TABLE_HASHSIZE; i++)
    {
        curr = src->libFuncIndexed[i];
        while (curr)
        {
            avm_tablesetelem(newT, &curr->key, &curr->value);
            curr = curr->next;
        }
    }

    return newT;
}

avm_table *avm_getTableKeys(avm_table *src)
{
    avm_table *newT = avm_tablenew();
    avm_table_bucket *curr;
    avm_memcell ind;
    int i;
    int counter = 0;

    ind.type = number_m;

    //copy str
    for (i = 0; i < AVM_TABLE_HASHSIZE; i++)
    {
        curr = src->strIndexed[i];
        while (curr)
        {
            ind.data.numVal = counter;
            avm_tablesetelem(newT, &ind, &curr->key);
            curr = curr->next;
            counter++;
        }
    }

    //copy nums
    for (i = 0; i < AVM_TABLE_HASHSIZE; i++)
    {
        curr = src->numIndexed[i];
        while (curr)
        {
            ind.data.numVal = counter;
            avm_tablesetelem(newT, &ind, &curr->key);
            curr = curr->next;
            counter++;
        }
    }

    //copy bools
    for (i = 0; i < 2; i++)
    {
        curr = src->boolIndexed[i];
        while (curr)
        {
            ind.data.numVal = counter;
            avm_tablesetelem(newT, &ind, &curr->key);
            curr = curr->next;
            counter++;
        }
    }

    //copy func
    for (i = 0; i < AVM_TABLE_HASHSIZE; i++)
    {
        curr = src->userfuncIndexed[i];
        while (curr)
        {
            ind.data.numVal = counter;
            avm_tablesetelem(newT, &ind, &curr->key);
            curr = curr->next;
            counter++;
        }
    }

    //copy libfunc
    for (i = 0; i < AVM_TABLE_HASHSIZE; i++)
    {
        curr = src->libFuncIndexed[i];
        while (curr)
        {
            ind.data.numVal = counter;
            avm_tablesetelem(newT, &ind, &curr->key);
            curr = curr->next;
            counter++;
        }
    }

    return newT;
}

//ok
void libfunc_objectmemberkeys() //t = objectmemberkeys(tab);
{
    unsigned n = avm_totalactuals();
    if (n != 1)
        avm_error("[AVM] -- Error: Object member keys requires one and only arg.\n", n);
    else
    {
        avm_memcell *t = avm_getactual(0);
        avm_memcellclear(&retval);

        if (t->type != table_m) //check if it's a string
        {
            avm_warning("[AVM] -- Warning: The argument provided is not a table.\n");
            avm_memcellclear(&retval);
            retval.type = nil_m;
            return;
        }

        avm_table *newT = avm_getTableKeys(t->data.tableVal);

        avm_memcellclear(&retval);
        retval.type = table_m;
        retval.data.tableVal = newT;
    }
}

//ok
void libfunc_objecttotalmembers()
{
    unsigned n = avm_totalactuals();
    if (n != 1)
        avm_error("[AVM] -- Error: Object member keys requires one and only arg!\n", n);
    else
    {
        avm_memcell *t = avm_getactual(0);
        avm_memcellclear(&retval);

        if (t->type != table_m) //check if it's a string
        {
            avm_warning("[AVM] -- Warnign: The argument provided is not a table!\n");
            avm_memcellclear(&retval);
            retval.type = nil_m;
            return;
        }

        avm_memcellclear(&retval);
        retval.type = number_m;
        retval.data.numVal = t->data.tableVal->total;
    }
}

//ok
void libfunc_objectcopy()
{
    unsigned n = avm_totalactuals();
    if (n != 1)
        avm_error("[AVM] -- Error: Objectcopy requires one and only arg!\n", n);
    else
    {
        avm_memcellclear(&retval);

        avm_memcell *t = avm_getactual(0);
        if (t->type != table_m) //check if it's a string
        {
            avm_warning("[AVM] -- Warning: The argument provided is not a table!\n");
            //avm_memcellclear(&retval);
            retval.type = nil_m;
            return;
        }

        avm_table *newT = avm_copyTable(t->data.tableVal);

        //avm_memcellclear(&retval);
        retval.type = table_m;
        retval.data.tableVal = newT;
    }
}

//ok
void libfunc_argument()
{
    unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    avm_memcellclear(&retval);

    if (!p_topsp)
    {
        avm_warning("[AVM] -- Warning: 'argument' called outside of function.\n");
        retval.type = nil_m;
    }
    else
    {
        unsigned int totalArgs = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);
        unsigned int totalActuals = avm_totalactuals();

        if (totalActuals != 1)
            avm_error("[AVM] -- Error: 'argument' expects one argument!'\n", totalActuals);
        else
        {
            avm_memcell *selectedArg = avm_getactual(0);

            if (selectedArg->type != number_m || !isInt(selectedArg->data.numVal) || selectedArg->data.numVal < 0 || selectedArg->data.numVal >= totalArgs)
            {
                avm_error("[AVM] -- Error: 'argument' requires int argument\n");
            }
            int off = (int)selectedArg->data.numVal; //2.00

            avm_memcell *arg = &stack[p_topsp + AVM_STACKENV_SIZE + 1 + off];
            retval.type = arg->type;
            if (retval.type == string_m)
            {
                retval.data.strVal = strdup(arg->data.strVal);
            }
            else
            {
                retval.data = arg->data;
            }
        }
    }
}

//ok
void libfunc_strtonum()
{
    unsigned n = avm_totalactuals();
    if (n != 1)
        avm_error("[AVM] -- Error: One argument (not %d) expected in 'strtonum'!\n", n);
    else
    {
        avm_memcellclear(&retval);

        avm_memcell *str = avm_getactual(0);

        if (str->type != string_m) //check if it's a string
        {
            avm_warning("[AVM] -- Warning: The argument provided for strtonum is not a string!\n", n);
            retval.type = nil_m;
            return;
        }

        //avm_memcellclear(&retval);

        if (isNumber(str->data.strVal))
        {
            retval.type = number_m;
            retval.data.numVal = atof(str->data.strVal);
        }
        else
        {
            retval.type = nil_m;
        }
    }
}

//ok
void libfunc_sqrt()
{
    unsigned n = avm_totalactuals();
    if (n != 1)
        avm_error("[AVM] -- Error: one argument (not %d) expected in 'sqrt'!\n", n);
    else
    {
        avm_memcell *number = avm_getactual(0);
        avm_memcellclear(&retval);

        if (number->type != number_m)
        {
            avm_warning("[AVM] -- Warning: The argument provided for sqrt is not a number!\n", n);
            retval.type = nil_m;
            return;
        }
        double x = number->data.numVal;
        //avm_memcellclear(&retval);

        if (x >= 0)
        {
            retval.type = number_m;
            retval.data.numVal = sqrt(x);
        }
        else
        {
            retval.type = nil_m;
        }
    }
}

//ok
void libfunc_cos()
{
    unsigned n = avm_totalactuals();
    if (n != 1)
        avm_error("[AVM] -- Error: one argument (not %d) expected in 'sin'!\n", n);
    else
    {
        avm_memcellclear(&retval);
        avm_memcell *arg = avm_getactual(0);
        if (arg->type != number_m)
        {
            avm_warning("[AVM] -- Warning: The argument provided for cos is not a number!\n");
            retval.type = nil_m;
            return;
        }

        double x = arg->data.numVal;
        //avm_memcellclear(&retval);
        retval.type = number_m;
        double radian = DegreeToRadians(x);
        retval.data.numVal = cos(radian);
    }
}

//ok
void libfunc_sin()
{
    unsigned n = avm_totalactuals();
    if (n != 1)
        avm_error("[AVM] -- Error: One argument (not %d) expected in 'sin'!\n", n);
    else
    {
        avm_memcellclear(&retval);
        avm_memcell *arg = avm_getactual(0);
        if (arg->type != number_m)
        {
            avm_warning("[AVM] -- Warning: The argument provided for sin is not a number!\n", n);
            retval.type = nil_m;
            return;
        }
        double x = arg->data.numVal;
        retval.type = number_m;
        double radian = DegreeToRadians(x);
        retval.data.numVal = sin(radian);
    }
}

//ok
void libfunc_totalarguments()
{
    unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    avm_memcellclear(&retval);

    if (!p_topsp)
    {
        avm_warning("[AVM] -- Warning: 'total arguments' called outside of function.\n");
        retval.type = nil_m;
    }
    else
    {
        retval.type = number_m;
        retval.data.numVal = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);
    }
}

//ok
void libfunc_typeof()
{
    unsigned n = avm_totalactuals();
    if (n != 1)
        avm_error("[AVM] -- Error: one argument (not %d) expected in 'typeof'!\n", n);
    else
    {
        avm_memcellclear(&retval);
        retval.type = string_m;
        retval.data.strVal = strdup(typeStrings[avm_getactual(0)->type]);
    }
}

//ok
void libfunc_print()
{
    unsigned n = avm_totalactuals(), i;
    for (i = 0; i < n; ++i)
    {
        char *s = avm_tostring(avm_getactual(i));
        printf("%s", s);
        free(s);
    }

    printf("\n");
}

void avm_initialize()
{
    avm_initstack();
    avm_registerlibfunc("print", libfunc_print);
    avm_registerlibfunc("typeof", libfunc_typeof);
    avm_registerlibfunc("input", libfunc_input);
    avm_registerlibfunc("objectmemberkeys", libfunc_objectmemberkeys);
    avm_registerlibfunc("objecttotalmembers", libfunc_objecttotalmembers);
    avm_registerlibfunc("objectcopy", libfunc_objectcopy);
    avm_registerlibfunc("totalarguments", libfunc_totalarguments);
    avm_registerlibfunc("argument", libfunc_argument);
    avm_registerlibfunc("strtonum", libfunc_strtonum);
    avm_registerlibfunc("sqrt", libfunc_sqrt);
    avm_registerlibfunc("cos", libfunc_cos);
    avm_registerlibfunc("sin", libfunc_sin);
}

static void avm_initstack()
{
    unsigned i;
    top = AVM_STACKSIZE - 1;

    for (i = 0; i < AVM_STACKSIZE; ++i)
    {
        AVM_WIPEOUT(stack[i]);
        stack[i].type = undef_m;
    }
}

void avm_tableincrefcounter(avm_table *t)
{
    ++(t->refCounter);
}

void avm_tabledecrefcounter(avm_table *t)
{
    if(1){
        return;
    }

    assert(t->refCounter > 0);
    if (!(--(t->refCounter)))
    {
        avm_tabledestroy(t);
    }
}

void avm_tablebucketsinit(avm_table_bucket **p)
{
    unsigned i;
    for (i = 0; i < AVM_TABLE_HASHSIZE; ++i)
        p[i] = (avm_table_bucket *)0;
}

void avm_tablebucketsinit_customSize(avm_table_bucket **p, unsigned size)
{
    unsigned i;
    for (i = 0; i < size; ++i)
        p[i] = (avm_table_bucket *)0;
}

avm_table *avm_tablenew(void)
{
    avm_table *t = (avm_table *)malloc(sizeof(avm_table));

    AVM_WIPEOUT(*t);

    t->refCounter = t->total = 0;
    t->isSimple = 1; //if it has only ints for indexed

    avm_tablebucketsinit(t->numIndexed);
    avm_tablebucketsinit(t->strIndexed);
    avm_tablebucketsinit(t->userfuncIndexed);
    avm_tablebucketsinit(t->libFuncIndexed);
    avm_tablebucketsinit(t->tableIndexed);

    avm_tablebucketsinit_customSize(t->boolIndexed, 2);

    return t;
}

void memclear_string(avm_memcell *m)
{
    assert(m->data.strVal);
    free(m->data.strVal);
}

void memclear_table(avm_memcell *m)
{
    assert(m->data.tableVal);
    avm_tabledecrefcounter(m->data.tableVal);
}

void avm_memcellclear(avm_memcell *m)
{
    if (m->type != undef_m)
    {
        memclear_func_t f = memclearFuncs[m->type];
        if (f)
            (*f)(m);
        m->type = undef_m;
    }
}

void avm_tablebucketsdestroy(avm_table_bucket **p)
{
    unsigned i;
    avm_table_bucket *b;
    for (i = 0; i < AVM_TABLE_HASHSIZE; ++i, ++p)
    {
        for (b = *p; b;)
        {
            avm_table_bucket *del = b;
            b = b->next;
            avm_memcellclear(&del->key);
            avm_memcellclear(&del->value);
            free(del);
        }
        p[i] = (avm_table_bucket *)0;
    }
}

void avm_tablebucketsdestroy_CustomSize(avm_table_bucket **p, unsigned size)
{
    unsigned i;
    avm_table_bucket *b;
    for (i = 0; i < size; ++i, ++p)
    {
        for (b = *p; b;)
        {
            avm_table_bucket *del = b;
            b = b->next;
            avm_memcellclear(&del->key);
            avm_memcellclear(&del->value);
            free(del);
        }
        p[i] = (avm_table_bucket *)0;
    }
}

void avm_tabledestroy(avm_table *t)
{
    avm_tablebucketsdestroy(t->strIndexed);
    avm_tablebucketsdestroy(t->numIndexed);
    avm_tablebucketsdestroy_CustomSize(t->boolIndexed, 2);
    avm_tablebucketsdestroy(t->libFuncIndexed);
    avm_tablebucketsdestroy(t->userfuncIndexed);

    free(t);
}

void decoder(char *filename)
{
    size_t len;
    char *currStr;
    unsigned magicNumber;
    int i;

    FILE *stream;

    stream = fopen(filename, "rb"); // r for read, b for binary
    if (!stream)
    {
        fprintf_red(stderr, "[AVM] -- Could not open the binary file.\n");
        exit(EXIT_FAILURE);
    }

    fread(&magicNumber, sizeof(magicNumber), 1, stream);

    assert(magicNumber == MAGIC_NUMBER);

    fread(&totalNumConsts, sizeof(totalNumConsts), 1, stream);
    numConsts = (double *)malloc(totalNumConsts * sizeof(double));
    for (i = 0; i < totalNumConsts; i++)
    {
        fread(&numConsts[i], sizeof(numConsts[i]), 1, stream); //sizeof(double better?)
        //printf("numConst[%d] = %f\n", i, numConsts[i]);
    }

    fread(&totalStringConsts, sizeof(totalStringConsts), 1, stream);
    stringConsts = (char **)malloc(totalStringConsts * sizeof(char *));
    for (i = 0; i < totalStringConsts; i++)
    {
        fread(&len, sizeof(len), 1, stream); //sizeof(double better?)
        //printf("LEN %lu\n", len);
        currStr = (char *)malloc(sizeof(char) * (len + 1));

        fread(currStr, len, 1, stream);
        currStr[len] = '\0';

        stringConsts[i] = currStr;
        //printf("strConst[%d] = %s\n", i, stringConsts[i]);
    }

    fread(&totalNamedLibfuncs, sizeof(totalNamedLibfuncs), 1, stream);

    namedLibfuncs = (char **)malloc(totalNamedLibfuncs * sizeof(char *));
    for (i = 0; i < totalNamedLibfuncs; i++)
    {
        fread(&len, sizeof(len), 1, stream); //sizeof(double better?)
        currStr = (char *)malloc(sizeof(char) * (len + 1));
        fread(currStr, len, 1, stream);
        currStr[len] = '\0';
        namedLibfuncs[i] = currStr; // strdup(currStr);
    }

    fread(&totalUserFuncs, sizeof(totalUserFuncs), 1, stream);
    userFuncs = (userfunc *)malloc(sizeof(userfunc) * totalUserFuncs);
    for (i = 0; i < totalUserFuncs; i++)
    {
        unsigned address;
        unsigned locals;

        fread(&address, sizeof(address), 1, stream);
        fread(&locals, sizeof(locals), 1, stream);

        fread(&len, sizeof(len), 1, stream);
        currStr = (char *)malloc(sizeof(char) * (len + 1));

        fread(currStr, len, 1, stream);
        currStr[len] = '\0';

        userFuncs[i].address = address;
        userFuncs[i].localSize = locals;
        userFuncs[i].id = currStr;

        //printf("UserFuncs[%d] = (%u %u %s)\n", i, userFuncs[i].address, userFuncs[i].localSize, userFuncs[i].id);
    }

    fread(&codeSize, sizeof(codeSize), 1, stream);
    code = (instruction *)malloc(sizeof(instruction) * codeSize);
    for (i = 0; i < codeSize; i++)
    {
        unsigned opcode;
        unsigned result_type, arg1_type, arg2_type;
        unsigned result_val, arg1_val, arg2_val;
        fread(&opcode, sizeof(opcode), 1, stream);
        fread(&result_type, sizeof(result_type), 1, stream);
        fread(&result_val, sizeof(result_val), 1, stream);
        fread(&arg1_type, sizeof(arg1_type), 1, stream);
        fread(&arg1_val, sizeof(arg1_val), 1, stream);
        fread(&arg2_type, sizeof(arg2_type), 1, stream);
        fread(&arg2_val, sizeof(arg2_val), 1, stream);

        code[i].opcode = opcode;
        code[i].result.type = result_type;
        code[i].result.val = result_val;
        code[i].arg1.type = arg1_type;
        code[i].arg1.val = arg1_val;
        code[i].arg2.type = arg2_type;
        code[i].arg2.val = arg2_val;

        avm_memcell *arg;

        if (code[i].result.type == 1)
        {
            arg = avm_translate_operand(&code[i].result, &ax);
            assert(arg);
            avm_assign(&stack[N - 1 - code[i].result.val], arg);
            if (N - 1 - code[i].result.val <= top)
            {
                avm_dec_top();
            }
        }

        if (code[i].arg1.type == 1)
        {
            arg = avm_translate_operand(&code[i].arg1, &ax);
            assert(arg);
            avm_assign(&stack[N - 1 - code[i].arg1.val], arg);
            if (N - 1 - code[i].arg1.val <= top)
            {
                avm_dec_top();
            }
        }

        if (code[i].arg2.type == 1)
        {
            arg = avm_translate_operand(&code[i].arg2, &ax);
            assert(arg);
            avm_assign(&stack[N - 1 - code[i].arg2.val], arg);
            if (N - 1 - code[i].arg2.val <= top)
            {
                avm_dec_top();
            }
        }
    }

    fclose(stream);
}

void print_log(int printInstr)
{
    int i;
    if (!printInstr)
    {
        return;
    }

    printf("----------- Load Report -----------\n");
    printf("--- Number Consts :%u ---\n", totalNumConsts);
    for (i = 0; i < totalNumConsts; i++)
    {
        printf("str[%d] = %f\n", i, numConsts[i]);
    }

    printf("--- String Consts :%u ---\n", totalStringConsts);
    for (i = 0; i < totalStringConsts; i++)
    {
        printf("str[%d] = %s\n", i, stringConsts[i]);
    }

    printf("--- Lib Funcs :%u ---\n", totalNamedLibfuncs);
    for (i = 0; i < totalNamedLibfuncs; i++)
    {
        printf("lib[%d] = %s\n", i, namedLibfuncs[i]);
    }

    printf("--- User Funcs :%u ---\n", totalUserFuncs);
    for (i = 0; i < totalUserFuncs; i++)
    {
        printf("UserFuncs[%d] = (%u %u %s)\n", i, userFuncs[i].address, userFuncs[i].localSize, userFuncs[i].id);
    }

    printf("--- Instructions :%u ---\n", codeSize);

    char *opcodes[26] = {
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
        "jump",
        "jeq",
        "jne",
        "jle",
        "jge",
        "jlt",
        "jgt",
        "call",
        "pusharg",
        "ret",
        "funcenter",
        "funcexit",
        "newtable",
        "tablegetelem",
        "tablesetelem",
        "nop"};

    char *types[8] = {
        "number",
        "string",
        "bool",
        "table",
        "userfunc",
        "libfunc",
        "nil",
        "undef"};

    for (i = 0; i < codeSize; i++)
    {
        printf("code[%d]: %s [%s %u] [%s %u] [%s %u]\n", i, opcodes[code[i].opcode],
               types[code[i].result.type], code[i].result.val,
               types[code[i].arg1.type], code[i].arg1.val,
               types[code[i].arg2.type], code[i].arg2.val);
    }

    printf("Total globals (including hidden vars) %d\n", (AVM_STACKSIZE - 1) - top);
    printf("Starting TOP value: %d\n", top);

    printf("----------- ----------- -----------\n\n");
}

int main(int argc, char **argv)
{
    int opt, printInstr = 0;
    char *binFile = NULL;

    while ((opt = getopt(argc, argv, "f:ph")) != -1)
    {
        switch (opt)
        {
        case 'f':
            binFile = strdup(optarg);
            break;
        case 'p':
            printInstr = 1;
            break;
        case 'h':
            printf(
                "---- Alpha Virtual Machine ----\n"
                "Usage: ./avm -f alphaBinFile.abc\n"
                "Options:\n"
                "   -f <string>         Specifies the filename of binary file.\n"
                "   -p                  Prints the runtime log.\n"
                "   -h                  Prints this help\n");
            return 0;
        default:
            printf("Run with \"[-h]\" for help.\n");
            exit(EXIT_FAILURE);
        }
    }

    avm_initialize();

    decoder(binFile);

    print_log(printInstr);

    while (!executionFinished)
    {
        execute_cycle();
    }

    free(binFile);
    return 0;
}

unsigned int hashNum(unsigned int x)
{
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x % AVM_TABLE_HASHSIZE;
}

unsigned int hashString(const char *pcKey)
{
    size_t ui;

    unsigned int uiHash = 0U;

    for (ui = 0U; pcKey[ui] != '\0'; ui++)
    {
        uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui];
    }

    return uiHash % AVM_TABLE_HASHSIZE;
}

unsigned int customHashNum(double x)
{
    unsigned long z = abs((int)x);
    return z % AVM_TABLE_HASHSIZE;
}

unsigned char isNumber(char *str)
{
    unsigned int counter = 0;
    unsigned char dotFound = 0;

    while (*(str + counter) != '\0')
    {
        /*- is only allowed in the start*/
        if (isMinus(*(str + counter)))
        {
            if (counter != 0 || !isDigit(*(str + counter + 1)))
            {
                return 0;
            }
        }

        /*Dot for double numbers is allowed inside the string, not in the start or in the end*/
        else if (isDot(*(str + counter)))
        {
            if (!dotFound && counter > 0 && *(str + counter + 1) != '\0')
            {
                dotFound = 1;
            }
            else
            {
                return 0;
            }
        }

        else if (!isDigit(*(str + counter)))
        {
            return 0;
        }

        counter++;
    }

    return 1;
}

unsigned char isDigit(char c)
{
    return (c >= '0' && c <= '9');
}

unsigned char isMinus(char c)
{
    return (c == '-');
}

unsigned char isDot(char c)
{
    return (c == '.');
}

unsigned char isTrue(char *str)
{
    return !(strcmp(str, "true"));
}

unsigned char isFalse(char *str)
{
    return !(strcmp(str, "false"));
}

unsigned char isNil(char *str)
{
    return !(strcmp(str, "nil"));
}

unsigned char isInt(double d)
{
    return (unsigned char)((int)d == d);
}

double DegreeToRadians(double degree)
{
    return degree * (M_PI / 180.0);
}

long hashPtr(void *ptr)
{
    long index = (long)ptr;

    return index % AVM_TABLE_HASHSIZE;
}