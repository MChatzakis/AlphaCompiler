//DONE
function f() {} 
local f; //ok, found locally 
local print; //ok, found in scope 0 
local x; //new global var in scope 0 
{ 
 local f; //new local var in scope 1 
 local print; //error: trying to 
 //shadow libfunc 
} 
function g(a, b) { local a = local b; } 