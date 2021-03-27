#include "symbol_table.h"

int main()
{
    symboltable_t *s;

    s = symboltable_init();

    symboltable_insert(s, "x", 0, 10, GLOBAL);
    symboltable_insert(s, "y", 1, 7, LOCAL);
    symboltable_insert(s, "z", 2, 10, LOCAL);

    symboltable_print(s);
    return 0;
}