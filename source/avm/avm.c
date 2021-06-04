#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#include "avm.h"
#include "../utils/utils.h"

#define MAGIC_NUMBER 12345678
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

avm_memcell ax, bx, cx;
avm_memcell retval;

unsigned top, topsp;
unsigned char executionFinished = 0;
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

typedef void (*execute_func_t)(instruction *);
typedef void (*library_func_t)();
typedef char *(*tostring_func_t)(avm_memcell *);

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
/* ---------------------- ------- ---------------------- */

/* ---------------------- AVM Functions ---------------------- */
avm_memcell *avm_translate_operand(vmarg *arg, avm_memcell *reg);
avm_memcell *avm_getactual(unsigned i);
avm_memcell *avm_tablegetelem(avm_table *table, avm_memcell *index);
userfunc *avm_getfuncinfo(unsigned address);
library_func_t avm_getlibraryfunc(char *id);
avm_table *avm_tablenew(void);
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
void avm_memcellclear(avm_memcell *m);
void avm_tablebucketsdestroy(avm_table_bucket **p);
void avm_tabledestroy(avm_table *t);
void avm_calllibfunc(char *id);
char *avm_tostring(avm_memcell *);
unsigned avm_get_envvalue(unsigned i);
unsigned avm_totalactuals();
unsigned char avm_tobool(avm_memcell *m);
/* ---------------------- ------- ---------------------- */

void execute_cycle(void);

double consts_getnumber(unsigned index);
char *consts_getstring(unsigned index);
char *libfuncs_getused(unsigned index);

char *number_tostring(avm_memcell *);
char *string_tostring(avm_memcell *);
char *bool_tostring(avm_memcell *);
char *table_tostring(avm_memcell *);
char *userfunc_tostring(avm_memcell *);
char *nil_tostring(avm_memcell *);
char *undef_tostring(avm_memcell *);

tostring_func_t tostringFuncs[] = {
    number_tostring,
    string_tostring,
    bool_tostring,
    table_tostring,
    userfunc_tostring,
    nil_tostring,
    undef_tostring};

#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic

typedef double (*arithmetic_func_t)(double x, double y);

double add_impl(double x, double y);
double sub_impl(double x, double y);
double mul_impl(double x, double y);
double div_impl(double x, double y);
double mod_impl(double x, double y);

arithmetic_func_t arithmeticFuncs[] = {
    add_impl,
    sub_impl,
    mul_impl,
    div_impl,
    mod_impl};

void execute_arithmetic(instruction *instr);
typedef unsigned char (*tobool_func_t)(avm_memcell *);
unsigned char number_tobool(avm_memcell *m);
unsigned char string_tobool(avm_memcell *m);
unsigned char bool_tobool(avm_memcell *m);
unsigned char table_tobool(avm_memcell *m);
unsigned char userfunc_tobool(avm_memcell *m);
unsigned char libfunc_tobool(avm_memcell *m);
unsigned char nil_tobool(avm_memcell *m);
unsigned char undef_tobool(avm_memcell *m);

tobool_func_t toboolFuncs[] = {
    number_tobool,
    string_tobool,
    bool_tobool,
    table_tobool,
    userfunc_tobool,
    libfunc_tobool,
    nil_tobool,
    undef_tobool};

char *typeStrings[8] = {
    "number",
    "string",
    "bool",
    "table",
    "userfunc",
    "libfunc",
    "nil",
    "undef"};

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
/* ---------------------- ------- ---------------------- */

void memclear_string(avm_memcell *m);
void memclear_table(avm_memcell *m);

void decoder(char *filename); //decodes the binary file created by compiler

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
    execute_funcenter,
    execute_funcexit,
    execute_newtable,
    execute_tablegetelem,
    execute_tablesetelem,
    execute_nop};

typedef struct libFuncPair
{
    char *id;
    library_func_t addr;
    struct libFuncPair *next;
}libFuncPair;

libFuncPair *libFuncPairs = NULL;

/* ---------------------- Code ---------------------- */
avm_memcell *avm_translate_operand(vmarg *arg, avm_memcell *reg)
{
    switch (arg->type)
    {
    case global_a:
        return &stack[AVM_STACKENV_SIZE - 1 - arg->val];
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
        (*executeFuncs[instr->opcode])(instr);
        if (pc == oldPC)
            pc++;
    }
}

void execute_assign(instruction *instr)
{
    avm_memcell *lv = avm_translate_operand(&instr->result, (avm_memcell *)0);
    avm_memcell *rv = avm_translate_operand(&instr->arg1, &ax);

    assert(lv && (&stack[N - 1] >= lv && lv > &stack[top] || lv == &retval));
    assert(rv); //!!!!!!!

    avm_assign(lv, rv);
}

void avm_assign(avm_memcell *lv, avm_memcell *rv)
{
    if (lv == rv)
        return;

    if (lv->type == table_m && rv->type == table_m && lv->data.tableVal == rv->data.tableVal)
        return;

    if (rv->type == undef_m)
        avm_warning("assigning from 'undef' content!");

    avm_memcellclear(lv);
    memcpy(lv, rv, sizeof(avm_memcell));

    if (lv->type == string_m)
        lv->data.strVal = strdup(rv->data.strVal);
    else if (lv->type == table_m)
        avm_tableincrefcounter(lv->data.tableVal);
}

void execute_call(instruction *instr)
{
    avm_memcell *func = avm_translate_operand(&instr->result, &ax);
    assert(func);
    avm_callsaveenvironment();
    switch (func->type)
    {
    case userfunc_m:
    {
        pc = func->data.funcVal;
        assert(pc < AVM_ENDING_PC);
        assert(code[pc].opcode == funcenter_v);
        break;
    }
    case string_m:
        avm_calllibfunc((func->data).strVal);
        break;
    case libfunc_m:
        avm_calllibfunc((func->data).libfuncVal);
        break;
    default:
    {
        char *s = avm_tostring(func);
        avm_error("call: cannot bind '%s' to function!", s);
        free(s);
        executionFinished = 1;
    }
    }
}

void avm_dec_top()
{
    if (!top)
    {
        avm_error("stack overflow");
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
    avm_memcell *func = avm_translate_operand(&instr->result, &ax);
    assert(func);
    assert(pc == func->data.funcVal);

    totalActuals = 0;
    userfunc *funcInfo = avm_getfuncinfo(pc);

    topsp = top;
    top = top - funcInfo->localSize;
}

unsigned avm_get_envvalue(unsigned i)
{
    assert(stack[i].type = number_m);
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
        avm_memcellclear(&stack[oldTop]);
}

void avm_calllibfunc(char *id)
{
    library_func_t f = avm_getlibraryfunc(id);
    if (!f)
    {
        avm_error("unsupported lib func '%s' called!", id);
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
    //check runtime errors
    avm_memcell *lv = avm_translate_operand(&instr->result, (avm_memcell *)0);
    avm_memcell *rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell *rv2 = avm_translate_operand(&instr->arg2, &bx);
    assert(lv && (&stack[N - 1] >= lv && lv > &stack[top] || lv == &retval));
    assert(rv1 && rv2);

    if (rv1->type != number_m || rv2->type != number_m)
    {
        avm_error("not a number in arithmetic!");
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

typedef unsigned char (*tobool_func_t)(avm_memcell *);

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
        avm_error("'undef involved in equality!");
    else if (rv1->type == nil_m || rv2->type == nil_m)
        result = rv1->type == nil_m && rv2->type == nil_m;
    else if (rv1->type = bool_m || rv2->type == bool_m)
        result = (avm_tobool(rv1) == avm_tobool(rv2));
    else if (rv1->type != rv2->type)
        avm_error("%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
    else
    {
        //eq chech with disp
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
        avm_error("illegal use of type %s as table!", typeStrings[t->type]);
    }
    else
    {
        avm_memcell *content = avm_tablegetelem(t->data.tableVal, i);
        if (content)
            avm_assign(lv, content);
        else
        {
            char *ts = avm_tostring(t);
            char *is = avm_tostring(i);
            avm_warning("%s[%s] not found!", ts, ts);
            free(ts);
            free(is);
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
        avm_error("illegal use of type %s as table!", typeStrings[t->type]);
    else
        avm_tablesetelem(t->data.tableVal, i, c);
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

//TODO: Implementations of these. We drop them here only for the compile
//Mallon thelei allo edw !!!!!!!!!!!!!!
userfunc *avm_getfuncinfo(unsigned address)
{
    return &userFuncs[address];
}

void execute_uminus(instruction *instr) {}

void execute_and(instruction *instr) {}

void execute_or(instruction *instr) {}

void execute_not(instruction *instr) {}

void execute_jump(instruction *instr) {}

void execute_jne(instruction *instr) {}

void execute_jle(instruction *instr) {}

void execute_jge(instruction *instr) {}

void execute_jlt(instruction *instr) {}

void execute_jgt(instruction *instr) {}

void execute_nop(instruction *instr) {}

char *number_tostring(avm_memcell *m)
{
    return "";
}

char *string_tostring(avm_memcell *m)
{
    return "";
}

char *bool_tostring(avm_memcell *m)
{
    return "";
}

char *table_tostring(avm_memcell *m)
{
    return "";
}

char *userfunc_tostring(avm_memcell *m)
{
    return "";
}

char *nil_tostring(avm_memcell *m)
{
    return "";
}

char *undef_tostring(avm_memcell *m)
{
    return "";
}

void avm_registerlibfunc(char *id, library_func_t addr)
{
    libFuncPair *pair = NULL;
    
    pair = (libFuncPair *)malloc(sizeof(libFuncPair));
    if(!pair){
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

    while(curr){
        if(!strcmp(curr->id,id)){
            return curr->addr;
        }
        curr = curr->next;
    }
    
    return NULL;
}

avm_memcell *avm_tablegetelem(avm_table *table, avm_memcell *index)
{
    avm_memcell *m;
    return m;
}

void avm_tablesetelem(avm_table *table, avm_memcell *index, avm_memcell *content)
{
    assert(table);
    switch (index->type)
    {
    case string_m:
        break;
    case number_m:
        break;
    }
}

//TODO: Lib funcs implementation
void libfunc_input() {}
void libfunc_objectmemberkeys() {}
void libfunc_objecttotalmembers() {}
void libfunc_objectcopy() {}
void libfunc_argument() {}
void libfunc_strtonum() {}
void libfunc_sqrt() {}
void libfunc_cos() {}
void libfunc_sin() {}

void libfunc_totalarguments(void)
{
    unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
    avm_memcellclear(&retval);

    if (p_topsp)
    {
        avm_error("'total arguments' called outside function");
        retval.type = nil_m;
    }
    else
    {
        retval.type = number_m;
        retval.data.numVal = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);
    }
}

void libfunc_typeof()
{
    unsigned n = avm_totalactuals();
    if (n != 1)
        avm_error("one argument (not %d) expected in 'typeof'!", n);
    else
    {
        avm_memcellclear(&retval);
        retval.type = string_m;
        retval.data.strVal = strdup(typeStrings[avm_getactual(0)->type]);
    }
}

void libfunc_print()
{
    unsigned n = avm_totalactuals();
    for (unsigned i = 0; i < n; ++i)
    {
        char *s = avm_tostring(avm_getactual(i));
        puts(s);
        free(s);
    }
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
    for (unsigned i = 0; i < AVM_STACKSIZE; ++i)
    {
        AVM_WIPEOUT(stack[i]);
        stack[i].type = undef_m;
    }
}

void avm_tableincrefcounter(avm_table *t)
{
    ++t->refCounter;
}

void avm_tabledecrefcounter(avm_table *t)
{
    assert(t->refCounter > 0);
    if (!--t->refCounter) //if(refCount == 0) { free table }
        avm_tabledestroy(t);
}

void avm_tablebucketsinit(avm_table_bucket **p)
{
    for (unsigned i = 0; i < AVM_TABLE_HASHSIZE; ++i)
        p[i] = (avm_table_bucket *)0;
}

avm_table *avm_tablenew(void)
{
    avm_table *t = (avm_table *)malloc(sizeof(avm_table));

    AVM_WIPEOUT(*t);

    t->refCounter = t->total = 0;

    avm_tablebucketsinit(t->numIndexed);
    avm_tablebucketsinit(t->strIndexed);
    avm_tablebucketsinit(t->userfuncIndexed);
    avm_tablebucketsinit(t->libFuncIndexed);
    avm_tablebucketsinit(t->boolIndexed);

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
    for (unsigned i = 0; i < AVM_TABLE_HASHSIZE; ++i, ++p)
    {
        for (avm_table_bucket *b = *p; b;)
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
    avm_tablebucketsdestroy(t->boolIndexed);
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

    //read magic number
    fread(&magicNumber, sizeof(magicNumber), 1, stream);
    printf("Magic number :%u\n", magicNumber);

    assert(magicNumber == MAGIC_NUMBER);

    //read numbers
    fread(&totalNumConsts, sizeof(totalNumConsts), 1, stream);
    printf("Total Number Consts :%u\n", totalNumConsts);
    numConsts = (double *)malloc(totalNumConsts * sizeof(double));
    for (i = 0; i < totalNumConsts; i++)
    {
        fread(&numConsts[i], sizeof(numConsts[i]), 1, stream); //sizeof(double better?)
        printf("numConst[%d] = %f\n", i, numConsts[i]);
    }

    //read strings
    fread(&totalStringConsts, sizeof(totalStringConsts), 1, stream);
    printf("Total String Consts :%u\n", totalStringConsts);
    stringConsts = (char **)malloc(totalStringConsts * sizeof(char *));
    for (i = 0; i < totalStringConsts; i++)
    {
        fread(&len, sizeof(len), 1, stream); //sizeof(double better?)
        printf("LEN %lu\n", len);
        currStr = (char *)malloc(sizeof(char) * (len + 1));

        fread(currStr, len, 1, stream);
        currStr[len] = '\0';

        stringConsts[i] = currStr;
        printf("strConst[%d] = %s\n", i, stringConsts[i]);
    }

    //read lib funcs
    fread(&totalNamedLibfuncs, sizeof(totalNamedLibfuncs), 1, stream);
    printf("Total Lib Funcs :%u\n", totalNamedLibfuncs);

    namedLibfuncs = (char **)malloc(sizeof(totalNamedLibfuncs * sizeof(char *)));
    for (i = 0; i < totalNamedLibfuncs; i++)
    {
        fread(&len, sizeof(len), 1, stream); //sizeof(double better?)
        currStr = (char *)malloc(sizeof(char) * (len + 1));

        fread(currStr, len, 1, stream);
        currStr[len] = '\0';

        namedLibfuncs[i] = currStr;

        printf("LibFuncs[%d] = %s\n", i, namedLibfuncs[i]);
    }

    //read user funcs
    fread(&totalUserFuncs, sizeof(totalUserFuncs), 1, stream);
    printf("Total User Funcs :%u\n", totalUserFuncs);
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

        printf("UserFuncs[%d] = (%u %u %s)\n", i, userFuncs[i].address, userFuncs[i].localSize, userFuncs[i].id);
    }

    //read instructions
    fread(&codeSize, sizeof(codeSize), 1, stream);
    printf("Total Instructions :%u\n", codeSize);
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

        printf("Opcode: %u\n", code[i].opcode);
        printf("Result type:  %u\n", code[i].result.type);
        printf("Result val:  %u\n", code[i].result.val);
        printf("Argument 1 type:  %u\n", code[i].arg1.type);
        printf("Argument 1 val:  %u\n", code[i].arg1.val);
        printf("Argument 2 type:  %u\n", code[i].arg2.type);
        printf("Argument 2 val:  %u\n", code[i].arg2.val);
    }

    fclose(stream);
}

int main(int argc, char **argv)
{
    int opt;
    char *binFile = NULL;

    while ((opt = getopt(argc, argv, "f:h")) != -1)
    {
        switch (opt)
        {
        case 'f':
            binFile = strdup(optarg);
            break;
        case 'h':
            printf(
                "---- Alpha Virtual Machine ----\n"
                "Usage: ./avm -f alphaBinFile.abc\n"
                "Options:\n"
                "   -f <string>         Specifies the filename of binary file.\n"
                "   -h                  Prints this help\n");
            return 0;
        default:
            printf("Run with \"[-h]\" for help.\n");
            exit(EXIT_FAILURE);
        }
    }

    decoder(binFile);

    avm_initialize();

    while (!executionFinished)
    {
        execute_cycle();
    }

    free(binFile);
    return 0;
}