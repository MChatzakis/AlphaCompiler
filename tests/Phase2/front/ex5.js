//DONE
x; //new global var x 
print(::x); //ok, x found 
print(::y); //error: no y 
function f() { return ::x;} //ok 
{ print(::f()); } //ok, f found 