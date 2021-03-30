#include "symboltable.h"

int main()
{
    SymbolTable *s;
    ScopeTable *t;
    SymbolTableEntry *entry;

    s = SymbolTable_init();
    t = ScopeTable_init();

    entry = SymbolTable_insert(s, "x", 0, 10, GLOBAL_ID);
    ScopeTable_insert(t, entry, 0);

    entry = SymbolTable_insert(s, "y", 1, 7, LOCAL_ID);
    ScopeTable_insert(t, entry, 1);

    entry = SymbolTable_insert(s, "x", 2, 10, LOCAL_ID);
    ScopeTable_insert(t, entry, 2);
    
    entry = SymbolTable_insert(s, "my_func", 1, 2, USERFUNC_ID);
    ScopeTable_insert(t, entry, 1);
    
    entry = SymbolTable_insert(s, "print", 1, 2, LIBFUNC_ID);
    ScopeTable_insert(t, entry, 1);
    
    //SymbolTable_hide(s, "my_func", 1);
    ScopeTable_hide_scope(t, 1);
    SymbolTable_print(s);
    ScopeTable_print(t);
    
    return 0;
}