#include "symboltable.h"

int main()
{
    SymbolTable *s;

    s = SymbolTable_init();

    SymbolTable_insert(s, "x", 0, 10, GLOBAL_ID);
    SymbolTable_insert(s, "y", 1, 7, LOCAL_ID);
    SymbolTable_insert(s, "x", 2, 10, LOCAL_ID);
    SymbolTable_insert(s, "my_func", 1, 2, USERFUNC_ID);
    SymbolTable_insert(s, "print", 1, 2, LIBFUNC_ID);
    
    //SymbolTable_hide(s, "my_func", 1);

    SymbolTable_print(s);
    return 0;
}