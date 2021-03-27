#include "symboltable.h"

int main()
{
    SymbolTable *s;

    s = SymbolTable_init();

    SymbolTable_insert(s, "x", 0, 10, GLOBAL);
    SymbolTable_insert(s, "y", 1, 7, LOCAL);
    SymbolTable_insert(s, "z", 2, 10, LOCAL);
    SymbolTable_insert(s, "my_func", 1, 2, USERFUNC);
    SymbolTable_insert(s, "print", 1, 2, LIBFUNC);
    

    SymbolTable_print(s);
    return 0;
}