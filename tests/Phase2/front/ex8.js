//DONE
function f(x, y, z) {} //ok, f with formals x, y, z
function g(x, y, x) {} //error: formal redeclaration 
function h(x, cos) {} //error: formal shadows libfunc 